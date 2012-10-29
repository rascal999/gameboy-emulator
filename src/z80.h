#ifndef _INCL_MEMORY
#define _INCL_MEMORY
#include "memory.h"
#endif

typedef struct
{
   unsigned char A;
   unsigned char B;
   unsigned char C;
   unsigned char D;
   unsigned char E;
   unsigned char H;
   unsigned char L;
   unsigned char F; /* Flag */
} Registers;

typedef struct
{
   Registers * r;

   /* Clocks */
   unsigned char M;
   unsigned char T;

   unsigned short PC;
   unsigned short SP;
} Z80;

int InitZ80(Z80 * z80, Registers * registers);
int ResetZ80(Z80 * z80, Registers * registers);
int Dispatch(Memory * memory, Z80 * z80);
int Fetch(Memory * memory, Z80 * z80);
int Execute(Memory * memory, Z80 * z80);
