/*
 * ADC.h
 *
 * Created: 2017/10/4 10:45:00
 *  Author: shikin
 */ 


#ifndef ADC_H_
#define ADC_H_

#define ADC5 0x05
#define ADC6 0x06
#define ADC7 0x07

#define ADC_CLK_DIV2	0x01
#define ADC_CLK_DIV4	0x02
#define ADC_CLK_DIV8	0x03
#define ADC_CLK_DIV16	0x04
#define ADC_CLK_DIV32	0x05
#define ADC_CLK_DIV64	0x06

#define REF_SEL_256		0x03
#define FREE_RUNNING 	0x00

// ADMUX REG
#define ADC_SET_REF(REF) 		SET(ADMUX,(_BV(REFS1) | _BV(REFS0)),REF)	// Select Reference
#define ADC_SET_SEL(ADCn) 		SET(ADMUX,(_BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1) | _BV(MUX0)),ADCn)	//Select ADC
#define ADC_LEFT_ADJUST(STATE) 	SET(ADMUX,_BV(ADLAR),STATE) 				// Set Left Adjust 

// ADC Control and Status Register A - ADCSRA
#define ADC_EN(STATE) 			SET(ADCSRA,_BV(ADEN),STATE)			// Enable ADC
#define ADC_SC(STATE) 			SET(ADCSRA,_BV(ADSC),STATE)			// Start Conversation
#define ADC_ATE(STATE) 			SET(ADCSRA,_BV(ADATE),STATE)		// Auto Trigger Enable
#define ADC_IF(STATE) 			SET(ADCSRA,_BV(ADIF),STATE)			// Interrupt Flag
#define ADC_IE(STATE)			SET(ADCSRA,_BV(ADIE),STATE)			// Interrupt Enable
#define ADC_PSB(STATE)			SET(ADCSRA,(_BV(ADPS2)|_BV(ADPS1)|_BV(ADPS0)),STATE)			// Prescaler Select Bits to set the CLK Division

// Special FunctionIO Register - SFIOR
#define ADC_ADT(STATE) 			SET(SFIOR,(_BV(ADTS2)|_BV(ADTS1)|_BV(ADTS0)),STATE)				// ADC Auto Trigger Source

float BatVolGet();










#endif /* ADC_H_ */