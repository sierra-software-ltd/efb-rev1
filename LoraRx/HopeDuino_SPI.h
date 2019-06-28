/*
 * THE FOLLOWING FIRMWARE IS PROVIDED:
 *  (1) "AS IS" WITH NO WARRANTY;
 *  (2) TO ENABLE ACCESS TO CODING INFORMATION TO GUIDE AND FACILITATE CUSTOMER.
 * CONSEQUENTLY, HopeRF SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT OR
 * CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT
 * OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION
 * CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * Copyright (C) SSLA
 *
 * website: www.sla.co.uk
 *          www.sla.co.uk
 */

/*!
 * file       HopeDuino_SPI.cpp
 * brief      for HopeRF's EVB to use Hardware SPI
 * hardware   HopeRF's EVB
 *
 *
 * version    1.3
 * date       Jan 15 2019
 * author     Nick
 */


#ifndef HopeDuino_SPI_h
#define HopeDuino_SPI_h

#include "Arduino.h"
//#include <util/delay.h>
//#include <avr/io.h>
#include <SPI.h>

#ifndef	byte
	typedef unsigned char byte;
#endif

#ifndef word
	typedef unsigned int  word;
#endif

//Dirver hardware I/O define

//esp32
#define RESET 12
#define nCS 5
#define MISO 19
#define MOSI 23
#define SCK 18
#define DIO0 4

//Arduino nano
//#define RESET 12
//#define nCS 5
//#define MISO 12//19
//#define MOSI 11//23
//#define SCK 13//18
//#define DIO0 4

//#define DIO4			4
//#define DIO3			5
//#define DIO2 		    6
//#define DIO1			7
//#define DIO0			8
//#define MISO			12
//#define MOSI			11
//#define SCK			    13
//#define nCS			    10
//#define RESET		    9

#define SOFT_SPI_nSS_DIRSET()      pinMode(nCS,OUTPUT)
#define SetnSS()				   digitalWrite(nCS,HIGH)
#define ClrnSS()				   digitalWrite(nCS,LOW)

#define SOFT_SPI_MISO_DIRSET()     pinMode(MISO,INPUT)
#define SOFT_SPI_MISO_PULLUP_SET() digitalWrite(MISO,HIGH)
#define SOFT_SPI_MISO_READ()       digitalRead(MISO)

#define SOFT_SPI_MOSI_DIRSET()     pinMode(MOSI,OUTPUT)
#define SOFT_SPI_MOSI_HI()         digitalWrite(MOSI,HIGH)
#define SOFT_SPI_MOSI_LO()         digitalWrite(MOSI,LOW)

#define SOFT_SPI_SCK_DIRSET()      pinMode(SCK,OUTPUT)
#define SOFT_SPI_SCK_HI()          digitalWrite(SCK,HIGH)
#define SOFT_SPI_SCK_LO()          digitalWrite(SCK,LOW)


void vSpiInit(void);				/** initialize hardware SPI config, SPI_CLK = Fcpu/4 **/
void vSpiWrite(word dat);			/** SPI send one word **/
byte bSpiRead(byte addr);			/** SPI read one byte **/
void vSpiBurstWrite(byte addr, byte ptr[], byte length);	/** SPI burst send N byte **/
void vSpiBurstRead(byte addr, byte ptr[], byte length);	 	/** SPI burst rend N byte **/
byte bSpiTransfer(byte dat);		/**	SPI send/read one byte **/

#else
	#warning "HopeDuino_SPI.h have been defined!"
#endif
