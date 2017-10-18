#include "LCD.h"
#include "GameMan.h"
#include "SPI.h"
#include "Init.h"


/*Game MAN*/
byte Line_x [ 4 ];
byte Line_y [ 4 ];

byte MAN_x;
byte MAN_y;
byte MAN_state;
extern byte random;
extern byte Score;
extern byte Score_MAN_max;

/*version2 Game MAN*/
byte LineX [4]; // 0~7
byte LineY [4];	// 0~100

void MAN2_Init()
{
	LCD_MAN_Init();
	byte cnt=0;
	for (cnt = 0; cnt < 4; cnt++)
	{
		LineX[cnt] = 3;
	}
	LineY[0] = 0;
	LineY[1] = LineY[0] + 15;
	LineY[2] = LineY[1] + 15;
	LineY[3] = LineY[2] + 15;

	MAN_x = 30;
	MAN_y = 26;
	MAN_state = ON_LINE;

	Score = 0;
	LCD_Draw_Num(32,0,Score_MAN_max/100,1);
	LCD_Draw_Num(40,0,(Score_MAN_max%100)/10,1);
	LCD_Draw_Num(48,0,Score_MAN_max%10,1);
}

byte Man2Check()
{
	if(MAN_y < 3)
		return DEAD;
	else if (MAN_y > 59)
		return DEAD;

	if(MAN_y >= LineY[0]-1 && MAN_y <= LineY[0]+1 && MAN_x >= (LineX[0] * 8) && MAN_x <= (LineX[0]*8 + 7 ) )
		MAN_state = ON_LINE;
	else if(MAN_y >= LineY[1]-1 && MAN_y <= LineY[1]+1 && MAN_x >= (LineX[1] * 8) && MAN_x <= (LineX[1]*8 + 7 ) )
		MAN_state = ON_LINE;
	else if(MAN_y >= LineY[2]-1 && MAN_y <= LineY[2]+1 && MAN_x >= (LineX[2] * 8) && MAN_x <= (LineX[2]*8 + 7 ) )
		MAN_state = ON_LINE;
	else if(MAN_y >= LineY[3]-1 && MAN_y <= LineY[3]+1 && MAN_x >= (LineX[3] * 8) && MAN_x <= (LineX[3]*8 + 7 ) )
		MAN_state = ON_LINE;
	else
		MAN_state = OFF_LINE;
	return LIVE;
}


void GAME_MAN2 ()
{
	LCD_Write_Sketch(LineY[0], LineX[0], 0);
	LCD_Write_Sketch(LineY[1], LineX[1], 0);
	LCD_Write_Sketch(LineY[2], LineX[2], 0);
	LCD_Write_Sketch(LineY[3], LineX[3], 0);


	LCD_Draw_Man2(MAN_y,MAN_x,0);
	//LCD_Clear(); 

	
 	if(LineY[0] > 15)
 	{
 		LineX[3] = LineX[2];
 		LineY[3] = LineY[2];
 		LineX[2] = LineX[1];
 		LineY[2] = LineY[1];
 		LineX[1] = LineX[0];
 		LineY[1] = LineY[0];

 		LineX[0] = (random % 6) + 2;
 		LineY[0] = 0;
 		
		Score ++;
		Score %= 999;
 	}
 	LineY[0] ++;
 	LineY[1] ++;
 	LineY[2] ++;
 	LineY[3] ++;
 	if(Man2Check() == DEAD)
	{
		
		if (Score + 2 > Score_MAN_max)
		{
			LCD_Draw_Num(32,0,Score_MAN_max/100,0);
			LCD_Draw_Num(40,0,(Score_MAN_max%100)/10,0);
			LCD_Draw_Num(48,0,Score_MAN_max%10,0);

			FRAM_Init();
			SPI_Sim_Tx_8bit(0x06);
			SPI_SR_Write();
			SPI_Sim_Tx_8bit(0x06);
			FRAM_Write (1, 0, Score);

			SPI_Init();	
			Score_MAN_max = Score;
		}
		MAN2_Init();
	}

 	if(MAN_state == ON_LINE)
 		MAN_y ++;
 	else if (MAN_state == OFF_LINE)
 		MAN_y --;
	

 	
	LCD_Write_Sketch(LineY[0], LineX[0], 1);
	LCD_Write_Sketch(LineY[1], LineX[1], 1);
	LCD_Write_Sketch(LineY[2], LineX[2], 1);
	LCD_Write_Sketch(LineY[3], LineX[3], 1);
	LCD_Draw_Man2(MAN_y,MAN_x,1);

	Display_Score();
}









void MAN_Init()
{
	byte cnt=0;
	for (cnt = 0; cnt < 4; cnt++)
	{
		Line_x[cnt] = 40;
	}
	Line_y[0] = 63;
	Line_y[1] = Line_y[0] - 15;
	Line_y[2] = Line_y[1] - 15;
	Line_y[3] = Line_y[2] - 15;

	MAN_x = 50;
	MAN_y = 63-15;
	MAN_state = ON_LINE;

	Score = 0;
}


byte ManCheck()
{
	if(MAN_y < 5)
		return DEAD;
	else if (MAN_y > 60)
		return DEAD;

	if(MAN_y >= Line_y[0]-1 && MAN_y <= Line_y[0]+1 && MAN_x > Line_x[0] && MAN_x < (Line_x[0] + LINE_LEN) )
		MAN_state = ON_LINE;
	else if(MAN_y >= Line_y[1]-1 && MAN_y <= Line_y[1]+1  && MAN_x > Line_x[1] && MAN_x < (Line_x[1] + LINE_LEN) )
		MAN_state = ON_LINE;
	else if(MAN_y >= Line_y[2]-1 && MAN_y <= Line_y[2]+1  && MAN_x > Line_x[2] && MAN_x < (Line_x[2] + LINE_LEN) )
		MAN_state = ON_LINE;
	else if(MAN_y >= Line_y[3]-1 && MAN_y <= Line_y[3]+1  && MAN_x > Line_x[3] && MAN_x < (Line_x[3] + LINE_LEN) )
		MAN_state = ON_LINE;
	else
		MAN_state = OFF_LINE;


	return LIVE;
}



void GAME_MAN ()
{
	

	LCD_Draw_Horizon(Line_x[0],Line_y[0],LINE_LEN,0);
	LCD_Draw_Horizon(Line_x[1],Line_y[1],LINE_LEN,0);
	LCD_Draw_Horizon(Line_x[2],Line_y[2],LINE_LEN,0);
	LCD_Draw_Horizon(Line_x[3],Line_y[3],LINE_LEN,0);
	LCD_Draw_Man(MAN_x,MAN_y,0);
	LCD_Clear(); 

	
 	if(Line_y[0] < 48)
 	{
 		Line_x[3] = Line_x[2];
 		Line_y[3] = Line_y[2];
 		Line_x[2] = Line_x[1];
 		Line_y[2] = Line_y[1];
 		Line_x[1] = Line_x[0];
 		Line_y[1] = Line_y[0];

 		Line_x[0] = random % 79;
 		Line_y[0] = 63;
 	}
 	Line_y[0] --;
 	Line_y[1] --;
 	Line_y[2] --;
 	Line_y[3] --;
 	if(ManCheck() == DEAD)
		MAN_Init();

 	if(MAN_state == ON_LINE)
 		MAN_y --;
 	else if (MAN_state == OFF_LINE)
 		MAN_y ++;
	
	Score = Line_y[0];
	Score %= 999;
 	
	LCD_Draw_Horizon(Line_x[0],Line_y[0],LINE_LEN,1);
	LCD_Draw_Horizon(Line_x[1],Line_y[1],LINE_LEN,1);
	LCD_Draw_Horizon(Line_x[2],Line_y[2],LINE_LEN,1);
	LCD_Draw_Horizon(Line_x[3],Line_y[3],LINE_LEN,1);
	LCD_Draw_Man(MAN_x,MAN_y,1);

	Display_Score();
}
