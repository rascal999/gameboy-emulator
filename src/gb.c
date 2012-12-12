#include <stdio.h>

#include "cartridge.h"
#include "display.h"
#include "error.h"
#ifndef _INCL_MEMORY
   #define _INCL_MEMORY
   #include "memory.h"
#endif
#include "rom.h"
#ifndef _INCL_Z80
   #define _INCL_Z80
   #include "z80.h"
#endif

int main()
{
   //Cartridge cartridge;
   //Display display;
   //Error error;
   Memory memory;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers);
   InitMemory(&memory);

   LoadGBROM(&memory,"/home/user/git/gameboy-emulator/roms/DMG_ROM.bin");
   //LoadGBROM(&memory,"/home/user/git/gameboy-emulator/roms/tetris.gb");
   //LoadROM("/home/user/git/gameboy-emulator/roms/tetris.gb",&cartridge);

   Dispatch(&memory,&z80);

   int i;
   for(i=0;i<100;i++)
   {
      printf("%x\n",memory.addr[i]);
   }

   printf("%d\n",z80.r->A);

   return 0;
}
