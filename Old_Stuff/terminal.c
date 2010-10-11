#define MAX_ROWS 25
#define MAX_COLUMNS 80

#include "terminal.h"

unsigned int current_row = 1;
unsigned int current_column = 0;

int current_style = WHITE_TXT;

void terminal_init()
{
	k_clear_screen();
	current_row = 0;
	current_column = 0;
}

int get_mem(int row, int column)
{
	return ((row * MAX_COLUMNS) + column) * 2;
}

int get_current_mem()
{
  return get_mem(current_row, current_column);
}

void k_clear_screen() // clear the entire text screen
{
	char *vidmem = (char *) 0xb8000;
	unsigned int i=0;
	while(i < (MAX_COLUMNS*MAX_ROWS*2))
	{
		vidmem[i]=' ';
		i++;
		vidmem[i]=WHITE_TXT;
		i++;
	};
};

unsigned int k_printf(char *message)
{

        char *vidmem = (char *) 0xb8000;
        unsigned int i=0;
        unsigned int y=0;

        /* i=((current_row*MAX_COLUMNS) + current_column) * 2; */
        i=((y*MAX_COLUMNS) + current_column) * 2;

        while(*message!=0)
        {
                if(*message=='\n') // check for a new line
                {
						y++;
                        current_row++;
                        current_column = 0;
                        /* i=((current_row*MAX_COLUMNS) + current_column) * 2; */
                        i=((y*MAX_COLUMNS) + current_column) * 2;
                        message++;
                } else {
                        vidmem[i]=*message;
                        current_column++;
                        message++;
                        i++;
                        vidmem[i]=WHITE_TXT;
                        i++;
                };
        };

        return(1);
};
