/*
 * ADC.c
 *
 * Created: 2017/10/4 10:44:52
 *  Author: shikin
 */ 

#include "game_console.h"

float BatVolGet()
{
	unsigned int BAT_read;
	float BAT_volt;
 	BAT_read = ADCH;
	BAT_volt = (BAT_read * 2.56) / 256 ;

	if (BAT_volt < 1.0) 
		BAT_LOW_LED(ON);
	else
		BAT_LOW_LED(OFF);

	return BAT_volt;

}
