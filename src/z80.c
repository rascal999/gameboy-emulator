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
      /*Fetch(memory,z80);*/
      Execute(memory,z80);
   }

   /* Testing register manipulation */
   z80->r->A = 1;

   return 0;
}

int Fetch(Memory * memory, Z80 * z80)
{
   /* Fetch correct number of bytes for instruction and decode */
   /* switch(memory->addr[z80->PC] & 0x00FF)
   {
   } */
   return 0; 
}

int Execute(Memory * memory, Z80 * z80)
{
   int debug = 1;
   Error error;

   usleep(50000);

   if (debug == 1) printf("rb %x\n",rb(memory,(z80->PC)));

   /* switch((memory->addr[z80->PC] & 0xFF00) >> 8) */
   switch(rb(memory,(z80->PC)))
   {
      case 0x00:
         z80->PC++;
         z80->ticks = 4;
      break;

      case 0x31: /* LD SP,nn */
         z80->SP = (rb(memory,(z80->PC+2)) << 8) + rb(memory,(z80->PC+1));
         z80->PC = z80->PC + 2;
         z80->ticks = 12;
         if (debug == 1) printf("SP = %x\n",z80->SP);
      break;

      case 0xFF: /* RST 0x38 */
         z80->SP--;
         z80->SP = z80->PC;
         z80->SP--;
         z80->PC = 0x38;
         z80->ticks = 16;
         if (debug == 1) printf("SP = %x\nPC = %x\n",z80->SP,z80->PC);
      break;

      default:
         error.code = 20;
         exiterror(&error);
      break;
   }

   z80->PC++;

   return 0;
}

int HertzToMilliseconds(int Hertz)
{
   int ms = (Hertz / 1) * 1000;
   usleep(ms);

   return 0;
}
