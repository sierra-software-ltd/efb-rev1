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
 * website: www.ssla.co.uk
 *          www.ssla.co.uk
 */

/*!
 * file       HopeDuino_LoRa.h
 * brief      driver for RFM92/95/96/98
 * hardware   HopeDuino with HopeRF's LoRa COB rf-module
 *
 *
 * version    1.3
 * date       Jun 23 2018
 * author     Nick
 */

#ifndef HopeDuino_LORA_h
	#define HopeDuino_LORA_h

	#ifndef F_CPU
		#define F_CPU 16000000UL		//for delay.h to use, & HopeDuino use 16MHz Xo
	#endif

	#ifndef	byte
		typedef unsigned char byte;
	#endif

	#ifndef word
		typedef unsigned int  word;
	#endif

	#ifndef lword
		typedef unsigned long lword;
	#endif

	#ifndef __DELAY_BACKWARD_COMPATIBLE__
		#define __DELAY_BACKWARD_COMPATIBLE__
	#endif

  #include "Arduino.h"
	//#include <avr/io.h>
	//#include <util/delay.h>
	#include "HopeDuino_SPI.h"

	//Output
	#define POROut()	 (pinMode(RESET,OUTPUT))
	#define	PORIn()		 (pinMode(RESET,INPUT))
	#define SetPOR()	 digitalWrite(RESET,HIGH)
	#define	ClrPOR()	 digitalWrite(RESET,LOW)

	//Input
	#define DIO0In()	(pinMode(DIO0,INPUT))
	#define	DIO0_H()	(digitalRead(DIO0)==1)
	#define	DIO0_L()	(digitalRead(DIO0)==0)


	typedef union
	{
	 struct
	 	{
	  	byte FreqL: 8;
	  	byte FreqM: 8;
	  	byte FreqH: 8;
	  	byte FreqX: 8;
	 	}freq;
	 unsigned long Freq;
	}FreqStruct;

	enum modulationType {OOK, FSK, GFSK, LORA};

	enum moduleType {RFM92, RFM93, RFM95, RFM96, RFM97, RFM98};

	enum sfType {SF6, SF7, SF8, SF9, SF10, SF11, SF12};

	enum bwType {BW62K, BW125K, BW250K, BW500K};	//

	enum crType {CR4_5, CR4_6, CR4_7, CR4_8};


	extern	modulationType Modulation;					//OOK/FSK/GFSK/LORA
	extern	moduleType COB;								//Chip on board

	//common parameter
	extern	lword Frequency;							//unit: KHz
	extern	byte  OutputPower;							//unit: dBm   range: 2-20 [2dBm~+20dBm]
	extern	word  PreambleLength;						//unit: byte

	extern	byte  FixedPktLength;						//OOK/FSK/GFSK:
	                                        //	 	true-------fixed packet length
	                                        //   	false------variable packet length
	                                        //LoRa:
	                                        //	 	true-------implicit header mode
	                                        //      false------explicit header mode

	extern	byte  CrcDisable;							//OOK/FSK/GFSK:
											//		true-------CRC disable
											//		fasle------CRC enable with CCITT
											//LoRa:
											//		true-------Header indicates CRC off
											//		false------Header indicates CRC on
	extern	byte  PayloadLength;						//PayloadLength is need to be set a value, when FixedPktLength is true.


	//for OOK/FSK/GFSK parameter
	extern	lword SymbolTime;							//unit: ns
	extern	lword Devation;								//unit: KHz
	extern	word  BandWidth;							//unit: KHz
	extern	byte  SyncLength;							//unit: none, range: 1-8[Byte], value '0' is not allowed!
	extern	byte  SyncWord[8];

	//for LoRa parameter
	extern	sfType SFSel;								//unit: none, range: SF6~SF12
	extern	bwType BWSel;
	extern	crType CRSel;

	void vInitialize(void);
	void vConfig(void);
	void vGoRx(void);
	void vGoStandby(void);
	void vGoSleep(void);
	byte bSendMessage(byte msg[], byte length);
	byte bGetMessage(byte msg[]);

	void vReset(void);
	byte bSelectBandwidth(byte rx_bw);
	byte bSelectRamping(lword symbol);
#else
	#warning "HopeDuino_LoRa.h have been defined!"
#endif
