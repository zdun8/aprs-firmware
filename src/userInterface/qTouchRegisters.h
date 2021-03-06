/*
 * qTouchRegisters.h
 *
 *  Created on: 02-06-2012
 *      Author: Bartek
 */

#ifndef QTOUCHREGISTERS_H_
#define QTOUCHREGISTERS_H_

#define QT_DEV_ADRESS 0x0D

#define QT_ID 	0x0
#define QT_CODE_VERSION		0x01
#define QT_GENERAL_STATUS 	0x02
#define QT_KEY_STATUS_1		0x03
#define QT_KEY_STATUS_2		0x04
#define QT_SLIDER_TOUCH_POSITION 	0x05
#define QT_GPIO_READ	0x06
#define QT_RESERVED 	0x08
#define QT_CALIBRATE 	0x0A
#define QT_RESET		0x0B
#define QT_LP_MODE		0x0C
#define QT_BURST_REPETITION 0x0D
#define QT_NEG_DRIFT_COMP 	0x0F
#define QT_POS_DRIFT_COMP	0x10
#define QT_NORMAL_DI_LIMIT	0x11
#define QT_NEG_RECAL_DELAY	0x12
#define QT_DRIFT_HOLD_TIME	0x13
#define QT_SLIDER_CONTROL	0x14
#define QT_SLIDER_OPTIONS	0x15
#define QT_KEY0_CONTROL		0x16
#define QT_KEY1_CONTROL		0x17
#define QT_KEY2_CONTROL		0x18
#define QT_KEY3_CONTROL		0x19
#define QT_KEY4_CONTROL		0x1A
#define QT_KEY5_CONTROL		0x1B
#define QT_KEY6_CONTROL		0x1C
#define QT_KEY7_CONTROL		0x1D
#define QT_KEY8_CONTROL		0x1E
#define QT_KEY9_CONTROL		0x1F
#define QT_KEY10_CONTROL	0x20
#define QT_KEY11_CONTROL	0x21
#define QT_KEY12_CONTROL	0x22
#define QT_KEY13_CONTROL	0x23
#define QT_KEY14_CONTROL	0x24
#define QT_KEY15_CONTROL	0x25
#define QT_KEY0_NEG_TRESHOLD	0x26
#define QT_KEY1_NEG_TRESHOLD	0x27
#define QT_KEY2_NEG_TRESHOLD	0x28
#define QT_KEY3_NEG_TRESHOLD	0x29
#define QT_KEY4_NEG_TRESHOLD	0x2A
#define QT_KEY5_NEG_TRESHOLD	0x2B
#define QT_KEY6_NEG_TRESHOLD	0x2C
#define QT_KEY7_NEG_TRESHOLD	0x2D
#define QT_KEY8_NEG_TRESHOLD	0x2E
#define QT_KEY9_NEG_TRESHOLD	0x2F
#define QT_KEY10_NEG_TRESHOLD	0x30
#define QT_KEY11_NEG_TRESHOLD	0x31
#define QT_KEY12_NEG_TRESHOLD	0x32
#define QT_KEY13_NEG_TRESHOLD	0x33
#define QT_KEY14_NEG_TRESHOLD	0x34
#define QT_KEY15_NEG_TRESHOLD	0x35
#define QT_KEY0_BURST_LENGTH	0x36
#define QT_KEY1_BURST_LENGTH	0x37
#define QT_KEY2_BURST_LENGTH	0x38
#define QT_KEY3_BURST_LENGTH	0x39
#define QT_KEY4_BURST_LENGTH	0x3A
#define QT_KEY5_BURST_LENGTH	0x3B
#define QT_KEY6_BURST_LENGTH	0x3C
#define QT_KEY7_BURST_LENGTH	0x3D
#define QT_KEY8_BURST_LENGTH	0x3E
#define QT_KEY9_BURST_LENGTH	0x3F
#define QT_KEY10_BURST_LENGTH	0x40
#define QT_KEY11_BURST_LENGTH	0x41
#define QT_KEY12_BURST_LENGTH	0x42
#define QT_KEY13_BURST_LENGTH	0x43
#define QT_KEY14_BURST_LENGTH	0x44
#define QT_KEY15_BURST_LENGTH	0x45
#define QT_GPIO_DRIVE1	0x46
#define QT_GPIO_DRIVE2 	0x47
#define QT_GPIO_DIRECTION2 	0x49
#define QT_GPIO_PWM1 	0x4A
#define QT_GPIO_PWM2	0x4B
#define QT_PWM_LEVEL	0x4C
#define QT_GPIO_WAKE	0x4D
#define QT_COMMON_CHANGE_KEYS1 	0x4E
#define QT_COMMON_CHANGE_KEYS2 	0x4F
#define QT_KEY0_SIGNAL_LSB	0x64
#define QT_KEY0_SIGNAL_MSB	0x65
#define QT_KEY1_SIGNAL_LSB	0x66
#define QT_KEY1_SIGNAL_MSB	0x67
#define QT_KEY2_SIGNAL_LSB	0x68
#define QT_KEY2_SIGNAL_MSB	0x69
#define QT_KEY3_SIGNAL_LSB	0x6A
#define QT_KEY3_SIGNAL_MSB	0x6B
#define QT_KEY4_SIGNAL_LSB	0x6C
#define QT_KEY4_SIGNAL_MSB	0x6D
#define QT_KEY5_SIGNAL_LSB	0x6E
#define QT_KEY5_SIGNAL_MSB	0x6F
#define QT_KEY6_SIGNAL_LSB	0x70
#define QT_KEY6_SIGNAL_MSB	0x71
#define QT_KEY7_SIGNAL_LSB	0x72
#define QT_KEY7_SIGNAL_MSB	0x73
#define QT_KEY8_SIGNAL_LSB	0x74
#define QT_KEY8_SIGNAL_MSB	0x75
#define QT_KEY9_SIGNAL_LSB	0x76
#define QT_KEY9_SIGNAL_MSB	0x77
#define QT_KEY10_SIGNAL_LSB	0x78
#define QT_KEY10_SIGNAL_MSB	0x79
#define QT_KEY11_SIGNAL_LSB	0x7A
#define QT_KEY11_SIGNAL_MSB	0x7B
#define QT_KEY12_SIGNAL_LSB	0x7C
#define QT_KEY12_SIGNAL_MSB	0x7D
#define QT_KEY13_SIGNAL_LSB	0x7E
#define QT_KEY13_SIGNAL_MSB	0x7F
#define QT_KEY14_SIGNAL_LSB	0x80
#define QT_KEY14_SIGNAL_MSB	0x81
#define QT_KEY15_SIGNAL_LSB	0x82
#define QT_KEY15_SIGNAL_MSB	0x83
#define QT_KEY0_REFERENCE_LSB	0x84
#define QT_KEY0_REFERENCE_MSB	0x85
#define QT_KEY1_REFERENCE_LSB	0x86
#define QT_KEY1_REFERENCE_MSB	0x87
#define QT_KEY2_REFERENCE_LSB	0x88
#define QT_KEY2_REFERENCE_MSB	0x89
#define QT_KEY3_REFERENCE_LSB	0x8A
#define QT_KEY3_REFERENCE_MSB	0x8B
#define QT_KEY4_REFERENCE_LSB	0x8C
#define QT_KEY4_REFERENCE_MSB	0x8D
#define QT_KEY5_REFERENCE_LSB	0x8E
#define QT_KEY5_REFERENCE_MSB	0x8F
#define QT_KEY6_REFERENCE_LSB	0x90
#define QT_KEY6_REFERENCE_MSB	0x91
#define QT_KEY7_REFERENCE_LSB	0x92
#define QT_KEY7_REFERENCE_MSB	0x93
#define QT_KEY8_REFERENCE_LSB	0x94
#define QT_KEY8_REFERENCE_MSB	0x95
#define QT_KEY9_REFERENCE_LSB	0x96
#define QT_KEY9_REFERENCE_MSB	0x97
#define QT_KEY10_REFERENCE_LSB	0x98
#define QT_KEY10_REFERENCE_MSB	0x99
#define QT_KEY11_REFERENCE_LSB	0x9A
#define QT_KEY11_REFERENCE_MSB	0x9B
#define QT_KEY12_REFERENCE_LSB	0x9C
#define QT_KEY12_REFERENCE_MSB	0x9D
#define QT_KEY13_REFERENCE_LSB	0x9E
#define QT_KEY13_REFERENCE_MSB	0x9F
#define QT_KEY14_REFERENCE_LSB	0xA0
#define QT_KEY14_REFERENCE_MSB	0xA1
#define QT_KEY15_REFERENCE_LSB	0xA2
#define QT_KEY15_REFERENCE_MSB	0xA3


#endif /* QTOUCHREGISTERS_H_ */
