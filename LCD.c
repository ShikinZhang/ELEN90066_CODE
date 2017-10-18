/*
 * LCD.c
 *
 * Created: 2017/10/4 11:48:32
 *  Author: shikin
 */ 

#include "LCD.h"

byte num[10][16];

extern byte Frame_Buffer[MAX_COLUMNS][MAX_PAGES];
extern int Score;
extern byte FRAM_TEST[16];




void LCD_tx (char cData)
{
/* Start transmission */
SPDR = cData;
/* Wait for transmission complete */
while(!(SPSR & (1<<SPIF)))
;
}

byte LCD_command_tx(byte tx_byte) //Sends a command byte
{
	LCD_CHIP_SELECT;
	LCD_CD_SET(COMMAND);
	LCD_tx(tx_byte);
	LCD_CHIP_DESELECT;
	return(TRUE);
}

byte LCD_data_tx(byte tx_byte) //Sends a data byte
{
	LCD_CHIP_SELECT;
	LCD_CD_SET(DATA);
	LCD_tx(tx_byte);
	LCD_CHIP_DESELECT;
	return(TRUE);
}

byte Select_Page (byte page)
{
	if (page > MAX_PAGES)
		page = MAX_PAGES-1;//if page selected beyound limit set to last page
	if (page < 0)
		page = 0;//if page selected is negtive set to first page
	byte page_cmd_address;
	page_cmd_address = (CMD_PAGE | page);
	LCD_command_tx(page_cmd_address);
	return(TRUE);
}

byte Select_Column (byte column)
{
	if (column > MAX_COLUMNS)
		column = MAX_COLUMNS-1;
	if (column < 0)
		column = 0;
	byte colunmn_cmd_address_LSB;
	byte colunmn_cmd_address_MSB;
	colunmn_cmd_address_LSB = (CMD_COL_LSB | (column&0x0F));
	colunmn_cmd_address_MSB = (CMD_COL_MSB | (column >> 4));
	LCD_command_tx(colunmn_cmd_address_LSB);
	LCD_command_tx(colunmn_cmd_address_MSB);
	return(TRUE);
}

byte Get_Page(byte y)
{
	if (y > 63)
		y = 63;
	return y/8;
}

byte Get_Page_Date(byte y)
{
	if (y > 63)
		y = 63;
	return (1<<y%8);
}
byte Get_Column(byte x)
{
	if (x > 101)
		x = 101;
	return x;
}


void LCD_Init()
{
	LCD_RST_INIT(HIGH);
	_delay_ms(20);
	LCD_RST_INIT(LOW);
	_delay_ms(20);
	LCD_RST_INIT(HIGH);
	_delay_ms(20);

	LCD_command_tx(0x40);
	LCD_command_tx(0xA1);
	LCD_command_tx(0xC0);
	LCD_command_tx(0xA4);
	LCD_command_tx(0xA6);

	_delay_ms(120);
	LCD_command_tx(0xA2);
	LCD_command_tx(0x2F);
	LCD_command_tx(0x27);
	LCD_command_tx(0x81);
	LCD_command_tx(0x10);
	LCD_command_tx(0xFA);
	LCD_command_tx(0x90);
	LCD_command_tx(0xAF);

	LCD_Clear();
	//Get_num();

	

}

void LCD_Write_Sketch(byte column, byte page, byte drawORclear)
{
	Select_Column(column);
	Select_Page(page);
	if(drawORclear == 1)
		LCD_data_tx(0xFF);
	else
		LCD_data_tx(0x00);
}

void LCD_MAN_Init()
{
	byte page, column;
	for (page = 0; page < MAX_PAGES; page++)
	{
		for (column = 66; column < MAX_COLUMNS; column++)
		{
			Select_Page(page);
			Select_Column(column);
			LCD_data_tx(0xFF);
		}
	}	
}

byte LCD_Fill(void)
{	
	byte page, column;
	for (page = 0; page < MAX_PAGES; page++)
	{
		for (column = 0; column < MAX_COLUMNS; column++)
		{
			Select_Page(page);
			Select_Column(column);
			LCD_data_tx(0xFF);
		}
	}
	return(TRUE);
}

void LCD_Clear(void)
{	
	byte page, column;
	for (page = 0; page < MAX_PAGES; page++)
	{
		for (column = 0; column < MAX_COLUMNS; column++)
		{
			Select_Page(page);
			Select_Column(column);
			// Frame_Buffer[column][page] &= 0x00;
			LCD_data_tx(0x00);
		}
	}
}

void LCD_Draw_Point(byte x,byte y,byte drawORclear)
{
	byte page, column;
	column = Get_Column(x);
	page = Get_Page(y);
	if (drawORclear == 1)
		Frame_Buffer[column][page] |= Get_Page_Date(y);
	else
		Frame_Buffer[column][page] ^= Get_Page_Date(y);

	Select_Page(page);
	Select_Column(column);
	LCD_data_tx(Frame_Buffer[column][page]);
}

void LCD_Clear_Point(byte x,byte y)
{
	byte page, column;
	column = Get_Column(x);
	page = Get_Page(y);
	Frame_Buffer[column][page] ^= Get_Page_Date(y);

	Select_Page(page);
	Select_Column(column);
	LCD_data_tx(Frame_Buffer[column][page]);
}

void LCD_Draw_Line(byte x1, byte y1, byte x2, byte y2, byte drawORclear)
{
	byte x,y;
	float cnt;
	float delta_x,delta_y;
	float f_x1,f_y1;
	float f_x2,f_y2;
	float f_x,f_y;
	f_x1 = x1;
	f_y1 = y1;
	f_x2 = x2;
	f_y2 = y2;
	for (cnt = 0; cnt < 128; cnt ++)
	{
		delta_x = (f_x2- f_x1) * cnt / 127.0;
		delta_y = (f_y2- f_y1) * cnt / 127.0;

		f_x = f_x1 + delta_x;
		f_y = f_y1 + delta_y;

		x = (byte) f_x;
		y = (byte) f_y;

		LCD_Draw_Point(x,y,drawORclear);
	}
}

void LCD_Draw_Horizon(byte x, byte y, byte len, byte drawORclear)
{
	byte temp_x;
	for (temp_x = 0; temp_x < len; temp_x++)
		LCD_Draw_Point(x+temp_x,y,drawORclear);

}

void LCD_Draw_Man(byte x, byte y, byte drawORclear)
{
	LCD_Draw_Point(x,y,drawORclear);
	LCD_Draw_Point(x,y-1,drawORclear);
	LCD_Draw_Point(x,y-2,drawORclear);
	LCD_Draw_Point(x,y-3,drawORclear);
	LCD_Draw_Point(x,y-4,drawORclear);
	LCD_Draw_Point(x,y-5,drawORclear);		
	LCD_Draw_Point(x-1,y-5,drawORclear);
	LCD_Draw_Point(x+1,y-5,drawORclear);
	LCD_Draw_Point(x,y-6,drawORclear);
}
void LCD_Draw_Man2(byte x, byte y, byte drawORclear)
{
	LCD_Draw_Point(x,y,drawORclear);
	LCD_Draw_Point(x+1,y,drawORclear);
	LCD_Draw_Point(x+2,y,drawORclear);
	LCD_Draw_Point(x+3,y,drawORclear);
	LCD_Draw_Point(x+4,y,drawORclear);
	LCD_Draw_Point(x+5,y-1,drawORclear);		
	LCD_Draw_Point(x+5,y+1,drawORclear);
	LCD_Draw_Point(x+5,y,drawORclear);
	LCD_Draw_Point(x+6,y,drawORclear);
}

void LCD_Write_Page(byte column, byte page, byte data, byte drawORclear)
{
	// if(drawORclear == 1)
	// 	Frame_Buffer[column ][page] |= data;
	// else
	// 	Frame_Buffer[column ][page] ^= data;
	Select_Page(page);
	Select_Column(column);
	// LCD_data_tx(Frame_Buffer[column][page]);
	if(drawORclear == 1)
		LCD_data_tx(data);
	else
		LCD_data_tx(0x00);
}


void LCD_Draw_Num(byte x, byte y, byte n, byte drawORclear)
{
	byte page, column, i;
	column = Get_Column(x);
	page = Get_Page(y);

	for (i = 0; i< 16; i++)
	{
		LCD_Write_Page(column + (i/2), page + (i%2), num[n][i], drawORclear);
	}
}

void Display_Score()
{
	static byte Score_delay;
	LCD_Draw_Num(0, 0, Score_delay/100, 0);
	LCD_Draw_Num(8, 0, (Score_delay%100)/10, 0);
	LCD_Draw_Num(16, 0, (Score_delay%10), 0);

	Score_delay = Score;
	LCD_Draw_Num(1, 0, Score_delay/100, 1);
	LCD_Draw_Num(8, 0, ((Score_delay)%100)/10, 1);
	LCD_Draw_Num(16, 0, (Score_delay%10), 1);
}

void Test_For_FRAM()
{
	byte page, column, i;
	column = 1;
	page = 1;

	for (i = 0; i< 16; i++)
	{
		LCD_Write_Page(column + (i/2), page + (i%2), FRAM_TEST[i], 1);
	}
}

void LCD_DR_show(byte dir, byte drawORclear)
{
	byte col;
	byte p3,p4,p5,p6,p7;
	col = 20;
	// For Left and Right

	if(dir == RIGHT)
	{
		p3 = 0xff;
		p4 = 0x00;
		p6 = 0x00;
		p7 = 0xff;
		for (col = 30; col < 80; col ++)
		{
			LCD_Write_Page(col, 5, 0xff, drawORclear);		
			if(col > 59 && col <= 67)
			{
				LCD_Write_Page(col, 3, p3, drawORclear);
				LCD_Write_Page(col, 4, p4, drawORclear);	
				LCD_Write_Page(col, 6, p6, drawORclear);
				LCD_Write_Page(col, 7, p7, drawORclear);

				p3 = p3 << 1;
				p4 = (p4 << 1) + 0x01;
				p6 = (p6 >> 1) + 0x80;
				p7 = p7 >> 1;

			}
			if(col > 67 && col <= 75)
			{
				// LCD_Write_Page(col, 3, p3, drawORclear);
				LCD_Write_Page(col, 4, p4, drawORclear);	
				LCD_Write_Page(col, 6, p6, drawORclear);
				// LCD_Write_Page(col, 7, p7, drawORclear);

				p4 = p4 << 1;
				p6 = p6 >> 1;
			}
			if(col == 77)
				LCD_Write_Page(col, 5, 0x7e, drawORclear);
			if(col == 78)
				LCD_Write_Page(col, 5, 0x3c, drawORclear);
			if(col == 79)
				LCD_Write_Page(col, 5, 0x18, drawORclear);
		}

	}
	else if (dir == LEFT)
	{
		p3 = 0x00;
		p4 = 0x80;
		p6 = 0x01;
		p7 = 0x00;
		for(col = 30; col < 80; col ++)
		{
			LCD_Write_Page(col, 5, 0xff, drawORclear);

			if(col == 32)
				LCD_Write_Page(col, 5, 0x7e, drawORclear);
			if(col == 31)
				LCD_Write_Page(col, 5, 0x3c, drawORclear);
			if(col == 30)
				LCD_Write_Page(col, 5, 0x18, drawORclear);
			if(col > 33 && col <= 40)
			{
				LCD_Write_Page(col, 4, p4, drawORclear);
				LCD_Write_Page(col, 6, p6, drawORclear);
				p4 = (p4 >> 1) + 0x80;
				p6 = (p6 << 1) + 0x01;
			}

			if(col > 40 && col <= 47)
			{
				LCD_Write_Page(col, 3, p3, drawORclear);
				LCD_Write_Page(col, 4, p4, drawORclear);	
				LCD_Write_Page(col, 6, p6, drawORclear);
				LCD_Write_Page(col, 7, p7, drawORclear);

				p3 = (p3 >> 1) + 0x80;
				p4 = (p4 >> 1) ;
				p6 = (p6 << 1) ;
				p7 = (p7 << 1) + 0x01;
			}

		}
	}
	else if (dir == UP)
	{
		p3 = 0;
		p4 = 0;
		p5 = 0;
		for (col = 30; col < 80; col++)
		{
			if(col > 34 && col <= 42)
			{
				p5 = (p5 >> 1) + 0x80;
				LCD_Write_Page(col, 5, p5, drawORclear);
			}
			if(col > 42 && col <= 49)
			{
				p5 = (p5 >> 1);
				p4 = (p4 >> 1) + 0x80;
				LCD_Write_Page(col, 5, p5, drawORclear);
				LCD_Write_Page(col, 4, p4, drawORclear);
			}
			if(col > 49 && col <= 57)
			{
				LCD_Write_Page(col, 7, 0xff, drawORclear);
				LCD_Write_Page(col, 6, 0xff, drawORclear);
				LCD_Write_Page(col, 5, 0xff, drawORclear);
				LCD_Write_Page(col, 4, 0xff, drawORclear);
				if(col == 51)
					LCD_Write_Page(col, 3, 0x80, drawORclear);
				if(col == 52)
					LCD_Write_Page(col, 3, 0xC0, drawORclear);
				if(col == 53)
					LCD_Write_Page(col, 3, 0xE0, drawORclear);
				if(col == 54)
					LCD_Write_Page(col, 3, 0xE0, drawORclear);
				if(col == 55)
					LCD_Write_Page(col, 3, 0xC0, drawORclear);
				if(col == 56)
					LCD_Write_Page(col, 3, 0x80, drawORclear);
				p4 = 0xff;
				p5 = 0x00;
			}
			if(col > 57 && col <= 65)
			{
				p4 = (p4 << 1);
				p5 = (p5 << 1) + 0x01;
				LCD_Write_Page(col, 4, p4, drawORclear);
				LCD_Write_Page(col, 5, p5, drawORclear);
			}
			if(col > 65 && col < 73)
			{
				p5 = (p5 << 1);
				LCD_Write_Page(col, 5, p5, drawORclear);
			}
		}
	}
	else if (dir == DOWN)
	{
		p5 = 0;
		p6 = 0;
		p7 = 0;
		for (col = 30; col < 80; col++)
		{
			if(col > 34 && col <= 42)
			{
				p5 = (p5 << 1) + 0x01;
				LCD_Write_Page(col, 5, p5, drawORclear);
			}
			if(col > 42 && col <= 49)
			{
				p5 = (p5 << 1);
				p6 = (p6 << 1) + 0x01;
				LCD_Write_Page(col, 5, p5, drawORclear);
				LCD_Write_Page(col, 6, p6, drawORclear);
			}
			if(col > 49 && col <= 57)
			{
				LCD_Write_Page(col, 3, 0xff, drawORclear);
				LCD_Write_Page(col, 6, 0xff, drawORclear);
				LCD_Write_Page(col, 5, 0xff, drawORclear);
				LCD_Write_Page(col, 4, 0xff, drawORclear);
				if(col == 51)
					LCD_Write_Page(col, 7, 0x01, drawORclear);
				if(col == 52)
					LCD_Write_Page(col, 7, 0x03, drawORclear);
				if(col == 53)
					LCD_Write_Page(col, 7, 0x07, drawORclear);
				if(col == 54)
					LCD_Write_Page(col, 7, 0x07, drawORclear);
				if(col == 55)
					LCD_Write_Page(col, 7, 0x03, drawORclear);
				if(col == 56)
					LCD_Write_Page(col, 7, 0x01, drawORclear);
				p6 = 0xff;
				p5 = 0x00;
			}
			if(col > 57 && col <= 65)
			{
				p6 = (p6 >> 1);
				p5 = (p5 >> 1) + 0x80;
				LCD_Write_Page(col, 6, p6, drawORclear);
				LCD_Write_Page(col, 5, p5, drawORclear);
			}
			if(col > 65 && col < 73)
			{
				p5 = (p5 >> 1);
				LCD_Write_Page(col, 5, p5, drawORclear);
			}
		}
	}
	
}

void LCD_DR_display(byte index, byte dir)
{
	byte col;
	byte p;
	byte w1,w2;
	if(dir == RIGHT)
	{
		for (col = index*10; col < index*10 + 8; col++)
		{
			LCD_Write_Page(col, 5, 0x18, 1);
			if(col == index * 10 + 4)
				LCD_Write_Page(col, 5, 0x99, 1);
			if(col == index * 10 + 5)
				LCD_Write_Page(col, 5, 0x5A, 1);
			if(col == index * 10 + 6)
				LCD_Write_Page(col, 5, 0x3c, 1);
		}
	}
	else if (dir == LEFT)
	{
		for (col = index*10; col < index*10 + 8; col++)
		{
			LCD_Write_Page(col, 5, 0x18, 1);
			if(col == index * 10 + 1)
				LCD_Write_Page(col, 5, 0x3C, 1);
			if(col == index * 10 + 2)
				LCD_Write_Page(col, 5, 0x5A, 1);
			if(col == index * 10 + 3)
				LCD_Write_Page(col, 5, 0x99, 1);
		}
	}
	else if (dir == UP)
	{
		p = 16;
		for (col = index*10; col < index*10 + 8; col++)
		{
			if(col < (index * 10 + 3))
			{
				p = (p >> 1);
				LCD_Write_Page(col, 5, p, 1);
			}
			else if(col > (index * 10 + 4))
			{
				LCD_Write_Page(col, 5, p, 1);
				p = (p << 1);
			}
			else
				LCD_Write_Page(col, 5, 0xff, 1);
		}
	}
	else if (dir == DOWN)
	{
		p = 8;
		for (col = index*10; col < index*10 + 8; col++)
		{
			if(col < (index * 10 + 3))
			{
				p = (p << 1);
				LCD_Write_Page(col, 5, p, 1);
			}
			else if(col > (index * 10 + 4))
			{
				LCD_Write_Page(col, 5, p, 1);
				p = (p >> 1);
			}
			else
				LCD_Write_Page(col, 5, 0xff, 1);
		}
	}
	else if (dir == WRONG)
	{
		w1 = 0x80;
		w2 = 0x01;
		for(col = index * 10; col < index * 10 + 8; col++)
		{
			LCD_Write_Page(col, 5, w1|w2, 1);
			w1 = (w1 >> 1);
			w2 = (w2 << 1);
		}
	}
}
