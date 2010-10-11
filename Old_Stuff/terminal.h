#define WHITE_TXT 0x07 // white on black text

void terminal_init();
int get_mem(int row, int column);
int get_current_mem();
int get_current_row();
int get_current_column();
void k_clear_screen();
unsigned int k_printf(char *message);

