#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>

#ifdef UNITTEST_OPCODES
   #define UNIT_TEST 1
#else
   #define UNIT_TEST 0
#endif

#include "cartridge.h"
#include "debug.h"
#include "display.h"
#include "error.h"
#include "memory.h"
#include "opcode_attributes.h"
#include "opcode_wrappers.h"
#include "rom.h"
#include "timer.h"
#include "z80.h"

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

int InitZ80(Z80 * z80, Registers * registers, Opcodes * op, Opcodes * cb_op)
{
   op = malloc(sizeof(Opcodes) * 0x100);
   cb_op = malloc(sizeof(Opcodes) * 0x100);
   z80->op = op;
   z80->cb_op = cb_op;

   InitZ80OpcodeStats(z80,registers,op,cb_op);

   z80->r = registers;
   /* http://www.devrs.com/gb/files/gbspec.txt */
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

int ResetZ80(Z80 * z80, Registers * registers, Opcodes * op, Opcodes * cb_op)
{
   InitZ80(z80,registers,op,cb_op);

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
 *         Name:  OP_LDXd8
 *  Description:  Load immediate into register X
 * =====================================================================================
 */
int OP_LDXd8(Memory * memory, Z80 * z80, uint8_t x)
{
   z80->r->r[(x & 0xF)] = rb(memory,(z80->regPC)) & 0xFF;

   z80->regPC = z80->regPC + 1;
   z80->ticks = 8;

   return 0;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  OP_LDXd16
 *  Description:  Load immediate into register X
 * =====================================================================================
 */
   int
OP_LDXd16 ( Memory * memory, Z80 * z80, uint8_t x )
{
   z80->r->r[(x & 0xF)] = rb(memory,(z80->regPC + 1)) & 0xFF;
   z80->r->r[(x & 0xF) + 1] = rb(memory,(z80->regPC)) & 0xFF;

   z80->regPC = z80->regPC + 2;
   z80->ticks = 12;

   return 0;
}		/* -----  end of function OP_LDXd16  ----- */

int OP_LDXY(Memory * memory, Z80 * z80, uint8_t x)
{
   z80->r->r[((x & 0xF0) >> 4)] = z80->r->r[(x & 0xF)];

   z80->ticks = 4;

   return 0;
}

int OP_LDHLX(Memory * memory, Z80 * z80, uint8_t x)
{
   wb(memory,(z80->regH << 8) + z80->regL,z80->r->r[x & 0xF]);

   z80->ticks = 8;

   return 0;
}

/* OPCODES */
int OP_INCX(Memory * memory, Z80 * z80, uint8_t x)
{
   uint8_t oldRegValue = z80->r->r[x & 0xF];

   z80->r->r[x & 0xF]++;

   z80->regF = z80->regF & 0x10;

   // Zero flag
   if (z80->r->r[x & 0xF] == 0x0)
   {
      z80->regF = z80->regF | 0x80;
   }

   // Half carry
   // If 0xF on oldRegValue, then set H flag
   if (((oldRegValue + 1) & 0xF) == 0x0)
   {
      z80->regF = z80->regF | 0x20;
   }

   // Set N flag to 0x0;
   z80->regF = z80->regF & 0xB0;

   z80->ticks = 4;

   return 0;
}

int OP_00h_NOP(Memory * memory, Z80 * z80)
{
   z80->ticks = 4;

   return 0;
}

int OP_01h_LDBCd16(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_02h_LDBCA(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_03h_INCBC(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_04h_INCB(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_05h_DECB(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_06h_LDBd8(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_07h_RLCA(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_08h_LDnnSP(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_09h_ADDHLBC(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_0Ah_LDABC(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_0Bh_DECBC(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_0Ch_INCC(Memory * memory, Z80 * z80)
{
   // Not used
   // Wrapper redirect to OP_INCX

   return 1;
}

int OP_0Dh_DECC(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_0Eh_LDCd8(Memory * memory, Z80 * z80)
{
   // Not used
   // Wrapper redirect to OP_LDXd8

   return 1;
}

int OP_0Fh_RRCA(Memory * memory, Z80 * z80)
{
   

   return 1;
}


int OP_10h_STOP0(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_11h_LDDEd16(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_12h_LDDEA(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_13h_INCDE(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_14h_INCD(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_15h_DECD(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_16h_LDd8(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_17h_RLA(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_18h_JRr8(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_19h_ADDHLDE(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_1Ah_LDADE(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_1Bh_DECDE(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_1Ch_INCE(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_1Dh_DECE(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_1Eh_LDEd8(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_1Fh_RRA(Memory * memory, Z80 * z80)
{
   

   return 1;
}


int OP_20h_JRNZr8(Memory * memory, Z80 * z80)
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

int OP_21h_LDHLd16(Memory * memory, Z80 * z80)
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

int OP_23h_INCHL(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_24h_INCH(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_25h_DECH(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_26h_LDHd8(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_27h_DAA(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_28h_JRZr8(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_29h_ADDHLHL(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_2Ah_LDIAHL(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_2Bh_DECHL(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_2Ch_INCL(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_2Dh_DECL(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_2Eh_LDLd8(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_2Fh_CPL(Memory * memory, Z80 * z80)
{
   

   return 1;
}


int OP_30h_JRNCr8(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_31h_LDSPd16(Memory * memory, Z80 * z80)
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

int OP_33h_INCSP(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_34h_INCHL(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_35h_DECHL(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_36h_LDHLd8(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_37h_SCF(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_38h_JRCr8(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_39h_ADDHLSP(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_3Ah_LDDAHL(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_3Bh_DECSP(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_3Ch_INCA(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_3Dh_DECA(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_3Eh_LDAd8(Memory * memory, Z80 * z80)
{
   // Not used
   // Wrapper redirect to OP_LDXd8

   return 1;
}

int OP_3Fh_CCF(Memory * memory, Z80 * z80)
{
   

   return 1;
}


int OP_40h_LDBB(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_41h_LDBC(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_42h_LDBD(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_43h_LDBE(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_44h_LDBH(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_45h_LDBL(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_46h_LDBHL(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_47h_LDBA(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_48h_LDCB(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_49h_LDC(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_4Ah_LDCD(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_4Bh_LDCE(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_4Ch_LDCH(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_4Dh_LDCL(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_4Eh_LDCHL(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_4Fh_LDCA(Memory * memory, Z80 * z80)
{
   

   return 1;
}


int OP_50h_LDDB(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_51h_LDDC(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_52h_LDDD(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_53h_LDDE(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_54h_LDDH(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_55h_LDDL(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_56h_LDDHL(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_57h_LDDA(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_58h_LDEB(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_59h_LDEC(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_5Ah_LDED(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_5Bh_LDEE(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_5Ch_LDEH(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_5Dh_LDEL(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_5Eh_LDEHL(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_5Fh_LDEA(Memory * memory, Z80 * z80)
{
   

   return 1;
}


int OP_60h_LDHB(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_61h_LDHC(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_62h_LDHD(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_63h_LDHE(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_64h_LDHH(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_65h_LDHL(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_66h_LDHHL(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_67h_LDHA(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_68h_LDLB(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_69h_LDLC(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_6Ah_LDLD(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_6Bh_LDLE(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_6Ch_LDLH(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_6Dh_LDLL(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_6Eh_LDLHL(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_6Fh_LDLA(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_70h_LDHLB(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_71h_LDHLC(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_72h_LDHLD(Memory * memory, Z80 * z80)
{
   wb(memory,(z80->regH << 8) + z80->regL,z80->regD);

   z80->ticks = 8;

   return 0;
}

int OP_73h_LDHLE(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_74h_LDHLH(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_75h_LDHLL(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_76h_HALT(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_77h_LDHLA(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_78h_LDAB(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_79h_LDAC(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_7Ah_LDAD(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_7Bh_LDAE(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_7Ch_LDAH(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_7Dh_LDAL(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_7Eh_LDAHL(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_7Fh_LDAA(Memory * memory, Z80 * z80)
{
   

   return 1;
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

int OP_86h_ADDAHL(Memory * memory, Z80 * z80)
{
   

   return 1;
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

int OP_8Eh_ADCAHL(Memory * memory, Z80 * z80)
{
   

   return 1;
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

int OP_96h_SUBHL(Memory * memory, Z80 * z80)
{
   

   return 1;
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

int OP_9Eh_SBCAHL(Memory * memory, Z80 * z80)
{
   

   return 1;
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

int OP_A6h_ANDHL(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_A7h_ANDA(Memory * memory, Z80 * z80)
{
   z80->regA = (z80->regA & z80->regA) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateAndFlags(memory,z80,dest);

   z80->ticks = 4;

   return 0;
}

int OP_A8h_XORB(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_A9h_XORC(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_AAh_XORD(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_ABh_XORE(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_ACh_XORH(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_ADh_XORL(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_AEh_XORHL(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_AFh_XORA(Memory * memory, Z80 * z80)
{
   z80->regA = 0;
   z80->regF = 0x80;
   z80->ticks = 4;

   return 0;
}

int OP_B0h_ORB(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_B1h_ORC(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_B2h_ORD(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_B3h_ORE(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_B4h_ORH(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_B5h_ORL(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_B6h_ORHL(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_B7h_ORA(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_B8h_CPB(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_B9h_CPC(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_BAh_CPD(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_BBh_CPE(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_BCh_CPH(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_BDh_CPL(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_BEh_CPHL(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_BFh_CPA(Memory * memory, Z80 * z80)
{
   

   return 1;
}


int OP_C0h_RETNZ(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_C1h_POPBC(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_C2h_JPNZa16(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_C3h_JPa16(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_C4h_CALLNZa16(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_C5h_PUSHBC(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_C6h_ADDAd8(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_C7h_RST00H(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_C8h_RETZ(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_C9h_RET(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_CAh_JPZa16(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_CBh_PREFIXCB(Memory * memory, Z80 * z80)
{
   ExecuteCB(memory,z80);

   // Maybe return value specific to CB prefix?
   return 0;
}

int OP_CCh_CALLZa16(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_CDh_CALLa16(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_CEh_ADCAd8(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_CFh_RST08H(Memory * memory, Z80 * z80)
{
   

   return 1;
}


int OP_D0h_RETNC(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_D1h_POPDE(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_D2h_JPNCa16(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_D3h_INVALID(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_D4h_CALLNCa16(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_D5h_PUSHDE(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_D6h_SUBd8(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_D7h_RST10H(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_D8h_RETC(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_D9h_RETI(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_DAh_JPCa16(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_DBh_INVALID(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_DCh_CALLCa16(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_DDh_INVALID(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_DEh_SBCAd8(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_DFh_RST18H(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_E0h_LDHa8A(Memory * memory, Z80 * z80)
{
   wb(memory,(0xff00 + rb(memory,z80->regPC)),z80->regA);

   z80->regPC = z80->regPC + 1;
   z80->ticks = 12;

   return 0;
}

int OP_E1h_POPHL(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_E2h_LDHCA(Memory * memory, Z80 * z80)
{
   wb(memory,(0xff00 + z80->regC),z80->regA);
   z80->ticks = 8;

   return 0;
}

int OP_E3h_INVALID(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_E4h_INVALID(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_E5h_PUSHHL(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_E6h_ANDd8(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_E7h_RST20H(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_E8h_ADDSPr8(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_E9h_JPHL(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_EAh_LDnnA(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_EBh_INVALID(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_ECh_INVALID(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_EDh_INVALID(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_EEh_XORd8(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_EFh_RST28H(Memory * memory, Z80 * z80)
{
   

   return 1;
}


int OP_F0h_LDHAa8(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_F1h_POPAF(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_F2h_LDAC(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_F3h_DI(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_F4h_INVALID(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_F5h_PUSHAF(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_F6h_ORd8(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_F7h_RST30H(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_F8h_LDHLSPr8(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_F9h_LDSPHL(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_FAh_LDAa16(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_FBh_EI(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_FCh_INVALID(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_FDh_INVALID(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_FEh_CPd8(Memory * memory, Z80 * z80)
{
   

   return 1;
}

int OP_FFh_RST38H(Memory * memory, Z80 * z80)
{
   z80->regSP--;
   z80->regSP = z80->regPC;
   z80->regSP--;
   z80->regPC = 0x38;
   z80->ticks = 16;

   return 0;
}

int Execute(Memory * memory, Z80 * z80)
{
   int callDebug = 1;
   uint16_t tmp;

   Debug debug;
   Error err;

   //usleep(50000);

   if (callDebug == 1)
   {
      printf("rb %x\n",rb(memory,(z80->regPC)));
      debug.instructionSize = 1;
      DebugAll(z80, memory, &debug);
   }

   // This line has replaced the commented out
   // switch statement, but the switch is still here
   // so I can set appropriate values in the wrapper
   // opcode functions which use a 'common' opcode
   // function (for example, LDXY)
   //
   // Return 1 if the opcode has not been implemented
   if ((err.code = z80->op[rb(memory,(z80->regPC++))].call(memory,z80)) != 0)
   {
      err.code = 20;
      exiterror(&err);
   }
   /* switch((memory->addr[z80->regPC] & 0xFF00) >> 8) */
   /* switch(rb(memory,(z80->regPC++)))
   {
      case 0x00: OP_00h_NOP(memory,z80); break;

      case 0x04: OP_INCX(memory,z80,(uint8_t) 0x1); break;
      case 0x06: OP_LDXd8(memory,z80,(uint8_t) 0x1); break;
      case 0x0C: OP_INCX(memory,z80,(uint8_t) 0x2); break;
      case 0x0E: OP_LDXd8(memory,z80,(uint8_t) 0x2); break;
      case 0x14: OP_INCX(memory,z80,(uint8_t) 0x3); break;
      case 0x16: OP_LDXd8(memory,z80,(uint8_t) 0x3); break;
      case 0x1C: OP_INCX(memory,z80,(uint8_t) 0x4); break;
      case 0x1E: OP_LDXd8(memory,z80,(uint8_t) 0x4); break;
      case 0x26: OP_LDXd8(memory,z80,(uint8_t) 0x6); break;
      case 0x2E: OP_LDXd8(memory,z80,(uint8_t) 0x7); break;
      case 0x3E: OP_LDXd8(memory,z80,(uint8_t) 0x0); break;

      case 0x20: OP_20h_JRNZn(memory,z80); break;
      case 0x21: OP_21h_LDHLnn(memory,z80); break;
      case 0x22: OP_22h_LDIHLA(memory,z80); break;
      case 0x24: OP_INCX(memory,z80,(uint8_t) 0x6); break;
      case 0x2C: OP_INCX(memory,z80,(uint8_t) 0x7); break;
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

      case 0x70: OP_LDHLX(memory,z80,0x1); break;
      case 0x71: OP_LDHLX(memory,z80,0x2); break;
      case 0x72: OP_LDHLX(memory,z80,0x3); break;
      case 0x73: OP_LDHLX(memory,z80,0x4); break;
      case 0x74: OP_LDHLX(memory,z80,0x6); break;
      case 0x75: OP_LDHLX(memory,z80,0x7); break;
      case 0x77: OP_LDHLX(memory,z80,0x0); break;

      case 0xAF: OP_AFh_XORA(memory,z80); break;

      case 0xE0: OP_E0h_LDHAn(memory,z80); break;
      case 0xE2: OP_E2h_LDHCA(memory,z80); break;

      // CB prefixed opcodes
      case 0xCB: OP_CBh_PREFIXCB(memory,z80); break;
      case 0xFF: OP_FFh_RST38h(memory,z80); break;

      default:
         err.code = 20;
         exiterror(&err);
      break;
   } */

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

