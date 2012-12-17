#include <string.h>
#ifndef _INCL_STDINT
   #define _INCL_STDINT
   #include <stdint.h>
#endif

#ifdef UNITTEST_OPCODES
   #ifndef _INCL_MOCK_HELPER
      #define _INCL_MOCK_HELPER
      #include "mock_helper.h"
   #endif
#else
   #ifndef _INCL_MEMORY
      #define _INCL_MEMORY
      #include "memory.h"
   #endif
   #ifndef _INCL_Z80
      #define _INCL_Z80
      #include "z80.h"
   #endif
#endif

/* MMU */
/* 8 bit */
/* Read byte */
uint8_t rb(Memory * mem, uint16_t addr)
{
   switch(addr & 0xF000)
   {
      case 0x0000:
         if (mem->bios_rom_loaded == 1)
         {
            if (addr < 0x100)
            {
               return mem->bios_rom[addr];
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
         return mem->bank0[addr];
      break;

      default:
      break;

      return 0;
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
int wb(Memory * mem, uint16_t addr, uint8_t value)
{
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

      default:
      break;

      return 0;
   }

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
