#include "terminal.h"

void kmain( void* mbd, unsigned int magic )
{
   if ( magic != 0x2BADB002 )
   {
      /* Something went not according to specs. Print an error */
      /* message and halt, but do *not* rely on the multiboot */
      /* data structure. */
   }

   /* You could either use multiboot.h */
   /* (http://www.gnu.org/software/grub/manual/multiboot/multiboot.html#multiboot_002eh) */
   /* or do your offsets yourself. The following is merely an example. */
   char * boot_loader_name =(char*) ((long*)mbd)[16];


   /* Write your kernel here. */
   terminal_init();

   int i;

   for(i = 0; i < 10000000; i++);

   char str[] = "Welcome to Mark Kernel\n";
   k_printf(str);

   for(i = 0; i < 10000000; i++);

   char str2[] = "This is a \n";
   k_printf(str2);
}

