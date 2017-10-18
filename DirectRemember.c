#include "LCD.h"
#include "SPI.h"
#include "Init.h"


extern byte Que[6];
extern byte index;
extern byte Stage;

extern byte Score;
extern byte Score_DIRECT_max;

byte Score_Flag;

void DIRECT_Init()
{
	byte i;
	LCD_Clear();
	if(Score_Flag == 1)
		Score = 0;

	index = 0;
	Stage = SHOW;

	for(i = 0; i < 6;)
	{

		if(ADCSRA & (1<<ADIF))
		{
			ADCSRA ^= (1<<ADIF);
			ADCSRA ^= (1<<ADSC);
			Que[i] = (ADCH & 0x03);
			ADCSRA |= (1<<ADSC);
			i++;
		}
	}

	LCD_Draw_Num(32,0,Score_DIRECT_max/100,1);
	LCD_Draw_Num(40,0,(Score_DIRECT_max%100)/10,1);
	LCD_Draw_Num(48,0,Score_DIRECT_max%10,1);

	Display_Score();
}

void GAME_DIRECT()
{
	if(Stage == SHOW)
	{
		if((index & 0x01) == 0x00)
			LCD_DR_show(Que[index>>1], 1);
		else
			LCD_DR_show(Que[index>>1], 0);
		index ++;
		if(index == 14)
		{
			Stage = INPUT;
			index = 0;
		}
	}
	else if (Stage == READY)
	{
		if(Score > Score_DIRECT_max)
		{
			LCD_Draw_Num(32,0,Score_DIRECT_max/100,0);
			LCD_Draw_Num(40,0,(Score_DIRECT_max%100)/10,0);
			LCD_Draw_Num(48,0,Score_DIRECT_max%10,0);

			FRAM_Init();
			SPI_Sim_Tx_8bit(0x06);
			SPI_SR_Write();
			SPI_Sim_Tx_8bit(0x06);
			FRAM_Write (1, 1, Score);

			SPI_Init();	
			Score_DIRECT_max = Score;

			LCD_Draw_Num(32,0,Score_DIRECT_max/100,1);
			LCD_Draw_Num(40,0,(Score_DIRECT_max%100)/10,1);
			LCD_Draw_Num(48,0,Score_DIRECT_max%10,1);
		}
	}
}
