#include "game_console.h" 
#include "test.h"
#include "LCD.h"
#include "GameMan.h"
#include "PWM.h"
#include "DirectRemember.h"

extern byte State;
extern byte MAN_x;
extern byte MAN_y;
extern byte Rate;

extern byte Que[6];
extern byte index;
extern byte Stage;

extern byte Lightness;

extern byte Score;

extern byte Score_Flag;



byte sketch_column;
byte sketch_page;

ISR(INT0_vect)
{
	cli();
	// Button_Test();
	// _delay_ms(500);
	// BAT_LOW_LED(ON);
	if (State == MAN)
	{
		if(~UP_BUTTON) 
		{
			LCD_Draw_Man2(MAN_y,MAN_x,0);
			if(MAN_x > 5)
				MAN_x -= 2;
			LCD_Draw_Man2(MAN_y,MAN_x,1);
		}
		else if(~DOWN_BUTTON) 
		{
			LCD_Draw_Man2(MAN_y,MAN_x,0);
			if(MAN_x < 60)
				MAN_x += 2;
			LCD_Draw_Man2(MAN_y,MAN_x,1);
		} 
		else if(~LEFT_BUTTON) 
		{
			// LCD_Draw_Man(MAN_x,MAN_y,0);
			// if(MAN_x > 5)
			// 	MAN_x -= 2;
			// LCD_Draw_Man(MAN_x,MAN_y,1);
		}
		else if(~RIGHT_BUTTON) 
		{
			// LCD_Draw_Man(MAN_x,MAN_y,0);
			// if(MAN_x < 97)
			// 	MAN_x += 2;
			// LCD_Draw_Man(MAN_x,MAN_y,1);
		}
		else if(~FA_BUTTON)
		{
			if(Rate == RATE_MAN_FAST)
				Rate = RATE_MAN_SLOW;
			else if (Rate == RATE_MAN_MEDIUM)
				Rate = RATE_MAN_FAST;
			else if (Rate == RATE_MAN_SLOW)
				Rate = RATE_MAN_MEDIUM;
		} 
		else if(~FB_BUTTON) 
		{
			State = TEST;
			LCD_Clear();
		}
		else
		{
		}
	}
	else if (State == TEST)
	{
		// BAT_LOW_LED(ON);
		if(~UP_BUTTON) 
		{
			if(sketch_page > 0)
			{
				LCD_Write_Sketch(sketch_column, sketch_page, 0);
				sketch_page--;
				LCD_Write_Sketch(sketch_column, sketch_page, 1);
			}
		}
		else if(~DOWN_BUTTON) 
		{
			if(sketch_page < 8)
			{
				LCD_Write_Sketch(sketch_column, sketch_page, 0);
				sketch_page++;
				LCD_Write_Sketch(sketch_column, sketch_page, 1);
			}
		} 
		else if(~LEFT_BUTTON) 
		{
			if(sketch_column > 1)
			{
				LCD_Write_Sketch(sketch_column, sketch_page, 0);
				sketch_column--;
				LCD_Write_Sketch(sketch_column, sketch_page, 1);
			}
		}
		else if(~RIGHT_BUTTON) 
		{
			if(sketch_column < 101)
			{
				LCD_Write_Sketch(sketch_column, sketch_page, 0);
				sketch_column++;
				LCD_Write_Sketch(sketch_column, sketch_page, 1);
			}
		}
		else if(~FA_BUTTON)
		{
			LCD_Write_Sketch(sketch_column, sketch_page, 0);
			sketch_column = 0;
			sketch_page = 0;
			LCD_Write_Sketch(sketch_column, sketch_page, 1);
		} 
		else if(~FB_BUTTON) 
		{
			State = DIRECT;
			Score_Flag = 1;
			Rate = RATE_MAN_SLOW;
			LCD_Clear();
			DIRECT_Init();
		}
		else
		{
		}
	}
	else if (State == DIRECT)
	{
		// BAT_LOW_LED(ON);
		if(~UP_BUTTON && Stage == INPUT) 
		{
			if(Que[index] == UP)
			{
				
				LCD_DR_display(index, Que[index]);
				index ++;
				if(index == 6)
				{
					Score ++;
					Stage = READY;
					Display_Score();
					Score_Flag = 0;
				}
			}
			else
			{
				Stage = READY;
				LCD_DR_display(index, WRONG);
				Score_Flag = 1;
			}
		}
		else if(~DOWN_BUTTON && Stage == INPUT) 
		{
			if(Que[index] == DOWN)
			{
				LCD_DR_display(index, Que[index]);
				index ++;
				if(index == 6)
				{
					Score ++;
					Stage = READY;
					Display_Score();
					Score_Flag = 0;
				}
			}
			else
			{
				Stage = READY;
				LCD_DR_display(index, WRONG);
				Score_Flag = 1;
			}
		} 
		else if(~LEFT_BUTTON && Stage == INPUT) 
		{
			if(Que[index] == LEFT)
			{
				LCD_DR_display(index, Que[index]);
				index ++;
				if(index == 6)
				{
					Score ++;
					Stage = READY;
					Display_Score();
					Score_Flag = 0;
				}
			}
			else
			{
				Stage = READY;
				LCD_DR_display(index, WRONG);
				Score_Flag = 1;
			}
		}
		else if(~RIGHT_BUTTON && Stage == INPUT) 
		{
			if(Que[index] == RIGHT)
			{
				LCD_DR_display(index, Que[index]);
				index ++;
				if(index == 6)
				{
					Score ++;
					Stage = READY;
					Display_Score();
					Score_Flag = 0;
				}
			}
			else
			{
				Stage = READY;
				LCD_DR_display(index, WRONG);
				Score_Flag = 1;
			}
		}
		else if(~FA_BUTTON && Stage == READY)
		{
			Stage = SHOW;
			DIRECT_Init();
		} 
		else if(~FB_BUTTON) 
		{
			State = MAN;
			LCD_Clear();
			MAN2_Init();
		}
		else
		{
		}
	}
	if(~LIGHT_BUTTON) 
	{
		if(Lightness == 200)
			Lightness = 0;
		else
			Lightness += 50;
		PWM_Modify(Lightness);
	}

	// BAT_LOW_LED(OFF);
	sei();




}
