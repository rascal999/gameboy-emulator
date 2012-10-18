#include <stdio.h>

#include "src/cartridge.h"
#include "src/display.h"
#include "src/error.h"
#ifndef _INCL_MEMORY
#define _INCL_MEMORY
#include "src/memory.h"
#endif
#include "src/rom.h"
#ifndef _INCL_Z80
#define _INCL_Z80
#include "src/z80.h"
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

   LoadGBROM(&memory,"/home/user/git/gameboy-emulator/roms/DMG_ROM.bin");
   //LoadROM("/home/user/git/gameboy-emulator/roms/tetris.gb",&cartridge);

   Dispatch(&z80);

   printf("%x\n",memory.addr[0]);
   printf("%d\n",z80.r->A);

   return 0;
}
