# ELEN90066_CODE


## Configure

This project should do something to success build

1. Create a folder named "default"

2. In "default" create a folder named "dep"

3. Copy game_console.o.d file to the dep folder

4. In the avr studio 4, open project options. In "custom options"-->"Extern Tools" change the "avr-gcc" and "make" catalogue to your related catalog 

and then this project should be build but it might not work in your board since the pin is not the same with you. 

## My configuration

PWM --> Timer/Counter2
BUTTON INTERUPT --> INT0
INER INTERUP --> Timer/Counter1
