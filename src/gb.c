#include <stdio.h>

#ifdef UNITTEST_OPCODES
   #include "mock_cartridge.h"
   #include "mock_display.h"
   #include "mock_error.h"
   #ifndef _INCL_MEMORY
      #define _INCL_MEMORY
      #include "mock_memory.h"
   #endif
   #include "mock_rom.h"
   #ifndef _INCL_Z80
      #define _INCL_Z80
      #include "mock_z80.h"
   #endif
#else
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
#endif

#ifndef Z80_REGISTERS
   #define regA r->r[0x0]
   #define regB r->r[0x1] 
   #define regC r->r[0x2]
   #define regD r->r[0x3]
   #define regE r->r[0x4]
   #define regF r->r[0x5]
   #define regH r->r[0x6]
   #define regL r->r[0x7]
   #define regPC r->r16[0x0]
   #define regSP r->r16[0x1]
#endif

int main()
{
   //Cartridge cartridge;
   //Display display;
   //Error error;
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);
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

   return 0;
}
