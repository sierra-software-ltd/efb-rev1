/******************************************************************************
* Copyright (C) 2016, Huada Semiconductor Co.,Ltd All rights reserved.
*
* This software is owned and published by:
* Huada Semiconductor Co.,Ltd ("HDSC").
*
* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
*
* This software contains source code for use with HDSC
* components. This software is licensed by HDSC to be adapted only
* for use in systems utilizing HDSC components. HDSC shall not be
* responsible for misuse or illegal use of this software for devices not
* supported herein. HDSC is providing this software "AS IS" and will
* not be responsible for issues arising from incorrect user implementation
* of the software.
*
* Disclaimer:
* HDSC MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
* REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS),
* ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING,
* WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED
* WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED
* WARRANTY OF NONINFRINGEMENT.
* HDSC SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT,
* NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT
* LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION,
* LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR
* INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA,
* SAVINGS OR PROFITS,
* EVEN IF Disclaimer HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
* INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED
* FROM, THE SOFTWARE.
*
* This software may be replicated in part or whole for the licensed use,
* with the restriction that this Disclaimer and Copyright notice must be
* included with each copy of this software, whether used in part or whole,
* at all times.
*/
/******************************************************************************/
/** \file main.c
 **
 ** A detailed description is available at
 ** @link Sample Group Some description @endlink
 **
 **   - 2016-02-16  1.0  XYZ First version for Device Driver Library of Module.
 **
 ******************************************************************************/

/******************************************************************************
 * Include files
 ******************************************************************************/
#include <arduino.h>
#include "HopeDuino_LoRa.h"

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/


/******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

#define 	RX_MODE       0
#define 	TX_MODE		  (!RX_MODE)

/******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/******************************************************************************
 * Local variable definitions ('static')                                      *
 ******************************************************************************/

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define LEN 32

//#define KEY_PIN		2			//for tx and rx selection

//#define KEY_SET_IN()    do{DDRD &= (~(1<<KEY_PIN));PORTD |= (1<<KEY_PIN); }while(0);
//#define KEY_READ()      (PIND &(1<<KEY_PIN))

/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
byte str[LEN] = {'H','o','p','e','R','F',' ','R','F','M',' ','C','O','B','R','F','M','9','5','W','A','+','+','+'};
byte getstr[LEN];
byte mode = RX_MODE;	
const byte app_syncword[] = { 0x2D, 0xD4, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0 } ;

	
/**
 ******************************************************************************
 ** \brief  Main function of project
 **
 ** \return uint32_t return value, if needed
 **
 ** This sample
 **
 ******************************************************************************/
void setup(void)
{
	byte i;

	//KEY_SET_IN();			//for select work mode
	
	Modulation	 = LORA;
	COB			 = RFM95;
	Frequency 	 = 866000;
	OutputPower	 = 10;			   //17dBm OutputPower
	PreambleLength = 8;			   //8Byte preamble
	FixedPktLength = true;		   //explicit header mode for LoRa
	PayloadLength  = 24;
	CrcDisable	 = true ;
	
	//for LORA parameter
	SFSel 		 = SF9;
	BWSel 		 = BW125K;
	CRSel 		 = CR4_5;

	//for OOK/FSK/GFSK parameter
	SymbolTime = 208000;				//4800bps unit: ns
	Devation = 35; 						//unit: KHz
	BandWidth = 100;					//unit: KHz
	SyncLength = 2;						//unit: none, range: 1-8[Byte], value '0' is not allowed!
	for(i=0; i<SyncLength;i++){
		SyncWord[i] = app_syncword[i];
	}

	vInitialize();

	vGoRx();
	
	Serial.begin(115200);
	//_delay_ms(3000);

  mode = TX_MODE;
	Serial.println("Tx starting...");
 vGoStandby();
}

void loop(void)
{
	//static byte last_mode=RX_MODE;
	byte tmp;
	
//	if(KEY_READ()==0){
//		_delay_ms(10);
//		if(KEY_READ()==0){
//			mode = !mode;
//		}
//		Serial.println("Key press enough,release the key");
//		while(KEY_READ()==0);
//	}
	
//	if(last_mode != mode){
//		//change mode
//		switch(mode){
//			case TX_MODE:
//				Serial.println("Enter tx mode...");
//				last_mode = mode;
//				vGoStandby();
//				break;
//			case RX_MODE:
//				Serial.println("Enter rx mode...");
//				last_mode = mode;
//				vGoRx();
//				break;
//		}	
//	}		
	switch(mode){
		case TX_MODE:
			bSendMessage(str, 26);
      Serial.println("Send the data");
			delay(1000);  //ms
		break;
		case RX_MODE:
			tmp = bGetMessage(getstr);
			if(tmp!=0)
   			{
			   Serial.print("Got message: ");
			   Serial.write(getstr,tmp);
			   Serial.print("\r\n");
			   //do someting 
   			}  
			break;
	}
}
