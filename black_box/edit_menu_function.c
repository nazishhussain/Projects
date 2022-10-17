#include "main.h"
#include <string.h>
int adr1=0x00, lap = 0, fl = 1;
unsigned int wait;
void view_log(unsigned char key, char reset_flag, char event_count)
{
		if(!reset_flag)
		{	
			clcd_print("... VIEW LOG....", LINE1(0));
			adr1=0x00;
			char ch;
			if(key == MK_SW8 || key == MK_SW9)
			fl = 1;
			

				if(key == MK_SW8 &&  lap < event_count)
				{
					lap++;
				}
				else if(key == MK_SW9 && lap > 0)
				{
					lap--;
				}
			if(fl &&  lap <= event_count)
			{
			
				adr1 = adr1 + (16 * lap);
				for(int i = 0; i <= 15; i++)
				{
					ch = read_ext_eeprom(adr1++);
					clcd_putch(ch, LINE2(i));
				}
				fl = 0;
			}

							
				
		}
		else
		{
			clcd_print("..DATA NOT......", LINE1(0));
			clcd_print("-----AVAILABLE--", LINE2(0));
		}
}

void download_log(unsigned char reset_flag, char event_count)
{
	adr1 = 0x00;
	char data;
	if(!reset_flag)
	{
		for(int k=0; k <= event_count; k++)
		{
			for(int i=0; i<=15; i++)
			{
				data = read_ext_eeprom(adr1++);
				putch(data);
			}
			puts("\n\r");
		}
		
		puts("\n\r");
		
		puts("\n\r    DOWNLOADED  \n\r");
		puts("\n\r!!SUCCESSFULLY!!\n\r");
		puts("\n\r");
		puts("\n\r");
		
		clcd_print("DOWNLOADING DATA", LINE1(0));
		for(int i=15; i--;)
		{
			clcd_putch('.', LINE2(15-i));
			for(int j=60000; j--;);
		}
		clcd_print("    DOWNLOADED  ", LINE1(0));
		clcd_print("!!SUCCESSFULLY!!", LINE2(0));
		for(int k=18;k--;)
			for(int i=50000; i--;);
	}
	else
	{
		clcd_print("NO DATA PRESENT", LINE1(0));
		clcd_print("  TO DOWNLOAD  ", LINE2(0));
		
		puts("\n\rNO DATA PRESENT\n\r");
		puts("\n\r  TO DOWNLOAD  \n\r");
		puts("\n\r");
		puts("\n\r");
		for(int k=25;k--;)
			for(int i=50000; i--;);
		
	}
}

int clear_log(char reset_flag)
{
	

	if(!reset_flag)
	{
		clcd_print("RESETTING DATA..", LINE1(0));
		for(int i=15; i--;)
		{
			clcd_putch('.', LINE2(15-i));
			for(int j=60000; j--;);
		}
		clcd_print(" RESET / GO TO  ", LINE1(0));
		clcd_print(" home save data ", LINE2(0));
		
		for(int k=25;k--;)
			for(int i=50000; i--;);
		
	}
	else
	{
		clcd_print(" NO DATA FOUND  ", LINE1(0));
		clcd_print("  TO CLEAR LOG  ", LINE2(0));
		for(int k=25;k--;)
			for(int i=50000; i--;);
	}

	return SUCCESS;
}

void reset_password(char real_pass[])
{
	unsigned char key, pass1[MAX_PASS_SIZE], pass2[MAX_PASS_SIZE], atmpt = 0, i = 0;
	pass1[MAX_PASS_SIZE - 1] = '\0';
	pass2[MAX_PASS_SIZE - 1] = '\0';
	clcd_print("ENTER NEW PASS", LINE1(0));
	
	while(1)
	{
		display_cursor_reset(i);
		key = read_switches(STATE_CHANGE);
		if(key == MK_SW8 && i < (MAX_PASS_SIZE - 1)  && atmpt == 0)
		{	
			clcd_print("*", LINE2(i + 6));
			pass1[i++] = '0';
    		}
    		else if(key == MK_SW9 && i < (MAX_PASS_SIZE - 1) && atmpt == 0)
    		{	
			clcd_print("*", LINE2(i + 6));
			pass1[i++] = '1';
    		}	   
    			
    		

		if(key == MK_SW8 && i < (MAX_PASS_SIZE - 1) && atmpt == 1)
		{
			clcd_print("*", LINE2(i + 6));
			pass2[i++] = '0';
    		}
    		else if(key == MK_SW9 && i < (MAX_PASS_SIZE - 1) && atmpt == 1)
    		{
			clcd_print("*", LINE2(i + 6));
			pass2[i++] = '1';
    		}
		if(!strcmp(pass1, pass2))
		{
			clcd_print("SUCCESSFULL!!!!!", LINE1(0));
			clcd_print("PASS CHANGED....", LINE2(0));
			for(int k=25;k--;)
			for(int i=50000; i--;);
			strcpy(real_pass, pass1);
			return ;
		}
		else if (i == (MAX_PASS_SIZE - 1) && atmpt == 1)
		{	
			
			clcd_print("...Ohhhh....!!!!.", LINE1(0));
			clcd_print("PASS CHANGE FAIL", LINE2(0));
			for(int k=25;k--;)
			for(int i=50000; i--;);
			return;
		}
		else if(i == (MAX_PASS_SIZE - 1))
		{
			clcd_print("RE-ENTER NEW PAS", LINE1(0));
			clcd_print("                ", LINE2(0));
			atmpt = 1;
			i=0;	
		}
	}
	
}
void display_cursor_reset(unsigned char i)
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











