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
 *  \brief  This file contains implementations of interface independent functions
 *          for the AES132 device.
 *  \author Atmel Crypto Products
 *  \date   June 08, 2015
 */

#include <stdint.h>
#include <string.h>

#include "aes132_comm.h"

/** \brief This function calculates a 16-bit CRC.
 * \param[in] length number of bytes in data buffer
 * \param[in] data pointer to data
 * \param[out] crc pointer to calculated CRC (high byte at crc[0])
 */
void aes132c_calculate_crc(uint8_t length, uint8_t *data, uint8_t *crc)
{
	uint8_t counter;
	uint8_t crc_low = 0, crc_high = 0, crc_carry;
	uint8_t poly_low = 0x05, poly_high = 0x80;
	uint8_t shift_register;
	uint8_t data_bit, crc_bit;

	for (counter = 0; counter < length; counter++) {
		for (shift_register = 0x80; shift_register > 0x00; shift_register >>= 1) {
			data_bit = (data[counter] & shift_register) ? 1 : 0;
			crc_bit = crc_high >> 7;

			// Shift CRC to the left by 1.
			crc_carry = crc_low >> 7;
			crc_low <<= 1;
			crc_high <<= 1;
			crc_high |= crc_carry;

			if ((data_bit ^ crc_bit) != 0) {
				crc_low ^= poly_low;
				crc_high ^= poly_high;
			}
		}
	}
	crc[0] = crc_high;
	crc[1] = crc_low;
}


/** \brief This function resets the command and response buffer address.
 * \return status of the operation
 */
uint8_t aes132c_reset_io_address(void)
{
	return aes132p_write_memory_physical(0, AES132_RESET_ADDR, (void *) 0);
}


/** \brief This function resynchronizes communication with the device.
 * \return status of the operation
 */
uint8_t aes132c_resync()
{
	uint8_t aes132_lib_return = aes132p_resync_physical();
	if (aes132_lib_return != AES132_FUNCTION_RETCODE_SUCCESS)
		return aes132_lib_return;

	return aes132c_reset_io_address();
}


/** \brief This function reads the device status register.
 * \param[out] device_status_register pointer to byte where the register value is stored
 * \return status of the operation
 */
uint8_t aes132c_read_device_status_register(uint8_t *device_status_register)
{
	uint8_t aes132_lib_return;
	uint8_t n_retries = AES132_RETRY_COUNT_ERROR;

	do {
		aes132_lib_return = aes132p_read_memory_physical(1, AES132_STATUS_ADDR, device_status_register);
	} while ((aes132_lib_return != AES132_FUNCTION_RETCODE_SUCCESS) && (--n_retries > 0));

	return aes132_lib_return;
}


/** \brief This function waits until a bit in the device status register is set or reset.
 *         Reading this register will wake up the device.
 * \param[in] mask contains bit pattern to wait for
 * \param[in] is_set specifies whether to wait until bit is set (#AES132_BIT_SET) or reset (#AES132_BIT_SET)
 * \param[in] n_retries 16-bit number that indicates the number of retries before stopping to poll.
 * \return status of the operation
 */
uint8_t aes132c_wait_for_status_register_bit(uint8_t mask, uint8_t is_set, uint16_t n_retries)
{
	uint8_t aes132_lib_return;
	uint8_t device_status_register;

	do {
		aes132_lib_return = aes132p_read_memory_physical(1, AES132_STATUS_ADDR, &device_status_register);
		if (aes132_lib_return != AES132_FUNCTION_RETCODE_SUCCESS)
			// The device is busy. Continue polling until "n_retries" is depleted.
			continue;

		if (is_set == AES132_BIT_SET) {
			// Wait for the mask bit(s) being set.
			if ((device_status_register & mask) == mask)
				// Mask pattern has been found in device status register. Return success.
				return aes132_lib_return;

		} else {
			// Wait for the mask bit(s) being cleared.
			if ((device_status_register & mask) == 0)
				// Mask pattern has been found in device status register. Return success.
				return aes132_lib_return;
		}

		// Device is busy, or "mask" pattern does not yet match the device status register value.
		// Continue polling.
	} while (n_retries-- > 0);

	// The mask pattern was not found in the device status register after "n_retries" polling
	// iterations. Return timeout error.
	return AES132_FUNCTION_RETCODE_TIMEOUT;
}


/** \brief This function waits for the Write-In-Progress (WIP) bit in the device status register to be cleared.
 * \return status of the operation
 */
uint8_t aes132c_wait_for_device_ready(void)
{
	return aes132c_wait_for_status_register_bit(AES132_WIP_BIT, AES132_BIT_CLEARED, AES132_RETRY_COUNT_DEVICE_READY);
}


/** \brief This function waits for the Response-Ready (RRDY) bit in the device status register to be set.
 * \ return status of the operation
 */
uint8_t aes132c_wait_for_response_ready(void)
{
	return aes132c_wait_for_status_register_bit(AES132_RESPONSE_READY_BIT, AES132_BIT_SET, AES132_RETRY_COUNT_RESPONSE_READY);
}


/** \brief This function sends a Sleep command to the device.
 * \param[in] standby mode (0: sleep, non-zero: standby)
 * \return status of the operation
 */
uint8_t aes132c_send_sleep_command(uint8_t standby)
{
	// command buffer fields:
	// <count = 0x09><op code = 0x11><mode = 0x00 (sleep)><param1 = 0x0000><param2 = 0x0000><CRC = 0x7181>
	const uint8_t command_sleep[] = {AES132_COMMAND_SIZE_MIN, 0x11, AES132_COMMAND_MODE_SLEEP, 0, 0, 0, 0, 0x71, 0x81};
	const uint8_t command_standby[] = {AES132_COMMAND_SIZE_MIN, 0x11, AES132_COMMAND_MODE_STANDBY, 0, 0, 0, 0, 0xEF, 0x82};

	// Disable reading the device status register after sending the command and disable appending the CRC.
	const uint8_t options = (AES132_OPTION_NO_APPEND_CRC | AES132_OPTION_NO_STATUS_READ);

	// We reset the IO buffer address as a precaution.
	// Since we cannot read the device status register after sending the Sleep command
	// without waking up the device again, we cannot know whether the command failed.
	uint8_t aes132_lib_return = aes132c_reset_io_address();
	if (aes132_lib_return != AES132_FUNCTION_RETCODE_SUCCESS)
		return aes132_lib_return;

	if (standby == AES132_COMMAND_MODE_SLEEP)
		return aes132c_send_command((uint8_t *) command_sleep, options);

	return aes132c_send_command((uint8_t *) command_standby, options);
}


/** \brief This function wakes up a device.
 *
 * It takes about 1.5 ms for the device to wake up when in Sleep mode, and
 * about 0.3 ms when in Standby mode.
 * \return status of the operation
 */
uint8_t aes132c_wakeup(void)
{
	return aes132c_wait_for_device_ready();
}


/** \brief This function puts a device into Sleep mode.
 * \return status of the operation
 * */
uint8_t aes132c_sleep(void)
{
	return aes132c_send_sleep_command(AES132_COMMAND_MODE_SLEEP);
}


/** \brief This function puts a device into Standby mode.
 * \return status of the operation
 * */
uint8_t aes132c_standby(void)
{
	return aes132c_send_sleep_command(AES132_COMMAND_MODE_STANDBY);
}


/** \brief This function writes to or reads from memory with retries.
 * \param[in] count number of bytes to send
 * \param[in] word_address word address
 * \param[in, out] data pointer to tx or rx data
 * \param[in] read flag indicating whether to read (#AES132_READ) or write (#AES132_WRITE)
 * \return status of the operation or response return code
 * */
uint8_t aes132c_access_memory(uint8_t count, uint16_t word_address, uint8_t *data, uint8_t read)
{
	uint8_t aes132_lib_return;

	// inner while loop
	uint8_t n_retries_memory_access;

	// outer while loop that resynchronizes communication if inner while loop got exhausted / timed out
	uint8_t n_retries_resync = AES132_RETRY_COUNT_RESYNC;

	// used to hold the return code after writing to memory (word address < AES132_IO_ADDR)
	uint8_t response_buffer[AES132_RESPONSE_SIZE_MIN];

	do {
		n_retries_memory_access = AES132_RETRY_COUNT_ERROR;

		do {
			aes132_lib_return = aes132c_wait_for_device_ready();
			if (aes132_lib_return != AES132_FUNCTION_RETCODE_SUCCESS)
				// We lost communication. Re-synchronize.
				break;

			if (read == 0) {
				// Write to the device.
				aes132_lib_return = aes132p_write_memory_physical(count, word_address, data);
				if (aes132_lib_return != AES132_FUNCTION_RETCODE_SUCCESS)
					// Communication failed. Retry.
					continue;

				// Communication succeeded.
				if	(word_address >= AES132_IO_ADDR)
					// Return success and do not read response buffer if we wrote to the I/O buffer
					// or to the address used to reset the I/O buffer index.
					return aes132_lib_return;

				// Read response buffer when writing to device memory to check for write success.
				aes132c_wait_for_response_ready();

				aes132_lib_return = aes132c_receive_response(sizeof(response_buffer), response_buffer);
				if (aes132_lib_return == AES132_FUNCTION_RETCODE_SUCCESS)
					// Reading the return code from the I/O buffer succeeded. Return the code byte.
					return response_buffer[AES132_RESPONSE_INDEX_RETURN_CODE];
				else
					// Reading the return code from the I/O buffer failed. Return the error code that
					// aes132c_receive_response returned.
					return aes132_lib_return;
			}
			else {
				// Read from the device.
				aes132_lib_return = aes132p_read_memory_physical(count, word_address, data);
				if (aes132_lib_return == AES132_FUNCTION_RETCODE_SUCCESS)
					return aes132_lib_return;
			}
			// Accessing the device failed. Retry until "n_retries_memory_access" is depleted.
		} while (--n_retries_memory_access > 0);

		// We failed to communicate with the device even after retrying.
		if (--n_retries_resync == 0)
			// We failed to communicate with the device even after re-synchronizing. Return.
			return aes132_lib_return;

		// Re-synchronize communication.
		// Do not override return value from previous call to communication function.
		(void) aes132c_resync();

		// Communication failed. Retry accessing device after having re-synchronized communication.
	} while (aes132_lib_return != AES132_FUNCTION_RETCODE_SUCCESS);

	return aes132_lib_return;
}


/** \brief This function writes a command into the I/O buffer of the device.
 *
 * The fields of the command buffer are described below:\n
 * <count, 1 byte> <op-code, 1 byte> <mode, 1 byte>
 * <param1, 2 bytes> <param2, 2 bytes> <data, n bytes (optional)> <crc, 2 bytes)>\n
 * The "count" field and size of the command buffer has to include the
 * two CRC bytes independent from the #AES132_OPTION_NO_APPEND_CRC flag in the
 * options parameter.\n
 * The function retries sending the command if the device indicates a CRC error.
 * \param[in] command pointer to command buffer
 * \param[in] options flags for communication behavior
 * \return status of the operation
 */
uint8_t aes132c_send_command(uint8_t *command, uint8_t options)
{
	uint8_t aes132_lib_return;
	uint8_t n_retries = AES132_RETRY_COUNT_ERROR;
	uint8_t device_status_register;
	uint8_t count = command[AES132_COMMAND_INDEX_COUNT];

	if ((options & AES132_OPTION_NO_APPEND_CRC) == 0)
		// Append two-byte CRC to command.
		aes132c_calculate_crc(count - AES132_CRC_SIZE, command, &command[count - AES132_CRC_SIZE]);

	do {
		aes132_lib_return = aes132c_access_memory(count, AES132_IO_ADDR, command,  AES132_WRITE);
		if (aes132_lib_return != AES132_FUNCTION_RETCODE_SUCCESS)
			// Writing to the I/O buffer failed. Retry.
			continue;

		if ((options & AES132_OPTION_NO_STATUS_READ) != 0)
			// We don't read device status register when sending a Sleep command.
			return aes132_lib_return;

		// Try to read the device status register. If it fails with an I2C nack of the I2C write address,
		// we know that the device is busy.
		aes132_lib_return = aes132c_read_device_status_register(&device_status_register);
		//aes132_lib_return = aes132p_read_memory_physical(1, AES132_STATUS_ADDR, &device_status_register);
		if (aes132_lib_return == AES132_FUNCTION_RETCODE_SUCCESS) {
			// We were able to read the device status register. Check the CRC bit.
			if ((device_status_register & AES132_CRC_ERROR_BIT) != 0)
				// The device has calculated a not-matching CRC, which indicates a flawed communication.
				// Retry sending the command.
				aes132_lib_return = AES132_FUNCTION_RETCODE_BAD_CRC_TX;
		}
		else if (aes132_lib_return == AES132_FUNCTION_RETCODE_COMM_FAIL){
			// This code block applies to I2C only. Receiving a nack to a I2C address write
			// indicates that the device is busy executing the command. We therefore return success.
			return AES132_FUNCTION_RETCODE_SUCCESS;

		// In case of read-device-status-register failure, we do not send the command again but only
		// re-synchronize, because we do not want certain commands being repeated, e.g. the Counter command.
		}else {
			// Do not override the return value from the call to aes132p_read_memory_physical.
			(void) aes132c_resync();
			return aes132_lib_return;
		}

		// Retry sending the command if an error occurred sending the command, or the device status register
		// indicates a CRC error after having sent the command.
	} while ((aes132_lib_return != AES132_FUNCTION_RETCODE_SUCCESS) && (--n_retries > 0));

	// We did not succeed sending a command. Return the error from aes132p_read_memory_physical or
	// AES132_FUNCTION_RETCODE_BAD_CRC_TX.
	return aes132_lib_return;
}


/** \brief This function reads a response from the I/O buffer of the device.
 * \param[in] size number of bytes to retrieve (<= response buffer size allocated by caller)
 * \param[out] response pointer to retrieved response
 * \return status of the operation
 */
uint8_t aes132c_receive_response(uint8_t size, uint8_t *response)
{
	uint8_t aes132_lib_return;
	uint8_t n_retries = AES132_RETRY_COUNT_ERROR;
	uint8_t crc[AES132_CRC_SIZE];
	uint8_t crc_index;
	uint8_t count_byte;

	do {
		aes132_lib_return = aes132c_wait_for_response_ready();
		if (aes132_lib_return != AES132_FUNCTION_RETCODE_SUCCESS) {
			// Waiting for the Response-Ready bit timed out. We might have lost communication.
			// Re-synchronize and retry.
			// Do not override the return value from the call to aes132c_wait_for_response_ready.
			(void) aes132c_resync();
			continue;
		}

		// Read count byte from response buffer.
		aes132_lib_return = aes132p_read_memory_physical(1, AES132_IO_ADDR, &response[AES132_COMMAND_INDEX_COUNT]);
		if (aes132_lib_return != AES132_FUNCTION_RETCODE_SUCCESS) {
			// Reading the count byte failed. We might have lost communication.
			// Re-synchronize and retry.
			// Do not override the return value from the call to aes132p_read_memory_physical.
			(void) aes132c_resync();
			continue;
		}

		count_byte = response[AES132_RESPONSE_INDEX_COUNT];
		if (count_byte > size) {
			// The buffer provided by the caller is not big enough to store the entire response,
			// or the count value got corrupted due to a bad communication channel.
			// Re-synchronize and retry.
			aes132_lib_return = AES132_FUNCTION_RETCODE_SIZE_TOO_SMALL;
			// Do not override aes132_lib_return.
			(void) aes132c_resync();
			continue;
		}

		if ((count_byte < AES132_RESPONSE_SIZE_MIN) || (count_byte > AES132_RESPONSE_SIZE_MAX)) {
			// A response has to be between #AES132_RESPONSE_SIZE_MIN and #AES132_RESPONSE_SIZE_MAX bytes long to be valid.
			// Re-synchronize and retry.
			aes132_lib_return = AES132_FUNCTION_RETCODE_COUNT_INVALID;
			// Do not override aes132_lib_return.
			(void) aes132c_resync();
			continue;
		}

		// Read remainder of response.
		aes132_lib_return = aes132p_read_memory_physical(count_byte - 1, AES132_IO_ADDR, &response[AES132_RESPONSE_INDEX_RETURN_CODE]);
		if (aes132_lib_return != AES132_FUNCTION_RETCODE_SUCCESS) {
			// Reading the remainder of the response failed. We might have lost communication.
			// Re-synchronize and retry.
			// Do not override the return value from the call to aes132p_read_memory_physical.
			(void) aes132c_resync();
			continue;
		}

		// Check CRC.
		crc_index = count_byte - AES132_CRC_SIZE;
		aes132c_calculate_crc(crc_index, response, crc);
		if ((crc[0] == response[crc_index]) && (crc[1] == response[crc_index + 1]))
			// We received a consistent response packet. Return the response return code.
			return response[AES132_RESPONSE_INDEX_RETURN_CODE];

		// Received and calculated CRC do not match. Retry reading the response buffer.
		aes132_lib_return = AES132_FUNCTION_RETCODE_BAD_CRC_RX;

		// Do not override aes132_lib_return.
		(void) aes132c_resync();

		// Retry if communication failed, or CRC did not match.
	} while ((aes132_lib_return != AES132_FUNCTION_RETCODE_SUCCESS) && (--n_retries > 0));

	// Even after re-synchronizing and retrying, we could not receive a consistent response packet.
	return aes132_lib_return;
}


/** \brief This function sends a command and reads its response.
 * \param[in] command pointer to command buffer
 * \param[in] size size of response buffer
 * \param[out] response pointer to response buffer
 * \param[in] options flags for communication behavior
 * \return status of the operation
 */
uint8_t aes132c_send_and_receive(uint8_t *command, uint8_t size, uint8_t *response, uint8_t options)
{
	uint8_t aes132_lib_return = aes132c_send_command(command, options);
	if (aes132_lib_return != AES132_FUNCTION_RETCODE_SUCCESS)
		return aes132_lib_return;

	return aes132c_receive_response(size, response);
}

