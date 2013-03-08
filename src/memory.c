#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>

#ifdef UNITTEST_OPCODES
   #define UNIT_TEST 1
#else
   #define UNIT_TEST 0
#endif

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
uint8_t mock_rb(Z80 * z80, Memory * mem, uint16_t addr)
{
   return mem->addr[addr];    
}

/* Write byte */              
int mock_wb(Z80 * z80, Memory * mem, uint16_t addr, uint8_t value)
{
   mem->addr[addr] = value;   

   return 0;
}

/* 16 bit */                  
/* Read word */               
uint16_t mock_rw(Z80 * z80, Memory * mem, uint16_t addr)
{
   return (rb(z80,mem,(addr+1)) << 8) + rb(z80,mem,(addr));
}

/* Write word */              
int mock_ww(Z80 * z80, Memory * mem, uint16_t addr, uint16_t value) 
{
   mem->addr[addr] = (value & 0xFF);
   mem->addr[addr + 1] = ((value & 0xFF00) >> 8);

   return 0;                  
}
/* END MMU */

int mock_InitMemory(Memory * memory)
{
   int random_seed = time(NULL), i = 0;
   printf("Random seed == %x\n",random_seed);
   srand(random_seed);

   for ( i=0 ; i<0xFFFF ; i++ )
   {
      memory->addr[i] = rand() % 0xF;
   }
}

/* MMU */
/* 8 bit */
/* Read byte */
uint8_t rb(Z80 * z80, Memory * mem, uint16_t addr)
{
   // Mock function
   int mock_func_return = 0;
   if (UNIT_TEST == 1)
   {
      mock_func_return = mock_rb(z80,mem,addr);
      return mock_func_return;
   }

   switch(addr & 0xF000)
   {
      case 0x0000:
         if (mem->bios_rom_loaded == 1)
         {
            if (addr < 0x100)
            {
               return mem->bios_rom[addr];
            } else if (z80->regPC == 0x0100) {
               mem->bios_rom_loaded = 0;
            }
         }
         return mem->bank0[addr];
      break;

      // bank0
      case 0x1000:
      case 0x2000:
      case 0x3000:
         return mem->bank0[addr];
      break;

      // bankNNN
      case 0x4000:
      case 0x5000:
      case 0x6000:
      case 0x7000:
         return mem->bank0[addr & 0x6FFF];
      break;

      // vram
      case 0x8000:
      case 0x9000:
         return mem->vram[addr & 0x1FFF];
      break;

      // eram
      case 0xA000:
      case 0xB000:
         return mem->eram[addr & 0x1FFF];
      break;

      // wram0
      case 0xC000:
         return mem->wram0[addr & 0x1FFF];
      break;

      // wram1 (switchable bank in CGB)
      case 0xD000:
         return mem->wram1[addr & 0x2FFF];
      break;

      // wram (shadow)
      case 0xE000:
         return mem->wram_shadow[addr & 0x1FFF];
      break;

      default:
      break;

      return 0;
   }

   // Working RAM shadow and sat
   switch(addr & 0xFF00)
   {
      case 0xF000: case 0xF100: case 0xF200: case 0xF300:
      case 0xF400: case 0xF500: case 0xF600: case 0xF700:
      case 0xF800: case 0xF900: case 0xFA00: case 0xFB00:
      case 0xFC00: case 0xFD00:
         return mem->wram_shadow[addr & 0x1FFF];
      break;

      case 0xFE00:
         if (addr < 0xFFA0)
         {
            return mem->sat[addr & 0xFF];
         } else {
            // Unaddressable memory region
            err.code = 30;
            exiterror(&err);
         }
      break;

      case 0xFF00:
         if (addr < 0xFF80)
         {
            return mem->io_ports[addr & 0xFF];
         } else {
            return mem->hram[addr & 0x7F];
         }
      break;
   }

   /* Timer registers */
   switch(addr & 0xFFFF)
   {
      case 0xFF04:
         return mem->div;
      break;

      case 0xFF05:
         return mem->tima;
      break;

      case 0xFF06:
         return mem->tma;
      break;

      case 0xFF07:
         return mem->tac;
      break;

      default:
      break;

      return 0;
   }

   return 0;
}

/* Write byte */
int wb(Z80 * z80, Memory * mem, uint16_t addr, uint8_t value)
{
   // Mock function
   int mock_func_return = 0;
   if (UNIT_TEST == 1)
   {
      mock_func_return = mock_wb(z80,mem,addr,value);
      return mock_func_return;
   }

   /* Timer registers */
   switch(addr & 0xFFFF)
   {
      case 0xFF04:
         mem->div = value;
      break;

      case 0xFF05:
         mem->tima = value;
      break;

      case 0xFF06:
         mem->tma = value;
      break;

      case 0xFF07:
         mem->tac = value;
      break;
   }

   // Working RAM shadow and sat
   switch(addr & 0xFF00)
   {
      case 0xF000: case 0xF100: case 0xF200: case 0xF300:
      case 0xF400: case 0xF500: case 0xF600: case 0xF700:
      case 0xF800: case 0xF900: case 0xFA00: case 0xFB00:
      case 0xFC00: case 0xFD00:
         mem->wram_shadow[addr & 0x1FFF] = value;
      break;

      case 0xFE00:
         if (addr < 0xFFA0)
         {
            mem->sat[addr & 0xFF] = value;
         } else {
            // Unaddressable memory region
            err.code = 30;
            exiterror(&err);
         }
      break;

      case 0xFF00:
         if (addr < 0xFF80)
         {
            mem->io_ports[addr & 0xFF] = value;
         } else {
            mem->hram[addr & 0x7F] = value;
         }
      break;
   }

   return 0;
}

/* 16 bit */
/* Read word */
uint16_t rw(Z80 * z80, Memory * mem, uint16_t addr)
{
   // Mock function
   //int mock_func_return = 0;
   //if (UNIT_TEST == 1)
   //{
      //mock_func_return = mock_rw(z80,mem,addr);
      //return mock_func_return;
   //}

   return (rb(z80,mem,(addr+1)) << 8) + rb(z80,mem,(addr));
}

/* Write word */
int ww(Z80 * z80, Memory * mem, uint16_t addr, uint16_t value)
{
   // Mock function
   //int mock_func_return = 0;
   //if (UNIT_TEST == 1)
   //{
      //mock_func_return = mock_ww(z80,mem,addr,value);
      //return mock_func_return;
   //}

   //mem->addr[addr] = (value & 0xFF);
   wb(z80,mem,addr,(value & 0xFF));
   //mem->addr[addr + 1] = ((value & 0xFF00) >> 8);
   wb(z80,mem,(addr + 0x1),((value & 0xFF00) >> 8));

   return 0;
}
/* END MMU */

int InitMemory(Memory * memory)
{
   // Mock function
   int mock_func_return = 0;
   if (UNIT_TEST == 1)
   {
      mock_func_return = mock_InitMemory(memory);
      return mock_func_return;
   }

   /* Start in BIOS ROM */
   memory->bios_rom_loaded = 1;

   return 0;
}
