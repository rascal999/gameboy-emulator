#include <stdio.h>
#include <stdlib.h>

#ifndef _INCL_DEBUG
#define _INCL_DEBUG
#include "debug.h"
#endif
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
   z80->r->PC = 0x00;
   z80->r->SP = 0xFFFE;

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
   /* switch(memory->addr[z80->r->PC] & 0x00FF)
   {
   } */
   return 0; 
}

int Execute(Memory * memory, Z80 * z80)
{
   int callDebug = 1;
   uint16_t tmp;

   Debug debug;
   Error error;

   usleep(50000);

   if (callDebug == 1) printf("rb %x\n",rb(memory,(z80->r->PC)));

   if (callDebug == 1)
   {
      debug.instructionSize = 1;
      DebugAll(z80, memory, &debug);
   }

   /* switch((memory->addr[z80->r->PC] & 0xFF00) >> 8) */
   switch(rb(memory,(z80->r->PC++)))
   {
      case 0x00:
         OP_00h_NOP(memory,z80);
      break;

      case 0x21: /* LD HL,nn */
         OP_21h_LDHLnn(memory,z80);
      break;

      case 0x31: /* LD SP,nn */
         OP_31h_JRNCn(memory,z80);
      break;

      case 0x32: /* LD (HL-),A */
         OP_32h_LDDHLA(memory,z80);
      break;

      case 0xAF: /* XOR A */
         OP_AFh_XORA(memory,z80);
      break;

      case 0xFF: /* RST 0x38 */
         OP_FFh_RST38h(memory,z80);
      break;

      default:
         error.code = 20;
         exiterror(&error);
      break;
   }

   return 0;
}

int HertzToMilliseconds(int Hertz)
{
   int ms = (Hertz / 1) * 1000;
   usleep(ms);

   return 0;
}

int decrementHL(Z80 * z80)
{
   uint16_t tmpHL;

   tmpHL = (z80->r->H << 8) + z80->r->L;
   tmpHL--;

   z80->r->H = (tmpHL & 0xFF00) >> 8;
   z80->r->L = (tmpHL & 0xFF);

   return 0;
}

/* OPCODES */
int OP_00h_NOP(Memory * memory, Z80 * z80)
{
   z80->r->PC++;
   z80->ticks = 4;

   return 0;
}

int OP_21h_LDHLnn(Memory * memory, Z80 * z80)
{
   z80->r->H = rb(memory,(z80->r->PC+1));
   z80->r->L = rb(memory,(z80->r->PC));
   z80->r->PC = z80->r->PC + 2;
   z80->ticks = 12;

   return 0;
}

int OP_31h_JRNCn(Memory * memory, Z80 * z80)
{
   //z80->r->SP = (rb(memory,(z80->r->PC+2)) << 8) + rb(memory,(z80->r->PC+1));
   z80->r->SP = rw(memory,z80->r->PC);
   z80->r->PC = z80->r->PC + 2;
   z80->ticks = 12;

   return 0;
}

int OP_32h_LDDHLA(Memory * memory, Z80 * z80)
{
   uint16_t tmp;

   wb(memory,(z80->r->H << 8) + z80->r->L,0xA);
   tmp = (z80->r->H << 8) + z80->r->L;

   decrementHL(z80);
   z80->ticks = 8;

   return 0;
}

int OP_AFh_XORA(Memory * memory, Z80 * z80)
{
   z80->r->A = 0;
   z80->ticks = 4;

   return 0;
}

int OP_FFh_RST38h(Memory * memory, Z80 * z80)
{
   z80->r->SP--;
   z80->r->SP = z80->r->PC;
   z80->r->SP--;
   z80->r->PC = 0x38;
   z80->ticks = 16;

   return 0;
}
