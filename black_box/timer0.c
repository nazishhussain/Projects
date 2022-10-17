#include <xc.h>
#include "timer0.h"

void init_timer0(void)
{
	/*
	 * Setting instruction cycle clock (Fosc / 4) as the source of
	 * timer0
	 */
    	
    	//To set timer or  counter=1
    	T0CS = 0;
   	
   	//To enable timer 0
	TMR0ON = 0;
  	
  	//For accuracy we start count from 6
	TMR0 = 6;

	/* Clearing timer0 overflow interrupt flag bit */
	TMR0IF = 0;

	/* Enabling timer0 overflow interrupt */
	TMR0IE = 1;
}
