// ----------------------------------------------------------------------------
//         ATMEL Crypto-Devices Software Support  -  Colorado Springs, CO -
// ----------------------------------------------------------------------------
// DISCLAIMER:  THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
// DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
// OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// ----------------------------------------------------------------------------

/** \file
 *  \brief Header file for aes132.c.
 *  \author Atmel Crypto Products
 *  \date  June 08, 2015
 */

#ifndef AES132_H_
#define AES132_H_

#include <stdint.h>
#include "aes132_i2c.h"

#ifdef __cplusplus
extern "C"
{
#endif

//~ #ifdef AES132_I2C
//~ #   include "aes132_i2c.h"
//~ #elif AES132_SPI
//~ #   include "aes132_spi.h"
//~ #else
//~ #   error You have to define either AES132_I2C or AES132_SPI.
//~ #endif


/** \brief These enumerations are used as arguments
 *         when calling aes132m_access_memory(). */
enum aes132_read_write_flag {
	AES132_WRITE = (uint8_t) 0,         //!< write flag
	AES132_READ  = (uint8_t) 1          //!< read flag
};


/** \brief These enumerations are used as arguments
 *         when calling aes132c_wait_for_status_register_bit(). */
enum aes132_bit_set_flag {
	AES132_BIT_CLEARED = (uint8_t) 0,   //!< bit cleared flag
	AES132_BIT_SET     = (uint8_t) 1    //!< bit set flag
};

// ------------------------ timing definitions -----------------------------------

//! Poll this many ms for the device being ready for access.
#define AES132_DEVICE_READY_TIMEOUT      (100)

/** \brief Poll this many ms for the response buffer being ready for reading.
 *
 * When adjusting this number, consider the command execution delays used.
 * As these delays lie closer to or farther from the minimum command execution
 * delays, this number has to be made bigger or smaller accordingly. With other
 * words: The earlier we start polling after sending a command,
 * the longer we have to make the wait-for-response-ready time-out.
 */
#define AES132_RESPONSE_READY_TIMEOUT     (145) // Biggest response timeout is the one for the TempSense command (in ms).


// ----------------------- definitions for retry counts -----------------------------

//! number of retries for sending a command, receiving a response, and accessing memory
#define AES132_RETRY_COUNT_ERROR           ((uint8_t) 2)

//! number of re-synchronization retries
#define AES132_RETRY_COUNT_RESYNC          ((uint8_t) 2)


// ------------- definitions for packet sizes --------------------

//! size of CRC
#define AES132_CRC_SIZE                    ((uint8_t)  2)

//! minimum command size
#define AES132_COMMAND_SIZE_MIN            ((uint8_t)  9)

//! maximum command size (KeyImport command)
#define AES132_COMMAND_SIZE_MAX            ((uint8_t) 63)

//! minimum response size (EncRead and Encrypt command)
#define AES132_RESPONSE_SIZE_MIN           ((uint8_t)  4)

//! maximum response size
#define AES132_RESPONSE_SIZE_MAX           ((uint8_t) 52)

//! maximum number of bytes to write to or read from memory
#define AES132_MEM_ACCESS_MAX              ((uint8_t) 32)


// ------------- definitions for device word addresses --------------------

//! word address of command / response buffer
#define AES132_IO_ADDR                     ((uint16_t) 0xFE00)

//! Write to this word address to reset the index of the command / response buffer.
#define AES132_RESET_ADDR                  ((uint16_t) 0xFFE0)

//! word address of device status register
#define AES132_STATUS_ADDR                 ((uint16_t) 0xFFF0)


// ------------- definitions for device status register bits --------------------

//! bit position of the Write-In-Progress bit (WIP) in the device status register
#define AES132_WIP_BIT                          ((uint8_t) 0x01)

//! bit position of the Write-Enabled bit in the device status register (SPI only)
#define AES132_WEN_BIT                          ((uint8_t) 0x02)

//! bit position of the power state bit in the device status register
#define AES132_WAKE_BIT                         ((uint8_t) 0x04)

//! bit position of reserved bit 3 in the device status register
#define AES132_RESERVED3_BIT                    ((uint8_t) 0x08)

//! bit position of the CRC error bit in the device status register
#define AES132_CRC_ERROR_BIT                    ((uint8_t) 0x10)

//! bit position of reserved bit 5 in the device status register
#define AES132_RESERVED5_BIT                    ((uint8_t) 0x20)

//! bit position of the CRC error bit in the device status register
#define AES132_RESPONSE_READY_BIT               ((uint8_t) 0x40)

//! bit position of bit in the device status register that indicates error
#define AES132_DEVICE_ERROR_BIT                 ((uint8_t) 0x80)


// --- definitions for device return codes (byte at index 1 of device response buffer ---

//! no error in executing a command and receiving a response, or writing data to memory
#define AES132_DEVICE_RETCODE_SUCCESS           ((uint8_t) 0x00)

//! error when crossing a page or key boundary for a Write, BlockRead or EncRead
#define AES132_DEVICE_RETCODE_BOUNDARY_ERROR    ((uint8_t) 0x02)

//! Access to the specified User Zone is not permitted due to the current configuration or internal state.
#define AES132_DEVICE_RETCODE_RW_CONFIG         ((uint8_t) 0x04)

//! Address is not implemented, or address is illegal for this command, or attempted to write locked memory.
#define AES132_DEVICE_RETCODE_BAD_ADDR          ((uint8_t) 0x08)

//! Counter limit reached, or count usage error, or restricted key error.
#define AES132_DEVICE_RETCODE_COUNT_ERROR       ((uint8_t) 0x10)

//! no nonce available, or nonce invalid, or nonce does not include a random source, or MacCount limit has been reached
#define AES132_DEVICE_RETCODE_NONCE_ERROR       ((uint8_t) 0x20)

//! Authorization MAC input is missing, or MAC compare failed.
#define AES132_DEVICE_RETCODE_MAC_ERROR         ((uint8_t) 0x40)

//! bad opcode, bad mode, bad parameter, invalid length, or other encoding failure
#define AES132_DEVICE_RETCODE_PARSE_ERROR       ((uint8_t) 0x50)

//! EEPROM post-write automatic data verification failed due to data mismatch.
#define AES132_DEVICE_RETCODE_DATA_MISMATCH     ((uint8_t) 0x60)

//! Lock command contained bad checksum or bad MAC.
#define AES132_DEVICE_RETCODE_LOCK_ERROR        ((uint8_t) 0x70)

/** \brief Key is not permitted to be used for this operation,
 *         or wrong key was used for operation,
 *         or prior authentication has not been performed,
 *         or other authentication error,
 *         or other key error has occurred.
 */
#define AES132_DEVICE_RETCODE_KEY_ERROR         ((uint8_t) 0x80)

//! temperature sensor timeout error
#define AES132_DEVICE_RETCODE_TEMP_SENSE_ERROR  ((uint8_t) 0x90)


// ------------- definitions for option flags used when sending a command --------

//! default flags for option parameter
#define AES132_OPTION_DEFAULT                   ((uint8_t) 0x00)

/** \brief flag for option parameter that indicates whether or not to
 *         calculate and append a CRC.
 */
#define AES132_OPTION_NO_APPEND_CRC             ((uint8_t) 0x01)

/** \brief flag for option parameter that indicates whether or not to
 *         read the device status register after sending a command.
 */
#define AES132_OPTION_NO_STATUS_READ            ((uint8_t) 0x02)


// ----- definitions for byte indexes of command buffer --------

//! count at index 0 (1 byte)
#define AES132_COMMAND_INDEX_COUNT              (0)

//! op-code at index 1 (1 byte)
#define AES132_COMMAND_INDEX_OPCODE             (1)

//! mode at index 2 (1 byte)
#define AES132_COMMAND_INDEX_MODE               (2)

//! msb of param1 (2 bytes) at index 3
#define AES132_COMMAND_INDEX_PARAM1_MSB         (3)

//! lsb of param1 (2 bytes) at index 4
#define AES132_COMMAND_INDEX_PARAM1_LSB         (4)

//! msb of param2 (2 bytes) at index 5
#define AES132_COMMAND_INDEX_PARAM2_MSB         (5)

//! msb of param2 (2 bytes) at index 5
#define AES132_COMMAND_INDEX_PARAM2_LSB         (6)


// ----- definitions for Standby and Sleep modes --------

//! value of mode byte for the Sleep command to put device into Sleep mode
#define AES132_COMMAND_MODE_SLEEP               ((uint8_t) 0x00)

//! value of mode byte for the Sleep command to put device into Standby mode
#define AES132_COMMAND_MODE_STANDBY             ((uint8_t) 0x40)


// ----- definitions for byte indexes of response buffer --------

//! count at index 0 (1 byte)
#define AES132_RESPONSE_INDEX_COUNT             ((uint8_t)    0)

//! response return code at index 1 (1 byte)
#define AES132_RESPONSE_INDEX_RETURN_CODE       ((uint8_t)    1)

//! Response data start at index 2 (1 or more bytes).
#define AES132_RESPONSE_INDEX_DATA              ((uint8_t)    2)




uint8_t aes132c_access_memory(uint8_t count, uint16_t word_address, uint8_t *data, uint8_t read);
uint8_t aes132c_read_device_status_register(uint8_t *deviceStatus);
uint8_t aes132c_send_command(uint8_t *command, uint8_t options);
uint8_t aes132c_receive_response(uint8_t count, uint8_t *response);
uint8_t aes132c_send_and_receive(uint8_t *command, uint8_t size, uint8_t *response, uint8_t options);
uint8_t aes132c_wakeup(void);
uint8_t aes132c_sleep(void);
uint8_t aes132c_standby(void);
uint8_t aes132c_resync(void);
uint8_t aes132c_wait_for_status_register_bit(uint8_t mask, uint8_t is_set, uint16_t n_retries);
uint8_t aes132c_wait_for_response_ready(void);
uint8_t aes132c_wait_for_device_ready(void);
uint8_t aes132c_send_sleep_command(uint8_t standby);
uint8_t aes132c_reset_io_address(void);
void    aes132c_calculate_crc(uint8_t count, uint8_t *data, uint8_t *crc);

#ifdef __cplusplus
}
#endif


#endif
