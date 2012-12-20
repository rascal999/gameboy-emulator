#include <stdio.h>
#include <stdlib.h>
#ifndef _INCL_STDINT
   #define _INCL_STDINT
   #include <stdint.h>
#endif

#ifdef UNITTEST_OPCODES
   #ifndef _INCL_MOCK_HELPER
      #define _INCL_MOCK_HELPER
      #include "mock_helper.h"
      #undef rb
      #undef wb
      #define rb mock_rb
      #define wb mock_wb
   #endif
#else
   #ifndef _INCL_DEBUG
      #define _INCL_DEBUG
      #include "debug.h"
   #endif
   #ifndef _INCL_Z80
      #define _INCL_Z80
      #include "z80.h"
   #endif
   #ifndef _INCL_ERROR
      #define _INCL_ERROR
      #include "error.h"
   #endif
#endif

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
   Error err;

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
      case 0x00: OP_00h_NOP(memory,z80); break;
      case 0x21: OP_21h_LDHLnn(memory,z80); break;
      case 0x22: OP_22h_LDIHLA(memory,z80); break;
      case 0x31: OP_31h_JRNCn(memory,z80); break;
      case 0x40: OP_40h_LDBB(memory,z80); break;
      case 0x41: OP_41h_LDBC(memory,z80); break;
      case 0x42: OP_42h_LDBD(memory,z80); break;
      case 0x43: OP_43h_LDBE(memory,z80); break;
      case 0x44: OP_44h_LDBH(memory,z80); break;
      case 0x45: OP_45h_LDBL(memory,z80); break;
      case 0x50: OP_50h_LDDB(memory,z80); break;
      case 0x51: OP_51h_LDDC(memory,z80); break;
      case 0x52: OP_52h_LDDD(memory,z80); break;
      case 0x53: OP_53h_LDDE(memory,z80); break;
      case 0x54: OP_54h_LDDH(memory,z80); break;
      case 0x55: OP_55h_LDDL(memory,z80); break;
      case 0x60: OP_60h_LDHB(memory,z80); break;
      case 0x61: OP_61h_LDHC(memory,z80); break;
      case 0x62: OP_62h_LDHD(memory,z80); break;
      case 0x63: OP_63h_LDHE(memory,z80); break;
      case 0x64: OP_64h_LDHH(memory,z80); break;
      case 0x65: OP_65h_LDHL(memory,z80); break;
      case 0xAF: OP_AFh_XORA(memory,z80); break;
      case 0xFF: OP_FFh_RST38h(memory,z80); break;

      default:
         err.code = 20;
         exiterror(&err);
      break;
   }

   // Reset after acting on ticks
   z80->ticks = 0;

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

int incrementHL(Z80 * z80)
{
   uint16_t tmpHL;

   tmpHL = (z80->r->H << 8) + z80->r->L;
   tmpHL++;

   z80->r->H = (tmpHL & 0xFF00) >> 8;
   z80->r->L = (tmpHL & 0xFF);

   return 0;
}

int calculateAdditionFlags(Memory * memory, Z80 * z80, uint8_t dest, uint8_t oldDest, uint8_t oldSrc)
{
   // Flags
   if (((dest & 0xFF) < oldDest) | ((dest & 0xFF) < oldSrc))
   {
      // Carry
      z80->r->F = 0x10;
   }

   if ((dest & 0xFF) == 0x00)
   {
      // Zero flag
      z80->r->F = z80->r->F | 0x80;
   }

   if (((oldSrc & 0xF) + (oldDest & 0xF)) & 0x10)
   {
      // Half-carry
      z80->r->F = z80->r->F | 0x20;
   }

   return 0;
}

int calculateSubtractionFlags(Memory * memory, Z80 * z80, uint8_t dest, uint8_t oldDest, uint8_t oldSrc)
{
   // Flags
   if (((dest & 0xFF) > oldDest) | ((dest & 0xFF) > oldSrc))
   {
      // Carry
      z80->r->F = 0x10;
   }

   if ((dest & 0xFF) == 0x00)
   {
      // Zero flag
      z80->r->F = z80->r->F | 0x80;
   }

   if (((oldSrc & 0xF) - (oldDest & 0xF)) & 0x10)
   {
      // Half-carry
      z80->r->F = z80->r->F | 0x20;
   }

   //Subtract
   z80->r->F = z80->r->F | 0x40;

   return 0;
}

/* OPCODES */
int OP_00h_NOP(Memory * memory, Z80 * z80)
{
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

int OP_22h_LDIHLA(Memory * memory, Z80 * z80)
{
   uint16_t tmp;

   wb(memory,(z80->r->H << 8) + z80->r->L,z80->r->A);
   tmp = (z80->r->H << 8) + z80->r->L;

   incrementHL(z80);
   z80->ticks = 8;

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

   wb(memory,(z80->r->H << 8) + z80->r->L,z80->r->A);
   tmp = (z80->r->H << 8) + z80->r->L;

   decrementHL(z80);
   z80->ticks = 8;

   return 0;
}

int OP_40h_LDBB(Memory * memory, Z80 * z80)
{
   z80->r->B = z80->r->B;

   z80->ticks = 4;

   return 0;
}

int OP_41h_LDBC(Memory * memory, Z80 * z80)
{
   z80->r->B = z80->r->C;

   z80->ticks = 4;

   return 0;
}

int OP_42h_LDBD(Memory * memory, Z80 * z80)
{
   z80->r->B = z80->r->D;

   z80->ticks = 4;

   return 0;
}

int OP_43h_LDBE(Memory * memory, Z80 * z80)
{
   z80->r->B = z80->r->E;

   z80->ticks = 4;

   return 0;
}

int OP_44h_LDBH(Memory * memory, Z80 * z80)
{
   z80->r->B = z80->r->H;

   z80->ticks = 4;

   return 0;
}

int OP_45h_LDBL(Memory * memory, Z80 * z80)
{
   z80->r->B = z80->r->L;

   z80->ticks = 4;

   return 0;
}

int OP_48h_LDCB(Memory * memory, Z80 * z80)
{
   z80->r->C = z80->r->B;

   z80->ticks = 4;

   return 0;
}

int OP_49h_LDCC(Memory * memory, Z80 * z80)
{
   z80->r->C = z80->r->C;

   z80->ticks = 4;

   return 0;
}

int OP_4Ah_LDCD(Memory * memory, Z80 * z80)
{
   z80->r->C = z80->r->D;

   z80->ticks = 4;

   return 0;
}

int OP_4Bh_LDCE(Memory * memory, Z80 * z80)
{
   z80->r->C = z80->r->E;

   z80->ticks = 4;

   return 0;
}

int OP_4Ch_LDCH(Memory * memory, Z80 * z80)
{
   z80->r->C = z80->r->H;

   z80->ticks = 4;

   return 0;
}

int OP_4Dh_LDCL(Memory * memory, Z80 * z80)
{
   z80->r->C = z80->r->L;

   z80->ticks = 4;

   return 0;
}

int OP_4Fh_LDCA(Memory * memory, Z80 * z80)
{
   z80->r->C = z80->r->A;

   z80->ticks = 4;

   return 0;
}

int OP_50h_LDDB(Memory * memory, Z80 * z80)
{
   z80->r->D = z80->r->B;

   z80->ticks = 4;

   return 0;
}

int OP_51h_LDDC(Memory * memory, Z80 * z80)
{
   z80->r->D = z80->r->C;

   z80->ticks = 4;

   return 0;
}

int OP_52h_LDDD(Memory * memory, Z80 * z80)
{
   z80->r->D = z80->r->D;

   z80->ticks = 4;

   return 0;
}

int OP_53h_LDDE(Memory * memory, Z80 * z80)
{
   z80->r->D = z80->r->E;

   z80->ticks = 4;

   return 0;
}

int OP_54h_LDDH(Memory * memory, Z80 * z80)
{
   z80->r->D = z80->r->H;

   z80->ticks = 4;

   return 0;
}

int OP_55h_LDDL(Memory * memory, Z80 * z80)
{
   z80->r->D = z80->r->L;

   z80->ticks = 4;

   return 0;
}

int OP_58h_LDEB(Memory * memory, Z80 * z80)
{
   z80->r->E = z80->r->B;

   z80->ticks = 4;

   return 0;
}

int OP_59h_LDEC(Memory * memory, Z80 * z80)
{
   z80->r->E = z80->r->C;

   z80->ticks = 4;

   return 0;
}

int OP_5Ah_LDED(Memory * memory, Z80 * z80)
{
   z80->r->E = z80->r->D;

   z80->ticks = 4;

   return 0;
}

int OP_5Bh_LDEE(Memory * memory, Z80 * z80)
{
   z80->r->E = z80->r->E;

   z80->ticks = 4;

   return 0;
}

int OP_5Ch_LDEH(Memory * memory, Z80 * z80)
{
   z80->r->E = z80->r->H;

   z80->ticks = 4;

   return 0;
}

int OP_5Dh_LDEL(Memory * memory, Z80 * z80)
{
   z80->r->E = z80->r->L;

   z80->ticks = 4;

   return 0;
}

int OP_5Fh_LDEA(Memory * memory, Z80 * z80)
{
   z80->r->E = z80->r->A;

   z80->ticks = 4;

   return 0;
}

int OP_60h_LDHB(Memory * memory, Z80 * z80)
{
   z80->r->H = z80->r->B;

   z80->ticks = 4;

   return 0;
}

int OP_61h_LDHC(Memory * memory, Z80 * z80)
{
   z80->r->H = z80->r->C;

   z80->ticks = 4;

   return 0;
}

int OP_62h_LDHD(Memory * memory, Z80 * z80)
{
   z80->r->H = z80->r->D;

   z80->ticks = 4;

   return 0;
}

int OP_63h_LDHE(Memory * memory, Z80 * z80)
{
   z80->r->H = z80->r->E;

   z80->ticks = 4;

   return 0;
}

int OP_64h_LDHH(Memory * memory, Z80 * z80)
{
   z80->r->H = z80->r->H;

   z80->ticks = 4;

   return 0;
}

int OP_65h_LDHL(Memory * memory, Z80 * z80)
{
   z80->r->H = z80->r->L;

   z80->ticks = 4;

   return 0;
}

int OP_68h_LDLB(Memory * memory, Z80 * z80)
{
   z80->r->L = z80->r->B;

   z80->ticks = 4;

   return 0;
}

int OP_69h_LDLC(Memory * memory, Z80 * z80)
{
   z80->r->L = z80->r->C;

   z80->ticks = 4;

   return 0;
}

int OP_6Ah_LDLD(Memory * memory, Z80 * z80)
{
   z80->r->L = z80->r->D;

   z80->ticks = 4;

   return 0;
}

int OP_6Bh_LDLE(Memory * memory, Z80 * z80)
{
   z80->r->L = z80->r->E;

   z80->ticks = 4;

   return 0;
}

int OP_6Ch_LDLH(Memory * memory, Z80 * z80)
{
   z80->r->L = z80->r->H;

   z80->ticks = 4;

   return 0;
}

int OP_6Dh_LDLL(Memory * memory, Z80 * z80)
{
   z80->r->L = z80->r->L;

   z80->ticks = 4;

   return 0;
}

int OP_6Fh_LDLA(Memory * memory, Z80 * z80)
{
   z80->r->L = z80->r->A;

   z80->ticks = 4;

   return 0;
}

int OP_72h_LDHLD(Memory * memory, Z80 * z80)
{
   wb(memory,(z80->r->H << 8) + z80->r->L,z80->r->D);

   z80->ticks = 8;

   return 0;
}

int OP_78h_LDAB(Memory * memory, Z80 * z80)
{
   z80->r->A = z80->r->B;

   z80->ticks = 4;

   return 0;
}

int OP_79h_LDAC(Memory * memory, Z80 * z80)
{
   z80->r->A = z80->r->C;

   z80->ticks = 4;

   return 0;
}

int OP_7Ah_LDAD(Memory * memory, Z80 * z80)
{
   z80->r->A = z80->r->D;

   z80->ticks = 4;

   return 0;
}

int OP_7Bh_LDAE(Memory * memory, Z80 * z80)
{
   z80->r->A = z80->r->E;

   z80->ticks = 4;

   return 0;
}

int OP_7Ch_LDAH(Memory * memory, Z80 * z80)
{
   z80->r->A = z80->r->H;

   z80->ticks = 4;

   return 0;
}

int OP_7Dh_LDAL(Memory * memory, Z80 * z80)
{
   z80->r->A = z80->r->L;

   z80->ticks = 4;

   return 0;
}

int OP_7Fh_LDAA(Memory * memory, Z80 * z80)
{
   z80->r->A = z80->r->A;

   z80->ticks = 4;

   return 0;
}

int OP_80h_ADDAB(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->r->A;
   uint8_t oldSrc = z80->r->B;

   z80->r->A = z80->r->A + z80->r->B;

   uint8_t dest = z80->r->A;

   calculateAdditionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->ticks = 4;

   return 0;
}

int OP_81h_ADDAC(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->r->A;
   uint8_t oldSrc = z80->r->C;

   z80->r->A = z80->r->A + z80->r->C;

   uint8_t dest = z80->r->A;

   calculateAdditionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->ticks = 4;

   return 0;
}

int OP_82h_ADDAD(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->r->A;
   uint8_t oldSrc = z80->r->D;

   z80->r->A = z80->r->A + z80->r->D;

   uint8_t dest = z80->r->A;

   calculateAdditionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->ticks = 4;

   return 0;
}

int OP_83h_ADDAE(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->r->A;
   uint8_t oldSrc = z80->r->E;

   z80->r->A = (z80->r->A + z80->r->E) & 0xFF;

   uint8_t dest = z80->r->A;

   calculateAdditionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->ticks = 4;

   return 0;
}

int OP_84h_ADDAH(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->r->A;
   uint8_t oldSrc = z80->r->H;

   z80->r->A = z80->r->A + z80->r->H;

   uint8_t dest = z80->r->A;

   calculateAdditionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->ticks = 4;

   return 0;
}

int OP_85h_ADDAL(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->r->A;
   uint8_t oldSrc = z80->r->L;

   z80->r->A = z80->r->A + z80->r->L;

   uint8_t dest = z80->r->A;

   calculateAdditionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->ticks = 4;

   return 0;
}

int OP_87h_ADDAA(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->r->A;
   uint8_t oldSrc = z80->r->A;

   z80->r->A = z80->r->A + z80->r->A;

   uint8_t dest = z80->r->A;

   calculateAdditionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->ticks = 4;

   return 0;
}

int OP_88h_ADCAB(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->r->A;
   uint8_t oldSrc = z80->r->B;

   z80->r->A = (z80->r->A + z80->r->B) & 0xFF;

   uint8_t dest = z80->r->A & 0xFF;

   calculateAdditionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->r->A = z80->r->A + ((z80->r->F & 0x10) >> 4) & 0xFF;

   z80->ticks = 4;

   return 0;
}

int OP_89h_ADCAC(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->r->A;
   uint8_t oldSrc = z80->r->C;

   z80->r->A = (z80->r->A + z80->r->C) & 0xFF;

   uint8_t dest = z80->r->A & 0xFF;

   calculateAdditionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->r->A = z80->r->A + ((z80->r->F & 0x10) >> 4) & 0xFF;

   z80->ticks = 4;

   return 0;
}

int OP_8Ah_ADCAD(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->r->A;
   uint8_t oldSrc = z80->r->D;

   z80->r->A = (z80->r->A + z80->r->D) & 0xFF;

   uint8_t dest = z80->r->A & 0xFF;

   calculateAdditionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->r->A = z80->r->A + ((z80->r->F & 0x10) >> 4) & 0xFF;

   z80->ticks = 4;

   return 0;
}

int OP_8Bh_ADCAE(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->r->A;
   uint8_t oldSrc = z80->r->E;

   z80->r->A = (z80->r->A + z80->r->E) & 0xFF;

   uint8_t dest = z80->r->A & 0xFF;

   calculateAdditionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->r->A = z80->r->A + ((z80->r->F & 0x10) >> 4) & 0xFF;

   z80->ticks = 4;

   return 0;
}

int OP_8Ch_ADCAH(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->r->A;
   uint8_t oldSrc = z80->r->H;

   z80->r->A = (z80->r->A + z80->r->H) & 0xFF;

   uint8_t dest = z80->r->A & 0xFF;

   calculateAdditionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->r->A = z80->r->A + ((z80->r->F & 0x10) >> 4) & 0xFF;

   z80->ticks = 4;

   return 0;
}

int OP_8Dh_ADCAL(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->r->A;
   uint8_t oldSrc = z80->r->L;

   z80->r->A = (z80->r->A + z80->r->L) & 0xFF;

   uint8_t dest = z80->r->A & 0xFF;

   calculateAdditionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->r->A = z80->r->A + ((z80->r->F & 0x10) >> 4) & 0xFF;

   z80->ticks = 4;

   return 0;
}

int OP_8Fh_ADCAA(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->r->A;
   uint8_t oldSrc = z80->r->A;

   z80->r->A = (z80->r->A + z80->r->A) & 0xFF;

   uint8_t dest = z80->r->A & 0xFF;

   calculateAdditionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->r->A = z80->r->A + ((z80->r->F & 0x10) >> 4) & 0xFF;

   z80->ticks = 4;

   return 0;
}

int OP_90h_SUBB(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->r->A;
   uint8_t oldSrc = z80->r->B;

   z80->r->A = (z80->r->A - z80->r->B) & 0xFF;

   uint8_t dest = z80->r->A & 0xFF;

   calculateSubtractionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->ticks = 4;

   return 0;
}

int OP_91h_SUBC(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->r->A;
   uint8_t oldSrc = z80->r->C;

   z80->r->A = (z80->r->A - z80->r->C) & 0xFF;

   uint8_t dest = z80->r->A & 0xFF;

   calculateSubtractionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->ticks = 4;

   return 0;
}

int OP_92h_SUBD(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->r->A;
   uint8_t oldSrc = z80->r->D;

   z80->r->A = (z80->r->A - z80->r->D) & 0xFF;

   uint8_t dest = z80->r->A & 0xFF;

   calculateSubtractionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->ticks = 4;

   return 0;
}

int OP_93h_SUBE(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->r->A;
   uint8_t oldSrc = z80->r->E;

   z80->r->A = (z80->r->A - z80->r->E) & 0xFF;

   uint8_t dest = z80->r->A & 0xFF;

   calculateSubtractionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->ticks = 4;

   return 0;
}

int OP_94h_SUBH(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->r->A;
   uint8_t oldSrc = z80->r->H;

   z80->r->A = (z80->r->A - z80->r->H) & 0xFF;

   uint8_t dest = z80->r->A & 0xFF;

   calculateSubtractionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->ticks = 4;

   return 0;
}

int OP_95h_SUBL(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->r->A;
   uint8_t oldSrc = z80->r->L;

   z80->r->A = (z80->r->A - z80->r->L) & 0xFF;

   uint8_t dest = z80->r->A & 0xFF;

   calculateSubtractionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->ticks = 4;

   return 0;
}

int OP_AFh_XORA(Memory * memory, Z80 * z80)
{
   z80->r->A = 0;
   z80->r->F = 0;
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
