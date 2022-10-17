#include "main.h"
#include <string.h>
extern int delay_timer;
unsigned i;
char pass[MAX_PASS_SIZE], attempts, flag2 = 0; 
extern char real_pass[MAX_PASS_SIZE];
unsigned int wait;

int check_matrix_keypad(unsigned char key)
{
    if(key == MK_SW8 && attempts > 0)
    {
    	clcd_print("*", LINE2(i + 6));
	pass[i++] = '0';	
    }
    else if(key == MK_SW9 && attempts > 0)
    {
    	clcd_print("*", LINE2(i + 6));
	pass[i++] = '1';
    }   
    pass[MAX_PASS_SIZE - 1] = '\0'; 


    if(i == (MAX_PASS_SIZE - 1) && (!strcmp(pass, real_pass)) )
    {
    	clcd_print("     LOGIN      ", LINE1(0));
    	clcd_print(" SUCCESSFULL!!  ", LINE2(0));
    	for(int i=5;i--;)
	for(int j=50000;j--;);
    	attempts = 0;
       return SUCCESS;
    }
    else if(i == (MAX_PASS_SIZE - 1) && attempts > 0)
    {
    	clcd_print("                ", LINE2(0));
    	delay_timer = 60;
    	clcd_print("WRONG PASSWORD", LINE1(0));
    	attempts--;
    	clcd_print("ATTEMPTS LEFT:", LINE2(0));
    	clcd_putch('0' + attempts, LINE2(15));
    	for(int i = 10* (5-attempts); i--;)
		{
	   		RE0 = 1;
    		for(int j=10000; j--;);
		}
		if(attempts > 0)
		{
	 		RE0 = 0;
		}
    }
    else if(i == (MAX_PASS_SIZE - 1) && attempts == 0)
    { 
    	RE0 = 0;
      	delay_timer = 60;
       attempts = 3;
       RB0 = 1;
       while(1)
       {
       		clcd_print("ATTEMPTS LEFT: 0", LINE1(0));
       		clcd_print("Wait Time.....", LINE2(0));
    		clcd_putch('0' + (delay_timer / 10), LINE2(14));
    		clcd_putch('0' + (delay_timer % 10), LINE2(15));
    		if(delay_timer == 0)
    		{	
				delay_timer = 60;
    			break;
    		}
    		
       }
       RB0 = 0;
       
    }
    
    if(attempts > 0 && i == (MAX_PASS_SIZE - 1))
    {
      i=0;
      clcd_print(" ENTER  PASSWORD ", LINE1(0));
      clcd_print("                  ", LINE2(0));
    }
    
    return 55;

}



void display_cursor(void)
{
    if(i < (MAX_PASS_SIZE - 1))
    {
	if(wait++ < 2500)
	{
	    clcd_print("_", LINE2(i + 6));
	}
	else
	{
	    clcd_print(" ", LINE2(i + 6));
	    if(wait == 5000)
		wait = 0;
	}
    }
}


int check_matrix_password()
{
	unsigned char key, status;
	clcd_print(" ENTER  PASSWORD ", LINE1(0));
	attempts = 3;
	TMR0ON = 1;
    	while (1)
    	{
        	display_cursor();
        	key = read_switches(STATE_CHANGE);
        	status = check_matrix_keypad(key);
        	
        	if(status == SUCCESS || status == FAILURE)
        	{	
        		TMR0ON = 0;
        		i=0;
        		flag2 = 0;
        		return status;
        	}
        	if(delay_timer == 52 && status != SUCCESS)
        	{
        		i=0;
			delay_timer = 60;
        		TMR0ON = 0;
        		return FAILURE;
        	}
    	}
    
}

