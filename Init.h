/*
 * Init.h
 *
 * Created: 2017/10/4 10:36:41
 *  Author: shikin
 */ 
#include "game_console.h" 
#include "ADC.h"
#include "LCD.h"

#ifndef INIT_H_
#define INIT_H_

#define ADC_CLK2 0x00

#define FREE_RUNNING 0x00

byte Fram_Buffer_Init();
void Direction_Init();
void ADC_Init();
void SPI_Init();
void Interrupt_Init();
void FRAM_Init();






#endif /* INIT_H_ */
