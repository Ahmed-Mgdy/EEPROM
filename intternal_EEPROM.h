/*
 * intternal_EEPROM.h
 *
 * Created: 3/15/2024 11:11:51 AM
 *  Author: ahmed magdy
 */


#ifndef INTTERNAL_EEPROM_H_
#define INTTERNAL_EEPROM_H_

#include "std_types.h"
#include <stdbool.h>


#define EEPROM_SIZE 1024 // For ATmega328P, ATmega2560, etc. with 1KB EEPROM
// Or
// #define EEPROM_SIZE 512  // For ATmega16, ATmega32, etc. with 512B EEPROM
#define EEPROM_MAX_STRING_LENGTH 64   // Maximum length of string to be stored in EEPROM

#define EEPROM_ADDRESS0 0x00
#define EEPROM_ADDRESS1 0x01
#define EEPROM_ADDRESS2 0x02
#define EEPROM_ADDRESS3 0x03
#define EEPROM_ADDRESS4 0x04
#define EEPROM_ADDRESS5 0x05
#define EEPROM_ADDRESS6 0x06
#define EEPROM_ADDRESS7 0x07
#define EEPROM_ADDRESS8 0x08
#define EEPROM_ADDRESS9 0x09
#define EEPROM_ADDRESS10 0x10
#define EEPROM_ADDRESS14 0x0E
#define EEPROM_ADDRESS18 0x12
#define EEPROM_ADDRESS20 0x20
#define EEPROM_ADDRESS21 0x21
#define EEPROM_ADDRESS22 0x22
#define EEPROM_ADDRESS23 0x23
#define EEPROM_ADDRESS24 0x24
#define EEPROM_ADDRESS25 0x25
#define EEPROM_ADDRESS30 0x30
#define EEPROM_ADDRESS31 0x31
#define EEPROM_ADDRESS32 0x32
#define EEPROM_ADDRESS33 0x33

void eeprom_init(void);
uint8 read_eeprom(uint16 address) ;
void write_eeprom(uint8 data, uint16 address);
void access_eeprom_byte_by_byte(uint16 start_address, uint8 *data, uint16 length);
void clear_eeprom(void);
void clear_eeprom_byte(uint16 address);
void write_eeprom_long(uint16 start_address, uint32 data);
uint32 read_eeprom_long(uint16 start_address);
float read_eeprom_float(uint16 start_address);
void write_eeprom_float(uint16 start_address, float data);
//bool is_address_used(uint16 address);



#endif /* INTTERNAL_EEPROM_H_ */
