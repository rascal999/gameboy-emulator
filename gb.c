#include <stdio.h>
#include "src/display.h"
#include "src/memory.h"
#include "src/z80.h"

int main()
{
   Display display;
   Memory memory;
   Z80 z80;

   InitZ80(&z80);

   printf("%d\n",z80.tmp);

   return 0;
}
