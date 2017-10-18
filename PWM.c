#include "game_console.h"
#include "PWM.h"

void PWM_initialise(void)
{
	PWM0_SET_OUTPUT;


    TCCR2 |= (1<<WGM20)|(1<<WGM21)       // Start timer2 
             |(1<<COM21)|(1<<CS20);    
	OCR2 = 255; 
}

byte PWM_Modify(byte lightness)
{
	OCR2 = lightness;
                                         // fast PWM mode
    return 1;

}
