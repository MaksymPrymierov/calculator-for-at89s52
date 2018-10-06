#include <reg52.h>

#include "num_print.h"
#include "keyboard_io.h"
#include "delay.h"

const unsigned char PRELOAD_L = 255-100;
const unsigned char PRELOAD_H = 255-4;
int value_to_show = 0;

enum operator { ADD_OP = 14, SUB_OP = 15 }; //values correspond to button indices

void setup_timer0()
{
	EA = 1; //enable interrupts
	ET0 = 1; //enable timer0
	TMOD = (TMOD & 0xf0) | 1; //set timer mode
}

void start_timer0()
{
	TR0 = 1;
}

void stop_timer0()
{
	TR0 = 0;
}

void restart_timer0()
{
	stop_timer0();
	TH0 = PRELOAD_H;
	TL0 = PRELOAD_L;
	start_timer0();
}

void interrupt_1() interrupt 1
{
	static unsigned char dig_i = 0;
	static int div_val = 0;
	if(div_val == 0)
	{
		dig_i = 0;
		div_val = value_to_show;
	}

	set_pos(dig_i);
	set_digit(div_val % 10);

	dig_i++;
	div_val /= 10;
	
	restart_timer0();
}

void main()
{
	unsigned char btn_indx;
	int curr_val = 0, total_val = 0;

	setup_timer0();
	restart_timer0();

	while(1)
	{
		btn_indx = get_button();
		
		if(btn_indx != INVALID_BUTTON)
		{
			if(btn_indx < 10)
			{
				curr_val = curr_val*10 + btn_indx;
				value_to_show = curr_val;
			}
			else
			{
				switch(btn_indx)
				{
					case ADD_OP:
						total_val += curr_val;
						break;
					case SUB_OP:
						total_val -= curr_val;
				}
				curr_val = 0;
				value_to_show = total_val;
			}
		}
	}
}

