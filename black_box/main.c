/*Documentation
Name: Nazish Hussain
Date: 21/09/2022
Description: Project - BLACK BOX
*/

#include "main.h"
char real_pass[MAX_PASS_SIZE] = "0000";
extern int fl, set_time_flag;
int set_time_flag;
unsigned char time[9];
extern unsigned char new_time[9];
void set_new_time(void)
{
	write_ds1307(SEC_ADDR, (new_time[6] - '0') << 4 | (new_time[7] - '0'));
	write_ds1307(MIN_ADDR, (new_time[3] - '0') << 4 | (new_time[4] - '0'));
	write_ds1307(HOUR_ADDR, (new_time[0] - '0') << 4 | (new_time[1] - '0'));
	clcd_print("  SUCCESSFULLY  ", LINE1(0));	
	clcd_print("  Time Changed  ", LINE2(0));	
	for(int i = 20; i--;)
		for(int j = 50000; j--;);	
		
}

void init_config(void)
{
    /* Config PORTB as digital */
    ADCON1 = 0x0F;
    TRISE0 = 0;
    RE0 = 0; 
    TRISB0 = 0;
    RB0 = 0; 
    //Peripheral enable inurrupt pin
    PEIE = 1;
    GIE = 1;

    /* Configration */
    init_timer0();
    init_clcd();
    init_matrix_keypad();
    init_i2c();
    init_ds1307();
    init_uart();
    init_adc();	
}
void welcomeuser(void)
{
		clcd_print("...B.L.A.C.K....", LINE1(0));
		clcd_print(".....B.O.X......", LINE2(0));
		for(int k=20;k--;)
		for(int i=50000; i--;);
		clcd_print("---PROJECT BY---", LINE1(0));
		clcd_print(" NAZISH HUSSAIN ", LINE2(0));
		for(int k=20;k--;)
		for(int i=50000; i--;);		
}
void clear_display(void)
{
	clcd_print("                ", LINE1(0));
	clcd_print("                ", LINE2(0));
}

void main(void)
{
    init_config();
    unsigned char key, key2;
    unsigned short adc_reg_val, delay1 = 0, delay2 = 0;
    unsigned int open_flag, back_flag;
    char key7_flag = 1, menu_display_flag = 0, menu_pointer_flag, open_menu_content = 0, verify_pass_flag = 1, reset_flag = 0, check_flag = 0, event_count = 0, loop_flag = 1, wait07 = 5;
    welcomeuser();
    clear_display();
    while(1)
    {
		adc_reg_val = read_adc(CHANNEL4);
		key = read_switches(STATE_CHANGE);
		for(int i=550; i--;);
		
		key2 = read_switches(LEVEL_CHANGE);
				
	
		if(key2 == MK_SW8 || key2 == MK_SW9)
		{
   			delay1++;
   		}
		else 
		{
    			delay1 = 0;
  
		}
		
		
		
		
		
				
		if(key == MK_SW7 && !check_flag)
		{	
	    		key7_flag = !key7_flag;
	    		check_flag = 1;
		}
		
		if(key7_flag)
		{
	    		view_clcd();
			check_speed(adc_reg_val);
	    		event_count = check_events(key);
		}


		if(!key7_flag && (open_menu_content || menu_display_flag))
		{

			if(key2 == MK_SW8 && delay1 == 400)
			{
				open_menu_content = 1;
				clear_display();
				menu_display_flag = 0;
			}
			
			if (key2 == MK_SW9 && delay1 == 400)
			{
				clear_display();
				menu_display_flag = 1;
				if(open_menu_content == 0)
				{
					key7_flag = 1;
					verify_pass_flag = 1;
					menu_display_flag = 0;
					check_flag = 0;	
					reset_flag = 0;
					set_time_flag = 1;
				}
				open_menu_content = 0;
			}
			

		}



		if(menu_display_flag)
		{
			
			
			menu_pointer_flag = display_menu(key2);

			
			fl = 1;
			set_time_flag = 1;
		}
		else if(!key7_flag && verify_pass_flag)
		{
			clear_display();
			
			if(check_matrix_password() == SUCCESS)
			{
				verify_pass_flag = !verify_pass_flag;
				menu_display_flag = !menu_display_flag;
			}
			else 
			{
				key7_flag = !key7_flag;
				check_flag = 0;
			}
			clear_display();
			
		}
	
		if(open_menu_content)
		{
			switch (menu_pointer_flag)
			{
				
				case VIEW_LOG:
				{
		
					view_log(key, reset_flag, event_count);	
				}
				break;

				case CLEAR_LOG:
				{
					reset_flag = clear_log(reset_flag);
					event_count = 0;
					open_menu_content = !open_menu_content;
					menu_display_flag = !menu_display_flag;
					clear_display();
				}
				break;


				case DOWNLOAD_LOG:
				{
					download_log(reset_flag, event_count);
					open_menu_content = !open_menu_content;
					menu_display_flag = !menu_display_flag;
					clear_display();	
				}
				break;


				case SET_TIME:
				{
					set_time(key);
					if(key2 == MK_SW8 && delay1 == 1500)
					{
						set_new_time();
						open_menu_content = !open_menu_content;
						menu_display_flag = !menu_display_flag;
						clear_display();	
					}
				}
				break;

				case CHANGE_PWD:
				{
					reset_password(real_pass);
					open_menu_content = !open_menu_content;
					menu_display_flag = !menu_display_flag;
					clear_display();
				}
				break;	
			}
		}
    }
}

