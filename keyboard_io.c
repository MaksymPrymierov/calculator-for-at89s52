#include "keyboard_io.h"
#include <reg52.h>

unsigned char prev_btn_indx = INVALID_BUTTON;

unsigned char get_button()
{
	unsigned char btn_indx, col_i, row_i, scancode;
	for(col_i = 0; col_i < 4; col_i++)
	{	
		P2 = 0xFF & ~(1 << col_i); //set input signals for button press detection
		
		scancode = ~(P2 >> 4);
		
		if(scancode != 0) //F0 means that no button was pressed
		{
			for(row_i = 0; row_i < 4; row_i++) 
			{
				if(scancode & (1 << row_i))
				{
					btn_indx = col_i*4+row_i;
					goto end; //break out of both loops
				}
			}
		}
		else
		{
			btn_indx = INVALID_BUTTON;
		}		
	}
	
	end:
	if(btn_indx == prev_btn_indx)
	{
		btn_indx = INVALID_BUTTON;
	}
	else
	{
		prev_btn_indx = btn_indx;
	}
	return btn_indx;
}

