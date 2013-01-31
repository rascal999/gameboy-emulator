#include <string.h>
#ifndef _INCL_STDINT
   #define _INCL_STDINT
   #include <stdint.h>
#endif

#ifdef UNITTEST_OPCODES
   #ifndef _INCL_ERROR
      #define _INCL_ERROR
      #include "mock_error.h"
   #endif
   #ifndef _INCL_MEMORY
      #define _INCL_MEMORY
      #include "mock_memory.h"
   #endif
   #ifndef _INCL_Z80
      #define _INCL_Z80
      #include "mock_z80.h"
   #endif
#else
   #ifndef _INCL_ERROR
      #define _INCL_ERROR
      #include "error.h"
   #endif
   #ifndef _INCL_MEMORY
      #define _INCL_MEMORY
      #include "memory.h"
   #endif
   #ifndef _INCL_Z80
      #define _INCL_Z80
      #include "z80.h"
   #endif
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
