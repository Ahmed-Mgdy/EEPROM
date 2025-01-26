/*
 * intternal_EEPROM.c
 *
 * Created: 3/15/2024 11:10:33 AM
 *  Author: ahmed magdy
 */

#include "intternal_EEPROM.h"
#include "std_types.h"
#include "common_macros.h"
#include <avr/io.h>


void eeprom_init(void)
 {
	// Disable EEPROM Ready Interrupt (EERIE) - not needed for initialization
	CLEAR_BIT(EECR,EERIE);
	// Enable EEPROM Master Write Enable (EEMWE)
	SET_BIT(EECR,EEMWE);
	// Wait for EEMWE bit to be cleared by hardware
	while (BIT_IS_SET(EECR,EEMWE));

}

uint8 read_eeprom(uint16 address)
{

	while (BIT_IS_SET(EECR,EEWE));
	EEAR = address;
	SET_BIT(EECR,EERE);
	return EEDR;
}

void write_eeprom(uint8 data, uint16 address)
 {

	while (BIT_IS_SET(EECR,EEWE));

	EEAR = address;
	EEDR = data;
	SET_BIT(EECR,EEMWE);
	SET_BIT(EECR,EEWE);
}


void clear_eeprom(void)
 {
	for (uint16 address = 0; address < EEPROM_SIZE; ++address)
	 {
		write_eeprom(0xFF, address);
	}
}


void clear_eeprom_byte(uint16 address)
{
	write_eeprom(0xFF, address);
}


void access_eeprom_byte_by_byte(uint16 start_address, uint8 *data, uint16 length)
{
	for (uint16 i = 0; i < length; ++i)
	{
		uint16 address = start_address + i;
		data[i] = read_eeprom(address);
	}
	/*
	// Example usage to read 10 bytes from EEPROM starting at address 0x0000
	uint8 data[10];
	access_eeprom_byte_by_byte(0x0000, data, 10);

	// Example usage to write 5 bytes to EEPROM starting at address 0x0010
	uint8 data_to_write[] = {0x01, 0x02, 0x03, 0x04, 0x05};
	access_eeprom_byte_by_byte(0x0010, data_to_write, sizeof(data_to_write));*/
}



void write_eeprom_string(uint16 start_address, const char *str) {
	uint16 length = strlen(str);
	if (length > EEPROM_MAX_STRING_LENGTH) {
		return;
	}

	for (uint16 i = 0; i < length; ++i) {
		write_eeprom(str[i], start_address + i);
	}

	write_eeprom('\0', start_address + length);
}

void read_eeprom_string(uint16 start_address, char *str) {
	uint16 i = 0;
	uint8 data;
	do {
		data = read_eeprom(start_address + i);
		str[i] = data;
		++i;
	} while (data != '\0' && i < EEPROM_MAX_STRING_LENGTH);
	str[i - 1] = '\0';
	/*// Example usage to write a string to EEPROM
	write_eeprom_string(0x0000, "Hello, EEPROM!");

	// Example usage to read a string from EEPROM
	char str[EEPROM_MAX_STRING_LENGTH];
	read_eeprom_string(0x0000, str);*/
}





void access_all_eeprom_addresses(void)
 {
	for (uint16 address = 0; address < EEPROM_SIZE; ++address) {
		uint8 data = read_eeprom(address);
		// Do something with the data read from EEPROM
		/*// For example, you can print it
		printf("Address: 0x%04X, Data: 0x%02X\n", address, data);
		// Or perform some other operation
		*/
	}
}

void write_to_all_eeprom_addresses(uint8 data) {
	for (uint16 address = 0; address < EEPROM_SIZE; ++address) {
		write_eeprom(data, address);
	}
}

//bool is_address_used(uint16 address) {
//	uint8 data = read_eeprom(address);
//	// Assuming 0xFF indicates an erased (unused) EEPROM address
//	// Change this condition according to your application if 0xFF means something else
//	return data != 0xFF;
//}

void write_eeprom_long(uint16 start_address, uint32 data) {
    for (uint8 i = 0; i < 4; ++i) {
        write_eeprom((uint8)(data >> (i * 8)), start_address + i);
    }
}

uint32 read_eeprom_long(uint16 start_address) {
    uint32 data = 0;
    for (uint8 i = 0; i < 4; ++i) {
        data |= ((uint32)read_eeprom(start_address + i)) << (i * 8);
    }
    return data;
}

void write_eeprom_float(uint16 start_address, float data) {
    // Convert the float to bytes
    uint8 bytes[4];
    memcpy(bytes, &data, sizeof(data)); // Copy the float bytes to the array

    // Write each byte to the EEPROM
    for (uint8 i = 0; i < 4; ++i) {
        write_eeprom(bytes[i], start_address + i);
    }
}

float read_eeprom_float(uint16 start_address) {
    // Read the bytes from EEPROM
    uint8 bytes[4];
    for (uint8 i = 0; i < 4; ++i) {
        bytes[i] = read_eeprom(start_address + i);
    }

    // Convert the bytes back to a float
    float data;
    memcpy(&data, bytes, sizeof(data));
    return data;
}
//uint32 read_eeprom_long(uint16 start_address) {
//    uint32 data = 0;
//    // Read the 4 bytes from consecutive EEPROM addresses and reconstruct the long int
//    data |= ((uint32)read_eeprom(start_address)) << 0;        // Read Byte 0 (LSB)
//    data |= ((uint32)read_eeprom(start_address + 1)) << 8;    // Read Byte 1
//    data |= ((uint32)read_eeprom(start_address + 2)) << 16;   // Read Byte 2
//    data |= ((uint32)read_eeprom(start_address + 3)) << 24;   // Read Byte 3 (MSB)
//    return data;
//}

//void write_eeprom_long(uint16 start_address, uint32 data) {
//    // Writing the 4 bytes of the long int to consecutive EEPROM addresses
//    write_eeprom((uint8)(data >> 0), start_address);       // Store Byte 0 (LSB)
//    write_eeprom((uint8)(data >> 8), start_address + 1);   // Store Byte 1
//    write_eeprom((uint8)(data >> 16), start_address + 2);  // Store Byte 2
//    write_eeprom((uint8)(data >> 24), start_address + 3);  // Store Byte 3 (MSB)
//}





