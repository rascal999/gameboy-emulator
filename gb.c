#include <stdio.h>
#include "src/display.h"
#include "src/memory.h"
#include "src/z80.h"

int main()
{
   Display display;
   Memory memory;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers);

   Dispatch(&z80);

   printf("%d\n",z80.r->A);

   return 0;
}
