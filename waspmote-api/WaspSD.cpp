/*
 *  Copyright (C) 2018 Libelium Comunicaciones Distribuidas S.L.
 *  http://www.libelium.com
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 2.1 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.

 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Version:		3.2
 *  Design:			David Gascón
 *  Implementation:	David Cuartielles, Alberto Bielsa, Yuri Carmona
 */


#ifndef __WPROGRAM_H__
  #include "WaspClasses.h"
#endif



/// table_SD ///////////////////////////////////////////////////////////////////

const char sd_string_00[] 	PROGMEM	= "\nmanuf:  0x%x\noem:    %c%c\nprod:   %x\nrev:    %x.%x\nserial: 0x%lx\ndate:   %u/%u\n";
const char sd_string_01[] 	PROGMEM	= "no SD";


const char* const table_SD[] PROGMEM =
{
	sd_string_00, 		// 0
	sd_string_01, 		// 1
};




/*******************************************************************************
 * Functions
*******************************************************************************/

/*
 * User provided date time callback function.
 * See SdFile::dateTimeCallback() for usage.
 */
void dateTime(uint16_t* date, uint16_t* time)
{
  // User gets date and time from GPS or real-time
  // clock in real callback function
  // return date using FAT_DATE macro to format fields
  *date = FAT_DATE(RTC.year+2000, RTC.month, RTC.date);

  // return time using FAT_TIME macro to format fields
  *time = FAT_TIME(RTC.hour, RTC.minute, RTC.second);
}



/*  getNextPathComponent ( path, *p_offset, *buffer) - Parse individual
 * path components from a path.
 *
 * e.g. after repeated calls '/foo/bar/baz' will be split
 *         into 'foo', 'bar', 'baz'.
 * This is similar to `strtok()` but copies the component into the
 * supplied buffer rather than modifying the original string.
 *
 *
 * `buffer` needs to be PATH_COMPONENT_BUFFER_LEN in size.
 *
 * `p_offset` needs to point to an integer of the offset at
 *  which the previous path component finished.
 *
 * Returns `true` if more components remain.
 *
 * Returns `false` if this is the last component.
 *    (This means path ended with 'foo' or 'foo/'.)
 */
bool getNextPathComponent(	char *path,
							unsigned int *p_offset,
							char *buffer)
{

  // TODO: Have buffer local to this function, so we know it's the
  //       correct length?

  int bufferOffset = 0;

  int offset = *p_offset;

  // Skip root or other separator
  if (path[offset] == '/') {
    offset++;
  }

  // Copy the next next path segment
  while (bufferOffset < MAX_COMPONENT_LEN
	 && (path[offset] != '/')
	 && (path[offset] != '\0')) {
    buffer[bufferOffset++] = path[offset++];
  }

  buffer[bufferOffset] = '\0';

  // Skip trailing separator so we can determine if this
  // is the last component in the path or not.
  if (path[offset] == '/') {
    offset++;
  }

  *p_offset = offset;

  return (path[offset] != '\0');
}


/*
 * When given a file path (and parent directory--normally root),
 * this function traverses the directories in the path and at each
 * level calls the supplied callback function while also providing
 * the supplied object for context if required.
 *
 * 		e.g. given the path '/foo/bar/baz'
 * 			the callback would be called at the equivalent of
 * 		'/foo', '/foo/bar' and '/foo/bar/baz'.
 *
 * The implementation swaps between two different directory/file
 * handles as it traverses the directories and does not use recursion
 * in an attempt to use memory efficiently.
 *
 * If a callback wishes to stop the directory traversal it should
 * return false--in this case the function will stop the traversal,
 * tidy up and return false.
 *
 * If a directory path doesn't exist at some point this function will
 * also return false and not subsequently call the callback.
 * If a directory path specified is complete, valid and the callback
 * did not indicate the traversal should be interrupted then this
 * function will return true.
 */
boolean walkPath(	char *filepath,
					SdFile& parentDir,
					boolean (*callback)(	SdFile& parentDir,
											char *filePathComponent,
											boolean isLastComponent,
											void *object),
					void *object=NULL)
{

	SdFile subfile1;
	SdFile subfile2;

	char buffer[PATH_COMPONENT_BUFFER_LEN];

	unsigned int offset = 0;

	SdFile *p_parent;
	SdFile *p_child;

	SdFile *p_tmp_sdfile;

	p_child = &subfile1;

	p_parent = &parentDir;

	while (true)
	{
		boolean moreComponents = getNextPathComponent(filepath, &offset, buffer);
		boolean shouldContinue = callback((*p_parent), buffer, !moreComponents, object);

		if (!shouldContinue)
		{
			// TODO: Don't repeat this code?
			// If it's one we've created then we
			// don't need the parent handle anymore.
			if (p_parent != &parentDir)
			{
				(*p_parent).close();
			}
			return false;
		}

		if (!moreComponents)
		{
			break;
		}

		boolean exists = (*p_child).open(p_parent, buffer, O_RDONLY);

		// If it's one we've created then we
		// don't need the parent handle anymore.
		if (p_parent != &parentDir)
		{
			(*p_parent).close();
		}

		// Handle case when it doesn't exist and we can't continue...
		if (exists)
		{
			// We alternate between two file handles as we go down
			// the path.
			if (p_parent == &parentDir)
			{
				p_parent = &subfile2;
			}

			p_tmp_sdfile = p_parent;
			p_parent = p_child;
			p_child = p_tmp_sdfile;
		}
		else
		{
			return false;
		}
	}

	if (p_parent != &parentDir)
	{
		(*p_parent).close(); // TODO: Return/ handle different?
	}

	return true;
}



/*******************************************************************************

   The callbacks used to implement various functionality follow.

   Each callback is supplied with a parent directory handle,
   character string with the name of the current file path component,
   a flag indicating if this component is the last in the path and
   a pointer to an arbitrary object used for context.

*******************************************************************************/


/*
 *  Callback used to determine if a file/directory exists in parent
 *  directory.
 *
 *  Returns true if file path exists
 */
boolean callback_pathExists(	SdFile& parentDir,
								char *filePathComponent,
								boolean isLastComponent,
								void *object)
{

  SdFile child;

  boolean exists = child.open(&parentDir, filePathComponent, O_RDONLY);

  if (exists) {
     child.close();
  }

  return exists;
}


/*
 * Callback used to create a directory in the parent directory if
 * it does not already exist.
 *
 * Returns true if a directory was created or it already existed.
 */
boolean callback_makeDirPath(	SdFile& parentDir,
								char *filePathComponent,
								boolean isLastComponent,
								void *object)
{

	boolean result = false;
	SdFile child;

	result = callback_pathExists(parentDir, filePathComponent, isLastComponent, object);
	if (!result) {
		result = child.makeDir(&parentDir, filePathComponent);
	}

	return result;
}



/*
 * Callback used to delete a file specified by a path that may
 * specify one or more directories above it.
 */
boolean callback_remove(	SdFile& parentDir,
							char *filePathComponent,
							boolean isLastComponent,
							void *object)
{
	if (isLastComponent) {
		return SdFile::remove(&parentDir, filePathComponent);
	}
	return true;
}


/*
 * Callback used to delete a directory specified by a path that may
 * specify one or more directories above it.
 */
boolean callback_rmdir(	SdFile& parentDir,
						char *filePathComponent,
						boolean isLastComponent,
						void *object)
{
	if (isLastComponent) {
		SdFile f;
		if (!f.open(&parentDir, filePathComponent, O_READ)) return false;
		return f.rmDir();
	}
	return true;
}



/*
 * Callback used to delete a directory specified by a path and all
 * contained files.
 */
boolean callback_rmRfdir(	SdFile& parentDir,
						char *filePathComponent,
						boolean isLastComponent,
						void *object)
{
	if (isLastComponent)
	{
		SdFile f;
		if (!f.open(&parentDir, filePathComponent, O_READ))
		{
			// delete possible "damaged" file
			SdFile::remove(&parentDir, filePathComponent);
			return false;
		}
		// remove all contents and directory
		if(!f.rmRfStar())
		{
			// in the case it fails
			// delete possible "damaged" file
			if(!f.remove())
			{
				return false;
			}
		}
	}
	return true;
}



/*******************************************************************************
 * Class methods
*******************************************************************************/

/// Constructors ///////////////////////////////////////////////////////

WaspSD::WaspSD()
{
    // init SD flag
    flag = 0;
}

/// Public Methods /////////////////////////////////////////////////////

/*
 * ON (void) - It powers the SD card, initialize it and prepare it to
 * work with
 *
 *  It powers the SD card, initialize it and prepare it to work with
 */
uint8_t WaspSD::ON(void)
{
	// enable Chip select
	pinMode(SD_SS, OUTPUT);
	digitalWrite(SD_SS, LOW);

	// update Waspmote Control Register
	WaspRegister |= REG_SD;

	// mandatory delay
	delay(100);

	// configure pins as input/output
	pinMode(MEM_PW, OUTPUT);
	pinMode(SD_PRESENT, INPUT);

	// enable SD SPI flag
	SPI.isSD = true;

	// set power supply to the SD card
	setMode(SD_ON);

	// initialize FAT volume
	return init();
}


/*
 * OFF (void) - It powers off the SD card and closes the pointers
 *
 *  It powers off the SD card and closes the pointers
 */
void WaspSD::OFF(void)
{
	// delay for waiting pending operations
	delay(100);

	// disable SD SPI flag
	SPI.isSD = false;

	// close current working directory if it is not the root directory
	if(!currentDir.isRoot())
	{
		currentDir.close();
	}

	// close root directory
	root.close();

	// SD_SS (SD chip select) is disabled
  	pinMode(SD_SS, OUTPUT);
	digitalWrite(SD_SS, HIGH);

	// close SPI bus if it is posible
	SPI.close();

  	// switch SD off
	setMode(SD_OFF);
	delay(100);

	// update Waspmote Control Register
	WaspRegister &= ~(REG_SD);
}


/* setMode() - sets energy mode
 *
 * It sets SD ON/OFF, switching On or Off the corresponding pin
 * 'mode': Selects between SD_ON/SD_OFF
 */
void WaspSD::setMode(uint8_t mode)
{
	switch(mode)
	{
		case SD_ON: digitalWrite(MEM_PW, HIGH);
					delay(10);
					break;

		case SD_OFF:digitalWrite(MEM_PW,LOW);
					break;
	}
}



/* init ( void ) - initializes the use of SD cards, looks into the
 * root partition, opens the file system and initializes the
 * public pointer that can be used to access the filesystem
 *
 * Returns 1 when ok;
 * Returns 0 when error.
 * Also, there is a flag with the corresponding value of error:
 *
 * - NOTHING_FAILED = 0
 * - CARD_NOT_PRESENT = 1
 * - INIT_FAILED = 2
 * - VOLUME_FAILED = 3
 * - ROOT_FAILED = 4
 *
 */
uint8_t WaspSD::init()
{
	// check if the card is there or not
	if (!isSD())
	{
		flag = CARD_NOT_PRESENT;
		return 0;
	}

	// init SPI bus
	if(!card.init(SPI_FULL_SPEED))
	{
		flag = INIT_FAILED;
		return 0;
	}

	// initialize a FAT volume
	if(!volume.init(&card))
	{
		flag = INIT_FAILED;
		return 0;
	}

	// open the root directory
	if(!root.openRoot(&volume))
	{
		flag = ROOT_FAILED;
		return 0;
	}
	// Update current working directory to 'root' directory
	memcpy(&currentDir, &root, sizeof(SdFile));

	// update flag with no error
	flag = NOTHING_FAILED;

	return 1;
}



/*
 * isSD (void) - Is the SD inside the slot?
 *
 * This function checks if there is a SD card in the slot
 *
 * Here we make a call to close(), to avoid errors if users
 * tried to call any functions making use of the card
 *
 * Returns 1 if SD card is present, 0 otherwise
 */
uint8_t WaspSD::isSD()
{
	if(digitalRead(SD_PRESENT)) return 1;

	return 0;
}


/*
 * getDiskSize (void) - disk total size
 *
 * Returns the total size for the disk, but also updates the
 * SD.diskSize variable.
 * Returns 0 when error
 */
uint32_t WaspSD::getDiskSize()
{
	// check if the card is there or not
    if (!isSD())
    {
        flag = CARD_NOT_PRESENT;
        return 0;
    }

	// update the attribute 'diskSize' in bytes
    diskSize = 512*card.cardSize();
    return diskSize;
}


/*
 * print_disk_info (void) - disk information
 *
 * packs all the data about the disk into the buffer and returns it back.
 * The SD.buffer will then be available and offer the data to the
 * developers as a human-readable encoded string.
 *
 * An example of the output by this system would be:
 *
 * manuf:  0x2
 * oem:    TM
 * prod:   SD01G
 * rev:    32
 * serial: 0x9f70db88
 * date:   2/8
 *
 * Not all the information is relevant for further use. It is possible
 * to access different parts via the fat-implemented variables as you
 * will see in this function
 *
 */
char* WaspSD::print_disk_info()
{
	char aux[100];

	// Local variable
	cid_t cid;

	// check if the card is there or not
    if (!isSD())
    {
        flag = CARD_NOT_PRESENT;
		// aux <-- "no SD"
		strcpy_P(aux,  (char*)pgm_read_word(&(table_SD[1])));
        sprintf(buffer, aux);
		return buffer;
    }

    // Read  CID register
    card.readCID(&cid);

 	// aux <--
	strcpy_P(aux,  (char*)pgm_read_word(&(table_SD[0])));

	//Compose buffer to return
    snprintf(buffer
		, sizeof(buffer)
		, aux
		, cid.mid
		, cid.oid[0]
		, cid.oid[1]
		, cid.pnm
		, cid.prv_n
		, cid.prv_m
		, cid.psn
		, (int)cid.mdt_month
		, (int)cid.mdt_year_low);

	USB.println(buffer);

    return buffer;
}

/*
 * mkdir ( filepath ) - create directory/ies indicated by filepath
 *
 * Returns 1 on directory creation, 0 if error, will mark the flag with
 * DIR_CREATION_ERROR
 *
 * Be careful when calling this function to create a directory for the
 * first time. If it is interrupted, the directory results damaged and
 * it is necessary to delete it as a regular file using SD.del
 *
 * Remarks only short 8.3 names are valid!
 */
boolean WaspSD::mkdir(char *filepath)
{
	// set date for directory creation
	setFileDate();

	// check if the card is there or not
	if (!isSD())
	{
		flag = CARD_NOT_PRESENT;
		flag |= DIR_CREATION_ERROR;
		snprintf(buffer, sizeof(buffer), "%s", CARD_NOT_PRESENT_em);
		return false;
	}

	// check if directory already exists
	if(walkPath(filepath, currentDir, callback_pathExists, NULL))
	{
		flag |= DIR_CREATION_ERROR;
		return false;
	}

	// Makes a single directory or a hierarchy of directories.
	// A rough equivalent to `mkdir -p`. */
	return walkPath(filepath, currentDir, callback_makeDirPath, NULL);
}



/*
 * ls ( void ) - directory listing
 *
 * Lists the directory contents
 *
 * The information is printed through the serial port (UART0). This way,
 * the info can be seen in Waspmote IDE's serial port.
 * A possible example is:
 *
 * empty.txt	2945
 * secret/
 * hello.txt	1149
 *
 * Files are shown with their extention. The file size is shown in bytes.
 * Folders have a slash as the last character.
 *
 */
void WaspSD::ls(void)
{
  return currentDir.ls(LS_SIZE, 0);
}


/*
 * ls (flags) - directory listing
 *
 * Lists the directory contents
 *
 * The information is printed through the serial port (UART0). This way,
 * the info can be seen in Waspmote IDE's serial port.
 * A possible example is:
 *
 * 	FILE8         1980-01-01 00:00:00 204
 * 	FILE2         1980-01-01 00:00:00 2754
 * 	FOLDER/       2000-01-01 01:00:00
 * 	   SUBFOLD/      2000-01-01 01:00:00
 * 	FILE.TXT      2012-06-11 11:58:10 811
 *
 * parameter 'flags' is the inclusive OR of
 *
 * LS_DATE - Print file modification date
 * LS_SIZE - Print file size.
 * LS_R - Recursive list of subdirectories.
 *
 * Files are shown with their extention. The file size is shown in bytes.
 * Folders have a slash as the last character.
 *
 */
void WaspSD::ls(uint8_t flags)
{
  return currentDir.ls(flags, 0);
}

/*
 * find_file_in_dir (filepath) - tests existence of a specific
 * file in the current working directory
 *
 * Returns If the file is available in the folder, it will answer 1
 * (TRUE), if not available it will answer 0 (FALSE)
 *
 */
uint8_t WaspSD::find_file_in_dir(const char* filepath)
{
	// Check if path exists
	if(walkPath((char*)filepath, currentDir, callback_pathExists, NULL)) return 1;
	else return 0;
}

/*
 * isFile (filepath) - checks if 'filepath' is a file or not
 *
 * Answers whether the file "filepath" is available in the current
 * working directory or not.
 *
 * If the file is available in the folder, it will answer 1 (TRUE),
 * if it is not a file it will answer 0 (FALSE), and if it is not
 * available it will answer -1 (ERROR)
 *
 */
int8_t WaspSD::isFile(const char* filepath)
{
	// Local variable
	SdFile file;

	// try to open the file
	if(!openFile( (char*)filepath, &file, O_RDONLY)) return -1;
	else
	{
		// File opened. Check if it is a valid file
		if (!file.isFile())
		{
			file.close();
			return 0;
		}
		else file.close();
	}
    return 1;
}


/*
 * getParentDir(filepath, index) - gets parent directory of a filepath
 *
 * This function is a little helper used to traverse paths.
 * Answers the object SdFile which is related to the parent directory
 * of a path specified in 'filepath'
 *
 * If the file is available in the folder, it will answer 1 (TRUE),
 * if it is not a file it will answer 0 (FALSE), and if it is not
 * available it will answer -1 (ERROR)
 *
 */
SdFile WaspSD::getParentDir(const char *filepath, int *index)
{
	// get parent directory
	SdFile d1 = currentDir; // start with the current working directory
	SdFile d2;

	// we'll use the pointers to swap between the two objects
	SdFile *parent = &d1;
	SdFile *subdir = &d2;

	// copy original path
	const char *origpath = filepath;

	// loop while we find character: '/'
	while (strchr(filepath, '/'))
	{
		// get rid of leading /'s
		if (filepath[0] == '/')
		{
			filepath++;
			continue;
		}

		if (! strchr(filepath, '/'))
		{
			// it was in the root directory, so leave now
			break;
		}

		// extract just the name of the next subdirectory
		uint8_t idx = strchr(filepath, '/') - filepath;
		if (idx > 12)
		{
			// dont let them specify long names
			idx = 12;
		}
		char subdirname[13];
		strncpy(subdirname, filepath, idx);
		subdirname[idx] = 0;

		// close the subdir (we reuse them) if open
		subdir->close();
		if (! subdir->open(parent, subdirname, O_READ))
		{
			// failed to open one of the subdirectories
			return SdFile();
		}
		// move forward to the next subdirectory
		filepath += idx;

		// we reuse the objects, close it.
		parent->close();

		// swap the pointers
		SdFile *t = parent;
		parent = subdir;
		subdir = t;
	}

	// set index from the beginning of the path to the parent directory
	*index = (int)(filepath - origpath);

	// parent is now the parent diretory of the file!
	return *parent;
}




/*
 * getDir(filepath, index) - gets directory of a filepath
 *
 * This function is a little helper used to traverse paths.
 * Answers the object SdFile which is related to the directory
 * of a path specified in 'filepath'
 *
 * If the directory is available in the parent folder, it will answer 1
 * (TRUE), if it is not a directory it will answer 0 (FALSE), and if it
 * is not available it will answer -1 (ERROR)
 *
 */
SdFile WaspSD::getDir(const char *filepath, int *index)
{
	// get parent directory
	SdFile d1 = currentDir; // start with the current working directory
	SdFile d2;

	// we'll use the pointers to swap between the two objects
	SdFile *parent = &d1;
	SdFile *subdir = &d2;

	// copy original path
	const char *origpath = filepath;

	// loop while we find character: '/'
	while (strchr(filepath, '/'))
	{
		// get rid of leading /'s
		if (filepath[0] == '/')
		{
			filepath++;
			continue;
		}

		if (! strchr(filepath, '/'))
		{
			// it was in the root directory, so leave now
			break;
		}

		// extract just the name of the next subdirectory
		uint8_t idx = strchr(filepath, '/') - filepath;
		if (idx > 12)
		{
			// dont let them specify long names
			idx = 12;
		}
		char subdirname[13];
		strncpy(subdirname, filepath, idx);
		subdirname[idx] = 0;

		// close the subdir (we reuse them) if open
		subdir->close();
		if (! subdir->open(parent, subdirname, O_READ))
		{
			// failed to open one of the subdirectories
			return SdFile();
		}
		// move forward to the next subdirectory
		filepath += idx;

		// we reuse the objects, close it.
		parent->close();

		// swap the pointers
		SdFile *t = parent;
		parent = subdir;
		subdir = t;
	}

	// there isn't any '/' character left
	// copy directory name in order to open it
	char * pch;
	char str[strlen(filepath)+1];
	strncpy(str,filepath, strlen(filepath));
	str[strlen(filepath)]='\0';
	pch = strtok (str,"/");
	if( pch == NULL )
	{
		// Any name found
		return SdFile();
	}

	// close the subdir (we reuse them) if open
	subdir->close();

	if (! subdir->open(parent, pch, O_READ))
	{
		// failed to open one of the subdirectories
		return SdFile();
	}

	// check if it is the root directory
	if( subdir->firstCluster() == 0 )
	{
		// Update current working directory to 'root' directory
		subdir=(SdFile*)&root;
	}

	// close parent
	parent->close();

	// swap the pointers
	parent = subdir;

	*index = (int)(filepath - origpath);
	// parent is now the parent directory of the file!
	return *parent;
}



/*
 * openFile (filepath, file, mode) - opens a file
 *
 * opens the file "filepath" if available.
 * 'filepath' is the string with the file name
 * 'file' is the return pointer to a opened SdFile object
 * 'mode' selects the mode. This flag is constructed by a
 * bitwise-inclusive OR of flags from the following list:
 *
 * 	O_READ - Open for reading.
 *
 * 	O_RDONLY - Same as O_READ.
 *
 * 	O_WRITE - Open for writing.
 *
 * 	O_WRONLY - Same as O_WRITE.
 *
 * 	O_RDWR - Open for reading and writing.
 *
 * 	O_APPEND - If set, the file offset shall be set to the end of the
 * file prior to each write.
 *
 * 	O_CREAT - If the file exists, this flag has no effect except as
 * noted under O_EXCL below. Otherwise, the file shall be created
 *
 * 	O_EXCL - If O_CREAT and O_EXCL are set, open() shall fail if the
 * file exists.
 *
 * 	O_SYNC - Call sync() after each write.  This flag should not be
 * used with write(uint8_t), write_P(PGM_P), writeln_P(PGM_P), or the
 * Arduino Print class. These functions do character at a time writes
 * so sync() will be called after each byte.
 *
 * 	O_TRUNC - If the file exists and is a regular file, and the file is
 * successfully opened and is not read only, its length shall be
 * truncated to 0.
 *
 * Returns '1' on success, '0' otherwise
 *
 */
uint8_t WaspSD::openFile(const char* filepath, SdFile* file, uint8_t mode)
{
	// path index: number of characters to reach
	// the parent directory within filepath
	int pathidx;

	// do the iterative search to look for the file's parent directory
	SdFile parentdir = getParentDir(filepath, &pathidx);

	filepath += pathidx;

	if (! filepath[0])
	{
		// it was the directory itself!
		return 0;
	}

	// failed to open a subdir!
	if (!parentdir.isOpen())
    {
		return 0;
	}

	// there is a special case for the Root directory since its a static dir
	if (parentdir.isRoot())
	{
		if ( ! file->open(&root, filepath, mode))
		{
			// failed to open the file
			return 0;
		}
		// dont close the root!
	}
	else
	{
		if ( ! file->open(&parentdir, filepath, mode))
		{
			return 0;
		}
		// close the parent
		parentdir.close();
	}

	// Set file pointer to the end of the file
	//~ if (mode & (O_APPEND | O_WRITE))
	//~ {
		//~ file->seekSet(file->fileSize())
	//~ }

	return 1;
}

/*
 * closeFile (file) - closes a file
 *
 * closes the pointer 'file' which was pointing to a file
 * Returns '1' on success, '0' otherwise
 *
*/
uint8_t WaspSD::closeFile(SdFile* file)
{
	// Close the file
	if(!file->close()) return 0;
	else return 1;
}

/*
 * getFileSize (filepath) - answers the file size for filepath in current folder
 *
 * answers a longint with the file "filepath" size in the current folder
 *
 * If the file is not available in the folder, it will answer -1, it will also
 * update the DOS.flag to FILE_OPEN_ERROR
 */
int32_t WaspSD::getFileSize(const char* filepath)
{
	// Local variable
	SdFile file;
	uint32_t size;

	// Open file
	if(!openFile( (char*)filepath, &file, O_RDONLY)) return -1;

	// Get file size
	size=file.fileSize();

	// Close file
	file.close();

    return size;
}


/*
 * cat (filepath, offset, scope)
 *
 * dumps into the SD.buffer the amount of bytes in 'scope' after 'offset'
 * coming from filepath, it will also return it as a string
 *
 * There is a limitation in size, due to DOS_BUFFER_SIZE. If the data
 * read was bigger than that, the function will include the characters
 * ">>" at the end and activate the TRUNCATED_DATA value in the SD.flag.
 * It is recommened to check this value to assure data integrity.
 *
 * If there was an error opening the file, the returned string will say
 * so and the DOS.flag will show the FILE_OPEN_ERROR bit active
 *
 * An example of calls to cat(filepath, offset, scope) is:
 *
 * - SD.cat("hola.txt", 3, 17): will show the 17 characters after
 * jumping over 3 in the file "hola.txt"
 *
 * The information is sent back as a string where each one of the
 * characters are printed one after the next, EOL ('\n') will be encoded
 * as EOL, and will be accounted as one byte, an example of this would be:
 *
 * un lugar
 * de la man
 *
 */
char* WaspSD::cat(const char* filepath, int32_t offset, uint16_t scope)
{
	// Local variable
	SdFile file;

    // check if the card is there or not
	if (!isSD())
	{
		flag = CARD_NOT_PRESENT;
		flag |= FILE_OPEN_ERROR;
		snprintf(buffer, sizeof(buffer),"%s", CARD_NOT_PRESENT_em);
		return buffer;
	}

	// if scope is zero, then we should make it
	// ridiculously big, so that it goes on reading forever
	if (scope <= 0) scope = DOS_BUFFER_SIZE;
	if (scope > DOS_BUFFER_SIZE) scope = DOS_BUFFER_SIZE;

	flag &= ~(TRUNCATED_DATA | FILE_OPEN_ERROR | FILE_SEEKING_ERROR);

	// search file in current working directory and open it
	// exit if error and modify the general flag with FILE_OPEN_ERROR
	if(!openFile((char*)filepath, &file, O_RDONLY))
	{
		snprintf(buffer, sizeof(buffer), "error opening %s", filepath);
		flag |= FILE_OPEN_ERROR;
		return buffer;
	}

	// iterate through the file

	// size of the buffer to use when reading
	byte maxBuffer = 10;

	// buffer so as to store data
	uint8_t bufferSD[maxBuffer];

	// counter so as not to exceed buffer size
	uint32_t cont = 0;

	// first jump over the offset
	if(!file.seekSet(offset))
	{
		snprintf(buffer, sizeof(buffer), "error seeking on: %s\n", filepath);
		flag |= FILE_SEEKING_ERROR;
		file.close();
		return buffer;
	}

	// Read first time from file, 'maxBuffer' bytes
	uint8_t readRet = file.read(bufferSD, sizeof(bufferSD));

	// second, read the data and store it in the buffer
	// Breaks in the case it exceeds its size.
	while(readRet > 0 && scope > 0 && cont < DOS_BUFFER_SIZE)
	{
		// Store data in buffer until scope ends, or
		// buffer size limit is exceeded
		for(uint8_t i = 0; i < readRet; ++i)
		{
			buffer[cont++] = bufferSD[i];
			scope--;
			if( scope <=0 ) break;
			if( cont>=DOS_BUFFER_SIZE ) break;
		}

		// Break in the case the file ends
		if( readRet<maxBuffer ) break;

		// Read other block of data from SD file
		readRet = file.read(bufferSD, sizeof(bufferSD));
	}

	// In the case the buffer is NOT exceeded, set end of string
	if (cont < DOS_BUFFER_SIZE - 1)
	{
		buffer[cont++] = '\0';
	}
	else
	{
		// in case we filled up the whole buffer, we add a
		// visual end of buffer indicator and leave the loop
		buffer[DOS_BUFFER_SIZE - 4] = '>';
		buffer[DOS_BUFFER_SIZE - 3] = '>';
		buffer[DOS_BUFFER_SIZE - 2] = '\n';
		buffer[DOS_BUFFER_SIZE - 1] = '\0';
		flag |= TRUNCATED_DATA;
	}

	// Close file
	file.close();

	return buffer;

}

/*
 * catBin(filepath, offset, scope)
 *
 * dumps into the SD.bufferBin the amount of bytes in 'scope' after
 * 'offset' coming from filepath, it will also return it.
 *
 * There is a limitation in size, due to BIN_BUFFER_SIZE. If the data
 * read was bigger than that, the function will include the characters
 * ">>" at the end and activate the TRUNCATED_DATA value in the SD.flag.
 * It is recommended to check this value to assure data integrity.
 *
 * If there is an error opening the file, 'buffer' is printed with an
 * error message and the SD.flag will show the FILE_OPEN_ERROR bit active.
 *
 */
uint8_t* WaspSD::catBin(const char* filepath, int32_t offset, uint16_t scope)
{
	// Local variable
	SdFile file;

	// check if the card is there or not
	if (!isSD())
	{
		flag = CARD_NOT_PRESENT;
		flag |= FILE_OPEN_ERROR;
		snprintf(buffer, sizeof(buffer),"%s", CARD_NOT_PRESENT_em);
		USB.println(buffer);
		return bufferBin;
	}

	// if scope is zero, then we should make it
	// ridiculously big, so that it goes on reading forever
	if (scope <= 0) scope = BIN_BUFFER_SIZE;
	if (scope > BIN_BUFFER_SIZE) scope = BIN_BUFFER_SIZE;

	flag &= ~(TRUNCATED_DATA | FILE_OPEN_ERROR | FILE_SEEKING_ERROR);

	// search file in current working directory and open it
	// exit if error and modify the general flag with FILE_OPEN_ERROR
	if(!openFile((char*)filepath, &file, O_RDONLY))
	{
		snprintf(buffer, sizeof(buffer), "error opening %s", filepath);
		USB.println(buffer);
		flag |= FILE_OPEN_ERROR;
		return bufferBin;
	}

	// iterate through the file
	byte maxBuffer = 1;  // size of the buffer to use when reading
	uint8_t bufferSD[maxBuffer]; // buffer so as to store data
	uint32_t cont = 0; // counter so as not to exceed buffer size

	// first jump over the offset
	if(!file.seekSet(offset))
	{
		snprintf(buffer, sizeof(buffer), "error seeking on: %s\n", filepath);
		USB.println(buffer);
		flag |= FILE_SEEKING_ERROR;
		file.close();
		return bufferBin;
	}

  	// Read first time from file, 'maxBuffer' bytes
	uint8_t readRet = file.read(bufferSD, sizeof(bufferSD));

	// clear 'bufferBin'
	memset(bufferBin, 0x00, sizeof(bufferBin) );

	// second, read the data and store it in the buffer
	// Breaks in the case it exceeds its size.
	while( (readRet > 0) && (scope > 0) && (cont < BIN_BUFFER_SIZE) )
	{
		// Store data in buffer until scope ends, or
		// buffer size limit is exceeded
		for(uint8_t i = 0; i < readRet; ++i)
		{
			bufferBin[cont++] = bufferSD[i];
			scope--;
			if( scope <=0 ) break;
			if( cont>=BIN_BUFFER_SIZE ) break;
		}

		// Break in the case the file ends
		if( readRet<maxBuffer ) break;

		// Read other block of data from SD file
		readRet = file.read(bufferSD, sizeof(bufferSD));
	}

	// Close file
	file.close();

	return bufferBin;

}

/*
 * catln (filepath, offset, scope)
 *
 * dumps into the SD.buffer the amount of lines in 'scope' after 'offset'
 * lines coming from filepath, it will also return it as a string.
 *
 * There is a limitation in size, due to DOS_BUFFER_SIZE. If the data
 * read is bigger than that, the function will include the characters
 * ">>" at the end and activate the TRUNCATED_DATA value in the SD.flag.
 * It is recommened to check this value to assure data integrity.
 *
 * If there was an error opening the file, the returned string will say
 * so and the SD.flag will show the FILE_OPEN_ERROR bit active
 *
 * An example of calls to catln(filepath, offset, scope) is:
 *
 * - SD.catln("hola.txt", 10, 5): will show 5 lines following the 10th
 * line in the file "hola.txt"
 *
 * The information is sent back as a string where each one of the file's
 * lines are printed in one line, an example of this would be:
 *
 * en un lugar
 * de la mancha de
 * cuyo nombre no qui>>
 *
 * Lines end with EOF ('\n'), this is the symbol used to count the
 * amount of lines.
 */
char* WaspSD::catln (const char* filepath, uint32_t offset, uint16_t scope)
{
	// Local variables
	SdFile file;
	uint8_t j=0;

    // check if the card is there or not
	if (!isSD())
	{
		flag = CARD_NOT_PRESENT;
		flag |= FILE_OPEN_ERROR;
		snprintf(buffer, sizeof(buffer),"%s", CARD_NOT_PRESENT_em);
		return buffer;
	}

	// if scope is zero, then we should make it
	// ridiculously big, so that it goes on reading forever
	if (scope <= 0) scope = DOS_BUFFER_SIZE;

	// Limit the maximum size of 'scope'
	if (scope > DOS_BUFFER_SIZE) scope = DOS_BUFFER_SIZE;

	// Unset any error flag there could be
	flag &= ~(TRUNCATED_DATA | FILE_OPEN_ERROR);

	// search file in current working directory and open it
	// exit if error and modify the general flag with FILE_OPEN_ERROR
	if(!openFile((char*)filepath, &file, O_RDONLY))
	{
		snprintf(buffer, sizeof(buffer), "error opening %s", filepath);
		flag |= FILE_OPEN_ERROR;
		return buffer;
	}

	// iterate through the file
	byte maxBuffer = 1;  // size of the buffer to use when reading
	uint8_t bufferSD[maxBuffer];
	uint32_t cont = 0;

  	// Read first byte of the file
	uint8_t readRet = file.read(bufferSD, sizeof(bufferSD));

	// jump over offset lines (seek number of '\n' characters)
	if (offset > 0)
	{
		// count EOL in order to set the selected 'offset'
		j=0;
		while( readRet > 0 && offset > 0)
		{
			for(j = 0; j < readRet; ++j)
			{
				if (bufferSD[j] == '\n')
				offset--;
				if( offset <=0 ) break;
			}
			if(offset>0)
			{
				// read data from SD file
				readRet = file.read(bufferSD, sizeof(bufferSD));
			}
		}

		// do not forget the first buffer
		for(uint8_t i = j+1; i < maxBuffer; ++i)
		{
			buffer[cont++] = bufferSD[i];
			if (bufferSD[i] == '\n')
				scope--;
		}
		// read data from SD file
		readRet = file.read(bufferSD, sizeof(bufferSD));
	}

	// add 'scope' lines to buffer
	while(readRet > 0 && scope > 0 && cont < DOS_BUFFER_SIZE)
	{
		// copy data until we count 'scope' lines
		for(uint8_t i = 0; i < maxBuffer; ++i)
		{
			buffer[cont++] = bufferSD[i];
			if (bufferSD[i] == '\n')
				scope--;
			if( scope <=0 ) break;
		}
		// read data from SD file
		if( scope >0 )
			readRet = file.read(bufferSD, sizeof(bufferSD));
	}

	// are we at the end of the buffer yet?
	if (cont < DOS_BUFFER_SIZE - 1)
	{
		// set end of string
		buffer[cont++] = '\0';
	}
	else
	{
		// in case we filled up the whole buffer, we add a
		// visual end of buffer indicator and leave the loop
		buffer[DOS_BUFFER_SIZE - 4] = '>';
		buffer[DOS_BUFFER_SIZE - 3] = '>';
		buffer[DOS_BUFFER_SIZE - 2] = '\n';
		buffer[DOS_BUFFER_SIZE - 1] = '\0';
		flag |= TRUNCATED_DATA;
	}

	// close file
	file.close();

	return buffer;

}


/*
 * indexOf ( filepath, pattern, offset ) - search for first occurrence
 * of an specific string in a file
 *
 * Seeks inside 'filepath' file for the first occurrence of the pattern
 * after a certain 'offset'. The algorithm will jump over 'offset'
 * bytes before starting the search of the pattern. It will return the
 * amount of bytes (as an int32_t) to the pattern from the offset
 *
 * Example, file hola.txt contains:
 *
 * hola caracola\nhej hej\n   hola la[EOF]
 *
 * The following table shows the results from searching different patterns:
 *
 * Command                            	Answer
 * SD.indexOf("hola.txt", "hola", 0)       0
 * SD.indexOf("hola.txt", "hola", 1)       23
 * SD.indexOf("hola.txt", "hej", 3)        11
 *
 * Notes:
 * - the special characters like '\n' (EOL) are accounted as one byte
 * - files are indexed from 0
 *
 * If there was an error opening the file, the buffer string will say so
 * and the SD.flag will show the FILE_OPEN_ERROR bit active
 */
int32_t WaspSD::indexOf (const char* filepath, const char* pattern, uint32_t offset)
{
	// Local variables
	SdFile file;
	uint8_t exit = 0;
	uint32_t cont = 0;
	uint8_t readRet;

	// check if the card is there or not
	if (!isSD())
	{
		flag = CARD_NOT_PRESENT;
		flag |= FILE_OPEN_ERROR;
		snprintf(buffer, sizeof(buffer),"%s", CARD_NOT_PRESENT_em);
		return -1;
	}

	// unset any flag error
	flag &= ~(FILE_OPEN_ERROR);

	// open file in current directory
	// exit if error and modify the general flag with FILE_OPEN_ERROR
	if(!openFile((char*)filepath, &file, O_RDONLY))
	{
		snprintf(buffer, sizeof(buffer), "error opening %s", filepath);
		flag |= FILE_OPEN_ERROR;
		return -2;
	}

	// get file length
	uint32_t limitSize = getFileSize(filepath);

	// get pattern length
	uint8_t limitPattern = strlen(pattern);

	// buffer in order to read bytes from SD file
	uint8_t bufferSD[1];

	// buffer to store comparison pattern
	uint8_t* cmpPattern = (uint8_t*) calloc(limitPattern,sizeof(uint8_t));
	if( cmpPattern==NULL )
	{
		file.close();
		return -1;
	}

	// jump over the 'offset'
	if(!file.seekSet(offset))
	{
		file.close();
		free(cmpPattern);
		cmpPattern=NULL;
		return -1;
	}

	// fill in the first buffer
	readRet = file.read(bufferSD, sizeof(bufferSD));
	for(int j=0; j < limitPattern - 1; j++)
	{
		if (readRet > 0)
		{
			cmpPattern[j] = bufferSD[0];
			readRet = file.read(bufferSD, sizeof(bufferSD));
		}
		else
			exit = 1;  // exit if the filesize is smaller than the pattern
	}

	// to debug the code in the library it is possible to
	// use the buffer together with snprintf, e.g.
	//~ snprintf(buffer, sizeof(buffer),"%s - %c%c%c%c - %lu - %u -%lu",
				//~ pattern,
				//~ cmpPattern[0],
				//~ cmpPattern[1],
				//~ cmpPattern[2],
				//~ bufferSD[0],
				//~ cont,
				//~ limitPattern,
				//~ limitSize);

	// run inside the buffer
	while(readRet > 0 && cont < limitSize && !exit)
	{
		// take the last position in the buffer
		cmpPattern[limitPattern-1] = bufferSD[0];

		// compare the strings, exit if found
		//if(Utils.strCmp((const char*) pattern, (const char*) cmpPattern, limitPattern) == 0)
		if(strncmp((const char*) pattern, (const char*) cmpPattern, limitPattern) == 0)
			exit = 1;

		// if not exit, increment counter
		if (!exit)
			cont++;

		// shift cmpPattern to the left one position
		for(int j = 0; j < limitPattern - 1; j++) cmpPattern[j] = cmpPattern[j+1];

		// read the next buffer
		readRet = file.read(bufferSD, sizeof(bufferSD));
	}

	// close file
	file.close();

	// free dynamic memory
	free(cmpPattern);
	cmpPattern=NULL;

	// in case we checked the whole buffer, we return error
	if (cont >= limitSize - limitPattern )
		return -1;

	// otherwise we return the pattern's location
	return cont;
}


/*
 * isDir ( dir_entry ) - answers whether a file is a directory or not
 *
 * Returns 1 if it is a dir, 0 if error, will
 * not modify any flags
 */
uint8_t WaspSD::isDir(SdFile* dir)
{
	// Check if it is a valid file
	if (!dir->isDir())
	{
		return 0;
	}
	else return 1;
}


/*
 * isDir ( dirpath ) - tests the existence of a directory in the current
 * working directory and checks if it is a directory or not
 *
 * Returns:
 * 	1	: if it exists and it is a dir,
 * 	0	: if exists but it is not a dir,
 * -1	: if error
 * 	will not modify any flags
 */
int8_t WaspSD::isDir(const char* dirpath)
{
	// Local variable
	SdFile file;

	// try to open the file
	if(!openFile( (char*)dirpath, &file, O_RDONLY))
	{
		return -1;
	}
	else
	{
		// File opened. Check if it is a valid file
		if (!file.isDir())
		{
			file.close();
			return 0;
		}
		else file.close();
	}
    return 1;
}


/*
 * del ( filepath ) - delete file
 *
 * Returns 1 if it is possible to delete "filepath", 0 if error, will
 * not modify any flags
 *
 * This function should not be used to delete the 8.3 version of a
 * file that has a long name.
 *
 */
boolean WaspSD::del(const char* filepath)
{
	return walkPath((char*)filepath, currentDir, callback_remove, NULL);
}


/*
 * rmdir ( dirpath ) - delete Directory
 *
 * returns 1 if it is possible to delete "dirname", 0 if error, will
 * not modify any flags
 *
 * The directory file will be removed only if it is empty and
 * is not the root directory.  rmDir() follows DOS and Windows and
 * ignores the read-only attribute for the directory.
 *
 * This function should not be used to delete the 8.3 version of a
 * file that has a long name.
 *
 */
boolean WaspSD::rmdir(const char* dirpath)
{
	boolean result = walkPath((char*)dirpath, currentDir, callback_rmdir, NULL);
	if(!result)
	{
		//try to delete a possible "damaged" directory
		result = del(dirpath);
	}
	return result;
}


/*
 * rmRfDir ( dirpath ) - delete Directory and all contained files.
 *
 * returns 1 if it is possible to delete "dirpath", 0 if error, will
 * not modify any flags
 *
 * This function should not be used to delete the 8.3 version of a
 * file that has a long name. For example if a file has the long name
 *
 */
boolean WaspSD::rmRfDir(const char* dirpath)
{
	boolean answer = false;
	answer = walkPath((char*)dirpath, currentDir, callback_rmRfdir, NULL);

	if(answer == false)
	{
		// if corrupted when a bad 'rmRfDir' call was done,
		// then try to delete the generated corrupted file
		if( SD.isFile(dirpath) == true )
		{
			answer = SD.del(dirpath);
		}
	}

	return answer;
}





/*
 * create ( filepath ) - create file called filepath
 *
 * If filepath is a path, i.e. "/FOLDER/SUBFOLD/file1.txt", the file
 * called file1.txt is created inside the subdirectory SUBFOLD always
 * the path has been created before using SD.mkdir("/FOLDER/SUBFOLD");
 *
 * Returns 1 on file creation, 0 if error, will mark the flag with
 * FILE_CREATION_ERROR
 */
uint8_t WaspSD::create(const char* filepath)
{
	// Local variables
	SdFile file;

	// set file date
	setFileDate();

	// check if the card is there or not
	if (!isSD())
	{
		flag = CARD_NOT_PRESENT;
		flag |= FILE_CREATION_ERROR;
		snprintf(buffer, sizeof(buffer),"%s", CARD_NOT_PRESENT_em);
		return 0;
	}

	// unset any error flag
	flag &= ~(FILE_CREATION_ERROR);

	// create/open new file. modes:
	//  O_READ - Open for reading
	//	O_WRITE - Open for writing
	// 	O_CREAT: create the file if nonexistent
	// 	O_EXCL: If O_CREAT and O_EXCL are set, open shall fail if the file exists
	if(!openFile( (char*)filepath, &file, O_READ | O_WRITE | O_CREAT | O_EXCL))
	{
		flag |= FILE_CREATION_ERROR;
		return 0;
	}

	// close file
	file.close();

	return 1;
}


/*
 * writeSD ( filepath, str, offset ) - write string to file
 *
 * writes the string 'str' to the file 'filepath' after a certain 'offset'
 *
 * Returns
 * 	1 on success,
 * 	0 if error,
 * 	will mark the flag with FILE_WRITING_ERROR
 */
uint8_t WaspSD::writeSD(const char* filepath, const char* str, int32_t offset)
{
	// get "str" length
    uint16_t data_len = strlen(str);

    return writeSD(filepath, str, offset, data_len);
}


/*
 * writeSD ( filepath, str, offset, length ) - write string to file
 *
 * writes the string "str" to the file "filepath" after a certain "offset"
 *
 * Returns
 * 	1 on success,
 * 	0 if error,
 * 	will mark the flag with FILE_WRITING_ERROR
 */
uint8_t WaspSD::writeSD(	const char* filepath,
							const char* str,
							int32_t offset,
							uint16_t length	)
{
	// Local variables
	SdFile file;

	// check if the card is there or not
    if (!isSD())
    {
        flag = CARD_NOT_PRESENT;
        flag |= FILE_WRITING_ERROR;
        snprintf(buffer, sizeof(buffer),"%s", CARD_NOT_PRESENT_em);
        return 0;
    }

	// unset error flag
    flag &= ~(FILE_WRITING_ERROR | FILE_SEEKING_ERROR);

	// search file in current directory and open it in write mode
    if(!openFile(filepath, &file, O_READ | O_WRITE | O_SYNC))
    {
        snprintf(buffer, sizeof(buffer), "error opening: %s\n", filepath);
        flag |= FILE_WRITING_ERROR;
        return 0;
    }

	// jump over the 'offset'
	if(!file.seekSet(offset))
	{
		snprintf(buffer, sizeof(buffer), "error seeking on: %s\n", filepath);
		file.close();
		flag |= FILE_SEEKING_ERROR;
		return 0;
	}

	// set length properly in case it was not
	if(strlen(str)<length)
	{
		length=strlen(str);
	}

	// write text to file
    if((uint16_t)file.write((uint8_t*) str, length) != length)
    {
        snprintf(buffer, sizeof(buffer), "error writing to: %s\n", filepath);
        file.close();
        flag |= FILE_WRITING_ERROR;
        return 0;
    }

    // close file
    file.close();

	return 1;
}


/*
 * writeSD ( filepath, str, offset ) - write numbers to files
 *
 * writes the array of integers "str" to the file "filepath" after a
 * certain "offset". The array MUST end with the following pattern:
 * "0xAAAA"
 *
 * Returns
 * 	1 on success,
 * 	0 if error,
 * 	will mark the flag with FILE_WRITING_ERROR
 */
uint8_t WaspSD::writeSD(const char* filepath, uint8_t* str, int32_t offset)
{
	// get array length
	uint16_t data_len = 0;
	while( (str[data_len]!=0xAA) || (str[data_len+1]!=0xAA) ) data_len++;

	return writeSD(filepath, str, offset, data_len);
}


/*
 * writeSD ( filepath, str, offset, length ) - write numbers to files
 *
 * writes the array of integers "str" to the file "filepath" after a
 * certain "offset". The length of the array is indicated by "length"
 *
 * Returns
 * 	1 on success,
 * 	0 if error,
 * 	will mark the flag with FILE_WRITING_ERROR
 */
uint8_t WaspSD::writeSD(const char* filepath, uint8_t* str, int32_t offset, uint16_t length)
{
	// Local variables
	SdFile file;

	// check if the card is there or not
	if (!isSD())
	{
		flag = CARD_NOT_PRESENT;
		flag |= FILE_WRITING_ERROR;
		snprintf(buffer, sizeof(buffer),"%s", CARD_NOT_PRESENT_em);
		return 0;
	}

	// unset error flag
	flag &= ~(FILE_WRITING_ERROR | FILE_SEEKING_ERROR);

	// search file in current directory and open it
    if(!openFile(filepath, &file, O_READ | O_WRITE | O_SYNC))
    {
        snprintf(buffer, sizeof(buffer), "error opening: %s\n", filepath);
        flag |= FILE_WRITING_ERROR;
        return 0;
    }

	// jump over the 'offset'
	if(!file.seekSet(offset))
	{
		snprintf(buffer, sizeof(buffer), "error seeking on: %s\n", filepath);
		file.close();
		flag |= FILE_SEEKING_ERROR;
		return 0;
	}

	// write text to file
    if( (uint16_t)file.write((uint8_t*) str, length) != length)
    {
        snprintf(buffer, sizeof(buffer), "error writing to: %s\n", filepath);
        file.close();
        flag |= FILE_WRITING_ERROR;
        return 0;
    }

    // close file
    file.close();

	return 1;
}


/*
 * append ( filepath, str ) - write strings at the end of the file
 *
 * Writes the string "str" at the end of the file "filepath"
 *
 * Returns
 * 	1 on success,
 * 	0 if error,
 *	will mark the flag with FILE_WRITING_ERROR
 */
uint8_t WaspSD::append(const char* filepath, const char* str)
{
    return writeSD(filepath, str, getFileSize(filepath));
}


/*
 * append ( filepath, str, length ) - write string at the end of the file
 *
 * Writes the string "str" at the end of the file "filepath"
 *
 * \remarks length of string is indicated with "length"
 *
 * Returns
 * 	1 on success,
 * 	0 if error,
 * 	will mark the flag with FILE_WRITING_ERROR
 */
uint8_t WaspSD::append(const char* filepath, const char* str, uint16_t length)
{
	return writeSD(filepath, str, getFileSize(filepath), length);
}


/*
 * append ( filepath, str ) - write array of numbers at the end of the file
 *
 * Writes the array of numbers "str" at the end of the file "filepath"
 *
 * Returns
 * 	1 on success,
 * 	0 if error,
 * 	will mark the flag with FILE_WRITING_ERROR
 */
uint8_t WaspSD::append(const char* filepath, uint8_t* str)
{
	return writeSD(filepath, str, getFileSize(filepath));
}


/*
 * append ( filepath, str, length ) - write array of numbers at the end of the file
 *
 * Writes the array of numbers "str" at the end of the file "filepath"
 * The length of the string "str" is indicated with "length"
 *
 * Returns
 * 	1 on success,
 * 	0 if error,
 * 	will mark the flag with FILE_WRITING_ERROR
 */
uint8_t WaspSD::append(const char* filepath, uint8_t* str, uint16_t length)
{
	return writeSD(filepath, str, getFileSize(filepath), length);
}



/*
 * appendln ( filepath, str, length ) -  write array of numbers at the end of the file
 *
 * Writes the array of numbers "str" at the end of the file "filepath"
 * The length of the string "str" is indicated with "length". End of line is
 * added when the first writing is done successfully.
 *
 * Returns
 * 	1 on success,
 * 	0 if error,
 * 	will mark the flag with FILE_WRITING_ERROR
 */
uint8_t WaspSD::appendln(const char* filepath, uint8_t* str, uint16_t length)
{
    uint8_t exit = 0;
    exit = append(filepath, str, length);
    if (exit)
    {
		exit &= writeEndOfLine(filepath);
	}
    return exit;
}


/*
 * appendln ( filepath, str ) - write strings at the end of files
 *
 * Writes the string "str" at the end of the file "filepath" adding end
 * of line. Depending on  the tag FILESYSTEM_LINUX, a '\r' is also
 * written to the SD file.
 *
 * Returns
 * 	1 on success,
 * 	0 if error,
 * 	will mark the flag with FILE_WRITING_ERROR
 */
uint8_t WaspSD::appendln(const char* filepath, const char* str)
{
    uint8_t exit = 0;
    exit = append(filepath, str);
    if (exit)
    {
		exit &= writeEndOfLine(filepath);
	}
    return exit;
}


/*
 * appendln ( filepath, str ) - write array of numbers at the end of the file
 *
 * Writes the array of numbers "str" at the end of the file "filepath"
 * adding end of line. Depending on  the tag FILESYSTEM_LINUX, a '\r' is
 * also written to the SD file.
 *
 * Returns
 * 	1 on success,
 * 	0 if error,
 * 	will mark the flag with FILE_WRITING_ERROR
 */
uint8_t WaspSD::appendln(const char* filepath, uint8_t* str)
{
	uint8_t exit = 0;
	exit = append(filepath, str);
    if (exit)
    {
		exit &= writeEndOfLine(filepath);
	}
	return exit;
}

/*
 * numln ( filepath ) - returns the amount of lines in a file
 *
 * returns the amount of lines in "filepath" that should be in the
 * current directory, a negative answer indicates error, zero means no
 * lines in the file
 *
 * This method counts the occurrence of the character '\n' in the file.
 * If there was a problem opening it, the FILE_OPEN_ERROR would be
 * activated and will return -1
 */
int32_t WaspSD::numln(const char* filepath)
{
	// local variables
	SdFile file;
	byte maxBuffer = 10;  // size of the buffer to use when reading
	uint8_t bufferSD[maxBuffer]; // buffer to store read data
	uint32_t cont = 0; // lines counter

	// check if the card is there or not
	if (!isSD())
	{
		flag = CARD_NOT_PRESENT;
		flag |= FILE_OPEN_ERROR;
		snprintf(buffer, sizeof(buffer),"%s", CARD_NOT_PRESENT_em);
		return -1;
	}

    // unset error flag
	flag &= ~(FILE_OPEN_ERROR);

	// search file in the current working directory and open it
	// exit if error and modify the general flag with FILE_OPEN_ERROR
    if(!openFile(filepath, &file, O_READ))
    {
        snprintf(buffer, sizeof(buffer), "error opening: %s\n", filepath);
        flag |= FILE_OPEN_ERROR;
        return 0;
    }

	// count lines by reading '\n' characters
	uint8_t readRet = file.read(bufferSD, maxBuffer);

	// count '\n' characters while there is available data in SD file
	while( readRet > 0)
	{
		// search '\n' characters
		for(uint8_t i = 0; i < readRet; ++i)
		{
			if (bufferSD[i] == '\n')
			cont++;
		}
		readRet = file.read(bufferSD, maxBuffer);
	}

	// close file
	file.close();

	return cont;

}



/*
 * cd(dirpath) - changes directory,
 *
 * Returns: 0=error; 1=ok
 */
uint8_t WaspSD::cd(const char* dirpath)
{
	// local variables
	int pathidx;

	// do the iterative search to look for the path's directory
	SdFile newdir = getDir(dirpath, &pathidx);

	// check if newdir was correctly found and opened
	if (!newdir.isOpen())
	{
		// failed to open a subdir!
		return 0;
	}
	else
	{
		// copy object to 'newdir'
		memcpy(&currentDir, &newdir, sizeof(SdFile));
	}

	return 1;
}


/*
 * goRoot(path) - go to root directory
 *
 * Update "currentDir" with "root" attribute by copying the context of the root
 * directory in currentDir.
 *
 * Returns: 0=error; 1=ok
 */
uint8_t WaspSD::goRoot()
{
	// Check if currentDir is the root directory
	if(currentDir.isRoot())
	{
		return 1;
	}

	// close actual directory
	if(!currentDir.close())
	{
		// Can't close actual current directory
		return 0;
	}

	// Update current working directory to 'root' directory
	memcpy(&currentDir, &root, sizeof(SdFile));

	return 1;

}


/*
 * numFiles ( void ) - returns the amount of files in dir
 *
 * returns the amount of files in the current directory
 * a negative answer indicates error, zero means no files in the folder
 */
int8_t WaspSD::numFiles()
{
	// set the file's current position to zero
	currentDir.rewind();

	// check if the card is there or not
	if (!isSD())
	{
		flag = CARD_NOT_PRESENT;
		snprintf(buffer, sizeof(buffer),"%s", CARD_NOT_PRESENT_em);
		return -1;
	}

	uint8_t cont = -2;
	dir_t 	dir_entry;
	cont=0;
	while(currentDir.readDir(&dir_entry))
	{
		// Don't count TRASH~1 directory
		if(!(dir_entry.name[0]=='T' &&
			 dir_entry.name[1]=='R' &&
			 dir_entry.name[2]=='A' &&
			 dir_entry.name[3]=='S' &&
			 dir_entry.name[4]=='H' ))
		{
			// increase counter
			cont++;
		}
	}

	// set the file's current position to zero
	currentDir.rewind();

	return cont;
}


/*
 * cleanFlags ( void ) - resets all the flags, returns the flags
 */
uint16_t WaspSD::cleanFlags(void)
{
	flag = 0;
	return flag;
}


/*
 * writeEndOfLine -
 *
 * Write "\r\n" in specified file
 */
uint8_t WaspSD::writeEndOfLine(const char* filepath)
{
	uint8_t result = 1;

#ifndef FILESYSTEM_LINUX
    if(result)
    {
		result = append(filepath, "\r\n");
		if(!result)
		{
			result = append(filepath, "\r\n");
		}
	}
#else
    if(result)
    {
		result = append(filepath, "\n");
		if(!result)
		{
			result = append(filepath, "\n");
		}
	}
#endif

	return result;
}

/*
 * format() -
 *
 * Format SD card erasing all data first
 */
bool WaspSD::format()
{
	//! variables:
	//---------------------------------------------------------------
	uint32_t const ERASE_SIZE = 262144L;
	uint32_t cardSizeBlocks;
	uint16_t cardCapacityMB;

	// cache for SD block
	cache_t cache;

	// MBR information
	uint8_t partType;
	uint32_t relSector;
	uint32_t partSize;

	// Fake disk geometry
	uint8_t numberOfHeads;
	uint8_t sectorsPerTrack;

	// FAT parameters
	uint16_t reservedSectors;
	uint8_t sectorsPerCluster;
	uint32_t fatStart;
	uint32_t fatSize;
	uint32_t dataStart;

	// constants for file system structure
	uint16_t const BU16 = 128;
	uint16_t const BU32 = 8192;

	//  strings needed in file system structures
	char noName[] = "NO NAME    ";
	char fat16str[] = "FAT16   ";
	char fat32str[] = "FAT32   ";
	//---------------------------------------------------------------

	//! initialization process
	cardSizeBlocks = card.cardSize();
	if (cardSizeBlocks == 0)
	{
		#ifdef SD_DEBUG
		PRINTLN_SD(F("error cardSize"));
		#endif
		return 0;
	}
	cardCapacityMB = (cardSizeBlocks + 2047)/2048;

	#ifdef SD_DEBUG
	PRINT_SD(F("Card Size: "));
	USB.print(cardCapacityMB);
	USB.println(F(" MB, (MB = 1,048,576 bytes)"));
	#endif


	//! Erasing process
	#ifdef SD_DEBUG
	PRINTLN_SD(F("\nErasing\n"));
	#endif
	uint32_t firstBlock = 0;
	uint32_t lastBlock;
	uint16_t n = 0;

  #ifdef SD_DEBUG
  PRINT_SD(F(""));
  #endif
	do {
		lastBlock = firstBlock + ERASE_SIZE - 1;
		if (lastBlock >= cardSizeBlocks) lastBlock = cardSizeBlocks - 1;
		if (!card.erase(firstBlock, lastBlock))
		{
			#ifdef SD_DEBUG
			PRINTLN_SD(F("erase failed"));
			#endif
			return 0;
		}
		#ifdef SD_DEBUG
		USB.print(F("."));
		#endif
		if ((n++)%32 == 31) USB.println();
		firstBlock += ERASE_SIZE;
	} while (firstBlock < cardSizeBlocks);

	#ifdef SD_DEBUG
	USB.println();
	#endif

	if (!card.readBlock(0, cache.data))
	{
		#ifdef SD_DEBUG
		PRINTLN_SD(F("error readBlock"));
		#endif
		return 0;
	}

	#ifdef SD_DEBUG
	PRINT_SD(F("All data set to "));
	USB.println(int(cache.data[0]),DEC);
	PRINT_SD(F("Erase done\n"));
	#endif

	//! Formatting process
	#ifdef SD_DEBUG
	USB.println();
	PRINT_SD(F("Formatting\n"));
	#endif

	// initSizes
	if (cardCapacityMB <= 6)
	{
		#ifdef SD_DEBUG
		PRINTLN_SD(F("Card is too small."));
		#endif
		return 0;
	}
    else if (cardCapacityMB <= 16)		sectorsPerCluster = 2;
	else if (cardCapacityMB <= 32) 		sectorsPerCluster = 4;
	else if (cardCapacityMB <= 64) 		sectorsPerCluster = 8;
	else if (cardCapacityMB <= 128)		sectorsPerCluster = 16;
	else if (cardCapacityMB <= 1024) 	sectorsPerCluster = 32;
	else if (cardCapacityMB <= 32768)   sectorsPerCluster = 64;
	else{
			// SDXC cards
			sectorsPerCluster = 128;
		}

	#ifdef SD_DEBUG
	PRINT_SD(F("Blocks/Cluster: "));
	USB.println(sectorsPerCluster,DEC);
	#endif

	// set fake disk geometry
	sectorsPerTrack = cardCapacityMB <= 256 ? 32 : 63;

	if (cardCapacityMB <= 16)			numberOfHeads = 2;
	else if (cardCapacityMB <= 32)		numberOfHeads = 4;
	else if (cardCapacityMB <= 128)		numberOfHeads = 8;
	else if (cardCapacityMB <= 504)		numberOfHeads = 16;
	else if (cardCapacityMB <= 1008)	numberOfHeads = 32;
	else if (cardCapacityMB <= 2016)	numberOfHeads = 64;
	else if (cardCapacityMB <= 4032)	numberOfHeads = 128;
	else{
			numberOfHeads = 255;
		}

	if (volume.fatType() == 16)
	{
		#ifdef SD_DEBUG
		PRINT_SD(F("FAT16\n"));
		#endif
		/*start makeFat16()*/
		uint32_t nc;
		for (dataStart = 2 * BU16;; dataStart += BU16)
		{
			nc = (cardSizeBlocks - dataStart)/sectorsPerCluster;
			fatSize = (nc + 2 + 255)/256;
			uint32_t r = BU16 + 1 + 2 * fatSize + 32;
			if (dataStart < r) continue;
			relSector = dataStart - r + BU16;
			break;
		}

		// check valid cluster count for FAT16 volume
		if (nc < 4085 || nc >= 65525)
		{
			#ifdef SD_DEBUG
			PRINTLN_SD(F("Bad cluster count"));
			#endif
			return 0;
		}
		reservedSectors = 1;
		fatStart = relSector + reservedSectors;
		partSize = nc * sectorsPerCluster + 2 * fatSize + reservedSectors + 32;
		if (partSize < 32680) {
			partType = 0X01;
		} else if (partSize < 65536) {
			partType = 0X04;
		} else {
			partType = 0X06;
		}

		// write MBR
		/*start writeMbr()*/
			/*start clearCache(true)*/
			memset(&cache, 0, sizeof(cache));
			cache.mbr.mbrSig0 = BOOTSIG0;
			cache.mbr.mbrSig1 = BOOTSIG1;
			/*end clearCache(true)*/
		part_t* p = cache.mbr.part;
		p->boot = 0;
		// get cylinder number for a logical block number
		//~ uint16_t c = lbnToCylinder(relSector);
		uint16_t c = relSector / (numberOfHeads * sectorsPerTrack);
		if (c > 1023)
		{
			#ifdef SD_DEBUG
			PRINTLN_SD(F("error MBR CHS"));
			#endif
			return 0;
		}
		p->beginCylinderHigh = c >> 8;
		p->beginCylinderLow = c & 0XFF;
		//get head number for a logical block number
		//~ p->beginHead = lbnToHead(relSector);
		p->beginHead = (relSector % (numberOfHeads * sectorsPerTrack)) / sectorsPerTrack;
		//get sector number for a logical block number
		//~ p->beginSector = lbnToSector(relSector);
		p->beginSector = (relSector % sectorsPerTrack) + 1;
		p->type = partType;
		uint32_t endLbn = relSector + partSize - 1;
		//get cylinder number for a logical block number
		//~ c = lbnToCylinder(endLbn);
		c = endLbn / (numberOfHeads * sectorsPerTrack);
		if (c <= 1023) {
			p->endCylinderHigh = c >> 8;
			p->endCylinderLow = c & 0XFF;
			//get head number for a logical block number
			//~ p->endHead = lbnToHead(endLbn);
			p->endHead = (endLbn % (numberOfHeads * sectorsPerTrack)) / sectorsPerTrack;
			//get sector number for a logical block number
			//~ p->endSector = lbnToSector(endLbn);
			p->endSector = (endLbn % sectorsPerTrack) + 1;
			//get sector number for a logical block number
			//~ p->endSector = lbnToSector(endLbn);
			p->endSector = (endLbn % sectorsPerTrack) + 1;
		} else {
			// Too big flag, c = 1023, h = 254, s = 63
			p->endCylinderHigh = 3;
			p->endCylinderLow = 255;
			p->endHead = 254;
			p->endSector = 63;
		}
		p->firstSector = relSector;
		p->totalSectors = partSize;
		//~ if (!writeCache(0))
		if (!card.writeBlock(0, cache.data))
		{
			#ifdef SD_DEBUG
			PRINTLN_SD(F("error write MBR"));
			#endif
			return 0;
		}
		/*end writeMbr()*/

		/*start clearCache(true)*/
		memset(&cache, 0, sizeof(cache));
		cache.mbr.mbrSig0 = BOOTSIG0;
		cache.mbr.mbrSig1 = BOOTSIG1;
		/*end clearCache(true)*/
		fat_boot_t* pb = &cache.fbs;
		pb->jump[0] = 0XEB;
		pb->jump[1] = 0X00;
		pb->jump[2] = 0X90;
		for (uint8_t i = 0; i < sizeof(pb->oemId); i++) {
			pb->oemId[i] = ' ';
		}
		pb->bytesPerSector = 512;
		pb->sectorsPerCluster = sectorsPerCluster;
		pb->reservedSectorCount = reservedSectors;
		pb->fatCount = 2;
		pb->rootDirEntryCount = 512;
		pb->mediaType = 0XF8;
		pb->sectorsPerFat16 = fatSize;
		pb->sectorsPerTrack = sectorsPerTrack;
		pb->headCount = numberOfHeads;
		pb->hidddenSectors = relSector;
		pb->totalSectors32 = partSize;
		pb->driveNumber = 0X80;
		pb->bootSignature = EXTENDED_BOOT_SIG;
		//~ pb->volumeSerialNumber = volSerialNumber();
		pb->volumeSerialNumber = (cardSizeBlocks << 8) + millis();
		memcpy(pb->volumeLabel, noName, sizeof(pb->volumeLabel));
		memcpy(pb->fileSystemType, fat16str, sizeof(pb->fileSystemType));
		// write partition boot sector
		//~ if (!writeCache(relSector))
		if (!card.writeBlock(relSector, cache.data))
		{
			#ifdef SD_DEBUG
			PRINTLN_SD(F("FAT16 write PBS failed"));
			#endif
			return 0;
		}
		// clear FAT and root directory
		/* start clearFatDir(fatStart, dataStart - fatStart);*/
		/*start clearCache(false)*/
		memset(&cache, 0, sizeof(cache));
		/*end clearCache(false)*/
		if (!card.writeStart(fatStart, dataStart - fatStart))
		{
			#ifdef SD_DEBUG
			PRINTLN_SD(F("Clear FAT/DIR writeStart failed"));
			#endif
			return 0;
		}
		for (uint32_t i = 0; i < (dataStart - fatStart); i++)
		{
			if ((i & 0XFF) == 0)
			{
				#ifdef SD_DEBUG
				USB.print(F("."));
				#endif
			}
			if (!card.writeData(cache.data))
			{
				#ifdef SD_DEBUG
				USB.println(F("Clear FAT/DIR writeData failed"));
				#endif
				return 0;
			}
		}
		if (!card.writeStop())
		{
			#ifdef SD_DEBUG
			USB.println(F("Clear FAT/DIR writeStop failed"));
			#endif
			return 0;
		}
		#ifdef SD_DEBUG
		USB.println();
		#endif
		/* end clearFatDir(fatStart, dataStart - fatStart);*/
		/*start clearCache(false)*/
		memset(&cache, 0, sizeof(cache));
		/*end clearCache(false)*/
		cache.fat16[0] = 0XFFF8;
		cache.fat16[1] = 0XFFFF;
		// write first block of FAT and backup for reserved clusters
		//~ if (!writeCache(fatStart) || !writeCache(fatStart + fatSize)) {
		if(	!card.writeBlock(fatStart, cache.data) ||
			!card.writeBlock(fatStart + fatSize, cache.data) )
		{
			#ifdef SD_DEBUG
			USB.println(F("FAT16 reserve failed"));
			#endif
			return 0;
		}
	}
	else if (volume.fatType() == 32)
	{
		#ifdef SD_DEBUG
		USB.print(F("FAT32\n"));
		#endif

		/*start makeFat32()*/
		uint32_t nc;
		relSector = BU32;

		for (dataStart = 2 * BU32;; dataStart += BU32)
		{
			nc = (cardSizeBlocks - dataStart)/sectorsPerCluster;
			fatSize = (nc + 2 + 127)/128;
			uint32_t r = relSector + 9 + 2 * fatSize;
			if (dataStart >= r) {
			  break;
			}
		}

		  // error if too few clusters in FAT32 volume
		if (nc < 65525)
		{
			#ifdef SD_DEBUG
			USB.println(F("Bad cluster count"));
			#endif
		}
		reservedSectors = dataStart - relSector - 2 * fatSize;
		fatStart = relSector + reservedSectors;
		partSize = nc * sectorsPerCluster + dataStart - relSector;
		// type depends on address of end sector
		// max CHS has lbn = 16450560 = 1024*255*63
		if ((relSector + partSize) <= 16450560) {
		// FAT32
		partType = 0X0B;
		} else {
		// FAT32 with INT 13
		partType = 0X0C;
		}

		// write MBR
		/*start writeMbr()*/
		/*start clearCache(true)*/
		memset(&cache, 0, sizeof(cache));
		cache.mbr.mbrSig0 = BOOTSIG0;
		cache.mbr.mbrSig1 = BOOTSIG1;
		/*end clearCache(true)*/
		part_t* p = cache.mbr.part;
		p->boot = 0;
		// get cylinder number for a logical block number
		//~ uint16_t c = lbnToCylinder(relSector);
		uint16_t c = relSector / (numberOfHeads * sectorsPerTrack);
		if (c > 1023)
		{
			#ifdef SD_DEBUG
			USB.println(F("error MBR CHS"));
			#endif
			return 0;
		}
		p->beginCylinderHigh = c >> 8;
		p->beginCylinderLow = c & 0XFF;
		//get head number for a logical block number
		//~ p->beginHead = lbnToHead(relSector);
		p->beginHead = (relSector % (numberOfHeads * sectorsPerTrack)) / sectorsPerTrack;
		//get sector number for a logical block number
		//~ p->beginSector = lbnToSector(relSector);
		p->beginSector = (relSector % sectorsPerTrack) + 1;
		p->type = partType;
		uint32_t endLbn = relSector + partSize - 1;
		//get cylinder number for a logical block number
		//~ c = lbnToCylinder(endLbn);
		c = endLbn / (numberOfHeads * sectorsPerTrack);
		if (c <= 1023) {
			p->endCylinderHigh = c >> 8;
			p->endCylinderLow = c & 0XFF;
			//get head number for a logical block number
			//~ p->endHead = lbnToHead(endLbn);
			p->endHead = (endLbn % (numberOfHeads * sectorsPerTrack)) / sectorsPerTrack;
			//get sector number for a logical block number
			//~ p->endSector = lbnToSector(endLbn);
			p->endSector = (endLbn % sectorsPerTrack) + 1;
			//get sector number for a logical block number
			//~ p->endSector = lbnToSector(endLbn);
			p->endSector = (endLbn % sectorsPerTrack) + 1;
		} else {
			// Too big flag, c = 1023, h = 254, s = 63
			p->endCylinderHigh = 3;
			p->endCylinderLow = 255;
			p->endHead = 254;
			p->endSector = 63;
		}
		p->firstSector = relSector;
		p->totalSectors = partSize;
		//~ if (!writeCache(0))
		if (!card.writeBlock(0, cache.data))
		{
			#ifdef SD_DEBUG
			USB.println(F("error write MBR"));
			#endif
			return 0;
		}

		/*start clearCache(true)*/
		memset(&cache, 0, sizeof(cache));
		cache.mbr.mbrSig0 = BOOTSIG0;
		cache.mbr.mbrSig1 = BOOTSIG1;
		/*end clearCache(true)*/

		fat32_boot_t* pb = &cache.fbs32;
		pb->jump[0] = 0XEB;
		pb->jump[1] = 0X00;
		pb->jump[2] = 0X90;
		for (uint8_t i = 0; i < sizeof(pb->oemId); i++) {
		pb->oemId[i] = ' ';
		}
		pb->bytesPerSector = 512;
		pb->sectorsPerCluster = sectorsPerCluster;
		pb->reservedSectorCount = reservedSectors;
		pb->fatCount = 2;
		pb->mediaType = 0XF8;
		pb->sectorsPerTrack = sectorsPerTrack;
		pb->headCount = numberOfHeads;
		pb->hidddenSectors = relSector;
		pb->totalSectors32 = partSize;
		pb->sectorsPerFat32 = fatSize;
		pb->fat32RootCluster = 2;
		pb->fat32FSInfo = 1;
		pb->fat32BackBootBlock = 6;
		pb->driveNumber = 0X80;
		pb->bootSignature = EXTENDED_BOOT_SIG;
		//pb->volumeSerialNumber = volSerialNumber();
		pb->volumeSerialNumber = (cardSizeBlocks << 8) + millis();
		memcpy(pb->volumeLabel, noName, sizeof(pb->volumeLabel));
		memcpy(pb->fileSystemType, fat32str, sizeof(pb->fileSystemType));

		// write partition boot sector and backup
		//if (!card.writeBlock(0, cache.data) || !writeCache(relSector + 6))
		if(	!card.writeBlock(relSector, cache.data) ||
			!card.writeBlock(relSector + 6, cache.data) )
		{
			#ifdef SD_DEBUG
			USB.println(F("FAT32 write PBS failed"));
			#endif
		}
		/*start clearCache(true)*/
		memset(&cache, 0, sizeof(cache));
		cache.mbr.mbrSig0 = BOOTSIG0;
		cache.mbr.mbrSig1 = BOOTSIG1;
		/*end clearCache(true)*/

		// write extra boot area and backup
		//if (!writeCache(relSector + 2) || !writeCache(relSector + 8))
		if(	!card.writeBlock(relSector + 2, cache.data) ||
			!card.writeBlock(relSector + 8, cache.data) )
		{
			#ifdef SD_DEBUG
			USB.println(F("FAT32 PBS ext failed"));
			#endif
		}
		fat32_fsinfo_t* pf = &cache.fsinfo;
		pf->leadSignature = FSINFO_LEAD_SIG;
		pf->structSignature = FSINFO_STRUCT_SIG;
		pf->freeCount = 0XFFFFFFFF;
		pf->nextFree = 0XFFFFFFFF;

		// write FSINFO sector and backup
		//if (!writeCache(relSector + 1) || !writeCache(relSector + 7))
		if(	!card.writeBlock(relSector + 1, cache.data) ||
			!card.writeBlock(relSector + 7, cache.data) )
		{
			#ifdef SD_DEBUG
			USB.println(F("FAT32 FSINFO failed"));
			#endif
		}
		//clearFatDir(fatStart, 2 * fatSize + sectorsPerCluster);

		// clear FAT and root directory
		/* start clearFatDir(fatStart, dataStart - fatStart);*/
		/*start clearCache(false)*/
		memset(&cache, 0, sizeof(cache));
		/*end clearCache(false)*/
		if (!card.writeStart(fatStart, 2 * fatSize + sectorsPerCluster)) {
			#ifdef SD_DEBUG
			USB.println(F("Clear FAT/DIR writeStart failed"));
			#endif
			return 0;
		}
		for (uint32_t i = 0; i < 2 * fatSize + sectorsPerCluster; i++)
		{
			if ((i & 0XFF) == 0)
			{
				#ifdef SD_DEBUG
				USB.print(F("."));
				#endif
			}
			if (!card.writeData(cache.data))
			{
				#ifdef SD_DEBUG
				USB.println(F("Clear FAT/DIR writeData failed"));
				#endif
				return 0;
			}
		}
		if (!card.writeStop())
		{
			#ifdef SD_DEBUG
			USB.println(F("Clear FAT/DIR writeStop failed"));
			#endif
			return 0;
		}
		#ifdef SD_DEBUG
		USB.println();
		#endif
		/* end clearFatDir(fatStart, dataStart - fatStart);*/

		/*start clearCache(false)*/
		memset(&cache, 0, sizeof(cache));
		/*end clearCache(false)*/
		cache.fat32[0] = 0x0FFFFFF8;
		cache.fat32[1] = 0x0FFFFFFF;
		cache.fat32[2] = 0x0FFFFFFF;

		// write first block of FAT and backup for reserved clusters
		//if (!writeCache(fatStart) || !writeCache(fatStart + fatSize))
		if(	!card.writeBlock(fatStart, cache.data) ||
			!card.writeBlock(fatStart + fatSize, cache.data) )
		{
			#ifdef SD_DEBUG
			USB.println(F("FAT32 reserve failed"));
			#endif
		}
	}
	// print info
	#ifdef SD_DEBUG
	USB.print(F("partStart: "));   USB.println(relSector,DEC);
	USB.print(F("partSize: "));    USB.println(partSize,DEC);
	USB.print(F("reserved: "));    USB.println(reservedSectors,DEC);
	USB.print(F("fatStart: "));    USB.println(fatStart,DEC);
	USB.print(F("fatSize: "));     USB.println(fatSize,DEC);
	USB.print(F("dataStart: "));   USB.println(dataStart,DEC);
	USB.print(F("clusterCount: "));USB.println( (relSector + partSize - dataStart)/sectorsPerCluster,DEC);
	USB.println();
	USB.print(F("Heads: "));       USB.println(int(numberOfHeads),DEC);
	USB.print(F("Sectors: "));     USB.println(int(sectorsPerTrack),DEC);
	USB.print(F("Cylinders: "));   USB.println(cardSizeBlocks/(numberOfHeads*sectorsPerTrack),DEC);

	USB.print(F("Format done\n"));
	#endif

	return 1;
}



// Private Methods /////////////////////////////////////////////////////////////


/*
 * setFileDate() -
 *
 * Set the proper Date and Time for creating directories and files
 */
void WaspSD::setFileDate()
{
	// Get the 5V and 3V3 power supply actual state
	bool set5V = WaspRegister & REG_5V;
	bool set3V3 = WaspRegister & REG_3V3;

	// Get RTC data for creation time and date
	// It is necessary to switch on the power supply if any Sensor Board is
	// connected to Waspmote so as not to cause intereferences in the I2C bus
	PWR.setSensorPower(SENS_5V,SENS_ON);
	PWR.setSensorPower(SENS_3V3,SENS_ON);

	// update RTC attributes
	if (RTC.isON == 0)
	{
		RTC.ON();
	}
	RTC.getTime();

	if( !set3V3 )
	{
		PWR.setSensorPower(SENS_3V3,SENS_OFF);
	}
	if( !set5V )
	{
		PWR.setSensorPower(SENS_5V,SENS_OFF);
	}

	// set date time callback function
	SdFile::dateTimeCallback(dateTime);

}


/*
 * showFile() -
 *
 * Print out the contents of the whole input file
 */
void WaspSD::showFile(char* filepath)
{
	int32_t size = SD.getFileSize(filepath);
	int32_t block = 128;
	int32_t nL = size / block;
	int32_t nR = size % block;
	int32_t index = 0;

	// show file
	USB.println(F("\n-------------------"));
	USB.secureBegin();

	for(int32_t i=0 ; i<nL ; i++)
	{
		SD.cat(filepath, index, block);

		for (int j = 0; j < block; j++)
		{
			printByte(SD.buffer[j], 0);
		}
		index += block ;
	}

	SD.cat(filepath, index, nR);
	for (int j = 0; j < nR; j++)
	{
		printByte(SD.buffer[j], 0);
	}

	USB.secureEnd();
	USB.println(F("\n-------------------"));
}



/*
 * showSD() -
 *
 * Display the contents of the selected SD card folder o file
 */
void WaspSD::menu(uint32_t timeout)
{
	uint32_t previous;
	char option;
	int i = 0;
	char filename[20];

	// init SD card
	SD.ON();
	SD.goRoot();

	// check if the card is there or not
	if (!SD.isSD())
	{
		USB.println(F("No SD card inserted"));
		return (void)0;
	}

	// get current time
	previous = millis();

	do
	{
		USB.println(F("\r\n------------------------- MENU -------------------------"));
		USB.println(F("1: List files in current working directory"));
		USB.println(F("2: Show file"));
		USB.println(F("3: Change directory"));
		USB.println(F("4: Go to Root directory"));
		USB.println(F("9: Format SD"));
		USB.println(F("--------------------------------------------------------"));

		USB.print(F("\n==> Enter numeric option:"));
		USB.flush();

		// wait for incoming data from keyboard
		while (!USB.available() && (millis()-previous < timeout));

		// parse incoming bytes
		if (USB.available() > 0)
		{
			previous = millis();

			// get option number
			option = USB.read();
			USB.println(option);
			USB.flush();

			switch (option)
			{
				case '1':
						SD.ls(LS_DATE | LS_SIZE | LS_R);
						previous = millis();
						break;

				case '2':
						// init vars
						i = 0;
						previous = millis();
						memset(filename, 0x00, sizeof(filename));
						USB.print(F("==> Enter name of file to read:"));

						// wait for incoming data from keyboard
						while (!USB.available() && (millis()-previous < timeout));
						while (USB.available() > 0)
						{
							filename[i] = USB.read();
							i++;
							if (i >= sizeof(filename))
							{
								break;
							}
						}
						USB.println(filename);
						SD.showFile(filename);
						previous = millis();
						break;

				case '3':
						// init vars
						i = 0;
						previous = millis();
						memset(filename, 0x00, sizeof(filename));
						USB.print(F("==> Enter name of directory to change to:"));

						// wait for incoming data from keyboard
						while (!USB.available() && (millis()-previous < timeout));
						while (USB.available() > 0)
						{
							filename[i] = USB.read();
							i++;
							if (i >= sizeof(filename))
							{
								break;
							}
						}
						USB.println(filename);
						SD.cd(filename);
						previous = millis();
						break;

				case '4':
						SD.goRoot();
						previous = millis();
						break;

				case '9':
						SD.format();
						previous = millis();
						break;
				default:
						break;

			}
		}

		// Condition to avoid an overflow (DO NOT REMOVE)
		if (millis() < previous) previous = millis();

	} while (millis()-previous < timeout);

	USB.println();

}


// Preinstantiate Objects //////////////////////////////////////////////////////

WaspSD SD = WaspSD();
