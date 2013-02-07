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
   #include "mock_rom.h"
   #include "mock_timer.h"
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

Error err;

/* MMU */
/* 8 bit */                   
/* Read byte */
uint8_t rb(Memory * mem, uint16_t addr)
{
   return mem->addr[addr];    
}

/* Write byte */              
int wb(Memory * mem, uint16_t addr, uint8_t value)
{
   mem->addr[addr] = value;   

   return 0;
}

/* 16 bit */                  
/* Read word */               
uint16_t rw(Memory * mem, uint16_t addr)
{
   return (rb(mem,(addr+1)) << 8) + rb(mem,(addr));
}

/* Write word */              
int ww(Memory * mem, Z80 * z80, uint16_t addr, uint16_t value) 
{
   mem->addr[addr] = value;   
   return 0;                  
}
/* END MMU */

int InitMemory(Memory * memory)
{
   /* Start in BIOS ROM */
   memory->bios_rom_loaded = 1;

   return 0;
}
