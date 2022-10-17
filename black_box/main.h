#ifndef MAIN_H
#define MAIN_H

#include <xc.h>
#include "timer0.h"
#include "clcd.h"
#include "matrix_keypad.h"
#include "ext_eeprom.h"
#include "i2c.h"
#include "ds1307.h"
#include "uart.h"
#include "adc.h"


#define COUNT_ADDR		0x00
#define MAX_PASS_SIZE		5
#define MAX_GEAR		6
#define MAX_STORE		10
#define SUCCESS		1
#define FAILURE		0
#define MAX_MENU_COUNT		5
#define VIEW_LOG		0
#define CLEAR_LOG		1
#define DOWNLOAD_LOG		2
#define SET_TIME		3
#define CHANGE_PWD		4


/*
	//To read Pot value
	unsigned short adc_reg_val;
	adc_reg_val = read_adc(CHANNEL4);
	
	//To read Matrix switch
	char key = read_switches(STATE_CHANGE);
	
	//To print in clcd
	clcd_print("_", LINE2(i));
	
	//For RTC
	void write_ds1307(unsigned char address, unsigned char data)
	unsigned char read_ds1307(unsigned char address)
	
	//For EEPROM
	void write_ext_eeprom(unsigned char address, unsigned char data)
	unsigned char read_ext_eeprom(unsigned char address)

*/

void set_new_time(void);
void view_clcd(void);
void store_data_to_eep(void);
int check_events(unsigned char key);
void check_speed(unsigned short adc_reg_val);
int check_matrix_keypad(unsigned char key);
int check_matrix_password(void);
void display_cursor(void);
char display_menu(unsigned char key);
int clear_log(char reset_flag);
void download_log(unsigned char reset_flag, char event_count);
void reset_password(char real_pass[]);
void view_log(unsigned char key, char reset_flag, char event_count);
void display_cursor_reset(unsigned char i);
void set_time(unsigned char key);


#endif
