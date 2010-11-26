#include "system.h"

int apps_init(){
   int failed = 0;
   failed = shell_init();
   if (failed != 0) 
       return failed; 
   return 0;
}
