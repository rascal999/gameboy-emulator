#include "memory.h"

/* MMU */
/* 8 bit */
unsigned short rb(Memory * mem, unsigned short addr)
{
   return 0;
}

int wb(Memory * mem, unsigned short addr, unsigned char value)
{
   mem->addr[addr] = value;
   return 0;
}

/* 16 bit */
unsigned short rw(Memory * mem, unsigned short addr)
{
   return 0;
}

int ww(Memory * mem, unsigned short addr, unsigned short value)
{
   mem->addr[addr] = value;
   return 0;
}
/* END MMU */

int InitMemory(Memory * memory)
{
   return 0;
}
