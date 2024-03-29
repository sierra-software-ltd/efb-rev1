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
 * file       HopeDuino_SPI.cpp
 * brief      for HopeRF's EVB to use Hardware SPI
 * hardware   HopeRF's EVB
 *
 *
 * version    1.3
 * date       Feb 17 2019
 * author    Nick K
 */

#include "HopeDuino_SPI.h"

#define SPI_TYPE	0			//1: select hardware SPI, depond on platform
								//0: select software GPIO simulate SPI,

/**********************************************************
**Name: 	vSpiInit
**Func: 	Init Spi Config
**Note: 	SpiClk = Fcpu/4
**********************************************************/
void vSpiInit(void)
{
//modify this function to migrate to other platform
#if SPI_TYPE
	SPI.begin();
#else
	// can be optimized into single write if port wiring allows
	SOFT_SPI_nSS_DIRSET();
	SOFT_SPI_SCK_DIRSET();
	SOFT_SPI_MOSI_DIRSET();
	SOFT_SPI_MISO_DIRSET(); // always input after POR, can be commented out
	SOFT_SPI_MISO_PULLUP_SET(); // ??

	SOFT_SPI_SCK_LO();
	SOFT_SPI_MOSI_LO();
	ClrnSS();
#endif
}

/**********************************************************
**Name: 	bSpiTransfer
**Func: 	Transfer One Byte by SPI
**Input:
**Output:
**********************************************************/
byte bSpiTransfer(byte dat)
{
//modify this function to migrate to other platform
#if SPI_TYPE
  return SPI.transfer(dat);
#else
  byte i;

  for(i = 0; i < 8; i++)
  {
	  if (dat & 0x80)
		  SOFT_SPI_MOSI_HI();
	  else
		  SOFT_SPI_MOSI_LO();

	  delayMicroseconds(1);
	  SOFT_SPI_SCK_HI();
	  delayMicroseconds(1);

	  dat <<= 1;

	  if (SOFT_SPI_MISO_READ())
		  dat |= 0x01; // dat++

	  delayMicroseconds(1);
	  SOFT_SPI_SCK_LO();
	  delayMicroseconds(1);
   }

   return dat;
#endif
}

/**********************************************************
**Name:	 	vSpiWrite
**Func: 	SPI Write One word
**Input: 	Write word
**Output:	none
**********************************************************/
void vSpiWrite(word dat)
{
 ClrnSS();
 bSpiTransfer((byte)(dat>>8)|0x80);
 bSpiTransfer((byte)dat);
 SetnSS();
}

/**********************************************************
**Name:	 	bSpiRead
**Func: 	SPI Read One byte
**Input: 	readout addresss
**Output:	readout byte
**********************************************************/
byte bSpiRead(byte addr)
{
 byte tmp;
 ClrnSS();
 bSpiTransfer(addr);
 tmp = bSpiTransfer(0xFF);
 SetnSS();
 return(tmp);
}

/**********************************************************
**Name:	 	vSpiBurstWirte
**Func: 	burst wirte N byte
**Input: 	array length & start address & head pointer
**Output:	none
**********************************************************/
void vSpiBurstWrite(byte addr, byte ptr[], byte length)
{
 byte i;
 ClrnSS();
 bSpiTransfer(addr|0x80);
 for(i=0; i<length; i++)
 	bSpiTransfer(ptr[i]);
 SetnSS();
}

/**********************************************************
**Name:	 	vSpiBurstRead
**Func: 	burst read N byte
**Input: 	array length & start address & head pointer
**Output:	none
**********************************************************/
void vSpiBurstRead(byte addr, byte ptr[], byte length)
{
 if(length!=0)
 	{
 	if(length==1)
 		{
 		ClrnSS();
 		bSpiTransfer(addr);
		ptr[0] = bSpiTransfer(0xFF);
		SetnSS();
 		}
 	else
 		{
 		byte i;
 		ClrnSS();
 		bSpiTransfer(addr);
 		for(i=0; i<length; i++)
 			ptr[i] = bSpiTransfer(0xFF);
 		SetnSS();
 		}
 	}
 return;
}
