/*
 * LCD.h
 *
 * Created: 2017/10/4 11:47:58
 *  Author: shikin
 */ 
#include "game_console.h"
#include "DirectRemember.h"

#ifndef LCD_H_
#define LCD_H_

#define byte unsigned char

#define CMD_PAGE 0xB0
#define CMD_COL_LSB 0x00
#define CMD_COL_MSB 0x10
#define BACK 0xFF
#define COMMAND 0x00
#define DATA 0xFF
#define LCD_CS PA7
#define LCD_RST PA6
#define LCD_CD PA5
#define MAX_PAGES 8
#define MAX_COLUMNS 101


void Get_num();
void LCD_tx (char cData);
byte LCD_command_tx(byte tx_byte);
byte LCD_data_tx(byte tx_byte);
byte Select_Page (byte page);
byte Select_Column (byte column);

void LCD_Init();
void LCD_MAN_Init();

void LCD_Write_Sketch(byte column, byte page, byte drawORclear);
void LCD_Clear(void);
byte LCD_Fill(void);
void LCD_Draw_Point(byte x,byte y,byte drawORclear);
void LCD_Clear_Point(byte x,byte y);

void LCD_Draw_Line(byte x1, byte y1, byte x2, byte y2, byte drawORclear);
void LCD_Draw_Horizon(byte x, byte y, byte len, byte drawORclear);
void LCD_Draw_Man(byte x, byte y, byte drawORclear);
void LCD_Draw_Man2(byte x, byte y, byte drawORclear);
void LCD_Write_Page(byte column, byte page, byte data, byte drawORclear);
void LCD_Draw_Num(byte x, byte y, byte n, byte drawORclear);

void Display_Score();

void LCD_DR_show(byte dir, byte drawORclear);
void LCD_DR_display(byte index, byte dir);

void Test_For_FRAM();

#endif /* LCD_H_ */