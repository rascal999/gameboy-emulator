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
   uint8_t i;
   //DebugNextInstructionSize(rb(memory,z80->regPC));
   uint8_t k = z80->op[rb(memory,z80->regPC)].size;

   printf("FULL = ");
   for(i=0;i<k;i++)
   {
      printf("%x ",rb(memory,(z80->regPC + i)));
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
   printf("OPCODE = %x ( %s )\n",rb(memory,(z80->regPC)),z80->op[rb(memory,(z80->regPC))].name);
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
      case 0x21:
      case 0x31:
         return 3;
      break;

      case 0x01:
      case 0x06:
      case 0x0e:

      case 0x10:
      case 0x16:
      case 0x18:
      case 0x1e:

      case 0x20:
      case 0x26:
      case 0x2e:

      case 0x30:
      case 0x36:
      case 0x3e:

      case 0xd6:
      case 0xde:

      case 0xe0:
      case 0xe2:
      case 0xe6:
      case 0xe8:
      case 0xee:

      case 0xf0:
      case 0xf2:
      case 0xf6:
      case 0xf8:
      case 0xfe:
         return 2;
      break;

      default:
         return 1;
      break;
   }
}
