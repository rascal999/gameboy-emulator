#include <stdio.h>
#include <stdlib.h>

#ifndef _INCL_Z80
#define _INCL_Z80
#include "z80.h"
#endif
#include "error.h"

int InitZ80(Z80 * z80, Registers * registers)
{
   /* http://www.devrs.com/gb/files/gbspec.txt */
   z80->r = registers;
   z80->r->A = 0x01;
   z80->r->B = 0x00;
   z80->r->C = 0x13;
   z80->r->D = 0x00;
   z80->r->E = 0xD8;
   z80->r->H = 0x01;
   z80->r->L = 0x4D;
   z80->r->F = 0xB0;
   z80->PC = 0x00;
   z80->SP = 0xFFFE;

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
   Error error;

   usleep(50000);

   if (debug == 1) printf("what %x\n",memory->addr[z80->PC]);

   switch(memory->addr[z80->PC] & 0xFF)
   {
      case 0x00:
         z80->PC++;
      break;

      case 0x31:
         z80->SP = memory->addr[z80->PC + 1] & (memory->addr[z80->PC + 2] >> 8);
         z80->PC = z80->PC + 2;
         if (debug == 1) printf("SP = %x\n",z80->SP);
      break;

      case 0xFF: /* RST 0x38 */
         z80->SP--;
         z80->SP = z80->PC;
         z80->SP--;
         z80->PC = 0x38;
         if (debug == 1) printf("SP = %x\nPC = %x\n",z80->SP,z80->PC);
      break;

      default:
         error.code = 20;
         exiterror(&error);
      break;
   }

   return 0;
}
