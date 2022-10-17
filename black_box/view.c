 #include "main.h"
unsigned char clock_reg[3], save_on_status = 1, flag22 = 1;
unsigned char time[9], event[8][3] = {"RG", "G1", "G2", "G3", "G4", "G5", "C*", "ON"}, gear = 1, flag, str_i = 0, adr = 0x00;
extern int set_time_flag = 1;
unsigned char new_time[9], field = 0;
int wait22, speed;

static void get_time(void)
{
	clock_reg[0] = read_ds1307(HOUR_ADDR);
	clock_reg[1] = read_ds1307(MIN_ADDR);
	clock_reg[2] = read_ds1307(SEC_ADDR);

	if (clock_reg[0] & 0x40)
	{
		time[0] = '0' + ((clock_reg[0] >> 4) & 0x01);
		time[1] = '0' + (clock_reg[0] & 0x0F);
	}
	else
	{
		time[0] = '0' + ((clock_reg[0] >> 4) & 0x03);
		time[1] = '0' + (clock_reg[0] & 0x0F);
	}
	time[2] = ':';
	time[3] = '0' + ((clock_reg[1] >> 4) & 0x0F);
	time[4] = '0' + (clock_reg[1] & 0x0F);
	time[5] = ':';
	time[6] = '0' + ((clock_reg[2] >> 4) & 0x0F);
	time[7] = '0' + (clock_reg[2] & 0x0F);
	time[8] = '\0';
}


void view_clcd(void)
{
		clcd_print("  TIME   EVNT SP", LINE1(0));
		get_time();
		clcd_print(time, LINE2(0));
		
}

int check_events(unsigned char key)
{
	int store_flag = 0;
	if(key == MK_SW2)
	{
		gear++;
		store_flag = 1;
		if(gear > MAX_GEAR)
		{
			store_flag = 0;
			gear = 6;
		}
		else
		{
			str_i++;
		}
		flag = 1;
	}
	else if(key == MK_SW3)
	{
		gear--;
		store_flag = 1;
		if(gear > MAX_GEAR)
		{	
			store_flag = 0;
			gear = 0;
		}
		else
		{
			str_i++;
		}
		flag = 1;
	}
	if(str_i == MAX_STORE)
	{
		flag22 = 0;
		str_i = 0;
		adr = 0x00;
	}

	if(store_flag)
			store_data_to_eep();


	if(flag)
	{
		clcd_print(event[gear], LINE2(10));
	}
	else
	{
		clcd_print(event[7], LINE2(10));
	}
	if(save_on_status)
	{
		save_on_status = 0;
		gear = 8;
		store_data_to_eep();
		gear = 1;
	}

	if(flag22)
	{
		return str_i;
	}
	else
	{
		return MAX_STORE - 1;
	}
	
}

void check_speed(unsigned short adc_reg_val)
{
	speed = adc_reg_val;
	speed = speed / 10;
	if(speed > 99)
		speed = 99;
	clcd_putch('0' + (speed / 10), LINE2(14));
	clcd_putch('0' + (speed % 10), LINE2(15));
}

void store_data_to_eep()
{
	write_ext_eeprom(adr++, '0' + str_i);
	write_ext_eeprom(adr++, ' ');
	write_ext_eeprom(adr++, time[0]);
	write_ext_eeprom(adr++, time[1]);
	write_ext_eeprom(adr++, time[2]);
	write_ext_eeprom(adr++, time[3]);
	write_ext_eeprom(adr++, time[4]);
	write_ext_eeprom(adr++, time[5]);
	write_ext_eeprom(adr++, time[6]);
	write_ext_eeprom(adr++, time[7]);
	write_ext_eeprom(adr++, ' ');
	write_ext_eeprom(adr++, event[gear][0]);
	write_ext_eeprom(adr++, event[gear][1]);
	write_ext_eeprom(adr++, ' ');
	write_ext_eeprom(adr++, '0' + speed / 10);
	write_ext_eeprom(adr++, '0' + speed % 10);
}

void set_time(unsigned char key)
{		clcd_print("  SET NEW TIME  ", LINE1(0));
		if(set_time_flag)
		{
			get_time();
			set_time_flag = 0;
			for(int i=0; i <= 8; i++)
			{
				new_time[i] = time[i];
			}
		}
		
		if(key == MK_SW8)
		{
			field++;
			if(field > 2)
			{
				field = 0;
			}
		}
		
		if(key == MK_SW9)
		{
		
			if(field == 0)
			{
				new_time[1]++;
				if(new_time[1] > '9')
				{
					new_time[1] = '0';
					new_time[0]++;
				}
				if(new_time[0] == '2' && new_time[1] == '4')
					{
						new_time[0] = '0';
						new_time[1] = '0';
					}
			}
			else if(field == 1)
			{
				new_time[4]++;
				if(new_time[4] > '9')
				{
					new_time[4] = '0';
					new_time[3]++;
					if(new_time[3] >= '6')
					{
						new_time[3] = '0';
					}
				}
			}
			else if(field == 2)
			{
				new_time[7]++;
				if(new_time[7] > '9')
				{
					new_time[7] = '0';
					new_time[6]++;
					if(new_time[6] >= '6')
					{
						new_time[6] = '0';
					}
				}
			}
		}
		
		if(wait22++ < 100)
		{
	    		clcd_print("  ", LINE2(field * 3));
		}
		else
		{
	    		clcd_print(new_time, LINE2(0));
	    		if(wait22 == 200)
				wait22 = 0;
		}
		
		
}


