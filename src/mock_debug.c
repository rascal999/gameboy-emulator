#include <stdio.h>
#include <stdlib.h>

#ifdef UNITTEST_OPCODES
   #ifndef _INCL_MEMORY
      #define _INCL_MEMORY
      #include "mock_memory.h"
   #endif
   #ifndef _INCL_Z80
      #define _INCL_Z80
      #include "mock_z80.h"
   #endif
   #ifndef _INCL_DEBUG
      #define _INCL_DEBUG
      #include "mock_debug.h"
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
   #ifndef _INCL_DEBUG
      #define _INCL_DEBUG
      #include "debug.h"
   #endif
#endif

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

int DebugFullInstruction(Z80 * z80, Memory * memory)
{
   int i;
   int k = DebugNextInstructionSize(rb(memory,z80->regPC));

   printf("FULL = ");
   for(i=0;i<k;i++)
   {
      printf("%x",rb(memory,(z80->regPC + i)));
   }
   printf("\n");

   return 0;
}

int DebugAll(Z80 * z80, Memory * memory, Debug * debug)
{
   /* CPU Dump */
   /*printf("-------------\n");
   printf("| D E B U G |\n");
   printf("-------------\n");*/
   printf("OPCODE = %x\n",rb(memory,(z80->regPC)));
   DebugFullInstruction(z80,memory);
   printf("\n");
   printf("A = %x\tB = %x\tC = %x\n",z80->regA,z80->regB,z80->regC);
   printf("D = %x\tE = %x\tF = %x\n",z80->regD,z80->regE,z80->regF);
   printf("H = %x\tL = %x\tSP = %x\n",z80->regH,z80->regL,z80->regSP);
   printf("PC = %x\n",z80->regPC);
   /*printf("-------------\n");
   printf("| E   N   D |\n");
   printf("-------------\n");*/
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
