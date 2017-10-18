

#define PWM0_SET_OUTPUT SET(DDRD,_BV(PD7),OUT)


byte PWM_Modify(byte lightness);

void PWM_initialise(void);
