/*! \file WaspSD.h
    \brief Library for managing the SD Card

    Copyright (C) 2018 Libelium Comunicaciones Distribuidas S.L.
    http://www.libelium.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Version:		3.1
    Design:			David Gascón
    Implementation:	David Cuartielles, Alberto Bielsa, Yuri Carmona
*/



 /*! \def WaspSD_h
    \brief The library flag

  */
#ifndef WaspSD_h
#define WaspSD_h

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <inttypes.h>

// Include FAT16 libraries/utilities
#include <sd_utilities/Sd2Card.h>
#include <sd_utilities/SdVolume.h>
#include <sd_utilities/SdFile.h>
#include <sd_utilities/SdFat.h>
#include <sd_utilities/SdInfo.h>

/*******************************************************************************
 * Definitions & Declarations
 ******************************************************************************/

/*! \def SD_DEBUG
    \brief Uncomment this definition to enable the DEBUG mode in some functions
*/
//~ #define SD_DEBUG
#define PRINT_SD(str)	USB.print(F("[SD] ")); USB.print(str);
#define PRINTLN_SD(str)	USB.print(F("[SD] ")); USB.println(str);

/*! \def FILESYSTEM_LINUX
    \brief determines the type of EOL character, uncomment for Windows, leave for LIN/MAC
*/
#define FILESYSTEM_LINUX

/*! \def DOS_BUFFER_SIZE
    \brief Buffer size for storing data
*/
/*! \def BIN_BUFFER_SIZE
    \brief Buffer size for storing binary data
 */
#define DOS_BUFFER_SIZE 256
#define	BIN_BUFFER_SIZE	100


/*! \def NOTHING_FAILED
    \brief Flag possible values. Nothing failed in this case
 */
/*! \def CARD_NOT_PRESENT
    \brief Flag possible values. Card not present in this case
 */
/*! \def INIT_FAILED
    \brief Flag possible values. Initialization failed in this case
 */
/*! \def VOLUME_FAILED
    \brief Flag possible values. Volume init failed in this case
 */
/*! \def ROOT_FAILED
    \brief Flag possible values. Opening root directory failed in this case
 */
/*! \def TRUNCATED_DATA
    \brief Flag possible values. Data has been truncated in this case
 */
/*! \def FILE_OPEN_ERROR
    \brief Flag possible values. Opening a file failed in this case
 */
/*! \def FILE_CREATION_ERROR
    \brief Flag possible values. Creating a file failed in this case
 */
/*! \def DIR_CREATION_ERROR
    \brief Flag possible values. Creating a directory failed in this case
 */
/*! \def FILE_WRITING_ERROR
    \brief Flag possible values. Writing a file failed in this case
 */

#define NOTHING_FAILED 		0
#define CARD_NOT_PRESENT 	1
#define INIT_FAILED 		2
#define VOLUME_FAILED 		4
#define ROOT_FAILED 		8
#define TRUNCATED_DATA 		16
#define FILE_OPEN_ERROR 	32
#define FILE_CREATION_ERROR 64
#define DIR_CREATION_ERROR 	128
#define FILE_WRITING_ERROR 	256
#define FILE_SEEKING_ERROR 	512

/*! \def CARD_NOT_PRESENT_em
    \brief Flag possible values. Card not present in this case
 */
#define CARD_NOT_PRESENT_em "no SD"


/*! \def SD_ON
    \brief SD Power Modes. ON in this case
 */
/*! \def SD_OFF
    \brief SD Power Modes. OFF in this case
 */
#define	SD_ON	1
#define	SD_OFF	2


/*! \def MAX_COMPONENT_LEN
    \brief Used in `getNextPathComponent` function as maximum length
 */
/*! \def PATH_COMPONENT_BUFFER_LEN
    \brief Maximum length for path buffer
 */
#define MAX_COMPONENT_LEN 			50
#define PATH_COMPONENT_BUFFER_LEN 	MAX_COMPONENT_LEN+1


/******************************************************************************
 * Class
 ******************************************************************************/

//! WaspSD Class
/*!
	WaspSD Class defines all the variables and functions used to manage the SD Card
 */
class WaspSD
{

private:


	//! Variable : volume is used as volume to open the SD card
	/*!
	*/
	SdVolume volume;

	//! Variable : root is used for SD card's root directory file
	/*!
	*/
	void setFileDate();


public:

	/***************************************************************************
	* Class Attributes
	***************************************************************************/

	//! Variable : root is used for SD card's root directory file
	/*!
	*/
	SdFile root;

	//! Variable : buffer containing the information coming from the
	//! card used to avoid calls to UART functions inside the library.
	//! Beware, there could be data longer than the buffer size
	/*!
	*/
	char buffer[DOS_BUFFER_SIZE];

	//! Variable : buffer containing the binary information coming from
	//! the card used to avoid calls to UART functions inside the library.
	//! Beware, there could be data longer than the buffer size
	/*!
	*/
	uint8_t bufferBin[BIN_BUFFER_SIZE];

	//! Variable : flag storing the state of the SD card during initialization
	//! and operation
	/*!
	*/
	uint16_t flag;

	//! Variable : total byte size of the drive
	/*!
	 */
	uint32_t diskSize;

	//! Variable : object to the SD card
  	/*!
	 */
	Sd2Card card;

	//! Variable : object to the current working directory
  	/*!
	 */
	SdFile currentDir;


	/***************************************************************************
	* Constructor and methods
	***************************************************************************/

	//! class constructor
	/*!
	It does nothing
	\param void
	\return void
	*/
	WaspSD();

	//! It clears the flag
	/*!
	It does nothing
	\param void
	\return 'flag' variable
	*/
	uint16_t cleanFlags(void);


	//! It checks if there is a SD Card in the slot
	/*!
	\param void
	\return '1' if SD is present, '0' otherwise
	*/
	uint8_t isSD ();

	//! It powers the SD card, initialize it and prepare it to work with
	/*!
	\param void
	\return '1' when ok; '0' when error.
	*/
	uint8_t ON();

	//! It powers off the SD card and closes the pointers
	/*!
	\param void
	\return void
	*/
	void OFF();

	//! It initializes the use of SD cards, looks into the root partition,
	//! opens the file system and initializes the public pointer that can
	//! be used to access the filesystem
	/*!
	\param void
	\return '1' when ok; '0' when error.
	*/
	uint8_t init();

	//! It sets power mode
	/*!
	\param uint8_t mode : SD_ON or SD_OFF
	\return void
	*/
	void setMode(uint8_t mode);

	//! It packs all the data about the disk into the buffer and returns
	//! it back. The buffer will then be available and offer the data to
	//! the developers as a human-readable encoded string.
	/*!
	\param void
	\return human readable string indicating success or possible errors
	that can be printed by the user directly
	*/
	char* print_disk_info();

	//! It gets the total disk size
	/*!
	\param void
	\return the total size for the disk
	*/
	uint32_t getDiskSize();

	//! It changes the current working directory
	/*!
	\param const char* dirpath : path to the directory we want to change to
	\return '1' on success, '0' if error
	*/
	uint8_t cd(const char* dirpath);

	//! It changes the current directory to the root directory
	/*!
	\param void
	\return '1' on success, '0' if error
	\sa cd(const char* dirpath)
	*/
	uint8_t goRoot();

	//! It gets the amount of files in a directory
	/*!
	\param void
	\return '0' if no files, a negative value if error and a possitive value
	indicating the amount of files
	*/
	int8_t numFiles();

	//! It prints the current working directory's contents
	/*!
	\param void
	\return void
	*/
	void ls(void);

	//! It prints the working directory indicating flags
	/*!
	\param uint8_t flags: The inclusive OR of:
							LS_DATE - Print file modification date
							LS_SIZE - Print file size
							LS_R - Recursive list of subdirectories
	\return void
	*/
	void ls(uint8_t flags);

	//! It tests the existence of files in the current directory
	/*! It is possible to introduce the complete path of the file
	\param const char* filepath : the file to find
	\return '1' if the file is availabe, '0' otherwise
	*/
	uint8_t find_file_in_dir(const char* filepath);

	//! It creates a directory
	/*!
	\param const char* filepath : the directory to create
	\return '1' on success, '0' otherwise
	\remarks only short 8.3 names are valid!
	\remarks Be careful when calling this function to create a directory
	for the first time. If it is interrupted, the directory results damaged
	and it is necessary to delete it as a regular file using SD.del
	*/
	boolean mkdir(char *filepath);

	//! It checks if an entry is a file or a directory
	/*!
	\param SdFile* dir : pointer to the previously opened file
	\return '1' if it is a directory, '0' otherwise
	\sa isDir(const char* dirname)
	*/
	uint8_t isDir(SdFile* dir);

	//! It checks if an entry is a file or a directory
	/*!
	\param const char* dirpath : the entry to check
	\return '1' if it is a directory, '0' otherwise
	\sa isDir(SdFile* dir)
	*/
	int8_t isDir(const char* dirpath);

	//! It deletes a file
	/*!	It allows erasing a file inside the current working directory. Besides,
	it is possible to delete a file iterating through directories
	\param const char* filepath : the path to the file to delete
	\return '1' on success, '0' otherwise
	\note This function should not be used to delete the 8.3 version of a
	file that has a long name.
	*/
	boolean del(const char* filepath);

	//! It deletes a directory
	/*!	It is possible to delete a directory iterating through directories
	It is not possible to delete the directory in case it is not empty.
	\param const char* dirpath : the path to the directory to delete
	\return '1' on success, '0' otherwise
	\note This function should not be used to delete the 8.3 version of a
	directory that has a long name.
	*/
	boolean rmdir(const char* dirpath);

	//! It deletes a directory and all contained files
	/*!
	\param const char* dirpath : the path to the file to delete
	\return '1' on success, '0' otherwise
	\note This function should not be used to delete the 8.3 version of a
	directory that has a long name.
	*/
	boolean rmRfDir(const char* dirpath);

	//! It opens a file if available
	/*! It is possible to open a file iterating through directories. So a valid
	filename path can be open. i.e. "/folder/dir/file1"
	\param const char* filepath : name of the file to open
	\param file : pointer to the opened file
	\param mode : opening mode.  This flag is constructed by a bitwise-inclusive
	OR of flags from the following list:
		O_READ - Open for reading
		O_RDONLY - Same as O_READ
		O_WRITE - Open for writing
		O_WRONLY - Same as O_WRITE
		O_RDWR - Open for reading and writing
		O_APPEND - If set, the file offset shall be set to the end of the
				file prior to each write
		O_CREAT - If the file exists, this flag has no effect except as
				noted under O_EXCL below. Otherwise, the file shall be created
		O_EXCL - If O_CREAT and O_EXCL are set, open() shall fail if the
				file exists
		O_SYNC - Call sync() after each write.  This flag should not be
				used with write(uint8_t), write_P(PGM_P), writeln_P(PGM_P), or
				the Arduino Print class. These functions do character at a time
				writes so sync() will be called after each byte.
		O_TRUNC - If the file exists and is a regular file, and the file is
				successfully opened and is not read only, its length shall be
				truncated to 0.
	\return '1' on success, '0' otherwise
	*/
	uint8_t openFile(const char* filepath, SdFile* file, uint8_t mode);

	//! It gets the parent directory of a filepath
	/*!
	This function is a little helper used to traverse paths.
	Answers the object SdFile which is related to the parent directory
	of a path specified in 'filepath'
	\param filepath : path to the file whose parent directory is the one we need
	\param index : output variable which means the index from the beginning of
	the path to the parent directory
	\return '1' on success, '0' otherwise
	*/
	SdFile getParentDir(const char *filepath, int *index);

	//! It gets the directory we need
	/*!
	\param filepath : path to the directory we need
	\return '1' on success, '0' otherwise
	*/
	SdFile getDir(const char *filepath, int *index);

	//! It closes a file
	/*!
	\param file : pointer to the file to close
	\return '1' on success, '0' otherwise
	*/
	uint8_t closeFile(SdFile* file);

	//! It tests the existence of a file in the current folder
	/*! It is possible to introduce the filepath and iterate through directories
	so as to check the existence of the file
	\param const char* filepath : the file to check
	\return '1' on success, '0' if it is a directory, '-1' otherwise
	*/
	int8_t isFile(const char* filepath);

	//! It gets the amount of lines in a file
	/*!
	\param const char* filepath : path to the file we want to check
	\return number of lines on success, '-1' otherwise
	*/
	int32_t numln (const char* filepath);

	//! It gets the file size for filepath in the current folder
	/*!
	\param const char* filepath : path to the file we want to check
	\return file size on success, '-1' otherwise
	*/
	int32_t getFileSize(const char* filepath);

	//! It dumps into the buffer the amount of bytes in scope after offset
	//! coming from filepath
	/*!
	There is a limitation in size, due to DOS_BUFFER_SIZE. If the data
	read was bigger than that, the function will include the characters
	">>" at the end and activate the TRUNCATED_DATA value in the SD.flag.
	It is recommened to check this value to assure data integrity.
	\param const char* filepath : path to the file to get the data from
	\param int32_t offset : amount of bytes to jump before start dumping the
	data to the buffer
	\param uint16_t scope : amount of bytes for dumping to the buffer
	\return 'buffer' variable where the data has been dumped
	\sa catBin (const char* filepath, int32_t offset, uint16_t scope)
	\sa catln (const char* filepath, uint32_t offset, uint16_t scope)
	*/
	char* cat (const char* filepath, int32_t offset, uint16_t scope);

	//! It dumps into the bufferBin the amount of bytes in scope after offset
	//! coming from filepath
	/*!
	\param const char* filepath : path to the file to get the data from
	\param int32_t offset : amount of bytes to jump before start dumping the
	data to the buffer
	\param uint16_t scope : amount of bytes for dumping to the buffer
	\return 'bufferBin' variable where the data has been dumped
	\sa cat (const char* filepath, int32_t offset, uint16_t scope)
	\sa catln (const char* filepath, uint32_t offset, uint16_t scope)
	*/
	uint8_t* catBin (const char* filepath, int32_t offset, uint16_t scope);

	//! It dumps into the buffer the amount of lines in scope after offset
	//! lines coming from filepath
	/*!
	There is a limitation in size, due to DOS_BUFFER_SIZE. If the data
	read was bigger than that, the function will include the characters
	">>" at the end and activate the TRUNCATED_DATA value in the SD.flag.
	It is recommened to check this value to assure data integrity.
	\param const char* filepath : path to the file to get the data from
	\param uint32_t offset : amount of lines to jump before start dumping data
	to the buffer
	\param uint16_t scope : amount of lines for dumping to the buffer
	\return 'buffer' variable where the data has been dumped
	\sa cat (const char* filepath, int32_t offset, uint16_t scope)
	\sa catBin (const char* filepath, int32_t offset, uint16_t scope)
	*/
	char* catln (const char* filepath, uint32_t offset, uint16_t scope);

	//! It searches for first occurrence of a string in a file
	/*!
	\param const char* filepath : path to the file where looking for the pattern
	\param const char* pattern : pattern to find
	\param uint32_t offset : amount of bytes to jump before start looking for
	the pattern
	\return the amount of bytes to the pattern from the offset
	*/
	int32_t indexOf (const char* filepath, const char* pattern, uint32_t offset);

	//! It creates a file
	/*!
	\param const char* filepath : path to the file to create
	\return '1' on success, '0' otherwise
	*/
	uint8_t create(const char* filepath);

	//! It writes strings to a file
	/*!
	\param const char* filepath : the file to write to
	\param const char* str : the string to write into the file
	\param int32_t offset : amount of bytes to jump before start writing the string
	\return '1' on success, '0' otherwise
	\sa writeSD(const char* filepath, uint8_t* str, int32_t offset)
	*/
	uint8_t writeSD(const char* filepath, const char* str, int32_t offset);

	//! It writes strings to a file of a specific length
	/*!
	\param const char* filepath : the file to write to
	\param const char* str : the string to write into the file
	\param int32_t offset : amount of bytes to jump before start writing the
	string
	\param int16_t length : amount of bytes to write to the file
	\return '1' on success, '0' otherwise
	\sa writeSD(const char* filepath, const char* str, int32_t offset, int16_t length)
	*/
	uint8_t writeSD(const char* filepath, const char* str, int32_t offset, uint16_t length);

	//! It writes integer array to a file
	/*!
	\param const char* filepath : the file to write to
	\param uint8_t* str : the integer array to write into the file
	\param int32_t offset : amount of bytes to jump before start writing the string
	\return '1' on success, '0' otherwise
	\sa writeSD(const char* filepath, const char* str, int32_t offset)
	*/
	uint8_t writeSD(const char* filepath, uint8_t* str, int32_t offset);

	//! It writes integer array to a file indicating the length of the array
	/*!
	\param const char* filepath : the file to write to
	\param uint8_t* str : the integer array to write into the file
	\param int32_t offset : amount of bytes to jump before start writing the string
	\return '1' on success, '0' otherwise
	\sa writeSD(const char* filepath, const char* str, int32_t offset)
	*/
	uint8_t writeSD(const char* filepath, uint8_t* str, int32_t offset, uint16_t length);

	//! It writes strings at the end of files
	/*!
	\param const char* filepath : the file to write to
	\param const char* str : the string to write into the file
	\return '1' on success, '0' otherwise
	\sa writeSD(const char* filepath, const char* str, int32_t offset)
	*/
	uint8_t append(const char* filepath, const char* str);

	//! It writes strings at the end of files of a specific length
	/*!
	\param const char* filepath : the file to write to
	\param const char* str : the string to write into the file
	\param uint16_t length : the length to write
	\return '1' on success, '0' otherwise
	\sa writeSD(const char* filepath, const char* str, int32_t offset, uint16_t length)
	*/
	uint8_t append(const char* filepath, const char* str, uint16_t length);

	//! It writes integer arrays at the end of files
	/*!
	\param const char* filepath : the file to write to
	\param uint8_t* str : the integer array to write into the file
	\return '1' on success, '0' otherwise
	\sa writeSD(const char* filepath, const char* str, int32_t offset)
	\sa writeSD(const char* filepath, uint8_t* str, int32_t offset)
	\sa append(const char* filepath, const char* str)
	\sa appendln(const char* filepath, const char* str)
	\sa appendln(const char* filepath, uint8_t* str)
	*/
	uint8_t append(const char* filepath, uint8_t* str);

	//! It writes integer arrays at the end of files of a specific length
	/*!
	\param const char* filepath : the file to write to
	\param uint8_t* str : the integer array to write into the file
	\param uint16_t length : the length to write
	\return '1' on success, '0' otherwise
	\sa writeSD(const char* filepath, const char* str, int32_t offset)
	\sa writeSD(const char* filepath, uint8_t* str, int32_t offset)
	\sa append(const char* filepath, const char* str)
	\sa appendln(const char* filepath, const char* str)
	\sa appendln(const char* filepath, uint8_t* str)
	*/
	uint8_t append(const char* filepath, uint8_t* str, uint16_t length);

	//! It writes integer arrays at the end of files of a specific length
	/*!End of line is added when teh first writing is done successfully
	\param const char* filepath : the file to write to
	\param uint8_t* str : the integer array to write into the file
	\param uint16_t length : the length to write
	\return '1' on success, '0' otherwise
	\sa writeSD(const char* filepath, const char* str, int32_t offset)
	\sa writeSD(const char* filepath, uint8_t* str, int32_t offset)
	\sa append(const char* filepath, const char* str)
	\sa appendln(const char* filepath, const char* str)
	\sa appendln(const char* filepath, uint8_t* str)
	*/
	uint8_t appendln(const char* filepath, uint8_t* str, uint16_t length);

	//! It writes strings at the end of files adding an EOL
	/*!
	\param const char* filepath : the file to write to
	\param const char* str : the string to write into the file
	\return '1' on success, '0' otherwise
	\sa writeSD(const char* filepath, const char* str, int32_t offset)
	\sa writeSD(const char* filepath, uint8_t* str, int32_t offset)
	\sa append(const char* filepath, const char* str)
	\sa append(const char* filepath, uint8_t* str)
	\sa appendln(const char* filepath, uint8_t* str)
	*/
	uint8_t appendln(const char* filepath, const char* str);

	//! It writes integer arrays at the end of files adding an EOL
	/*!
	\param const char* filepath : the file to write to
	\param uint8_t* str : the integer array to write into the file
	\return '1' on success, '0' otherwise
	\sa writeSD(const char* filepath, const char* str, int32_t offset)
	\sa writeSD(const char* filepath, uint8_t* str, int32_t offset)
	\sa append(const char* filepath, const char* str)
	\sa append(const char* filepath, uint8_t* str)
	\sa appendln(const char* filepath, const char* str)
	*/
	uint8_t appendln(const char* filepath, uint8_t* str);



	//! It writes an EOL in the specified file
	/*!
	\param const char* filepath : the file to write to
	\param uint8_t* str : the integer array to write into the file
	\return '1' on success, '0' otherwise
	*/
	uint8_t writeEndOfLine(const char* filepath);

	bool format();

	//! It writes all the contents of the file specified
	/*!
	\param const char* filepath : the file to read from
	\return void
	*/
	void showFile(char* filepath);

	void menu(uint32_t timeout);

};

/// END FUNCTIONS //////////////////////////////////////////////////////

extern WaspSD SD;


#endif
