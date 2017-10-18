#include "game_console.h"
#include "PWM.h"
#include "LCD.h"


extern byte Lightness;

void Button_Test()
{
	if(~UP_BUTTON) 
		BAT_LOW_LED(OFF);
	else if(~DOWN_BUTTON) 
		BAT_LOW_LED(OFF); 
	else if(~LEFT_BUTTON) 
		BAT_LOW_LED(OFF);
	else if(~RIGHT_BUTTON) 
		BAT_LOW_LED(OFF);
	else if(~FA_BUTTON) 
		BAT_LOW_LED(OFF);
	else if(~FB_BUTTON) 
		BAT_LOW_LED(OFF);
	else if(~LIGHT_BUTTON) 
		BAT_LOW_LED(OFF);
	else
		BAT_LOW_LED(ON);	
}
void PWM_Test()
{

	//SET(PORTD,_BV(PD7),OFF);

	PWM_Modify(Lightness);
		
	

	Lightness ++;
	_delay_ms(10);
}


void LCD_Test()
{
	LCD_Fill();
	BAT_LOW_LED(ON);
	_delay_ms(1000);
	LCD_Clear();
	BAT_LOW_LED(OFF);
	_delay_ms(1000);

}

void ADC_Test()
{
	if(ADCSRA & (1<<ADIF))
	{
		ADCSRA ^= (1<<ADIF);
		ADCSRA ^= (1<<ADSC);
	
		//Buffer_Clear();
		_delay_ms(10);
		LCD_Draw_Num(1,0,(ADCH/100),1);
		LCD_Draw_Num(8,0,(ADCH%100)/10,1);
		LCD_Draw_Num(16,0,(ADCH%10),1);

		BAT_LOW_LED(ON);
		_delay_ms(100);
			
			//LCD_Clear();
		LCD_Draw_Num(1,0,(ADCH/100),0);
		LCD_Draw_Num(8,0,(ADCH%100)/10,0);
		LCD_Draw_Num(16,0,(ADCH%10),0);
		BAT_LOW_LED(OFF);
		_delay_ms(100);

		ADCSRA |= (1<<ADSC);
			
		}
}