#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>

#ifdef UNITTEST_OPCODES
   #include "mock_cartridge.h"
   #include "mock_debug.h"
   #include "mock_display.h"
   #include "mock_error.h"
   #include "mock_memory.h"
   #include "mock_opcode_attributes.h"
   #include "mock_opcode_wrappers.h"
   #include "mock_z80.h"
#else
   #include "cartridge.h"
   #include "debug.h"
   #include "display.h"
   #include "error.h"
   #include "memory.h"
   #include "opcode_attributes.h"
   #include "opcode_wrappers.h"
   #include "rom.h"
   #include "timer.h"
   #include "z80.h"
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
