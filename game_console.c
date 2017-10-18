/*************************************************************************
Title:    game_console Template
Initial Author:   David Jahshan
Extended by : (Zhang Gan) (926206)
Software: AVR-GCC 
Hardware: ATMEGA16 @ 8Mhz 

DESCRIPTION:
	Main and functions for Game Console basic sample code

*************************************************************************/


#include "game_console.h" 

#include "Init.h"
#include "PWM.h"
#include "test.h"
#include "LCD.h"
#include "GameMan.h"
#include "SPI.h"


extern byte num[10][16];

int Flag;

byte Score;
byte Score_MAN_max;
byte Score_DIRECT_max;

byte Stage;
byte Que[6];
byte index;

byte Rate;
byte Count;

byte Lightness;
byte State;
byte Frame_Buffer[MAX_COLUMNS][MAX_PAGES];


byte FRAM_TEST[16];






byte random;

void Buffer_Clear()
{
	byte page, column;
	for (page = 0; page < MAX_PAGES-1; page++)
	{
		for (column = 0; column < MAX_COLUMNS-1; column++)
		{
			Frame_Buffer[column][page] = OFF;
		}
	}
}




int main(void)
{
	//BAT_LOW_LED(OFF); //Make sure it is off before changing direction
	//BAT_LOW_LED_DIR(OUT); //Set BATTERY LED I/Os as outputs.
	//UP_BUTTON_DIR(IN); //Set UP_BUTTON I/Os as input.
	

	// State = TEST;
	// Count = 0;
	// Rate = RATE_MAN_MEDIUM;
	// random = 0;
	Lightness = 128;

	// //Get_num();
	// Direction_Init();

	// FRAM_Init();

	// SPI_Sim_Tx_8bit(0x06);
	// SPI_SR_Write();
	// SPI_Sim_Tx_8bit(0x06);
	// FRAM_Write (1, 0, 10);
	// byte i;
	// byte j;
	
	// for (j = 0; j < 10; j++)
	// {
	// 	for (i = 0; i < 16; i++)
	// 	{
	// 		// SPI_Sim_Tx_8bit(0x06);
	// 		// FRAM_Write (0, i + j*16, num[j][i]);
	// 		num[j][i] = FRAM_Read(0, i + 16 * j);
	// 	}	
	// }

	// Score_MAN_max = FRAM_Read(0x01, 0x00);
	// Score_DIRECT_max = FRAM_Read(0x01, 0x01);
	// Score_MAN_max = 1;
	
	// for (i = 0; i < 16; i++)
	// 	FRAM_TEST[i] = FRAM_Read(0, i + 16);


	
	// BAT_LOW_LED(ON);
	// SPI_Init();	
	// LCD_Init();
	// LCD_Clear();
	// ADC_Init();
	
	PWM_initialise();
	PWM_Modify(Lightness);
	//Buffer_Clear(Frame_Buffer);
	// Interrupt_Init();
	

	// //Game Init
	

	// //LCD_Draw_Horizon(Line_x[0],Line_y[0],LINE_LEN,1);

	// BAT_LOW_LED(OFF);


	//BAT_LOW_LED(ON);

	while (TRUE)//Master loop always true so always loop
	{

		//Button_Test();
		//PWM_Test();
		//LCD_Test();
		//LCD_Draw_Line(0,0,50,50,1);
		//LCD_Draw_Man(40,40,1);
		//LCD_Draw_Line(50,0,50,50,0);
		//BAT_LOW_LED(ON);

		//LCD_Write_Page(1, 1, 0xff, 1);
		//LCD_Write_Page(1, 2, 0xff, 1);
		// LCD_Draw_Num(1,1,0,1);
		// LCD_Draw_Num(8,0,1,1);
		// LCD_Draw_Num(16,0,2,1);
		// LCD_Draw_Num(24,0,3,1);
		// LCD_Draw_Num(32,0,4,1);
		// LCD_Draw_Num(40,0,5,1);
		// LCD_Draw_Num(48,0,6,1);
		// LCD_Draw_Num(56,0,7,1);
		// LCD_Draw_Num(64,0,8,1);
		// LCD_Draw_Num(72,0,9,1);

		// Test_For_FRAM();
		//ADC_Test();
		// LCD_DR_show(RIGHT, 1);
		// _delay_ms(1000);
		// LCD_DR_show(RIGHT, 0);
		// LCD_DR_show(LEFT, 1);
		// _delay_ms(1000);
		// LCD_DR_show(LEFT, 0);
		// LCD_DR_show(UP, 1);
		// _delay_ms(1000);
		// LCD_DR_show(UP, 0);
		// LCD_DR_show(DOWN, 1);
		// _delay_ms(1000);
		// LCD_DR_show(DOWN, 0);

		// LCD_DR_display(0, RIGHT);
		// LCD_DR_display(1, LEFT);
		// LCD_DR_display(2, UP);
		// LCD_DR_display(3, DOWN);
		// LCD_DR_display(4, WRONG);



		// if(ADCSRA & (1<<ADIF))
		// {
		// 	ADCSRA ^= (1<<ADIF);
		// 	ADCSRA ^= (1<<ADSC);
	
		// 	if(ADCH/100 == 0)
		// 		BAT_LOW_LED(ON);
		// 	else
		// 		BAT_LOW_LED(OFF);
		// 	_delay_ms(1000);

		// 	ADCSRA |= (1<<ADSC);
			
		// }
		
		
	}

}

ISR(TIMER1_OVF_vect)
{
	cli();
	TCNT1H = 0x3C;
	TCNT1L = 0XB0;
	Count ++;
	random+=11;
	random %= 255;
	// BAT_LOW_LED(ON);
	if(Count>=Rate)
 	{
 		if(State == MAN)
 			GAME_MAN2 ();
 		else if (State == TEST)
 			;
 		else if (State == DIRECT)
 			GAME_DIRECT();
 		else
 			;


		//BAT_LOW_LED(OFF);


  		Count = 0;
 	}
 	sei();
}


