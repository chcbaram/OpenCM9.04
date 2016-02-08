/*
 * dxl2.h
 *
 *  Created on: 2013. 11. 8.
 *      Author: in2storm
 */

#ifndef DXL2_H_
#define DXL2_H_
#ifdef __cplusplus
extern "C" {
#endif
#include "usart.h"
#include "gpio.h"
#include "dxl_constants.h"


/** DYNAMIXEL device type  */
#define DXL_RX_BUF_SIZE 0x3FF
#define DXL_PARAMETER_BUF_SIZE 128


typedef struct dxl_dev {
/*

	gpio_dev *tx_port;      *< Maple pin's GPIO device
	gpio_dev *rx_port;      *< Maple pin's GPIO device
	gpio_dev *dir_port;      *< Maple pin's GPIO device

	uint8 tx_pin;
	uint8 rx_pin;
	uint8 dir_pin;*/
	uint16 write_pointer;
	uint16 read_pointer;
	uint8 data_buffer[DXL_RX_BUF_SIZE];
	voidFuncPtrUart handlers;
} dxl_dev;
extern dxl_dev *DXL_DEV1;
extern dxl_dev *DXL_DEV2;
extern dxl_dev *DXL_DEV3;

void dxlInterrupt1(byte data);
void dxlInterrupt2(byte data);
void dxlInterrupt3(byte data);
uint32 dxl_get_baudrate(int baudnum);
unsigned short update_crc(unsigned short crc_accum, unsigned char *data_blk_ptr, unsigned short data_blk_size); // for Dxl 2.0

void PrintBuffer(byte *bpPrintBuffer, byte bLength);

#ifdef __cplusplus
}
#endif
#endif /* DXL2_H_ */
