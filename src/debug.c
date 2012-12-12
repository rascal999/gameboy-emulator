#include <stdio.h>
#include <stdlib.h>

#ifndef _INCL_MEMORY
   #define _INCL_MEMORY
   #include "memory.h"
#endif
#ifndef _INCL_Z80
   #define _INCL_Z80
   #include "z80.h"
#endif
#ifndef _INCL_DEBUG
   #define _INCL_DEBUG
   #include "debug.h"
#endif

int DebugFullInstruction(Z80 * z80, Memory * memory)
{
   int i;
   int k = DebugNextInstructionSize(rb(memory,z80->r->PC));

   printf("FULL = ");
   for(i=0;i<k;i++)
   {
      printf("%x",rb(memory,(z80->r->PC + i)));
   }
   printf("\n");

   return 0;
}

int DebugAll(Z80 * z80, Memory * memory, Debug * debug)
{
   /* CPU Dump */
   printf("-------------\n");
   printf("| D E B U G |\n");
   printf("-------------\n");
   printf("OPCODE = %x\n",rb(memory,(z80->r->PC)));
   DebugFullInstruction(z80,memory);
   printf("\n");
   printf("A = %x\tB = %x\tC = %x\n",z80->r->A,z80->r->B,z80->r->C);
   printf("D = %x\tE = %x\tH = %x\n",z80->r->D,z80->r->E,z80->r->H);
   printf("L = %x\tSP\n",z80->r->L,z80->r->SP);
   printf("PC = %x\n",z80->r->PC);
   printf("-------------\n");
   printf("| E   N   D |\n");
   printf("-------------\n");
   printf("\n");

   return 0;
}

int DebugNextInstructionSize(uint8_t opcode)
{
   switch(opcode)
   {
      case 0x00:
      case 0x32:
      case 0xAF:
      case 0xFF:
         return 1;
      break;

      case 0x21:
      case 0x31:
         return 3;
      break;

      default:
         return 0;
      break;
   }
}
