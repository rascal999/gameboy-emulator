#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

int InitZ80(Z80 * z80, Registers * registers)
{
   /* http://www.devrs.com/gb/files/gbspec.txt */
   z80->r = registers;
   z80->regA = 0x01;
   z80->regB = 0x00;
   z80->regC = 0x13;
   z80->regD = 0x00;
   z80->regE = 0xD8;
   z80->regH = 0x01;
   z80->regL = 0x4D;
   z80->regF = 0xB0;
   z80->regPC = 0x00;
   z80->regSP = 0xFFFE;

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
   z80->regA = 1;

   return 0;
}

int Fetch(Memory * memory, Z80 * z80)
{
   /* Fetch correct number of bytes for instruction and decode */
   /* switch(memory->addr[z80->regPC] & 0x00FF)
   {
   } */
   return 0; 
}

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  math_pow_uint8
 *  Description:  Return 8-bit unsigned value of value (power of) pow
 *                Only works with positive numbers for which the answer
 *                does not exceed 255
 * =====================================================================================
 */
   uint8_t
math_pow_uint8 ( uint8_t value, uint8_t pow )
{
   int i;
   uint8_t tmp = value;

   if ( pow < 1 ) {
      return 1;
   }

   for ( i = 1; i < pow ; i++ )
   {
      value = value * tmp;
   }

   return value;
}

int8_t ensure_8b_signed(int8_t value)
{
   return (int8_t) value;
}

int CB_BIT(Memory * memory, Z80 * z80, uint8_t parameters)
{
   uint8_t bitTest;
   uint8_t cpuRegisterBit;
   uint16_t tmp_z80_F = z80->regF;

   cpuRegisterBit = (z80->r->r[(parameters & 0xF)] >> ((parameters & 0xF0) >> 4)) & 0x1;

   // Zero subtract flag and set half carry
   z80->regF = 0x20;

   // Preserve carry
   z80->regF = z80->regF | (tmp_z80_F & 0x10);

   if (cpuRegisterBit == 0x0)
   {
      // Zero flag
      z80->regF = z80->regF | 0x80;
   }

   z80->ticks = 8;

   return 0;
}

int CB_RES(Memory * memory, Z80 * z80, uint8_t parameters)
{
   char regName;
   uint8_t bitReset;
   uint8_t cpuRegister;
   uint8_t bitMask;

   z80->r->r[(parameters & 0xF)] = z80->r->r[(parameters & 0xF)] & math_pow_uint8(2,(((parameters & 0xF0) >> 4) & 0xF));

   z80->ticks = 8; 

   return 0;
}

int CB_SET(Memory * memory, Z80 * z80, uint8_t parameters)
{
   char regName;
   uint8_t bitSet;
   uint8_t cpuRegister;
   uint8_t bitMask;
 
   z80->r->r[(parameters & 0xF)] = (z80->r->r[(parameters & 0xF)] | math_pow_uint8(2,(((parameters & 0xF0) >> 4) & 0xF)));

   z80->ticks = 8; 

   return 0;
}

int CB_RLC(Memory * memory, Z80 * z80, uint8_t parameters)
{
   // Unset F register (flags)
   z80->regF = 0x0;

   // Set carry flag (0x10)
   z80->regF = z80->regF | ((z80->r->r[(parameters & 0xF)] >> 7) & 0x1) << 1;

   // Zero flag
   if (z80->r->r[(parameters & 0xF)] == 0)
   {
      z80->regF = z80->regF | 0x80;
   }

   // Rotate register, add carry bit, and ensure 8 bits
   z80->r->r[(parameters & 0xF)] = (((z80->r->r[(parameters & 0xF)] << 1) + ((z80->regF >> 5) & 0x1)) & 0xFF);

   z80->ticks = 8;

   return 0;
}

int CB_RRC(Memory * memory, Z80 * z80, uint8_t parameters)
{
   // Unset F register (flags)
   z80->regF = 0x0;

   // Set carry flag (0x10)
   z80->regF = z80->regF | (z80->r->r[(parameters & 0xF)] & 0x1) << 1;

   // Zero flag
   if (z80->r->r[(parameters & 0xF)] == 0)
   {
      z80->regF = z80->regF | 0x80;
   }

   // Rotate register, add carry bit, and ensure 8 bits
   z80->r->r[(parameters & 0xF)] = (z80->r->r[(parameters & 0xF)] >> 1) + (((z80->regF >> 5) & 0x1) << 7) & 0xFF;

   z80->ticks = 8;

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

   tmpHL = (z80->regH << 8) + z80->regL;
   tmpHL--;

   z80->regH = (tmpHL & 0xFF00) >> 8;
   z80->regL = (tmpHL & 0xFF);

   return 0;
}

int incrementHL(Z80 * z80)
{
   uint16_t tmpHL;

   tmpHL = (z80->regH << 8) + z80->regL;
   tmpHL++;

   z80->regH = (tmpHL & 0xFF00) >> 8;
   z80->regL = (tmpHL & 0xFF);

   return 0;
}

int calculateAdditionFlags(Memory * memory, Z80 * z80, uint8_t dest, uint8_t oldDest, uint8_t oldSrc)
{
   // Flags
   if (((dest & 0xFF) < oldDest) | ((dest & 0xFF) < oldSrc))
   {
      // Carry
      z80->regF = 0x10;
   }

   if ((dest & 0xFF) == 0x00)
   {
      // Zero flag
      z80->regF = z80->regF | 0x80;
   }

   if (((oldSrc & 0xF) + (oldDest & 0xF)) & 0x10)
   {
      // Half-carry
      z80->regF = z80->regF | 0x20;
   }

   return 0;
}

int calculateSubtractionFlags(Memory * memory, Z80 * z80, uint8_t dest, uint8_t oldDest, uint8_t oldSrc)
{
   // Flags
   if (((dest & 0xFF) > oldDest) | ((dest & 0xFF) > oldSrc))
   {
      // Carry
      z80->regF = 0x10;
   }

   if ((dest & 0xFF) == 0x00)
   {
      // Zero flag
      z80->regF = z80->regF | 0x80;
   }

   if (((oldSrc & 0xF) - (oldDest & 0xF)) & 0x10)
   {
      // Half-carry
      z80->regF = z80->regF | 0x20;
   }

   //Subtract
   z80->regF = z80->regF | 0x40;

   return 0;
}

int calculateAndFlags(Memory * memory, Z80 * z80, uint8_t dest)
{
   z80->regF = 0x00;

   if ((dest & 0xFF) == 0x00)
   {
      // Zero flag
      z80->regF = z80->regF | 0x80;
   }

   // Half-carry
   z80->regF = z80->regF | 0x20;

   return 0;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  OP_LDXD8
 *  Description:  Load immediate into register X
 * =====================================================================================
 */
int OP_LDXD8(Memory * memory, Z80 * z80, uint8_t parameters)
{
//printf("*** PC == %x\nrb(memory,(z80->regPC)) & 0xFF == %x\n",z80->regPC,rb(memory,(z80->regPC)) & 0xFF);

   z80->r->r[(parameters & 0xF)] = rb(memory,(z80->regPC + 1)) & 0xFF;

   z80->regPC = z80->regPC + 1;
   z80->ticks = 8;

   return 0;
}

int OP_LDXY(Memory * memory, Z80 * z80, uint8_t x)
{
   z80->r->r[((x & 0xF0) >> 4)] = z80->r->r[(x & 0xF)];

   z80->ticks = 4;

   return 0;
}

int Execute(Memory * memory, Z80 * z80)
{
   int callDebug = 1;
   uint16_t tmp;

   Debug debug;
   Error err;

   //usleep(50000);

   if (callDebug == 1) printf("rb %x\n",rb(memory,(z80->regPC)));

   if (callDebug == 1)
   {
      debug.instructionSize = 1;
      DebugAll(z80, memory, &debug);
   }

   /* switch((memory->addr[z80->regPC] & 0xFF00) >> 8) */
   switch(rb(memory,(z80->regPC++)))
   {
      case 0x00: OP_00h_NOP(memory,z80); break;
      case 0x0E: OP_LDXD8(memory,z80,(uint8_t) 0x2); break;
      case 0x20: OP_20h_JRNZn(memory,z80); break;
      case 0x21: OP_21h_LDHLnn(memory,z80); break;
      case 0x22: OP_22h_LDIHLA(memory,z80); break;
      case 0x31: OP_31h_LDSPnn(memory,z80); break;
      case 0x32: OP_32h_LDDHLA(memory,z80); break;

      case 0x40: OP_LDXY(memory,z80,0x11); break;
      case 0x41: OP_LDXY(memory,z80,0x12); break;
      case 0x42: OP_LDXY(memory,z80,0x13); break;
      case 0x43: OP_LDXY(memory,z80,0x14); break;
      case 0x44: OP_LDXY(memory,z80,0x16); break;
      case 0x45: OP_LDXY(memory,z80,0x17); break;
      case 0x50: OP_LDXY(memory,z80,0x31); break;
      case 0x51: OP_LDXY(memory,z80,0x32); break;
      case 0x52: OP_LDXY(memory,z80,0x33); break;
      case 0x53: OP_LDXY(memory,z80,0x34); break;
      case 0x54: OP_LDXY(memory,z80,0x36); break;
      case 0x55: OP_LDXY(memory,z80,0x37); break;
      case 0x60: OP_LDXY(memory,z80,0x61); break;
      case 0x61: OP_LDXY(memory,z80,0x62); break;
      case 0x62: OP_LDXY(memory,z80,0x63); break;
      case 0x63: OP_LDXY(memory,z80,0x64); break;
      case 0x64: OP_LDXY(memory,z80,0x66); break;
      case 0x65: OP_LDXY(memory,z80,0x67); break;

/*
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
*/

      case 0xAF: OP_AFh_XORA(memory,z80); break;
      // CB prefixed opcodes
      case 0xCB: OP_CBh_PREFIXCB(memory,z80); break;
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

int ExecuteCB(Memory * memory, Z80 * z80)
{
   int callDebug = 1;
   uint16_t tmp;

   Debug debug;
   Error err;

   //usleep(50000);

   if (callDebug == 1) printf("rb %x\n",rb(memory,(z80->regPC)));

   if (callDebug == 1)
   {
      debug.instructionSize = 1;
      DebugAll(z80, memory, &debug);
   }

   /* switch((memory->addr[z80->regPC] & 0xFF00) >> 8) */
   switch(rb(memory,(z80->regPC++)))
   {
      // NEED TO DEVELOP TEST CODE AND SORT OUT
      /*case 0x00: OP_CB_00h_RLCB(memory,z80); break;
      case 0x21: OP_CB_21h_SLAC(memory,z80); break;
      case 0x22: OP_CB_22h_SLAD(memory,z80); break;
      case 0x31: OP_CB_31h_SLAPB(memory,z80); break;*/
      // a = 0 b = 1 c = 2 d = 3 e = 4 f = 5 h = 6 l = 7
      //case 0x40: OP_CB_40h_BIT0B(memory,z80); break;
      case 0x40: CB_BIT(memory,z80,0x01); break;
      case 0x41: CB_BIT(memory,z80,0x02); break;
      case 0x42: CB_BIT(memory,z80,0x03); break;
      case 0x43: CB_BIT(memory,z80,0x04); break;
      case 0x44: CB_BIT(memory,z80,0x06); break;
      case 0x45: CB_BIT(memory,z80,0x07); break;
      case 0x47: CB_BIT(memory,z80,0x00); break;
      case 0x7c: CB_BIT(memory,z80,0x76); break;
      /*case 0x40: CB_BIT(memory,z80,0x01); break;
      case 0x40: CB_BIT(memory,z80,0x01); break;
      case 0x41: OP_CB_41h_BIT0C(memory,z80); break;
      case 0x42: OP_CB_42h_BIT0D(memory,z80); break;
      case 0x43: OP_CB_43h_BIT0E(memory,z80); break;
      case 0x44: OP_CB_44h_BIT0H(memory,z80); break;
      case 0x45: OP_CB_45h_BIT0L(memory,z80); break;
      case 0x50: OP_CB_50h_BIT2B(memory,z80); break;
      case 0x51: OP_CB_51h_BIT2C(memory,z80); break;
      case 0x52: OP_CB_52h_BIT2D(memory,z80); break;
      case 0x53: OP_CB_53h_BIT2E(memory,z80); break;
      case 0x54: OP_CB_54h_BIT2H(memory,z80); break;
      case 0x55: OP_CB_55h_L(memory,z80); break;
      case 0x60: OP_CB_60h_LDHB(memory,z80); break;
      case 0x61: OP_CB_61h_LDHC(memory,z80); break;
      case 0x62: OP_CB_62h_LDHD(memory,z80); break;
      case 0x63: OP_CB_63h_LDHE(memory,z80); break;
      case 0x64: OP_CB_64h_LDHH(memory,z80); break;
      case 0x65: OP_CB_65h_LDHL(memory,z80); break;
      case 0xAF: OP_CB_AFh_XORA(memory,z80); break;
      case 0xFF: OP_CB_FFh_RST38h(memory,z80); break;*/

      default:
         err.code = 20;
         exiterror(&err);
      break;
   }

   // Reset after acting on ticks
   z80->ticks = 0;

   return 0;
}

/* OPCODES */
int OP_00h_NOP(Memory * memory, Z80 * z80)
{
   z80->ticks = 4;

   return 0;
}

int OP_20h_JRNZn(Memory * memory, Z80 * z80)
{
   int8_t i;

   i = (int8_t) rb(memory,(z80->regPC)) & 0xFF;

   z80->regPC++;

   if ((z80->regF & 0x80) == 0x00)
   {
      z80->regPC = (z80->regPC + (int8_t) i) & 0xFF;
      z80->ticks = 12;
   } else {
      z80->ticks = 8;
   }

   return 0;
}

int OP_21h_LDHLnn(Memory * memory, Z80 * z80)
{
   z80->regH = rb(memory,(z80->regPC+1));
   z80->regL = rb(memory,(z80->regPC));
   z80->regPC = z80->regPC + 2;
   z80->ticks = 12;

   return 0;
}

int OP_22h_LDIHLA(Memory * memory, Z80 * z80)
{
   uint16_t tmp;

   wb(memory,(z80->regH << 8) + z80->regL,z80->regA);
   tmp = (z80->regH << 8) + z80->regL;

   incrementHL(z80);
   z80->ticks = 8;

   return 0;
}

int OP_31h_LDSPnn(Memory * memory, Z80 * z80)
{
   z80->regSP = (uint16_t) rw(memory,z80->regPC);
   z80->regPC = (uint16_t) z80->regPC + (uint16_t) 2;
   z80->ticks = 12;

   return 0;
}

int OP_32h_LDDHLA(Memory * memory, Z80 * z80)
{
   uint16_t tmp;

   // BUG?
   wb(memory,(z80->regH << 8) + z80->regL,z80->regA);
   tmp = (z80->regH << 8) + z80->regL;

   decrementHL(z80);
   z80->ticks = 8;

   return 0;
}

int OP_72h_LDHLD(Memory * memory, Z80 * z80)
{
   wb(memory,(z80->regH << 8) + z80->regL,z80->regD);

   z80->ticks = 8;

   return 0;
}

int OP_80h_ADDAB(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regB;

   z80->regA = z80->regA + z80->regB;

   uint8_t dest = z80->regA;

   calculateAdditionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->ticks = 4;

   return 0;
}

int OP_81h_ADDAC(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regC;

   z80->regA = z80->regA + z80->regC;

   uint8_t dest = z80->regA;

   calculateAdditionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->ticks = 4;

   return 0;
}

int OP_82h_ADDAD(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regD;

   z80->regA = z80->regA + z80->regD;

   uint8_t dest = z80->regA;

   calculateAdditionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->ticks = 4;

   return 0;
}

int OP_83h_ADDAE(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regE;

   z80->regA = (z80->regA + z80->regE) & 0xFF;

   uint8_t dest = z80->regA;

   calculateAdditionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->ticks = 4;

   return 0;
}

int OP_84h_ADDAH(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regH;

   z80->regA = z80->regA + z80->regH;

   uint8_t dest = z80->regA;

   calculateAdditionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->ticks = 4;

   return 0;
}

int OP_85h_ADDAL(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regL;

   z80->regA = z80->regA + z80->regL;

   uint8_t dest = z80->regA;

   calculateAdditionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->ticks = 4;

   return 0;
}

int OP_87h_ADDAA(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regA;

   z80->regA = z80->regA + z80->regA;

   uint8_t dest = z80->regA;

   calculateAdditionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->ticks = 4;

   return 0;
}

int OP_88h_ADCAB(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regB;

   z80->regA = (z80->regA + z80->regB) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateAdditionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->regA = z80->regA + ((z80->regF & 0x10) >> 4) & 0xFF;

   z80->ticks = 4;

   return 0;
}

int OP_89h_ADCAC(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regC;

   z80->regA = (z80->regA + z80->regC) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateAdditionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->regA = z80->regA + ((z80->regF & 0x10) >> 4) & 0xFF;

   z80->ticks = 4;

   return 0;
}

int OP_8Ah_ADCAD(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regD;

   z80->regA = (z80->regA + z80->regD) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateAdditionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->regA = z80->regA + ((z80->regF & 0x10) >> 4) & 0xFF;

   z80->ticks = 4;

   return 0;
}

int OP_8Bh_ADCAE(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regE;

   z80->regA = (z80->regA + z80->regE) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateAdditionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->regA = z80->regA + ((z80->regF & 0x10) >> 4) & 0xFF;

   z80->ticks = 4;

   return 0;
}

int OP_8Ch_ADCAH(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regH;

   z80->regA = (z80->regA + z80->regH) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateAdditionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->regA = z80->regA + ((z80->regF & 0x10) >> 4) & 0xFF;

   z80->ticks = 4;

   return 0;
}

int OP_8Dh_ADCAL(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regL;

   z80->regA = (z80->regA + z80->regL) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateAdditionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->regA = z80->regA + ((z80->regF & 0x10) >> 4) & 0xFF;

   z80->ticks = 4;

   return 0;
}

int OP_8Fh_ADCAA(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regA;

   z80->regA = (z80->regA + z80->regA) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateAdditionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->regA = z80->regA + ((z80->regF & 0x10) >> 4) & 0xFF;

   z80->ticks = 4;

   return 0;
}

int OP_90h_SUBB(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regB;

   z80->regA = (z80->regA - z80->regB) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateSubtractionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->ticks = 4;

   return 0;
}

int OP_91h_SUBC(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regC;

   z80->regA = (z80->regA - z80->regC) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateSubtractionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->ticks = 4;

   return 0;
}

int OP_92h_SUBD(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regD;

   z80->regA = (z80->regA - z80->regD) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateSubtractionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->ticks = 4;

   return 0;
}

int OP_93h_SUBE(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regE;

   z80->regA = (z80->regA - z80->regE) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateSubtractionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->ticks = 4;

   return 0;
}

int OP_94h_SUBH(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regH;

   z80->regA = (z80->regA - z80->regH) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateSubtractionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->ticks = 4;

   return 0;
}

int OP_95h_SUBL(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regL;

   z80->regA = (z80->regA - z80->regL) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateSubtractionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->ticks = 4;

   return 0;
}

int OP_97h_SUBA(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regA;

   z80->regA = (z80->regA - z80->regA) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateSubtractionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->ticks = 4;

   return 0;
}

int OP_98h_SBCAB(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regB;
   z80->regA = (z80->regA - z80->regB) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateSubtractionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->regA = z80->regA - ((z80->regF & 0x10) >> 4) & 0xFF;

   z80->ticks = 4;

   return 0;
}

int OP_99h_SBCAC(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regC;
   z80->regA = (z80->regA - z80->regC) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateSubtractionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->regA = z80->regA - ((z80->regF & 0x10) >> 4) & 0xFF;

   z80->ticks = 4;

   return 0;
}

int OP_9Ah_SBCAD(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regD;
   z80->regA = (z80->regA - z80->regD) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateSubtractionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->regA = z80->regA - ((z80->regF & 0x10) >> 4) & 0xFF;

   z80->ticks = 4;

   return 0;
}

int OP_9Bh_SBCAE(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regE;
   z80->regA = (z80->regA - z80->regE) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateSubtractionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->regA = z80->regA - ((z80->regF & 0x10) >> 4) & 0xFF;

   z80->ticks = 4;

   return 0;
}

int OP_9Ch_SBCAH(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regH;
   z80->regA = (z80->regA - z80->regH) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateSubtractionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->regA = z80->regA - ((z80->regF & 0x10) >> 4) & 0xFF;

   z80->ticks = 4;

   return 0;
}

int OP_9Dh_SBCAL(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regL;
   z80->regA = (z80->regA - z80->regL) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateSubtractionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->regA = z80->regA - ((z80->regF & 0x10) >> 4) & 0xFF;

   z80->ticks = 4;

   return 0;
}

int OP_9Fh_SBCAA(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regL;
   z80->regA = (z80->regA - z80->regA) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateSubtractionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->regA = z80->regA - ((z80->regF & 0x10) >> 4) & 0xFF;

   z80->ticks = 4;

   return 0;
}

int OP_A0h_ANDB(Memory * memory, Z80 * z80)
{
   z80->regA = (z80->regA & z80->regB) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateAndFlags(memory,z80,dest);

   z80->ticks = 4;

   return 0;
}

int OP_A1h_ANDC(Memory * memory, Z80 * z80)
{
   z80->regA = (z80->regA & z80->regC) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateAndFlags(memory,z80,dest);

   z80->ticks = 4;

   return 0;
}

int OP_A2h_ANDD(Memory * memory, Z80 * z80)
{
   z80->regA = (z80->regA & z80->regD) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateAndFlags(memory,z80,dest);

   z80->ticks = 4;

   return 0;
}

int OP_A3h_ANDE(Memory * memory, Z80 * z80)
{
   z80->regA = (z80->regA & z80->regE) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateAndFlags(memory,z80,dest);

   z80->ticks = 4;

   return 0;
}

int OP_A4h_ANDH(Memory * memory, Z80 * z80)
{
   z80->regA = (z80->regA & z80->regH) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateAndFlags(memory,z80,dest);

   z80->ticks = 4;

   return 0;
}

int OP_A5h_ANDL(Memory * memory, Z80 * z80)
{
   z80->regA = (z80->regA & z80->regL) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateAndFlags(memory,z80,dest);

   z80->ticks = 4;

   return 0;
}

int OP_A7h_ANDA(Memory * memory, Z80 * z80)
{
   z80->regA = (z80->regA & z80->regA) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateAndFlags(memory,z80,dest);

   z80->ticks = 4;

   return 0;
}

int OP_AFh_XORA(Memory * memory, Z80 * z80)
{
   z80->regA = 0;
   z80->regF = 0x80;
   z80->ticks = 4;

   return 0;
}

int OP_CBh_PREFIXCB(Memory * memory, Z80 * z80)
{
   ExecuteCB(memory,z80);

   return 0;
}

int OP_FFh_RST38h(Memory * memory, Z80 * z80)
{
   z80->regSP--;
   z80->regSP = z80->regPC;
   z80->regSP--;
   z80->regPC = 0x38;
   z80->ticks = 16;

   return 0;
}
