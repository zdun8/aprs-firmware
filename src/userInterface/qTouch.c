/*
 * qTouch.c
 *
 * Qtouch martix keyboard driver
 *
 *  Created on: 30-05-2012
 *      Author: Bartek
 */

/**
 * Includes
 */
#include "../stdPeriphLibs/lpc17xx_i2c.h"
#include "../stdPeriphLibs/lpc17xx_gpio.h"
#include "../stdPeriphLibs/lpc17xx_pinsel.h"
#include "../boardConfiguration.h"
#include "../stdPeriphLibs/LPC17xx.h"
#include "../stdPeriphLibs/lpc17xx_exti.h"
#include "qTouch.h"
#include "qTouchRegisters.h"
#include <string.h>
#include "commonFunctions.h"
/**
 * Defines
 */
#define I2C_CLOCK_SPEED	100000
#define QT_I2C	LPC_I2C1
#define I2C_RX_BUFFER_LENGTH	0x10
#define I2C_TX_BUFFER_LENGTH	0x10

/**
 * Global Variables
 */
static uint8_t I2C_RxBuffer[I2C_RX_BUFFER_LENGTH];
static uint8_t I2C_TxBuffer[I2C_TX_BUFFER_LENGTH];


/**
 * 	Private functions
 */
static void qtouchPinsConfiguration(void);
static void sendQtouchConfiguration(void);
static void sendQtouchCalibrateCmd(void);
static void initQtouchChangePinInterrupt(void);
static uint8_t readQtouchStatusRegisers(void);
static uint8_t getArrayElementsNumb(uint8_t *ptr);
static uint8_t checkIfReady(void);
/**
 * Keyboard Initialization
 */
void qtouchKeyboardInitialization(void)
{

	qtouchPinsConfiguration();
	while((GPIO_ReadValue(GPIO2) & 0x0400) == 0x400);

	//while(!checkIfReady());
	sendQtouchConfiguration();
	sendQtouchCalibrateCmd();
	readQtouchStatusRegisers();
//	while( (GPIO_ReadValue(GPIO2)&0x0400) == 0)
//		{
//		readQtouchStatusRegisers();
//		uint32_t i =0;
//		for(;i<30000;i++);
//		}
	initQtouchChangePinInterrupt();
}

/**
 * LPC17xx pins configuration
 *
 */
static void qtouchPinsConfiguration(void)
{
	PINSEL_CFG_Type PinSelConfigStruct;


	/// QTouch Reset Pin as output
	GPIO_SetDir(GPIO1, (0x01<<qtRstPin), OUTPUT);

	PinSelConfigStruct.Funcnum = PINSEL_FUNC_0;
	PinSelConfigStruct.OpenDrain = PINSEL_PINMODE_NORMAL;
	PinSelConfigStruct.Pinmode = PINSEL_PINMODE_PULLUP;
	PinSelConfigStruct.Pinnum = qtRstPin;
	PinSelConfigStruct.Portnum = GPIO1;

	PINSEL_ConfigPin(&PinSelConfigStruct);

	GPIO_SetValue(GPIO1, 0x01<<qtRstPin);


	/// QTouch Change Pin as external interrupt
	GPIO_SetDir(GPIO2, (0x01<<qtChgPin), INPUT);

	/**
	 * QTouch SCL and SDA pins I2C1
	 * clock speed 100kHz (max. value for QT chip)
	 */

	PinSelConfigStruct.Funcnum = PINSEL_FUNC_3;
	PinSelConfigStruct.OpenDrain = PINSEL_PINMODE_OPENDRAIN;
	PinSelConfigStruct.Pinmode = PINSEL_PINMODE_TRISTATE;
	PinSelConfigStruct.Pinnum = qtSdaPin;
	PinSelConfigStruct.Portnum = GPIO0;

	PINSEL_ConfigPin(&PinSelConfigStruct);

	PinSelConfigStruct.Pinnum = qtSclPin;

	PINSEL_ConfigPin(&PinSelConfigStruct);

	I2C_Init(QT_I2C, I2C_CLOCK_SPEED );

	I2C_Cmd(QT_I2C, ENABLE);

}

/**
 * Function initialize interrupt on P2.10
 * generated by Qtouch change pin
 * responds on FALLING_EDGE
 */
static void initQtouchChangePinInterrupt(void)
{
	PINSEL_CFG_Type PinSelConfigStruct;
	EXTI_InitTypeDef EXTI_InitStruct;


	PinSelConfigStruct.Funcnum = PINSEL_FUNC_1;
	PinSelConfigStruct.OpenDrain = PINSEL_PINMODE_OPENDRAIN;
	PinSelConfigStruct.Pinmode = PINSEL_PINMODE_TRISTATE;
	PinSelConfigStruct.Pinnum = qtChgPin;
	PinSelConfigStruct.Portnum = GPIO2;

	PINSEL_ConfigPin(&PinSelConfigStruct);

	EXTI_Init();
//
	EXTI_InitStruct.EXTI_Line = EXTI_EINT0;
	EXTI_InitStruct.EXTI_Mode = EXTI_MODE_EDGE_SENSITIVE;
	EXTI_InitStruct.EXTI_polarity = EXTI_POLARITY_LOW_ACTIVE_OR_FALLING_EDGE;
//
	EXTI_ClearEXTIFlag(0);
	EXTI_Config(&EXTI_InitStruct);

	NVIC_SetPriority(EINT0_IRQn, ((0x01<<3)|0x02));
	NVIC_EnableIRQ(EINT0_IRQn);

}


/**
 * EXINT Handler
 */
void EINT0_IRQHandler(void)
{

while( (GPIO_ReadValue(GPIO2)&0x0400) == 0)
{
	uint8_t status = readQtouchStatusRegisers();
	uint32_t i=0;

//for(;i<30000;i++);
	delay_ms(100);
	if(status&0x80)
		//TODO - qtouch reset, and key detect
		{
		qtouchResetControler();
		}
	else
		{
		}

	EXTI_ClearEXTIFlag(0);
}

}

/**
 * 	Function configures Qtouch chip to work
 */
static void sendQtouchConfiguration( void )
{
	uint8_t i;

	I2C_M_SETUP_Type I2C_MasterInitStruct;
	uint8_t * txBuffPtr = I2C_TxBuffer;

	I2C_TxBuffer[0] = QT_LP_MODE;
	I2C_TxBuffer[1] = 0x05; //LP mode 16ms*LP
	I2C_TxBuffer[2] = 0x04;	//Burst repetition
	I2C_TxBuffer[3] = '\n'; // EOF

	I2C_MasterInitStruct.sl_addr7bit = QT_DEV_ADRESS;
	I2C_MasterInitStruct.tx_count = 0;
	I2C_MasterInitStruct.tx_data = txBuffPtr;
	I2C_MasterInitStruct.tx_length = getArrayElementsNumb(txBuffPtr);
	I2C_MasterInitStruct.retransmissions_count = 0;
	I2C_MasterInitStruct.retransmissions_max = 5;
	I2C_MasterInitStruct.rx_data = NULL;
	I2C_MasterInitStruct.rx_length = 0;

	I2C_MasterTransferData(QT_I2C, &I2C_MasterInitStruct, I2C_TRANSFER_POLLING);

	I2C_TxBuffer[0] = QT_NORMAL_DI_LIMIT;
	I2C_TxBuffer[1] = 0x05;
	I2C_TxBuffer[2] = '\n'; // EOF

	I2C_MasterInitStruct.tx_length = getArrayElementsNumb(txBuffPtr);

	I2C_MasterTransferData(QT_I2C, &I2C_MasterInitStruct, I2C_TRANSFER_POLLING);

	I2C_TxBuffer[0] = QT_SLIDER_CONTROL;
	I2C_TxBuffer[1] = 0x00; // Disable slider
	//I2C_TxBuffer[2] = 0x00;
	I2C_TxBuffer[2] = '\n'; // EOF

	I2C_MasterInitStruct.tx_length = getArrayElementsNumb(txBuffPtr);

	I2C_MasterTransferData(QT_I2C, &I2C_MasterInitStruct, I2C_TRANSFER_POLLING);


	I2C_TxBuffer[0] = QT_KEY0_BURST_LENGTH;
	I2C_TxBuffer[1] = 32;
	I2C_TxBuffer[2] = 32;
	I2C_TxBuffer[3] = 32;
	I2C_TxBuffer[4] = 32;
	I2C_TxBuffer[5] = 32;
	I2C_TxBuffer[6] = 32;
	I2C_TxBuffer[7] = 0;
	I2C_TxBuffer[8] = 0;
	I2C_TxBuffer[9] = '\n';

	I2C_MasterInitStruct.tx_length = getArrayElementsNumb(txBuffPtr);

	I2C_MasterTransferData(QT_I2C, &I2C_MasterInitStruct, I2C_TRANSFER_POLLING);

	I2C_TxBuffer[0] = QT_KEY8_BURST_LENGTH;
	I2C_TxBuffer[1] = 32;
	I2C_TxBuffer[2] = 32;
	I2C_TxBuffer[3] = 32;
	I2C_TxBuffer[4] = 32;
	I2C_TxBuffer[5] = 32;
	I2C_TxBuffer[6] = 32;
	I2C_TxBuffer[7] = 0;
	I2C_TxBuffer[8] = 0;
	I2C_TxBuffer[9] = '\n';

	I2C_MasterInitStruct.tx_length = getArrayElementsNumb(txBuffPtr);

	I2C_MasterTransferData(QT_I2C, &I2C_MasterInitStruct, I2C_TRANSFER_POLLING);

//	// Keys AKS groups select
//	I2C_TxBuffer[0] = QT_KEY0_CONTROL;
//	for(i=1;i<4;i++)
//	{
//		I2C_TxBuffer[i] = 0x01;//0x01;
//	}
//	for(i=4;i<7;i++)
//	{
//		I2C_TxBuffer[i] = 0x02;//0x02;
//	}
//	I2C_TxBuffer[7] = 0x0;
//	I2C_TxBuffer[8] = 0x0;
//	for(i=9; i<12; i++)
//	{
//		I2C_TxBuffer[i] = 0x01; //0x01;
//	}
//	for(i=12;i<14;i++)
//	{
//		I2C_TxBuffer[i] = 0x02; //0x02;
//	}
//	I2C_TxBuffer[14] = '\n';
//
//	I2C_MasterInitStruct.tx_length = getArrayElementsNumb(txBuffPtr);
//
//	I2C_MasterTransferData(QT_I2C, &I2C_MasterInitStruct, I2C_TRANSFER_POLLING);

}


/**
 * Function starting calibrate process
 *
 * Writing any non 0 value to Calibrate register
 * will start re-calibration process on enabled
 * keys
 */
static void sendQtouchCalibrateCmd(void)
{
	uint8_t* txBuffPtr = I2C_TxBuffer;

	I2C_M_SETUP_Type I2C_MasterInitStruct;
	I2C_TxBuffer[0] = QT_CALIBRATE;
	I2C_TxBuffer[1] = 0x10; //send calibrate cmd
	I2C_TxBuffer[3] = '\n'; // EOF

	I2C_MasterInitStruct.sl_addr7bit = QT_DEV_ADRESS;
	I2C_MasterInitStruct.tx_count = 0;
	I2C_MasterInitStruct.tx_data = txBuffPtr;
	I2C_MasterInitStruct.tx_length = getArrayElementsNumb(txBuffPtr);
	I2C_MasterInitStruct.retransmissions_count = 0;
	I2C_MasterInitStruct.retransmissions_max = 5;
	I2C_MasterInitStruct.rx_data = NULL;
	I2C_MasterInitStruct.rx_length = 0;

	I2C_MasterTransferData(QT_I2C, &I2C_MasterInitStruct, I2C_TRANSFER_POLLING);

}

/**
 * Function reads all Qtouch status regisers
 * addresses from 2 to 6
 */
static uint8_t readQtouchStatusRegisers(void)
{
	uint8_t * txBuffPtr = I2C_TxBuffer;
	I2C_M_SETUP_Type I2C_MasterInitStruct;
	I2C_TxBuffer[0] = QT_GENERAL_STATUS;
	I2C_TxBuffer[1] = '\n'; // EOF
	I2C_MasterInitStruct.sl_addr7bit = QT_DEV_ADRESS;
	I2C_MasterInitStruct.tx_count = 0;
	I2C_MasterInitStruct.tx_data = txBuffPtr;
	I2C_MasterInitStruct.tx_length = getArrayElementsNumb(txBuffPtr);
	I2C_MasterInitStruct.retransmissions_count = 0;
	I2C_MasterInitStruct.retransmissions_max = 5;
	I2C_MasterInitStruct.rx_data = I2C_RxBuffer;
	I2C_MasterInitStruct.rx_length = 5;

	I2C_MasterTransferData(QT_I2C, &I2C_MasterInitStruct, I2C_TRANSFER_POLLING);

	I2C_RxBuffer[5] = '\n';

 return I2C_RxBuffer[0];
}
/**
 * Function returns last pressed key
 * indicator number
 */
uint8_t getQtouchPressedKeyIndicator(void)
{
	uint8_t keyInd = 255;

	if(I2C_RxBuffer[1]!=0)
	{
		switch (I2C_RxBuffer[1])
		{
			case 0x01:
				keyInd = 1;
				break;
			case 0x02:
				keyInd = 2;
				break;
			case 0x04:
				keyInd = 3;
				break;
			case 0x08:
				keyInd = 9;
				break;
			case 0x10:
				keyInd = 8;
				break;
			case 0x20:
				keyInd = 7;
				break;

		}
	}


	else if(I2C_RxBuffer[2]!=0)
	{
		switch (I2C_RxBuffer[2])
		{
					case 0x01:
						keyInd = 4;
						break;
					case 0x02:
						keyInd = 5;
						break;
					case 0x04:
						keyInd = 6;
						break;
					case 0x08:
						keyInd = 11;
						break;
					case 0x10:
						keyInd = 0;
						break;
					case 0x20:
						keyInd = 10;
						break;
		}

	}

	return keyInd;
}

static uint8_t getArrayElementsNumb(uint8_t *ptr)
{
	uint8_t i =0;
	while( (*ptr) != '\n')
	{
		i++;
		ptr++;
	}
return i;
}

static uint8_t checkIfReady(void)
{
	I2C_M_SETUP_Type I2C_MasterInitStruct;

	uint8_t I2C_TxBuff[] = {0x00, '\n'};
	uint8_t *ptr = I2C_TxBuff;

	I2C_MasterInitStruct.sl_addr7bit = QT_DEV_ADRESS;
	I2C_MasterInitStruct.tx_count = 0;
	I2C_MasterInitStruct.tx_data = ptr;
	I2C_MasterInitStruct.tx_length = getArrayElementsNumb(ptr);
	I2C_MasterInitStruct.retransmissions_count = 0;
	I2C_MasterInitStruct.retransmissions_max = 5;
	I2C_MasterInitStruct.rx_data = I2C_RxBuffer;
	I2C_MasterInitStruct.rx_length = 1;

	I2C_MasterTransferData(QT_I2C, &I2C_MasterInitStruct, I2C_TRANSFER_POLLING);

	if(I2C_RxBuffer[0]==0x11)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void qtouchResetControler(void)
{
	NVIC_DisableIRQ(EINT0_IRQn);
	sendQtouchConfiguration();
	sendQtouchCalibrateCmd();
	readQtouchStatusRegisers();
	NVIC_EnableIRQ(EINT0_IRQn);
}

void debugq(void)
{
	readQtouchStatusRegisers();
}
