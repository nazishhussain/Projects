#include "main.h"
char menu_content[MAX_MENU_COUNT][16] = {"View Log    ", "Clear Log   ", "Download Log", "Set Time    ", "Change PWD  "}, menu_star, menu_ptr = 0, ptr_flag, press_flag, press_flag2, key5;
extern unsigned long int count51;
char display_menu(unsigned char key)
	{
		if(key == MK_SW8 || key == MK_SW9)
		{
			TMR0ON = 1;
			if(key == MK_SW8)
				key5 = 8;
				
			if(key == MK_SW9)
				key5 = 9;
		}
		if(count51 > 8000 && count51 < 16000)
		{
		
			if(key == MK_SW8 || key == MK_SW9)
			{
				press_flag = 0;
				TMR0ON = 0;
				count51 = 0;
			}
			else if(key != MK_SW8 && key != MK_SW9)
			{
				press_flag = 1;
				TMR0ON = 0;
				count51 = 0;
			}
			
		
		}
		else if(count51 > 16000)
		{
			press_flag = 0;
			TMR0ON = 0;
			count51 = 0;
		}
		
		if(menu_ptr != 0 && press_flag && key5 == 8)
		{
			menu_ptr--;
			
			if(menu_star)
			{	
				menu_star = !menu_star;
			}
			key5 = 0;
		}
		if(menu_ptr != MAX_MENU_COUNT - 1 && press_flag && key5 == 9)
		{
			menu_ptr++;
				
			if(!menu_star)
			{ 
				menu_star = !menu_star;
			}
			key5 = 0;
		}



		

		if(menu_star)
		{
			clcd_putch(' ', LINE1(0));
			clcd_putch('*', LINE2(0));
		}
		else
		{
			clcd_putch('*', LINE1(0));
			clcd_putch(' ', LINE2(0));	
		}


		if(menu_ptr != MAX_MENU_COUNT - 1 && !menu_star)
		{
			clcd_print(menu_content[menu_ptr], LINE1(3));
			clcd_print(menu_content[menu_ptr + 1], LINE2(3));
		}
		else 
		{
			clcd_print(menu_content[menu_ptr - 1], LINE1(3));
			clcd_print(menu_content[menu_ptr], LINE2(3));
		}
		
		press_flag = 0;
		return menu_ptr;
		
	}
