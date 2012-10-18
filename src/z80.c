#include <stdio.h>
#include <stdlib.h>

#ifndef _INCL_Z80
#define _INCL_Z80
#include "z80.h"
#endif

int InitZ80(Z80 * z80, Registers * registers)
{
   z80->r = registers;
   z80->r->A = 0;
   z80->r->B = 0;
   z80->r->C = 0;
   z80->r->D = 0;
   z80->r->E = 0;
   z80->r->H = 0;
   z80->r->L = 0;
   z80->r->F = 0;
   z80->PC = 0;
   z80->SP = 0;

   return 0;
}

int ResetZ80(Z80 * z80, Registers * registers)
{
   InitZ80(z80,registers);

   return 0;
}

int Dispatch(Memory * memory, Z80 * z80)
{
   while(1)
   {
      Execute(memory,z80);
   }

   /* Testing register manipulation */
   z80->r->A = 1;

   return 0;
}

int Execute(Memory * memory, Z80 * z80)
{
   int debug = 1;

   switch(memory->addr[z80->PC++] & 0x00FF)
   {
      case 0x31:
         z80->SP = memory->addr[z80->PC++];
         if (debug == 1) printf("SP = %x\n",z80->SP);
      break;

      default:
         exit(1);
      break;

//      case 0x21:
         
   }

   return 0;
}
