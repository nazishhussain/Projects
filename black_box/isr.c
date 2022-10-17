#include <xc.h>
#include "main.h"
int delay_timer = 60;
unsigned int long count51;
void interrupt isr(void)
{
	static unsigned short count;
     //Whenever there is overflow in (TMRx) it will call for inturrupt
	if (TMR0IF) //Checking whether both the inuturupt called at once because (8bit timers)
	{
		TMR0 = TMR0 + 8; //After 250 it should call inuturrupt
		if (count++ == 20000) //Checking for 1 second when count is 20000
		{
			count = 0;
			delay_timer--;
		}
		//Turning off the flag to avoid recursive calling
		count51++;
		TMR0IF = 0;
	}	
	
	
	
}
