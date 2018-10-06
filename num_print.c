#include "num_print.h"

#include <reg52.h>

#include "delay.h"

int digit_codes[10] = {63, 6, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 7, 127, 0x6f};

void set_digit(int n)
{
	P1 = digit_codes[n];
}

int gen_pos(int i)
{
	return ~(8 >> i);
}

void set_pos(int i)
{
	P0 = gen_pos(i);
}

void flash_num(int n)
{
	int dig_i, delay_period = 50;
	for(dig_i = 0; 1; dig_i++)
	{
		set_pos(dig_i);
		set_digit(n % 10);
		n /= 10;
		
		delay(delay_period);
		
		if(n == 0)
		{
			break;
		}
	}
}

