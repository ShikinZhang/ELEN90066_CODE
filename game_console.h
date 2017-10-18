/*************************************************************************
Title:    Game Console Template Header File
Inital Author:   David Jahshan
Extended by : (PUT YOUR NAME HERE) (PUT YOUR STUDENT NUMBER HERE) 
Software: AVR-GCC 
Hardware: ATMEGA16 @ 8Mhz 

DESCRIPTION:
	Macros for Game Console

*************************************************************************/

#include <avr/io.h> 
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>



#define byte unsigned char 

/*State*/
#define TEST	0x00
#define DIRECT	0X01
#define MAN		0x02
#define PAUSE 	0x03



/*ON OFF*/
#define ON 0xFF
#define OFF 0x00
#define HIGH 0xFF
#define LOW 0x00
#define IN 0x00
#define OUT 0xFF
#define ALL 0xFF
#define TRUE 1
#define FALSE 0
#define FORWARD 0x00
#define BACK 0xFF
#define PULLUP 0xFF

/*SET and GET MACRO*/
#define SET(PORT,MASK,VALUE) PORT = ((MASK & VALUE) | (PORT & ~MASK))
#define GET(PORT,MASK) PORT & MASK

//Devices Direction MACROs
//#define MULTI_LINES_DIR(DIR) SET(DDR?,(_BV(P?#)|_BV(P?#)|_BV(P?#)),DIR)
#define BAT_LOW_LED_DIR(DIR) SET(DDRA,_BV(PA4),DIR)

// Button Direction 
#define UP_BUTTON_DIR(DIR) 		SET(DDRC,_BV(PC0),DIR)
#define DOWN_BUTTON_DIR(DIR) 	SET(DDRD,_BV(PD4),DIR)
#define LEFT_BUTTON_DIR(DIR) 	SET(DDRD,_BV(PD6),DIR)
#define RIGHT_BUTTON_DIR(DIR) 	SET(DDRD,_BV(PD5),DIR)
#define FA_BUTTON_DIR(DIR) 		SET(DDRD,_BV(PD3),DIR)
#define FB_BUTTON_DIR(DIR) 		SET(DDRD,_BV(PD0),DIR)
#define LIGHT_BUTTON_DIR(DIR) 	SET(DDRD,_BV(PD1),DIR)

// LCD Direction
#define LCD_CS_DIR(DIR) 		SET(DDRA,_BV(PA3),DIR)
#define LCD_RST_DIR(DIR) 		SET(DDRA,_BV(PA2),DIR)
#define LCD_CD_DIR(DIR) 		SET(DDRA,_BV(PA1),DIR)

// SPI Direction
#define SCK_DIR(DIR) 		SET(DDRB,_BV(PB7),DIR)
#define MISO_DIR(DIR) 		SET(DDRB,_BV(PB6),DIR)
#define MOSI_DIR(DIR) 		SET(DDRB,_BV(PB5),DIR)

//FRAM
#define WP_DIR(DIR) 		SET(DDRB,_BV(PB3),DIR)
#define HOLD_DIR(DIR) 		SET(DDRB,_BV(PB2),DIR)
#define CS_DIR(DIR) 		SET(DDRA,_BV(PA0),DIR)

// Interrupt Direction
#define INT_DIR(DIR) 		SET(DDRD,_BV(PD2),DIR)
// Battery Detection Direction
#define BAT_DETECTION_DIR(DIR)	SET(DDRA,_BV(PA7),DIR)
// Back Light Controller Direction
#define BACKLIGHT_DIR(DIR) 		SET(DDRD,_BV(PD7),DIR)
// SS
#define MCU_SS_DIR(DIR) 		SET(DDRB,_BV(PB4),DIR)


//Devices Outputs
//#define MULTI_LINES(STATE) SET(DDR?,(_BV(P?#)|_BV(P?#)|_BV(P?#)),DIR)

#define BAT_LOW_LED(STATE) SET(PORTA,_BV(PA4),STATE)

#define UP_BUTTON_INIT(DIR) 		SET(PORTC,_BV(PC0),DIR)
#define DOWN_BUTTON_INIT(DIR) 		SET(PORTD,_BV(PD4),DIR)
#define LEFT_BUTTON_INIT(DIR) 		SET(PORTD,_BV(PD6),DIR)
#define RIGHT_BUTTON_INIT(DIR) 		SET(PORTD,_BV(PD5),DIR)
#define FA_BUTTON_INIT(DIR) 		SET(PORTD,_BV(PD3),DIR)
#define FB_BUTTON_INIT(DIR) 		SET(PORTD,_BV(PD0),DIR)
#define LIGHT_BUTTON_INIT(DIR) 		SET(PORTD,_BV(PD1),DIR)

#define LCD_CS_INIT(DIR) 		SET(PORTA,_BV(PA3),DIR)
#define LCD_RST_INIT(DIR) 		SET(PORTA,_BV(PA2),DIR)
#define LCD_CD_INIT(DIR) 		SET(PORTA,_BV(PA1),DIR)

#define LCD_CHIP_SELECT 		SET(PORTA,_BV(PA3),LOW)
#define LCD_CHIP_DESELECT 		SET(PORTA,_BV(PA3),HIGH)
#define LCD_CD_SET(STATE) 		SET(PORTA,_BV(PA1),STATE)

#define INT_STATE(STATE) 		SET(PORTD,_BV(PD2),STATE)

#define MCU_SS_INI(STATE) SET(PORTB,_BV(PB4),STATE)


#define WP_INIT(STATE) 		SET(PORTB,_BV(PB3),STATE)
#define HOLD_INIT(STATE) 	SET(PORTB,_BV(PB2),STATE)
#define CS_INIT(STATE) 		SET(PORTA,_BV(PA0),STATE)

#define CS_SELECT			SET(PORTA,_BV(PA0),LOW)
#define CS_DESELECT			SET(PORTA,_BV(PA0),HIGH)
#define SCK_HIGH 			SET(PORTB,_BV(PB7),HIGH)
#define SCK_LOW 			SET(PORTB,_BV(PB7),LOW)
#define MOSI_HIGH			SET(PORTB,_BV(PB5),HIGH)
#define MOSI_LOW			SET(PORTB,_BV(PB5),LOW)


//Devices Inputs
//#define UP_BUTTON GET(PIN?,_BV(P?#))

#define UP_BUTTON		GET(PINC,_BV(PC0))
#define DOWN_BUTTON 	GET(PIND,_BV(PD4))
#define LEFT_BUTTON 	GET(PIND,_BV(PD6))
#define RIGHT_BUTTON 	GET(PIND,_BV(PD5))
#define FA_BUTTON 		GET(PIND,_BV(PD3))
#define FB_BUTTON 		GET(PIND,_BV(PD0))
#define LIGHT_BUTTON 	GET(PIND,_BV(PD1))

#define MISO_READ 		GET(PINB,_BV(PB6))
