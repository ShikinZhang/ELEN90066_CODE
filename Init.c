/*
 * Init.c
 *
 * Created: 2017/10/4 10:36:21
 *  Author: shikin
 */ 

#include "Init.h"
#include "ADC.h"


void Direction_Init()
{
	BAT_LOW_LED(OFF); //Make sure it is off before changing direction
	BAT_LOW_LED_DIR(OUT); //Set BATTERY LED I/Os as outputs.
	BACKLIGHT_DIR(OUT);
	
	UP_BUTTON_DIR(IN); //Set BUTTON I/Os as input.
	DOWN_BUTTON_DIR(IN);
	RIGHT_BUTTON_DIR(IN);
	LEFT_BUTTON_DIR(IN);
	FA_BUTTON_DIR(IN);
	FB_BUTTON_DIR(IN);

	// BUTTON PULL UP
	UP_BUTTON_INIT(PULLUP);
	DOWN_BUTTON_INIT(PULLUP);
	RIGHT_BUTTON_INIT(PULLUP);
	LEFT_BUTTON_INIT(PULLUP);
	FA_BUTTON_INIT(PULLUP);
	FB_BUTTON_INIT(PULLUP);
	LIGHT_BUTTON_INIT(PULLUP);

	LCD_CS_DIR(OUT);
	LCD_CD_DIR(OUT);
	LCD_RST_DIR(OUT);

	SCK_DIR(OUT);
    MOSI_DIR(OUT);
    MISO_DIR(IN);

	BAT_DETECTION_DIR(IN); //BATTERY

	BACKLIGHT_DIR(OUT);

	MCU_SS_DIR(OUT);

}

void ADC_Init()
{

  // 	ADC_SET_REF(REF_SEL_256);
  // 	ADC_SET_SEL(ADC7); // PA7 BATTERY

  // 	ADC_IE(ON);
  // 	ADC_PSB(ADC_CLK_DIV2);
  // 	ADC_ATE(OFF)
  // 	ADC_IF(LOW);

  //  	ADC_EN(ON);
 	// ADC_LEFT_ADJUST(ON);
  // 	ADC_SC(ON);
	ADMUX |= (1<<REFS1) | (1<<REFS0) | (1<<ADLAR) | (1<<MUX2) | (1<<MUX1) | (1<<MUX0);
	ADCSRA |= (1<<ADEN) | (1<<ADSC) ;

}


void SPI_Init()
{
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);

}

void Interrupt_Init()
{
	/* Button Interrupt */
	INT_DIR(IN);
	//MCUCR |= 0X03; //INT0 - falling enable 
	MCUCR |= _BV(ISC01) + _BV(ISC00); //rising
	GICR |= 0X40; //enable INT0

	/*Timer Interrupt with 8 Clock Div to 1MHz and 50000 counter*/	
	/*65535 - 50000 = 15535(0x3CAF) */
	TCNT1H = 0x3C;
	TCNT1L = 0XAF;
	TIMSK|=_BV(TOIE1); // Enable TC1 Overflow Interrupt 
	TCCR1B|=_BV(CS11); // 8 Clock Div
  	sei(); 

}

void FRAM_Init()
{
	SPCR = 0;
	WP_DIR(OUT);
	HOLD_DIR(OUT); 
	CS_DIR(OUT); 

	SCK_DIR(OUT);
    MOSI_DIR(OUT);
    MISO_DIR(IN);	

	WP_INIT(HIGH); 		
 	HOLD_INIT(HIGH); 	
 	CS_INIT(HIGH);
 	// SET(PORTB,_BV(PB6),0xFF); 		
}
