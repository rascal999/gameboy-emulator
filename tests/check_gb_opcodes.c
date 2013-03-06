/*
 * =====================================================================================
 *
 *       Filename:  check_gb_opcodes.c
 *
 *    Description:  Unit tests for opcodes
 *
 *        Version:  1.0
 *        Created:  23/01/13 11:48:51
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aidan Marlin (aidan.marlin+github@gmail.com), 
 *   Organization:  None
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <check.h>
#include <stdio.h>
#include <math.h>

#ifdef UNITTEST_OPCODES
   #define UNIT_TEST 1
#else
   #define UNIT_TEST 0
#endif

#ifndef _INCL_DEBUG
   #define _INCL_DEBUG
   #include "../src/debug.h"
#endif
#ifndef _INCL_Z80
   #define _INCL_Z80
   #include "../src/z80.h"
#endif
#include "../src/error.h"

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

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  resetCPURegisters
 *  Description:  Reset the CPU registers to a predefined state
 * =====================================================================================
 */
int resetCPURegisters(Memory * memory, Z80 * z80, Registers * registers)
{
   z80->r = registers;

/*
   z80->regA = 0xA; // 0x0
   z80->regB = 0xB; // 0x1
   z80->regC = 0xC; // 0x2
   z80->regD = 0xD; // 0x3
   z80->regE = 0xE; // 0x4
   z80->regF = 0xF; // 0x5
   z80->regH = 0x8; // 0x6
   z80->regL = 0x12; // 0x7

   z80->regA = 0xFF; // 0x0
   z80->regB = 0xFF; // 0x1
   z80->regC = 0xFF; // 0x2
   z80->regD = 0xFF; // 0x3
   z80->regE = 0xFF; // 0x4
   z80->regF = 0xFF; // 0x5
   z80->regH = 0xFF; // 0x6
   z80->regL = 0xFF; // 0x7
*/

   z80->regA = 0x0; // 0x0
   z80->regB = 0x0; // 0x1
   z80->regC = 0x0; // 0x2
   z80->regD = 0x0; // 0x3
   z80->regE = 0x0; // 0x4
   z80->regF = 0x0; // 0x5
   z80->regH = 0x0; // 0x6
   z80->regL = 0x0; // 0x7

   z80->regPC = 0x0;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  randomize_registers
 *  Description:  Randomize the contents of the registers
 * =====================================================================================
 */
int randomize_registers(Z80 * z80, Registers * registers)
{
   int r = rand();

   z80->r = registers;
   z80->regA = rand() % 0xFF;
   z80->regB = rand() % 0xFF;
   z80->regC = rand() % 0xFF;
   z80->regD = rand() % 0xFF;
   z80->regE = rand() % 0xFF;
   z80->regH = rand() % 0xFF;
   z80->regL = rand() % 0xFF;
   z80->regF = rand() % 0xFF;
   // 0xFF until the memory stuff is working
   z80->regPC = rand() % 0xFF;
   z80->regSP = rand() % 0xFFFF;

   return 0;
}

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  pow_uint8
 *  Description:  Return 8-bit unsigned value of value (power of) pow
 *                Only works with positive numbers for which the answer
 *                does not exceed 255
 * =====================================================================================
 */
   uint8_t
pow_uint8 ( uint8_t value, uint8_t pow )
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
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  LDXd8
 *  Description:  Load 8bit Y value into X register
 * =====================================================================================
 */
   int
LDXd8 ( Memory * memory, Z80 * z80, uint8_t reg, uint8_t value )
{
printf("FIND %x %x",z80->r->r[reg & 0xF],(value & 0xFF));
fflush(stdout);
   fail_unless( z80->r->r[reg & 0xF] == (value & 0xFF) );
 
   return 0;
}		/* -----  end of function LDXd8Y  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  LDXY
 *  Description:  Load value stored at Y register into X register
 * =====================================================================================
 */
int LDXY(Memory * memory, Z80 * z80, uint8_t regOrder, uint16_t tmp_z80_PC)
{
   uint8_t dest;
   char destName;

   switch((regOrder >> 4) & 0xF)
   {
      case 0x0: dest = z80->regA; destName = 'A'; break;
      case 0x1: dest = z80->regB; destName = 'B'; break;
      case 0x2: dest = z80->regC; destName = 'C'; break;
      case 0x3: dest = z80->regD; destName = 'D'; break;
      case 0x4: dest = z80->regE; destName = 'E'; break;
      case 0x5: dest = z80->regF; destName = 'F'; break;
      case 0x6: dest = z80->regH; destName = 'H'; break;
      case 0x7: dest = z80->regL; destName = 'L'; break;
   }

   switch(regOrder & 0xF)
   {
      case 0x0: fail_unless(dest == z80->regA,"Register %c does not equal register A",destName); break;
      case 0x1: fail_unless(dest == z80->regB,"Register %c does not equal register B",destName); break;
      case 0x2: fail_unless(dest == z80->regC,"Register %c does not equal register C",destName); break;
      case 0x3: fail_unless(dest == z80->regD,"Register %c does not equal register D",destName); break;
      case 0x4: fail_unless(dest == z80->regE,"Register %c does not equal register E",destName); break;
      case 0x5: fail_unless(dest == z80->regF,"Register %c does not equal register F",destName); break;
      case 0x6: fail_unless(dest == z80->regH,"Register %c does not equal register H",destName); break;
      case 0x7: fail_unless(dest == z80->regL,"Register %c does not equal register L",destName); break;
   }

   //fail_unless(z80->regPC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");

   return 0;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  LDXYZ
 *  Description:  
 * =====================================================================================
 */
   int
LDXYZ( Memory * memory, Z80 * z80, uint8_t x, uint8_t yz, uint16_t tmp_z80_PC )
{
   fail_unless( z80->r->r[(x & 0xF)] == (rb(z80,memory,(z80->r->r[yz] << 8) + z80->r->r[(yz + 1)]) & 0xFF) );

   //fail_unless(z80->regPC == tmp_z80_PC + 0x3);
   
   return 0;
}		/* -----  end of function LDXYZ  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ADDXY
 *  Description:  Add the contents of the Y register to the X register
 * =====================================================================================
 */
int ADDXY(Memory * memory, Z80 * z80, Z80 * old_z80, uint8_t regOrder, uint16_t tmp_z80_PC)
{
   uint8_t dest, oldDest, oldSrc;

   dest = z80->r->r[(regOrder >> 4) & 0xF];
   oldDest = old_z80->r->r[(regOrder >> 4) & 0xF];
   oldSrc = old_z80->r->r[regOrder & 0xF];

   fail_unless(dest == ((oldDest + oldSrc) & 0xFF));

   dest = (oldDest + oldSrc) & 0xFF;

   // Flags
   if ((dest < oldDest) | (dest < oldSrc))
   {
      // Carry
      fail_unless((z80->regF & 0x10) == 0x10,"Carry flag should be set %x",z80->regF & 0x10);
   }

   if ((dest & 0xFF) == 0x00)
   {
      // Zero flag
      fail_unless(z80->regF & 0x80);
   }

   if (((oldSrc & 0xF) + (oldDest & 0xF)) & 0x10)
   {
      // Half-carry
      fail_unless(z80->regF == z80->regF | 0x20,"Half-carry flag should be set");
   }

   //fail_unless(z80->regPC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");

   return 0;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ADCXY
 *  Description:  Add the contents of the Y register to the X register and set carry
 *                flag
 * =====================================================================================
 */
int ADCXY(Memory * memory, Z80 * z80, Z80 * old_z80, uint8_t regOrder, uint16_t tmp_z80_PC)
{
   uint8_t dest, oldDest, oldSrc;
   char destName;

   switch((regOrder >> 4) & 0xF)
   {
      case 0x0: dest = z80->regA; oldDest = old_z80->regA; destName = 'A'; break;
      case 0x1: dest = z80->regB; oldDest = old_z80->regB; destName = 'B'; break;
      case 0x2: dest = z80->regC; oldDest = old_z80->regC ;destName = 'C'; break;
      case 0x3: dest = z80->regD; oldDest = old_z80->regD; destName = 'D'; break;
      case 0x4: dest = z80->regE; oldDest = old_z80->regE; destName = 'E'; break;
      case 0x5: dest = z80->regF; oldDest = old_z80->regF; destName = 'F'; break;
      case 0x6: dest = z80->regH; oldDest = old_z80->regH; destName = 'H'; break;
      case 0x7: dest = z80->regL; oldDest = old_z80->regL; destName = 'L'; break;
   }

   switch(regOrder & 0xF)
   {
      case 0x0: oldSrc = old_z80->regA; fail_unless(dest == ((oldDest + oldSrc + ((z80->regF & 0x10) >> 4)) & 0xFF),"Register %c does not equal register %c + register A + carry flag",destName,destName); break;
      case 0x1: oldSrc = old_z80->regB; fail_unless(dest == ((oldDest + oldSrc + ((z80->regF & 0x10) >> 4)) & 0xFF),"Register %c does not equal register %c + register B + carry flag",destName,destName); break;
      case 0x2: oldSrc = old_z80->regC; fail_unless(dest == ((oldDest + oldSrc + ((z80->regF & 0x10) >> 4)) & 0xFF),"Register %c does not equal register %c + register C + carry flag",destName,destName); break;
      case 0x3: oldSrc = old_z80->regD; fail_unless(dest == ((oldDest + oldSrc + ((z80->regF & 0x10) >> 4)) & 0xFF),"Register %c does not equal register %c + register D + carry flag",destName,destName); break;
      case 0x4: oldSrc = old_z80->regE; fail_unless(dest == ((oldDest + oldSrc + ((z80->regF & 0x10) >> 4)) & 0xFF),"Register %c does not equal register %c + register E + carry flag",destName,destName); break;
      case 0x5: oldSrc = old_z80->regF; fail_unless(dest == ((oldDest + oldSrc + ((z80->regF & 0x10) >> 4)) & 0xFF),"Register %c does not equal register %c + register F + carry flag",destName,destName); break;
      case 0x6: oldSrc = old_z80->regH; fail_unless(dest == ((oldDest + oldSrc + ((z80->regF & 0x10) >> 4)) & 0xFF),"Register %c does not equal register %c + register H + carry flag",destName,destName); break;
      case 0x7: oldSrc = old_z80->regL; fail_unless(dest == ((oldDest + oldSrc + ((z80->regF & 0x10) >> 4)) & 0xFF),"Register %c does not equal register %c + register L + carry flag",destName,destName); break;
   }
   //dest = (oldDest + oldSrc) & 0xFF;

   // Flags
   if ((dest < oldDest) | (dest < oldSrc))
   {
      // Carry
      fail_unless((z80->regF & 0x10) == 0x10,"Carry flag should be set");
   }

   if ((dest & 0xFF) == 0x00)
   {
      // Zero flag
      fail_unless(z80->regF & 0x80,"Zero flag should be set");
   }

   if (((oldSrc & 0xF) + (oldDest & 0xF)) & 0x10)
   {
      // Half-carry
      fail_unless(z80->regF == z80->regF | 0x20,"Half-carry flag should be set");
   }

   //fail_unless(z80->regPC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");

   return 0;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  SUBXY
 *  Description:  Subtract the contents of the Y register from the X register
 * =====================================================================================
 */
int SUBXY(Memory * memory, Z80 * z80, Z80 * old_z80, uint8_t regOrder, uint16_t tmp_z80_PC)
{
   uint8_t dest, oldDest, oldSrc;
   char destName;

   switch((regOrder >> 4) & 0xF)
   {
      case 0x0: dest = z80->regA; oldDest = old_z80->regA; destName = 'A'; break;
      case 0x1: dest = z80->regB; oldDest = old_z80->regB; destName = 'B'; break;
      case 0x2: dest = z80->regC; oldDest = old_z80->regC; destName = 'C'; break;
      case 0x3: dest = z80->regD; oldDest = old_z80->regD; destName = 'D'; break;
      case 0x4: dest = z80->regE; oldDest = old_z80->regE; destName = 'E'; break;
      case 0x5: dest = z80->regF; oldDest = old_z80->regF; destName = 'F'; break;
      case 0x6: dest = z80->regH; oldDest = old_z80->regH; destName = 'H'; break;
      case 0x7: dest = z80->regL; oldDest = old_z80->regL; destName = 'L'; break;
   }

   switch(regOrder & 0xF)
   {
      case 0x0: oldSrc = old_z80->regA; fail_unless(dest == ((oldDest - oldSrc) & 0xFF),"Register %c does not equal register %c - register A",destName,destName); break;
      case 0x1: oldSrc = old_z80->regB; fail_unless(dest == ((oldDest - oldSrc) & 0xFF),"Register %c does not equal register %c - register B",destName,destName); break;
      case 0x2: oldSrc = old_z80->regC; fail_unless(dest == ((oldDest - oldSrc) & 0xFF),"Register %c does not equal register %c - register C",destName,destName); break;
      case 0x3: oldSrc = old_z80->regD; fail_unless(dest == ((oldDest - oldSrc) & 0xFF),"Register %c does not equal register %c - register D",destName,destName); break;
      case 0x4: oldSrc = old_z80->regE; fail_unless(dest == ((oldDest - oldSrc) & 0xFF),"Register %c does not equal register %c - register E",destName,destName); break;
      case 0x5: oldSrc = old_z80->regF; fail_unless(dest == ((oldDest - oldSrc) & 0xFF),"Register %c does not equal register %c - register F",destName,destName); break;
      case 0x6: oldSrc = old_z80->regH; fail_unless(dest == ((oldDest - oldSrc) & 0xFF),"Register %c does not equal register %c - register H",destName,destName); break;
      case 0x7: oldSrc = old_z80->regL; fail_unless(dest == ((oldDest - oldSrc) & 0xFF),"Register %c does not equal register %c - register L",destName,destName); break;
   }

   //dest = (oldDest - oldSrc) & 0xFF;

   // Flags
   if (dest > oldDest)
   {
      // Carry
      fail_unless((z80->regF & 0x10) == 0x10,"Carry flag should be set %x",z80->regF & 0x10);
   }

   if ((dest & 0xFF) == 0x00)
   {
      // Zero flag
      fail_unless(z80->regF & 0x80,"Zero flag should be set");
   }

   if (((oldSrc & 0xF) - (oldDest & 0xF)) & 0x10)
   {
      // Half-carry
      fail_unless(z80->regF == z80->regF | 0x20,"Half-carry flag should be set");
   }

   //Subtract flag
   fail_unless((z80->regF & 0x40) == 0x40,"Subtract flag not set");

   //fail_unless(z80->regPC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");

   return 0;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  SBCXY
 *  Description:  Subtract the contents of the Y register from the X register and set
 *                the carry flag
 * =====================================================================================
 */
int SBCXY(Memory * memory, Z80 * z80, Z80 * old_z80, uint8_t regOrder, uint16_t tmp_z80_PC)
{
   uint8_t dest, oldDest, oldSrc;
   char destName;

   switch((regOrder >> 4) & 0xF)
   {
      case 0x0: dest = z80->regA; oldDest = old_z80->regA; destName = 'A'; break;
      case 0x1: dest = z80->regB; oldDest = old_z80->regB; destName = 'B'; break;
      case 0x2: dest = z80->regC; oldDest = old_z80->regC; destName = 'C'; break;
      case 0x3: dest = z80->regD; oldDest = old_z80->regD; destName = 'D'; break;
      case 0x4: dest = z80->regE; oldDest = old_z80->regE; destName = 'E'; break;
      case 0x5: dest = z80->regF; oldDest = old_z80->regF; destName = 'F'; break;
      case 0x6: dest = z80->regH; oldDest = old_z80->regH; destName = 'H'; break;
      case 0x7: dest = z80->regL; oldDest = old_z80->regL; destName = 'L'; break;
   }

   switch(regOrder & 0xF)
   {
      case 0x0: oldSrc = old_z80->regA; fail_unless(dest == ((oldDest - oldSrc - ((z80->regF & 0x10) >> 4)) & 0xFF),"Register %c does not equal register %c - register A - carry flag dest = %x oldDest = %x oldSrc = %x carry flag = %x",destName,destName,dest,oldDest,oldSrc,((z80->regF & 0x10) >> 4)); break;
      case 0x1: oldSrc = old_z80->regB; fail_unless(dest == ((oldDest - oldSrc - ((z80->regF & 0x10) >> 4)) & 0xFF),"Register %c does not equal register %c - register B - carry flag",destName,destName); break;
      case 0x2: oldSrc = old_z80->regC; fail_unless(dest == ((oldDest - oldSrc - ((z80->regF & 0x10) >> 4)) & 0xFF),"Register %c does not equal register %c - register C - carry flag",destName,destName); break;
      case 0x3: oldSrc = old_z80->regD; fail_unless(dest == ((oldDest - oldSrc - ((z80->regF & 0x10) >> 4)) & 0xFF),"Register %c does not equal register %c - register D - carry flag",destName,destName); break;
      case 0x4: oldSrc = old_z80->regE; fail_unless(dest == ((oldDest - oldSrc - ((z80->regF & 0x10) >> 4)) & 0xFF),"Register %c does not equal register %c - register E - carry flag",destName,destName); break;
      case 0x5: oldSrc = old_z80->regF; fail_unless(dest == ((oldDest - oldSrc - ((z80->regF & 0x10) >> 4)) & 0xFF),"Register %c does not equal register %c - register F - carry flag",destName,destName); break;
      case 0x6: oldSrc = old_z80->regH; fail_unless(dest == ((oldDest - oldSrc - ((z80->regF & 0x10) >> 4)) & 0xFF),"Register %c does not equal register %c - register H - carry flag",destName,destName); break;
      case 0x7: oldSrc = old_z80->regL; fail_unless(dest == ((oldDest - oldSrc - ((z80->regF & 0x10) >> 4)) & 0xFF),"Register %c does not equal register %c - register L - carry flag",destName,destName); break;
   }

   //dest = (oldDest - oldSrc - ((z80->regF & 0x10) >> 4)) & 0xFF;

   // Flags
   if (dest > oldDest)
   {
      // Carry
      fail_unless((z80->regF & 0x10) == 0x10,"Carry flag should be set %x",z80->regF & 0x10);
   }

   if ((dest & 0xFF) == 0x00)
   {
      // Zero flag
      fail_unless(z80->regF & 0x80,"Zero flag should be set");
   }

   if (((oldSrc & 0xF) - (oldDest & 0xF)) & 0x10)
   {
      // Half-carry
      fail_unless(z80->regF == z80->regF | 0x20,"Half-carry flag should be set");
   }

   //Subtract flag
   fail_unless((z80->regF & 0x40) == 0x40,"Subtract flag not set");

   //fail_unless(z80->regPC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");

   return 0;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ANDXY
 *  Description:  Bitwise AND the contents of the Y register with the X register
 * =====================================================================================
 */
int ANDXY(Memory * memory, Z80 * z80, Z80 * old_z80, uint8_t regOrder, uint16_t tmp_z80_PC)
{
   uint8_t dest, oldDest, oldSrc;
   char destName;

   switch((regOrder >> 4) & 0xF)
   {
      case 0x0: dest = z80->regA; oldDest = old_z80->regA; destName = 'A'; break;
      case 0x1: dest = z80->regB; oldDest = old_z80->regB; destName = 'B'; break;
      case 0x2: dest = z80->regC; oldDest = old_z80->regC ;destName = 'C'; break;
      case 0x3: dest = z80->regD; oldDest = old_z80->regD; destName = 'D'; break;
      case 0x4: dest = z80->regE; oldDest = old_z80->regE; destName = 'E'; break;
      case 0x5: dest = z80->regF; oldDest = old_z80->regF; destName = 'F'; break;
      case 0x6: dest = z80->regH; oldDest = old_z80->regH; destName = 'H'; break;
      case 0x7: dest = z80->regL; oldDest = old_z80->regL; destName = 'L'; break;
   }

   switch(regOrder & 0xF)
   {
      case 0x0: oldSrc = old_z80->regA; fail_unless(dest == ((oldDest & oldSrc) & 0xFF),"Register %c does not equal register %c AND register A",destName,destName); break;
      case 0x1: oldSrc = old_z80->regB; fail_unless(dest == ((oldDest & oldSrc) & 0xFF),"Register %c does not equal register %c AND register B",destName,destName); break;
      case 0x2: oldSrc = old_z80->regC; fail_unless(dest == ((oldDest & oldSrc) & 0xFF),"Register %c does not equal register %c AND register C dest = %x oldDest = %x oldSrc = %x",destName,destName,dest,oldDest,oldSrc); break;
      case 0x3: oldSrc = old_z80->regD; fail_unless(dest == ((oldDest & oldSrc) & 0xFF),"Register %c does not equal register %c AND register D",destName,destName); break;
      case 0x4: oldSrc = old_z80->regE; fail_unless(dest == ((oldDest & oldSrc) & 0xFF),"Register %c does not equal register %c AND register E",destName,destName); break;
      case 0x5: oldSrc = old_z80->regF; fail_unless(dest == ((oldDest & oldSrc) & 0xFF),"Register %c does not equal register %c AND register F",destName,destName); break;
      case 0x6: oldSrc = old_z80->regH; fail_unless(dest == ((oldDest & oldSrc) & 0xFF),"Register %c does not equal register %c AND register H",destName,destName); break;
      case 0x7: oldSrc = old_z80->regL; fail_unless(dest == ((oldDest & oldSrc) & 0xFF),"Register %c does not equal register %c AND register L",destName,destName); break;
   }

   //dest = (oldDest + oldSrc) & 0xFF;

   if ((dest & 0xFF) == 0x00)
   {
      // Zero flag
      fail_unless((z80->regF & 0x80) == 0x80,"Zero flag not set");
   }

   //Subtract
   fail_unless((z80->regF & 0x40) != 0x40,"Subtract flag should not be set");

   // Half-carry
   fail_unless((z80->regF & 0x20) == 0x20,"Half carry flag not set");

   // Carry
   fail_unless((z80->regF & 0x10) != 0x10,"Carry flag should not be set");

   //fail_unless(z80->regPC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");

   return 0;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  CB_BITXY
 *  Description:  Test bit X of register Y
 * =====================================================================================
 */
int CB_BITXY(Memory * memory, Z80 * z80, Z80 * old_z80, uint8_t parameters, uint16_t tmp_z80_PC)
{
   uint8_t cpuRegisterBit;
   char destName;

   switch(parameters & 0xF)
   {
      // cpuRegisterBit = (regY & (2 to the power of X) >> X) & 0xF
      case 0x0: cpuRegisterBit = (((z80->regA & (pow_uint8(2,(parameters & 0xF0) >> 4))) >> ((parameters & 0xF0) >> 4)) & 0xF); break;
      case 0x1: cpuRegisterBit = (((z80->regB & (pow_uint8(2,(parameters & 0xF0) >> 4))) >> ((parameters & 0xF0) >> 4)) & 0xF); break;
      case 0x2: cpuRegisterBit = (((z80->regC & (pow_uint8(2,(parameters & 0xF0) >> 4))) >> ((parameters & 0xF0) >> 4)) & 0xF); break;
      case 0x3: cpuRegisterBit = (((z80->regD & (pow_uint8(2,(parameters & 0xF0) >> 4))) >> ((parameters & 0xF0) >> 4)) & 0xF); break;
      case 0x4: cpuRegisterBit = (((z80->regE & (pow_uint8(2,(parameters & 0xF0) >> 4))) >> ((parameters & 0xF0) >> 4)) & 0xF); break;
      case 0x5: cpuRegisterBit = (((z80->regH & (pow_uint8(2,(parameters & 0xF0) >> 4))) >> ((parameters & 0xF0) >> 4)) & 0xF); break;
      case 0x6: cpuRegisterBit = (((z80->regL & (pow_uint8(2,(parameters & 0xF0) >> 4))) >> ((parameters & 0xF0) >> 4)) & 0xF); break;
   }
printf("cpuRegisterBit == %x\n",cpuRegisterBit);
   if (cpuRegisterBit == 0x0)
   {
      // Zero flag
      fail_unless((z80->regF & 0x80) == 0x80,"Zero flag not set");
   }

   //Subtract
   fail_unless((z80->regF & 0x40) != 0x40,"Subtract flag should not be set");

   // Half-carry
   fail_unless((z80->regF & 0x20) == 0x20,"Half carry flag not set");

   // Carry
   fail_unless((z80->regF & 0x10) == (old_z80->regF & 0x10),"Carry flag should have been preserved");

   //fail_unless(z80->regPC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");

   return 0;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  CB_RESXY
 *  Description:  Reset bit X of register Y
 * =====================================================================================
 */
int CB_RESXY(Memory * memory, Z80 * z80, Z80 * old_z80, uint8_t parameters, uint16_t tmp_z80_PC)
{
   uint8_t cpuRegister;
   uint8_t flagBit;

   switch(parameters & 0xF)
   {
      case 0x0: cpuRegister = z80->regA; break;
      case 0x1: cpuRegister = z80->regB; break;
      case 0x2: cpuRegister = z80->regC; break;
      case 0x3: cpuRegister = z80->regD; break;
      case 0x4: cpuRegister = z80->regE; break;
      case 0x6: cpuRegister = z80->regH; break;
      case 0x7: cpuRegister = z80->regL; break;
   }

   flagBit = (((parameters & 0xF0) >> 4) & 0xF);

   fail_unless(((cpuRegister >> flagBit) & 0x1) == 0,"Register bit %x should be set to zero",flagBit);

   fail_unless(z80->regF == old_z80->regF,"Flags should not have been changed");

   //fail_unless(z80->regPC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");

   return 0;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  CB_SETXY
 *  Description:  Set bit X of register Y
 * =====================================================================================
 */
int CB_SETXY(Memory * memory, Z80 * z80, Z80 * old_z80, uint8_t parameters, uint16_t tmp_z80_PC)
{
   uint8_t cpuRegister;
   uint8_t flagBit;

   switch(parameters & 0xF)
   {
      case 0x0: cpuRegister = z80->regA; break;
      case 0x1: cpuRegister = z80->regB; break;
      case 0x2: cpuRegister = z80->regC; break;
      case 0x3: cpuRegister = z80->regD; break;
      case 0x4: cpuRegister = z80->regE; break;
      case 0x6: cpuRegister = z80->regH; break;
      case 0x7: cpuRegister = z80->regL; break;
   }

   flagBit = (((parameters & 0xF0) >> 4) & 0xF);

   fail_unless(((cpuRegister >> flagBit) & 0x1) == 1,"Register bit %x should be set",flagBit);

   fail_unless(z80->regF == old_z80->regF,"Flags should not have been changed");

   //fail_unless(z80->regPC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");

   return 0;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  CB_RLCX
 *  Description:  Rotate register X left and add carry
 * =====================================================================================
 */
int CB_RLCX(Memory * memory, Z80 * z80, Z80 * old_z80, uint8_t parameters, uint16_t tmp_z80_PC)
{
   uint8_t cpuRegister;
   uint8_t oldCpuRegister;

   switch(parameters & 0xF)
   {
      case 0x0: cpuRegister = z80->regA; oldCpuRegister = old_z80->regA; break;
      case 0x1: cpuRegister = z80->regB; oldCpuRegister = old_z80->regB; break;
      case 0x2: cpuRegister = z80->regC; oldCpuRegister = old_z80->regC; break;
      case 0x3: cpuRegister = z80->regD; oldCpuRegister = old_z80->regD; break;
      case 0x4: cpuRegister = z80->regE; oldCpuRegister = old_z80->regE; break;
      case 0x6: cpuRegister = z80->regH; oldCpuRegister = old_z80->regH; break;
      case 0x7: cpuRegister = z80->regL; oldCpuRegister = old_z80->regL; break;
   }

printf("\nparameters == %x\n((oldCpuRegister << 1) | ((oldCpuRegister >> 7) & 0x1) == %x\ncpuRegister == %x\n",parameters,((oldCpuRegister << 1) | ((oldCpuRegister >> 7) & 0x1)),cpuRegister);

   // Test rotate left with carry
   fail_unless(((oldCpuRegister << 1) | ((oldCpuRegister >> 7) & 0x1)) == cpuRegister,"Rotate left with carry seems to have failed");

   // Subtract flag
   fail_unless((z80->regF & 0x40) == 0,"Subtract flag should be set to zero");
   // Half-carry flag
   fail_unless((z80->regF & 0x20) == 0,"Half-carry flag should be set to zero");

   // Zero flag
   if (cpuRegister == 0x0)
   {
      fail_unless((z80->regF & 0x80) == 0x80,"Zero flag should be set");
   } else {
      fail_unless((z80->regF & 0x80) == 0x0,"Zero flag should not be set");
   }

   // Carry flag
   if ((oldCpuRegister & 0x80) == 1)
   {
      fail_unless((z80->regF & 0x10) == 1,"Carry flag should be set");
   } else {
      fail_unless((z80->regF & 0x10) == 0,"Carry flag should not be set");
   }

   //fail_unless(z80->regPC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");

   return 0;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  CB_RRCX
 *  Description:  Rotate register X right and add carry
 * =====================================================================================
 */
int CB_RRCX(Memory * memory, Z80 * z80, Z80 * old_z80, uint8_t parameters, uint16_t tmp_z80_PC)
{
   uint8_t cpuRegister;
   uint8_t oldCpuRegister;

   switch(parameters & 0xF)
   {
      case 0x0: cpuRegister = z80->regA; oldCpuRegister = old_z80->regA; break;
      case 0x1: cpuRegister = z80->regB; oldCpuRegister = old_z80->regB; break;
      case 0x2: cpuRegister = z80->regC; oldCpuRegister = old_z80->regC; break;
      case 0x3: cpuRegister = z80->regD; oldCpuRegister = old_z80->regD; break;
      case 0x4: cpuRegister = z80->regE; oldCpuRegister = old_z80->regE; break;
      case 0x6: cpuRegister = z80->regH; oldCpuRegister = old_z80->regH; break;
      case 0x7: cpuRegister = z80->regL; oldCpuRegister = old_z80->regL; break;
   }

   // Test rotate right with carry
   fail_unless((oldCpuRegister >> 1) | ((oldCpuRegister & 0x1) << 7) == cpuRegister,"Rotate right with carry seems to have failed %x %x",oldCpuRegister,cpuRegister);

   // Subtract flag
   fail_unless((z80->regF & 0x40) == 0,"Subtract flag should be set to zero");
   // Half-carry flag
   fail_unless((z80->regF & 0x20) == 0,"Half-carry flag should be set to zero");

   // Zero flag
   if (cpuRegister == 0x0)
   {
      fail_unless((z80->regF & 0x80) == 0x80,"Zero flag should be set");
   } else {
      fail_unless((z80->regF & 0x80) == 0x0,"Zero flag should not be set");
   }

   // Carry flag
   if ((oldCpuRegister & 0x10) == 1)
   {
      fail_unless((z80->regF & 0x10) == 1,"Carry flag should be set");
   } else {
      fail_unless((z80->regF & 0x10) == 0,"Carry flag should not be set");
   }

   //fail_unless(z80->regPC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");

   return 0;
}

int CB_RLX(Memory * memory, Z80 * z80, Z80 * old_z80, uint8_t parameters, uint16_t tmp_z80_PC)
{
   return 0;
}

int CB_RRX(Memory * memory, Z80 * z80, Z80 * old_z80, uint8_t parameters, uint16_t tmp_z80_PC)
{
   uint8_t cpuRegister;
   uint8_t oldCpuRegister;

   switch(parameters & 0xF)
   {
      case 0x0: cpuRegister = z80->regA; oldCpuRegister = old_z80->regA; break;
      case 0x1: cpuRegister = z80->regB; oldCpuRegister = old_z80->regB; break;
      case 0x2: cpuRegister = z80->regC; oldCpuRegister = old_z80->regC; break;
      case 0x3: cpuRegister = z80->regD; oldCpuRegister = old_z80->regD; break;
      case 0x4: cpuRegister = z80->regE; oldCpuRegister = old_z80->regE; break;
      case 0x5: cpuRegister = z80->regH; oldCpuRegister = old_z80->regH; break;
      case 0x6: cpuRegister = z80->regL; oldCpuRegister = old_z80->regL; break;
   }

   // Test rotate right with carry
   fail_unless((oldCpuRegister >> 1) | ((oldCpuRegister & 0x1) << 7) == cpuRegister,"Rotate right with carry seems to have failed %x %x",oldCpuRegister,cpuRegister);

   // Subtract flag
   fail_unless((z80->regF & 0x40) == 0,"Subtract flag should be set to zero");
   // Half-carry flag
   fail_unless((z80->regF & 0x20) == 0,"Half-carry flag should be set to zero");

   // Zero flag
   if (cpuRegister == 0x0)
   {
      fail_unless((z80->regF & 0x80) == 0x80,"Zero flag should be set");
   } else {
      fail_unless((z80->regF & 0x80) == 0x0,"Zero flag should not be set");
   }

   // Carry flag
   if ((oldCpuRegister & 0x80) == 1)
   {
      fail_unless((z80->regF & 0x10) == 1,"Carry flag should be set");
   } else {
      fail_unless((z80->regF & 0x10) == 0,"Carry flag should not be set");
   }

   //fail_unless(z80->regPC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");

   return 0;
}

START_TEST (test_check_OP_INCX)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);
   InitMemory(&memory);

   int result = 0, h = 0, i = 0;
   uint8_t tmp_z80_PC = z80.regPC, oldRegValue, tmp_z80_F;
   
   for ( h=0 ; h<0x7; h++ )
   {
      for(i=0;i<0xFF;i++)
      {
         oldRegValue = z80.r->r[h];
         tmp_z80_F = z80.regF;

         z80.regPC = i;

         tmp_z80_PC = (z80.regPC & 0xFF);

         result = OP_INCX(&memory,&z80,h);

         // Half carry
         if ((((oldRegValue & 0xF) + 0x1) & 0xF) == 0x0)
         {
            fail_unless((z80.regF & 0x20) == 0x20);
         }

         // Zero flag
         if (z80.r->r[h] == 0x0)
         {
            fail_unless((z80.regF & 0x80) == 0x80);
         }

         // Negate flag
         fail_unless((z80.regF & 0x40) == 0x0);

         // Carry flag
         fail_unless((z80.regF & 0x10) == (tmp_z80_F & 0x10));
      }
   }
}
END_TEST

START_TEST (test_check_OP_LDXd8)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);
   InitMemory(&memory);

   LoadGBROM(&memory,"/home/user/git/gameboy-emulator/roms/DMG_ROM.bin");

   int result = 0, h = 0, i = 0;
   uint8_t tmp_z80_PC = z80.regPC;
   
   for ( h=0 ; h<0x7; h++ )
   {
      for(i=0;i<0xFF;i++)
      {
         z80.regPC = i;

         tmp_z80_PC = (z80.regPC & 0xFF);

         result = OP_LDXd8(&memory,&z80,h);

         fail_unless((z80.r->r[h] & 0xFF) == rb(&z80,&memory,(tmp_z80_PC)) & 0xFF);
         //fail_unless(z80.regPC == tmp_z80_PC + 1,"Program Counter should not be incremented by opcode function code");

         fail_unless(result == 0,"Result was not 0");
      }
   }
}
END_TEST

START_TEST (test_check_OP_LDXd16)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);
   InitMemory(&memory);

   LoadGBROM(&memory,"/home/user/git/gameboy-emulator/roms/DMG_ROM.bin");

   int result = 0, h = 0, i = 0;
   uint8_t tmp_z80_PC = z80.regPC;
   
   z80.regPC = i;

   tmp_z80_PC = (z80.regPC & 0xFF);

   result = OP_LDXd16(&memory,&z80,h);

   fail_unless((z80.r->r[h] & 0xFF) == rb(&z80,&memory,(tmp_z80_PC + 1)) & 0xFF);
   fail_unless((z80.r->r[h + 1] & 0xFF) == rb(&z80,&memory,(tmp_z80_PC)) & 0xFF);
   //fail_unless(z80.regPC == tmp_z80_PC + 2);

   fail_unless(result == 0,"Result was not 0");
}
END_TEST

START_TEST (test_check_OP_LDHLX)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);
   InitMemory(&memory);

   LoadGBROM(&memory,"/home/user/git/gameboy-emulator/roms/DMG_ROM.bin");

   uint16_t tmp_z80_PC = z80.regPC;
   uint16_t tmp_z80_HL = (z80.regH << 8) + z80.regL;
   int result = 0, i = 0, h = 0;
   uint8_t reg = 0x0;

   for(h=0;h<2;h++)
   {
      for(i=0;i<256;i++)
      {
         // One round of sanity, one round of randomness
         if (h)
         {
            randomize_registers(&z80,&registers);

            reg = (rand() % 0xF) + 0x1;
            // Shouldn't be F register
            while(reg == 0x5)
            {
               reg = (rand() % 0xF) + 0x1;
            }
         } else{
            z80.regPC = i;
         }

         tmp_z80_PC = z80.regPC;
         tmp_z80_HL = (z80.regH << 8) + z80.regL;

//printf("HL = %x\n",(z80.regH << 8) + z80.regL);

         result = OP_LDHLX(&memory,&z80,reg);

//printf("z80.regPC == %x\ntmp_z80_PC == %x\n",z80.regPC,tmp_z80_PC);
         //fail_unless(z80.regPC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");

         fail_unless(result == 0,"Result was not 0");
printf("HERE -- HL addr content = %x\nHERE reg = %x\n",rb(&z80,&memory,(z80.regH << 8) + z80.regL),z80.r->r[reg]);
         fail_unless(rb(&z80,&memory,(z80.regH << 8) + z80.regL) == z80.r->r[reg],"Content at address pointed by HL does not match register.");
      }
   }
}
END_TEST

START_TEST (test_check_OP_00h_NOP)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);
   InitMemory(&memory);

   int result = 0;
   uint8_t tmp_z80_PC = z80.regPC;

   result = OP_00h_NOP(&memory,&z80);

   fail_unless(result == 0,"Result was not 0");
   fail_unless(z80.op_call[tmp_z80_PC].size == 1);
}
END_TEST

START_TEST (test_check_OP_01h_LDBCd16)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_02h_LDBCA)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_03h_INCBC)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_04h_INCB)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_05h_DECB)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_06h_LDBd8)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_07h_RLCA)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_08h_LDa16SP)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_09h_ADDHLBC)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_0Ah_LDABC)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_0Bh_DECBC)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_0Ch_INCC)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_0Dh_DECC)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_0Eh_LDCd8)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXd8(memory,z80,0x2);

   LDXd8(memory,z80,0x2,rb(z80,memory,tmp_z80_PC));

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_0Fh_RRCA)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_10h_STOP0)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_11h_LDDEd16)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_12h_LDDEA)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_13h_INCDE)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_14h_INCD)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_15h_DECD)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_16h_LDd8)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_17h_RLA)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_18h_JRr8)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_19h_ADDHLDE)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_1Ah_LDADE)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);
   resetCPURegisters(&memory,&z80,&registers);
   InitMemory(&memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80.regPC;

   result = OP_LDXYZ(&memory,&z80,0x0,0x3);

   LDXYZ(&memory,&z80,0x0,0x3,tmp_z80_PC);

   fail_unless(result == 0,"Result was not 0");
   fail_unless(z80.op_call[tmp_z80_PC].size == 1);
}
END_TEST

START_TEST (test_check_OP_1Bh_DECDE)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_1Ch_INCE)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_1Dh_DECE)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_1Eh_LDEd8)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_1Fh_RRA)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_20h_JRNZr8)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);
   InitMemory(&memory);

   // Perhaps it would be worth setting the PC to be at the 0x20 opcode?
   LoadGBROM(&memory,"/home/user/git/gameboy-emulator/roms/DMG_ROM.bin");

   int result = 0, i = 0, k = 0;
   z80.regPC = k;
   uint16_t tmp_z80_PC = z80.regPC;

   for(k=0;k<0xFF;k++)
   {
      for(i=0;i<0x2;i++)
      {
         z80.regPC = k;

         if (i == 0x0)
         {
            z80.regF = 0x80;
         } else {
            z80.regF = 0x00;
         }

         tmp_z80_PC = z80.regPC;

         result = OP_20h_JRNZr8(&memory,&z80);

         // Relative jump if last result is non-zero
         // If last result is non-zero, ticks == 12, else ticks == 8
         if ((z80.regF & 0x80) == 0x00)
         {
printf("*** k == %x\nz80.regPC == %x\nrb(&z80,&memory,tmp_z80_PC) + tmp_z80_PC == %x\n",k,z80.regPC - 1,rb(&z80,&memory,tmp_z80_PC) + tmp_z80_PC);
            //fail_unless(((z80.regPC - 1) & 0xFF) == ((rb(&z80,&memory,tmp_z80_PC) + (int8_t) tmp_z80_PC) & 0xFF));
         } else {
            //fail_unless((z80.regPC - 1) == tmp_z80_PC,"Program Counter should be incremented by opcode function code");
         }

         fail_unless(result == 0,"Result was not 0");
      }
   }
}
END_TEST

START_TEST (test_check_OP_21h_LDHLd16)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);
   InitMemory(&memory);

   LoadGBROM(&memory,"/home/user/git/gameboy-emulator/roms/DMG_ROM.bin");

   int result = 0, h = 0, i = 0;
   z80.regPC = h;
   uint16_t tmp_z80_PC = z80.regPC;

   for(h=0;h<2;h++)
   {
      for(i=0;i<256;i++)
      {
         // One round of sanity, one round of randomness
         if (h)
         {
            randomize_registers(&z80,&registers);
         } else {
            z80.regPC = i;
         }

         tmp_z80_PC = z80.regPC;

         result = OP_21h_LDHLd16(&memory,&z80);
//printf("z80.regPC - 2 == %x\ntmp_z80_PC == %x\n",(z80.regPC - 2),tmp_z80_PC);
         //fail_unless((uint16_t) (z80.regPC - 2) == (uint16_t) tmp_z80_PC,"Program Counter should be incremented by opcode function code");

         fail_unless(result == 0,"Result was not 0");
         //tmp_z80_PC is 0, and this byte is treated as an address
         fail_unless(z80.regH == rb(&z80,&memory,(tmp_z80_PC + 1)),"H register incorrect value");
         fail_unless(z80.regL == rb(&z80,&memory,(tmp_z80_PC)),"L register incorrect value");

      }
   }
}
END_TEST

START_TEST (test_check_OP_22h_LDIHLA)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);
   InitMemory(&memory);

   LoadGBROM(&memory,"/home/user/git/gameboy-emulator/roms/DMG_ROM.bin");

   uint16_t tmp_z80_PC = z80.regPC;
   uint16_t tmp_z80_HL = (z80.regH << 8) + z80.regL;
   int result = 0, i = 0, h = 0;

   for(h=0;h<2;h++)
   {
      for(i=0;i<256;i++)
      {
         // One round of sanity, one round of randomness
         if (h)
         {
            randomize_registers(&z80,&registers);
         } else{
            z80.regPC = i;
         }

         tmp_z80_PC = z80.regPC;
         tmp_z80_HL = (z80.regH << 8) + z80.regL;

//printf("HL = %x\n",(z80.regH << 8) + z80.regL);

         result = OP_22h_LDIHLA(&memory,&z80);

//printf("z80.regPC == %x\ntmp_z80_PC == %x\n",z80.regPC,tmp_z80_PC);
         //fail_unless(z80.regPC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");

         fail_unless(result == 0,"Result was not 0");
//printf("HL-1 addr content = %x\nA = %x\n",rb(&z80,&memory,(z80.regH << 8) + z80.regL - 1),z80.regA);
         fail_unless(rb(&z80,&memory,(z80.regH << 8) + z80.regL - 1) == z80.regA,"Content at address pointed by HL (-1 at this point) does not match A register.");
      }
   }
}
END_TEST

START_TEST (test_check_OP_23h_INCHL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_24h_INCH)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_25h_DECH)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_26h_LDHd8)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_27h_DAA)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_28h_JRZr8)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_29h_ADDHLHL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_2Ah_LDIAHL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_2Bh_DECHL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_2Ch_INCL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_2Dh_DECL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_2Eh_LDLd8)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_2Fh_CPL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_30h_JRNCr8)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_31h_LDSPd16)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);
   InitMemory(&memory);

   LoadGBROM(&memory,"/home/user/git/gameboy-emulator/roms/DMG_ROM.bin");

   int result = 0, h = 0, i = 0;
   uint16_t tmp_z80_PC = z80.regPC;

   for(h=0;h<2;h++)
   {
      for(i=0;i<256;i++)
      {
         // One round of sanity, one round of randomness
         if (h)
         {
            randomize_registers(&z80,&registers);
         } else{
            z80.regPC = i;
         }

         tmp_z80_PC = z80.regPC;

         result = OP_31h_LDSPd16(&memory,&z80);

         //fail_unless((z80.regPC - 2) == tmp_z80_PC,"Program Counter should be incremented by opcode function code");

         fail_unless(result == 0,"Result was not 0");

         // @TODO
         // Need to fully complete memory
         // before this opcode can be tested
         // Bare in mind, the mock_rb function
         // needs to work the same as the rb
         // function. Why do we have the mock?
         /*if (tmp_z80_PC > 0xFF)
         {
            continue;
         }*/

printf("z80.regSP == %x\n(rb(&z80,&memory,(tmp_z80_PC + 1)) << 8) == %x\nrb(&z80,&memory,(tmp_z80_PC)) == %x\n",z80.regSP,(rb(&z80,&memory,(tmp_z80_PC + 1)) << 8),rb(&z80,&memory,(tmp_z80_PC)));
printf("tmp_z80_PC == %x\n",tmp_z80_PC);
         fail_unless((uint16_t) z80.regSP == (uint16_t) (rb(&z80,&memory,((uint16_t) tmp_z80_PC + (uint16_t) 1)) << 8) + (uint16_t) rb(&z80,&memory,((uint16_t) tmp_z80_PC)),"SP register incorrect value");
      }
   }
}
END_TEST

START_TEST (test_check_OP_32h_LDDHLA)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);
   InitMemory(&memory);

   LoadGBROM(&memory,"/home/user/git/gameboy-emulator/roms/DMG_ROM.bin");

   int result = 0, h = 0, i = 0;
   uint16_t tmp_z80_PC = z80.regPC;
   uint16_t tmp_z80_HL = (z80.regH << 8) + z80.regL;

   for(h=0;h<2;h++)
   {
      for(i=0;i<256;i++)
      {
         // One round of sanity, one round of randomness
         if (h)
         {
            randomize_registers(&z80,&registers);
         } else{
            z80.regPC = i;
         }

         tmp_z80_PC = z80.regPC;
         tmp_z80_HL = (z80.regH << 8) + z80.regL;
         printf("HL = %x\n",(z80.regH << 8) + z80.regL);

         result = OP_32h_LDDHLA(&memory,&z80);

         // opcode should not increment PC because PC is incremented by 1 in the opcode switch
         //fail_unless(z80.regPC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");

         fail_unless(result == 0,"Result was not 0");
         printf("HL+1 addr content = %x\nA = %x\n",rb(&z80,&memory,(z80.regH << 8) + z80.regL + 1),z80.regA);

         fail_unless(rb(&z80,&memory,(z80.regH << 8) + z80.regL + 1) == z80.regA,"Content at address pointed by HL (+1 at this point) does not match A register.");
      }
   }
}
END_TEST

START_TEST (test_check_OP_33h_INCSP)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_34h_INCHL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_35h_DECHL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_36h_LDHLd8)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_37h_SCF)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_38h_JRCr8)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_39h_ADDHLSP)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_3Ah_LDDAHL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_3Bh_DECSP)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_3Ch_INCA)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_3Dh_DECA)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_3Eh_LDAd8)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_3Fh_CCF)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_40h_LDBB)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x11);

   LDXY(memory,z80,0x11,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_41h_LDBC)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x12);

   // Error checks take place in LDXY() function
   LDXY(memory,z80,0x12,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_42h_LDBD)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x13);

   LDXY(memory,z80,0x13,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_43h_LDBE)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x14);

   LDXY(memory,z80,0x14,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_44h_LDBH)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x16);

   LDXY(memory,z80,0x16,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_45h_LDBL)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x17);

   LDXY(memory,z80,0x17,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_46h_LDBHL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_47h_LDBA)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

//   tcase_add_test(tc_core,test_check_OP_48h_LDCB);
START_TEST (test_check_OP_48h_LDCB)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x21);

   LDXY(memory,z80,0x21,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//   tcase_add_test(tc_core,test_check_OP_49h_LDCC);
START_TEST (test_check_OP_49h_LDCC)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x22);

   LDXY(memory,z80,0x22,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//   tcase_add_test(tc_core,test_check_OP_4Ah_LDCD);
START_TEST (test_check_OP_4Ah_LDCD)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x23);

   LDXY(memory,z80,0x23,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//   tcase_add_test(tc_core,test_check_OP_4Bh_LDCE);
START_TEST (test_check_OP_4Bh_LDCE)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x24);

   LDXY(memory,z80,0x24,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//   tcase_add_test(tc_core,test_check_OP_4Ch_LDCH);
START_TEST (test_check_OP_4Ch_LDCH)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x26);

   LDXY(memory,z80,0x26,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//   tcase_add_test(tc_core,test_check_OP_4Dh_LDCL);
START_TEST (test_check_OP_4Dh_LDCL)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x27);

   LDXY(memory,z80,0x27,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_4Eh_LDCHL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

//   tcase_add_test(tc_core,test_check_OP_4Fh_LDCA);
START_TEST (test_check_OP_4Fh_LDCA)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x20);

   LDXY(memory,z80,0x20,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_50h_LDDB)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x31);

   LDXY(memory,z80,0x31,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_51h_LDDC)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x32);

   LDXY(memory,z80,0x32,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_52h_LDDD)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x33);

   LDXY(memory,z80,0x33,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_53h_LDDE)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x34);

   LDXY(memory,z80,0x34,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_54h_LDDH)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x36);

   LDXY(memory,z80,0x36,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_55h_LDDL)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x37);

   LDXY(memory,z80,0x37,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_56h_LDDHL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_57h_LDDA)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_58h_LDEB)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x41);

   LDXY(memory,z80,0x41,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//   tcase_add_test(tc_core,test_check_OP_59h_LDEC);
START_TEST (test_check_OP_59h_LDEC)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x42);

   LDXY(memory,z80,0x42,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//   tcase_add_test(tc_core,test_check_OP_5Ah_LDED);
START_TEST (test_check_OP_5Ah_LDED)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x43);

   LDXY(memory,z80,0x43,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//   tcase_add_test(tc_core,test_check_OP_5Bh_LDEE);
START_TEST (test_check_OP_5Bh_LDEE)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x44);

   LDXY(memory,z80,0x44,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//   tcase_add_test(tc_core,test_check_OP_5Ch_LDEH);
START_TEST (test_check_OP_5Ch_LDEH)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x46);

   LDXY(memory,z80,0x46,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//   tcase_add_test(tc_core,test_check_OP_5Dh_LDEL);
START_TEST (test_check_OP_5Dh_LDEL)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x47);

   LDXY(memory,z80,0x47,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_5Eh_LDEHL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_5Fh_LDEA)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x40);

   LDXY(memory,z80,0x40,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_60h_LDHB)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x61);

   LDXY(memory,z80,0x61,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_61h_LDHC)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x62);

   LDXY(memory,z80,0x62,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_62h_LDHD)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x63);

   LDXY(memory,z80,0x63,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_63h_LDHE)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x64);

   LDXY(memory,z80,0x64,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_64h_LDHH)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x66);

   LDXY(memory,z80,0x66,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_65h_LDHL)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x67);

   LDXY(memory,z80,0x67,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_66h_LDHHL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_67h_LDHA)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_68h_LDLB)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x71);

   LDXY(memory,z80,0x71,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//   tcase_add_test(tc_core,test_check_OP_69h_LDLC);
START_TEST (test_check_OP_69h_LDLC)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x72);

   LDXY(memory,z80,0x72,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//   tcase_add_test(tc_core,test_check_OP_6Ah_LDLD);
START_TEST (test_check_OP_6Ah_LDLD)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x73);

   LDXY(memory,z80,0x73,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//   tcase_add_test(tc_core,test_check_OP_6Bh_LDLE);
START_TEST (test_check_OP_6Bh_LDLE)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x74);

   LDXY(memory,z80,0x74,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//   tcase_add_test(tc_core,test_check_OP_6Ch_LDLH);
START_TEST (test_check_OP_6Ch_LDLH)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x76);

   LDXY(memory,z80,0x76,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//   tcase_add_test(tc_core,test_check_OP_6Dh_LDLL);
START_TEST (test_check_OP_6Dh_LDLL)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x77);

   LDXY(memory,z80,0x77,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_6Eh_LDLHL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_6Fh_LDLA)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x70);

   LDXY(memory,z80,0x70,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_70h_LDHLB)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_71h_LDHLC)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_72h_LDHLD)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);
   InitMemory(&memory);

   int result = 0;
   uint8_t tmp_z80_PC = z80.regPC;
   uint8_t tmp_z80_HL = (z80.regH << 8) + z80.regL;

   z80.regD = 0xD;
   z80.regH = 0x8;
   z80.regL = 0x8;

   result = OP_72h_LDHLD(&memory,&z80);

   //fail_unless(z80.regPC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");

   fail_unless(result == 0,"Result was not 0");
   fail_unless(rb(&z80,&memory,(z80.regH << 8) + z80.regL) == z80.regD,"Content of address held in HL register does not equal register D");
}
END_TEST

START_TEST (test_check_OP_73h_LDHLE)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_74h_LDHLH)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_75h_LDHLL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_76h_HALT)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_77h_LDHLA)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

//   tcase_add_test(tc_core,test_check_OP_78h_LDAB);
START_TEST (test_check_OP_78h_LDAB)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x01);

   LDXY(memory,z80,0x01,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//   tcase_add_test(tc_core,test_check_OP_79h_LDAC);
START_TEST (test_check_OP_79h_LDAC)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x02);

   LDXY(memory,z80,0x02,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//   tcase_add_test(tc_core,test_check_OP_7Ah_LDAD);
START_TEST (test_check_OP_7Ah_LDAD)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x03);

   LDXY(memory,z80,0x03,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//   tcase_add_test(tc_core,test_check_OP_7Bh_LDAE);
START_TEST (test_check_OP_7Bh_LDAE)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x04);

   LDXY(memory,z80,0x04,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//   tcase_add_test(tc_core,test_check_OP_7Ch_LDAH);
START_TEST (test_check_OP_7Ch_LDAH)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x06);

   LDXY(memory,z80,0x06,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//   tcase_add_test(tc_core,test_check_OP_7Dh_LDAL);
START_TEST (test_check_OP_7Dh_LDAL)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x07);

   LDXY(memory,z80,0x07,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_7Eh_LDAHL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

//   tcase_add_test(tc_core,test_check_OP_7Fh_LDAA);
START_TEST (test_check_OP_7Fh_LDAA)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_LDXY(memory,z80,0x00);

   LDXY(memory,z80,0x00,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//   tcase_add_test(tc_core,test_check_OP_80h_ADDAB);
START_TEST (test_check_OP_80h_ADDAB)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_80h_ADDAB(memory,z80);
   ADDXY(memory,z80,old_z80,0x01,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_81h_ADDAC)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_81h_ADDAC(memory,z80);
   ADDXY(memory,z80,old_z80,0x02,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_82h_ADDAD)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_82h_ADDAD(memory,z80);
   ADDXY(memory,z80,old_z80,0x03,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_83h_ADDAE)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_83h_ADDAE(memory,z80);
   ADDXY(memory,z80,old_z80,0x04,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_84h_ADDAH)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_84h_ADDAH(memory,z80);
   ADDXY(memory,z80,old_z80,0x06,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_85h_ADDAL)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_85h_ADDAL(memory,z80);
   ADDXY(memory,z80,old_z80,0x07,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_86h_ADDAHL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_87h_ADDAA)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_87h_ADDAA(memory,z80);
   ADDXY(memory,z80,old_z80,0x00,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_88h_ADCAB)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_88h_ADCAB(memory,z80);
   ADCXY(memory,z80,old_z80,0x01,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_89h_ADCAC)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_89h_ADCAC(memory,z80);
   ADCXY(memory,z80,old_z80,0x02,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_8Ah_ADCAD)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_8Ah_ADCAD(memory,z80);
   ADCXY(memory,z80,old_z80,0x03,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_8Bh_ADCAE)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_8Bh_ADCAE(memory,z80);
   ADCXY(memory,z80,old_z80,0x04,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_8Ch_ADCAH)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_8Ch_ADCAH(memory,z80);
   ADCXY(memory,z80,old_z80,0x06,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_8Dh_ADCAL)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_8Dh_ADCAL(memory,z80);
   ADCXY(memory,z80,old_z80,0x07,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_8Eh_ADCAHL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_8Fh_ADCAA)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_8Fh_ADCAA(memory,z80);
   ADCXY(memory,z80,old_z80,0x00,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_90h_SUBB)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_90h_SUBB(memory,z80);
   SUBXY(memory,z80,old_z80,0x01,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_91h_SUBC)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_91h_SUBC(memory,z80);
   SUBXY(memory,z80,old_z80,0x02,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_92h_SUBD)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_92h_SUBD(memory,z80);
   SUBXY(memory,z80,old_z80,0x03,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_93h_SUBE)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_93h_SUBE(memory,z80);
   SUBXY(memory,z80,old_z80,0x04,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_94h_SUBH)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_94h_SUBH(memory,z80);
   SUBXY(memory,z80,old_z80,0x06,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_95h_SUBL)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_95h_SUBL(memory,z80);
   SUBXY(memory,z80,old_z80,0x07,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_96h_SUBHL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_97h_SUBA)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_97h_SUBA(memory,z80);
   SUBXY(memory,z80,old_z80,0x00,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_98h_SBCAB)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_98h_SBCAB(memory,z80);
   SBCXY(memory,z80,old_z80,0x01,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_99h_SBCAC)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_99h_SBCAC(memory,z80);
   SBCXY(memory,z80,old_z80,0x02,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_9Ah_SBCAD)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_9Ah_SBCAD(memory,z80);
   SBCXY(memory,z80,old_z80,0x03,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_9Bh_SBCAE)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_9Bh_SBCAE(memory,z80);
   SBCXY(memory,z80,old_z80,0x04,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_9Ch_SBCAH)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_9Ch_SBCAH(memory,z80);
   SBCXY(memory,z80,old_z80,0x06,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_9Dh_SBCAL)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_9Dh_SBCAL(memory,z80);
   SBCXY(memory,z80,old_z80,0x07,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_9Eh_SBCAHL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_9Fh_SBCAA)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_9Fh_SBCAA(memory,z80);
   SBCXY(memory,z80,old_z80,0x00,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_A0h_ANDB)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_A0h_ANDB(memory,z80);
   ANDXY(memory,z80,old_z80,0x01,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_A1h_ANDC)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_A1h_ANDC(memory,z80);
   ANDXY(memory,z80,old_z80,0x02,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_A2h_ANDD)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_A2h_ANDD(memory,z80);
   ANDXY(memory,z80,old_z80,0x03,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_A3h_ANDE)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_A3h_ANDE(memory,z80);
   ANDXY(memory,z80,old_z80,0x04,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_A4h_ANDH)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_A4h_ANDH(memory,z80);
   ANDXY(memory,z80,old_z80,0x06,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_A5h_ANDL)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_A5h_ANDL(memory,z80);
   ANDXY(memory,z80,old_z80,0x07,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_A6h_ANDHL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_A7h_ANDA)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = OP_A7h_ANDA(memory,z80);
   ANDXY(memory,z80,old_z80,0x00,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_A8h_XORB)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_A9h_XORC)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_AAh_XORD)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_ABh_XORE)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_ACh_XORH)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_ADh_XORL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_AEh_XORHL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_AFh_XORA)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);
   InitMemory(&memory);

   int result = 0;
   uint8_t tmp_z80_PC = z80.regPC;

   result = OP_AFh_XORA(&memory,&z80);

   //fail_unless(z80.regPC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");

   fail_unless(result == 0,"Result was not 0");

   fail_unless(z80.regA == 0,"A register should be 0");
   fail_unless(z80.regF == 0x80,"Zero flag should be set and all others reset");
}
END_TEST

START_TEST (test_check_OP_B0h_ORB)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_B1h_ORC)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_B2h_ORD)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_B3h_ORE)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_B4h_ORH)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_B5h_ORL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_B6h_ORHL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_B7h_ORA)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_B8h_CPB)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_B9h_CPC)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_BAh_CPD)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_BBh_CPE)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_BCh_CPH)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_BDh_CPL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_BEh_CPHL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_BFh_CPA)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_C0h_RETNZ)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_C1h_POPBC)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_C2h_JPNZa16)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_C3h_JPa16)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_C4h_CALLNZa16)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_C5h_PUSHBC)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_C6h_ADDAd8)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_C7h_RST00H)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_C8h_RETZ)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_C9h_RET)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_CAh_JPZa16)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_CBh_PREFIXCB)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_CCh_CALLZa16)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_CDh_CALLa16)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   int result = 0;

   InitZ80(&z80,&registers,&op,&cb_op);

   uint16_t tmp_z80_SP = z80.regSP;

   result = OP_CDh_CALLa16_wrapper(&memory,&z80);

   fail_unless((z80.regSP + 2) == tmp_z80_SP);
   fail_unless(rw(&z80,&memory,z80.regSP) == (z80.regPC + 0x2));
   fail_unless(z80.regPC == rw(&z80,&memory,z80.regPC));
}
END_TEST

START_TEST (test_check_OP_CEh_ADCAd8)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_CFh_RST08H)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_D0h_RETNC)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_D1h_POPDE)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_D2h_JPNCa16)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_D3h_INVALID)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_D4h_CALLNCa16)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_D5h_PUSHDE)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_D6h_SUBd8)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_D7h_RST10H)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_D8h_RETC)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_D9h_RETI)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_DAh_JPCa16)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_DBh_INVALID)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_DCh_CALLCa16)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_DDh_INVALID)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_DEh_SBCAd8)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_DFh_RST18H)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_E0h_LDHa8A)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);
   InitMemory(&memory);

   int result = 0, i;
   uint8_t tmp_z80_PC = z80.regPC;

   for(i=0;i<0xFF;i++)
   {
      z80.regA = i;

      tmp_z80_PC = (z80.regPC & 0xFF);

      result = OP_E0h_LDHa8A(&memory,&z80);

      //fail_unless(z80.regPC == tmp_z80_PC + 0x1,"Program Counter should have been incremented by opcode function");

      fail_unless(result == 0,"Result was not 0");
//printf("SEG PC == %x\nSEG rb == %x\nSEG addr == %x\n",z80.regPC & 0xFF,0xff00 + z80.regPC);
//printf("fuck\n");
printf("regA == %x\nrb + offset == %x\n", z80.regA, rb(&z80,&memory,(0xff00 + (rb(&z80,&memory,(tmp_z80_PC & 0xFF)) & 0xFF))));
fflush( stdout );
      fail_unless(z80.regA == rb(&z80,&memory,(0xff00 + (rb(&z80,&memory,(tmp_z80_PC & 0xFF)) & 0xFF))));
   }
}
END_TEST

START_TEST (test_check_OP_E1h_POPHL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_E2h_LDHCA)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);
   InitMemory(&memory);

   int result = 0;
   uint8_t tmp_z80_PC = z80.regPC;

   result = OP_E2h_LDHCA(&memory,&z80);

   //fail_unless(z80.regPC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");

   fail_unless(result == 0,"Result was not 0");

   fail_unless(z80.regA == rb(&z80,&memory,(0xff00 + z80.regC)));
}
END_TEST

START_TEST (test_check_OP_E3h_INVALID)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_E4h_INVALID)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_E5h_PUSHHL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_E6h_ANDd8)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_E7h_RST20H)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_E8h_ADDSPr8)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_E9h_JPHL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_EAh_LDa16A)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_EBh_INVALID)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_ECh_INVALID)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_EDh_INVALID)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_EEh_XORd8)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_EFh_RST28H)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_F0h_LDHAa8)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_F1h_POPAF)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_F2h_LDAC)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_F3h_DI)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_F4h_INVALID)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_F5h_PUSHAF)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_F6h_ORd8)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_F7h_RST30H)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_F8h_LDHLSPr8)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_F9h_LDSPHL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_FAh_LDAa16)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_FBh_EI)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_FCh_INVALID)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_FDh_INVALID)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_FEh_CPd8)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_OP_FFh_RST38H)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_00h_RLCB)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RLC(memory,z80,0x1);
   CB_RLCX(memory,z80,old_z80,0x1,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_01h_RLCC)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RLC(memory,z80,0x2);
   CB_RLCX(memory,z80,old_z80,0x2,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_02h_RLCD)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RLC(memory,z80,0x3);
   CB_RLCX(memory,z80,old_z80,0x3,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_03h_RLCE)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RLC(memory,z80,0x4);
   CB_RLCX(memory,z80,old_z80,0x4,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_04h_RLCH)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RLC(memory,z80,0x6);
   CB_RLCX(memory,z80,old_z80,0x6,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_05h_RLCL)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RLC(memory,z80,0x7);
   CB_RLCX(memory,z80,old_z80,0x7,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_06h_RLCHL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_07h_RLCA)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RLC(memory,z80,0x0);
   CB_RLCX(memory,z80,old_z80,0x0,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_08h_RRCB)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RRC(memory,z80,0x1);
   CB_RRCX(memory,z80,old_z80,0x1,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_09h_RRCC)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RRC(memory,z80,0x2);
   CB_RRCX(memory,z80,old_z80,0x2,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_0Ah_RRCD)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RRC(memory,z80,0x3);
   CB_RRCX(memory,z80,old_z80,0x3,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_0Bh_RRCE)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RRC(memory,z80,0x4);
   CB_RRCX(memory,z80,old_z80,0x4,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_0Ch_RRCH)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RRC(memory,z80,0x6);
   CB_RRCX(memory,z80,old_z80,0x6,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_0Dh_RRCL)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RRC(memory,z80,0x7);
   CB_RRCX(memory,z80,old_z80,0x7,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_0Eh_RRCHL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_0Fh_RRCA)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RRC(memory,z80,0x0);
   CB_RRCX(memory,z80,old_z80,0x0,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_10h_RLB)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_11h_RLC)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_12h_RLD)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_13h_RLE)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_14h_RLH)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_15h_RLL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_16h_RLHL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_17h_RLA)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_18h_RRB)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_19h_RRC)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_1Ah_RRD)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_1Bh_RRE)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_1Ch_RRH)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_1Dh_RRL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_1Eh_RRHL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_1Fh_RRA)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_20h_SLAB)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_21h_SLAC)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_22h_SLAD)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_23h_SLAE)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_24h_SLAH)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_25h_SLAL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_26h_SLAHL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_27h_SLAA)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_28h_SRAB)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_29h_SRAC)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_2Ah_SRAD)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_2Bh_SRAE)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_2Ch_SRAH)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_2Dh_SRAL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_2Eh_SRAHL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_2Fh_SRAA)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_30h_SWAPB)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_31h_SWAPC)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_32h_SWAPD)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_33h_SWAPE)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_34h_SWAPH)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_35h_SWAPL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_36h_SWAPHL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_37h_SWAPA)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_38h_SRLB)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_39h_SRLC)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_3Ah_SRLD)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_3Bh_SRLE)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_3Ch_SRLH)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_3Dh_SRLL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_3Eh_SRLHL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_3Fh_SRLA)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_40h_BIT0B)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_BIT(memory,z80,0x01);
   CB_BITXY(memory,z80,old_z80,0x01,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_41h_BIT0C)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_BIT(memory,z80,0x02);
   CB_BITXY(memory,z80,old_z80,0x02,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_42h_BIT0D)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_BIT(memory,z80,0x03);
   CB_BITXY(memory,z80,old_z80,0x03,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_43h_BIT0E)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_BIT(memory,z80,0x04);
   CB_BITXY(memory,z80,old_z80,0x04,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_44h_BIT0H)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_BIT(memory,z80,0x06);
   CB_BITXY(memory,z80,old_z80,0x06,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_45h_BIT0L)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_BIT(memory,z80,0x06);
   CB_BITXY(memory,z80,old_z80,0x6,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_46h_BIT0HL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_47h_BIT0A)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_BIT(memory,z80,0x00);
   CB_BITXY(memory,z80,old_z80,0x00,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_48h_BIT1B)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_49h_BIT1C)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_4Ah_BIT1D)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_4Bh_BIT1E)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_4Ch_BIT1H)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_4Dh_BIT1L)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_4Eh_BIT1HL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_4Fh_BIT1A)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_50h_BIT2B)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_51h_BIT2C)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_52h_BIT2D)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_53h_BIT2E)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_54h_BIT2H)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_55h_BIT2L)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_56h_BIT2HL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_57h_BIT2A)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_58h_BIT3B)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_59h_BIT3C)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_5Ah_BIT3D)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_5Bh_BIT3E)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_5Ch_BIT3H)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_5Dh_BIT3L)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_5Eh_BIT3HL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_5Fh_BIT3A)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_60h_BIT4B)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_61h_BIT4C)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_62h_BIT4D)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_63h_BIT4E)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_64h_BIT4H)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_65h_BIT4L)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_66h_BIT4HL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_67h_BIT4A)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_68h_BIT5B)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_69h_BIT5C)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_6Ah_BIT5D)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_6Bh_BIT5E)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_6Ch_BIT5H)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_6Dh_BIT5L)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_6Eh_BIT5HL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_6Fh_BIT5A)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_70h_BIT6B)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_71h_BIT6C)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_72h_BIT6D)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_73h_BIT6E)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_74h_BIT6H)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_75h_BIT6L)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_76h_BIT6HL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_77h_BIT6A)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_78h_BIT7B)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_79h_BIT7C)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_7Ah_BIT7D)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_7Bh_BIT7E)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_7Ch_BIT7H)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_7Dh_BIT7L)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_7Eh_BIT7HL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_7Fh_BIT7A)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_80h_RES0B)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;
printf("B == %x\n",z80->regB);
   result = CB_RES(memory,z80,0x01);
   CB_RESXY(memory,z80,old_z80,0x01,tmp_z80_PC);
printf("B == %x\n",z80->regB);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_81h_RES0C)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x02);
   CB_RESXY(memory,z80,old_z80,0x02,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_82h_RES0D)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x03);
   CB_RESXY(memory,z80,old_z80,0x03,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_83h_RES0E)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x04);
   CB_RESXY(memory,z80,old_z80,0x04,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_84h_RES0H)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x06);
   CB_RESXY(memory,z80,old_z80,0x06,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_85h_RES0L)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x07);
   CB_RESXY(memory,z80,old_z80,0x07,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_86h_RES0HL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_87h_RES0A)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x00);
   CB_RESXY(memory,z80,old_z80,0x00,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_88h_RES1B)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x11);
   CB_RESXY(memory,z80,old_z80,0x11,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_89h_RES1C)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x12);
   CB_RESXY(memory,z80,old_z80,0x12,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_8Ah_RES1D)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x13);
   CB_RESXY(memory,z80,old_z80,0x13,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_8Bh_RES1E)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x14);
   CB_RESXY(memory,z80,old_z80,0x14,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_8Ch_RES1H)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x17);
   CB_RESXY(memory,z80,old_z80,0x17,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_8Dh_RES1L)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x17);
   CB_RESXY(memory,z80,old_z80,0x17,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_8Eh_RES1HL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_8Fh_RES1A)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x10);
   CB_RESXY(memory,z80,old_z80,0x10,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_90h_RES2B)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x21);
   CB_RESXY(memory,z80,old_z80,0x21,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_91h_RES2C)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x22);
   CB_RESXY(memory,z80,old_z80,0x22,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_92h_RES2D)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x23);
   CB_RESXY(memory,z80,old_z80,0x23,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_93h_RES2E)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x24);
   CB_RESXY(memory,z80,old_z80,0x24,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_94h_RES2H)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x26);
   CB_RESXY(memory,z80,old_z80,0x26,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_95h_RES2L)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x27);
   CB_RESXY(memory,z80,old_z80,0x27,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_96h_RES2HL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_97h_RES2A)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x20);
   CB_RESXY(memory,z80,old_z80,0x20,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_98h_RES3B)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x31);
   CB_RESXY(memory,z80,old_z80,0x31,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_99h_RES3C)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x32);
   CB_RESXY(memory,z80,old_z80,0x32,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_9Ah_RES3D)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x33);
   CB_RESXY(memory,z80,old_z80,0x33,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_9Bh_RES3E)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x34);
   CB_RESXY(memory,z80,old_z80,0x34,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_9Ch_RES3H)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x36);
   CB_RESXY(memory,z80,old_z80,0x36,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_9Dh_RES3L)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x37);
   CB_RESXY(memory,z80,old_z80,0x37,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_9Eh_RES3HL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_9Fh_RES3A)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x30);
   CB_RESXY(memory,z80,old_z80,0x30,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_A0h_RES4B)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x41);
   CB_RESXY(memory,z80,old_z80,0x41,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_A1h_RES4C)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x42);
   CB_RESXY(memory,z80,old_z80,0x42,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_A2h_RES4D)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x43);
   CB_RESXY(memory,z80,old_z80,0x43,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_A3h_RES4E)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x44);
   CB_RESXY(memory,z80,old_z80,0x44,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_A4h_RES4H)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x46);
   CB_RESXY(memory,z80,old_z80,0x46,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_A5h_RES4L)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x47);
   CB_RESXY(memory,z80,old_z80,0x47,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_A6h_RES4HL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_A7h_RES4A)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x40);
   CB_RESXY(memory,z80,old_z80,0x40,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_A8h_RES5B)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x51);
   CB_RESXY(memory,z80,old_z80,0x51,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_A9h_RES5C)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x52);
   CB_RESXY(memory,z80,old_z80,0x52,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_AAh_RES5D)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x53);
   CB_RESXY(memory,z80,old_z80,0x53,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_ABh_RES5E)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x54);
   CB_RESXY(memory,z80,old_z80,0x54,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_ACh_RES5H)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x56);
   CB_RESXY(memory,z80,old_z80,0x56,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_ADh_RES5L)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x57);
   CB_RESXY(memory,z80,old_z80,0x57,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_AEh_RES5HL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_AFh_RES5A)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x50);
   CB_RESXY(memory,z80,old_z80,0x50,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_B0h_RES6B)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x61);
   CB_RESXY(memory,z80,old_z80,0x61,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_B1h_RES6C)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x62);
   CB_RESXY(memory,z80,old_z80,0x62,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_B2h_RES6D)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x63);
   CB_RESXY(memory,z80,old_z80,0x63,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_B3h_RES6E)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x64);
   CB_RESXY(memory,z80,old_z80,0x64,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_B4h_RES6H)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x66);
   CB_RESXY(memory,z80,old_z80,0x66,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_B5h_RES6L)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x67);
   CB_RESXY(memory,z80,old_z80,0x67,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_B6h_RES6HL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_B7h_RES6A)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x60);
   CB_RESXY(memory,z80,old_z80,0x60,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_B8h_RES7B)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x71);
   CB_RESXY(memory,z80,old_z80,0x71,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_B9h_RES7C)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x72);
   CB_RESXY(memory,z80,old_z80,0x72,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_BAh_RES7D)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x73);
   CB_RESXY(memory,z80,old_z80,0x73,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_BBh_RES7E)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x74);
   CB_RESXY(memory,z80,old_z80,0x74,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_BCh_RES7H)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x76);
   CB_RESXY(memory,z80,old_z80,0x76,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_BDh_RES7L)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x77);
   CB_RESXY(memory,z80,old_z80,0x77,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_BEh_RES7HL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_BFh_RES7A)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_RES(memory,z80,0x70);
   CB_RESXY(memory,z80,old_z80,0x70,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_C0h_SET0B)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;
printf("CB_SET (pre) B == %x\n",z80->regB);
   result = CB_SET(memory,z80,0x01);
   CB_SETXY(memory,z80,old_z80,0x01,tmp_z80_PC);
printf("CB_SET (post) B == %x\n",z80->regB);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_C1h_SET0C)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

printf("CB_SET (pre) C == %x\n",z80->regC);
   result = CB_SET(memory,z80,0x02);
   CB_SETXY(memory,z80,old_z80,0x02,tmp_z80_PC);
printf("CB_SET (post) C == %x\n",z80->regC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_C2h_SET0D)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x03);
   CB_SETXY(memory,z80,old_z80,0x03,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_C3h_SET0E)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x04);
   CB_SETXY(memory,z80,old_z80,0x04,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_C4h_SET0H)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x06);
   CB_SETXY(memory,z80,old_z80,0x06,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_C5h_SET0L)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x07);
   CB_SETXY(memory,z80,old_z80,0x07,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_C6h_SET0HL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_C7h_SET0A)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x00);
   CB_SETXY(memory,z80,old_z80,0x00,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_C8h_SET1B)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x11);
   CB_SETXY(memory,z80,old_z80,0x11,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_C9h_SET1C)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x12);
   CB_SETXY(memory,z80,old_z80,0x12,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_CAh_SET1D)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x13);
   CB_SETXY(memory,z80,old_z80,0x13,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_CBh_SET1E)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x14);
   CB_SETXY(memory,z80,old_z80,0x14,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_CCh_SET1H)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x16);
   CB_SETXY(memory,z80,old_z80,0x16,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_CDh_SET1L)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x17);
   CB_SETXY(memory,z80,old_z80,0x17,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_CEh_SET1HL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_CFh_SET1A)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x10);
   CB_SETXY(memory,z80,old_z80,0x10,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_D0h_SET2B)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x21);
   CB_SETXY(memory,z80,old_z80,0x21,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_D1h_SET2C)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x22);
   CB_SETXY(memory,z80,old_z80,0x22,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_D2h_SET2D)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x23);
   CB_SETXY(memory,z80,old_z80,0x23,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_D3h_SET2E)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x24);
   CB_SETXY(memory,z80,old_z80,0x24,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_D4h_SET2H)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x26);
   CB_SETXY(memory,z80,old_z80,0x26,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_D5h_SET2L)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x27);
   CB_SETXY(memory,z80,old_z80,0x27,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_D6h_SET2HL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_D7h_SET2A)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x20);
   CB_SETXY(memory,z80,old_z80,0x20,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_D8h_SET3B)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x31);
   CB_SETXY(memory,z80,old_z80,0x31,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_D9h_SET3C)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x32);
   CB_SETXY(memory,z80,old_z80,0x32,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_DAh_SET3D)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x33);
   CB_SETXY(memory,z80,old_z80,0x33,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_DBh_SET3E)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x34);
   CB_SETXY(memory,z80,old_z80,0x34,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_DCh_SET3H)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x36);
   CB_SETXY(memory,z80,old_z80,0x36,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_DDh_SET3L)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x37);
   CB_SETXY(memory,z80,old_z80,0x37,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_DEh_SET3HL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_DFh_SET3A)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x30);
   CB_SETXY(memory,z80,old_z80,0x30,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_E0h_SET4B)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x41);
   CB_SETXY(memory,z80,old_z80,0x41,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_E1h_SET4C)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x42);
   CB_SETXY(memory,z80,old_z80,0x42,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_E2h_SET4D)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x43);
   CB_SETXY(memory,z80,old_z80,0x43,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_E3h_SET4E)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x44);
   CB_SETXY(memory,z80,old_z80,0x44,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_E4h_SET4H)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x46);
   CB_SETXY(memory,z80,old_z80,0x46,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_E5h_SET4L)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x47);
   CB_SETXY(memory,z80,old_z80,0x47,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_E6h_SET4HL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_E7h_SET4A)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x40);
   CB_SETXY(memory,z80,old_z80,0x40,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_E8h_SET5B)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x51);
   CB_SETXY(memory,z80,old_z80,0x51,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_E9h_SET5C)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x52);
   CB_SETXY(memory,z80,old_z80,0x52,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_EAh_SET5D)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x53);
   CB_SETXY(memory,z80,old_z80,0x53,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_EBh_SET5E)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x54);
   CB_SETXY(memory,z80,old_z80,0x54,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_ECh_SET5H)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x56);
   CB_SETXY(memory,z80,old_z80,0x56,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_EDh_SET5L)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x57);
   CB_SETXY(memory,z80,old_z80,0x57,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_EEh_SET5HL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_EFh_SET5A)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x50);
   CB_SETXY(memory,z80,old_z80,0x50,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_F0h_SET6B)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x61);
   CB_SETXY(memory,z80,old_z80,0x61,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_F1h_SET6C)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x62);
   CB_SETXY(memory,z80,old_z80,0x62,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_F2h_SET6D)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x63);
   CB_SETXY(memory,z80,old_z80,0x63,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_F3h_SET6E)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x64);
   CB_SETXY(memory,z80,old_z80,0x64,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_F4h_SET6H)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x66);
   CB_SETXY(memory,z80,old_z80,0x66,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_F5h_SET6L)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x67);
   CB_SETXY(memory,z80,old_z80,0x67,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_F6h_SET6HL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_F7h_SET6A)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x60);
   CB_SETXY(memory,z80,old_z80,0x60,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_F8h_SET7B)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x71);
   CB_SETXY(memory,z80,old_z80,0x71,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_F9h_SET7C)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));
   
   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x72);
   CB_SETXY(memory,z80,old_z80,0x72,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_FAh_SET7D)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x73);
   CB_SETXY(memory,z80,old_z80,0x73,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_FBh_SET7E)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x74);
   CB_SETXY(memory,z80,old_z80,0x74,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_FCh_SET7H)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x76);
   CB_SETXY(memory,z80,old_z80,0x76,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_FDh_SET7L)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x77);
   CB_SETXY(memory,z80,old_z80,0x77,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_CB_OP_FEh_SET7HL)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

}
END_TEST

START_TEST (test_check_CB_OP_FFh_SET7A)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->regPC;

   result = CB_SET(memory,z80,0x70);
   CB_SETXY(memory,z80,old_z80,0x70,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

Suite * add_suite(void)
{
   Suite * s = suite_create("Add");

   // Core test case
   TCase *tc_core = tcase_create("Core");
   tcase_add_test(tc_core,test_check_OP_00h_NOP);
   tcase_add_test(tc_core,test_check_OP_INCX);

   tcase_add_test(tc_core,test_check_OP_LDXd8);
   tcase_add_test(tc_core,test_check_OP_LDXd16);
   tcase_add_test(tc_core,test_check_OP_LDHLX);

   /*
   tcase_add_test(tc_core,test_check_OP_06h_LDBD8);
   tcase_add_test(tc_core,test_check_OP_0Eh_LDCD8);
   tcase_add_test(tc_core,test_check_OP_16h_LDDD8);
   tcase_add_test(tc_core,test_check_OP_1Eh_LDED8);
   tcase_add_test(tc_core,test_check_OP_26h_LDHD8);
   tcase_add_test(tc_core,test_check_OP_2Eh_LDLD8);
   tcase_add_test(tc_core,test_check_OP_3Eh_LDAD8);
   */

   tcase_add_test(tc_core,test_check_OP_00h_NOP);
   tcase_add_test(tc_core,test_check_OP_01h_LDBCd16);
   tcase_add_test(tc_core,test_check_OP_02h_LDBCA);
   tcase_add_test(tc_core,test_check_OP_03h_INCBC);
   tcase_add_test(tc_core,test_check_OP_04h_INCB);
   tcase_add_test(tc_core,test_check_OP_05h_DECB);
   tcase_add_test(tc_core,test_check_OP_06h_LDBd8);
   tcase_add_test(tc_core,test_check_OP_07h_RLCA);
   tcase_add_test(tc_core,test_check_OP_08h_LDa16SP);
   tcase_add_test(tc_core,test_check_OP_09h_ADDHLBC);
   tcase_add_test(tc_core,test_check_OP_0Ah_LDABC);
   tcase_add_test(tc_core,test_check_OP_0Bh_DECBC);
   tcase_add_test(tc_core,test_check_OP_0Ch_INCC);
   tcase_add_test(tc_core,test_check_OP_0Dh_DECC);
   tcase_add_test(tc_core,test_check_OP_0Eh_LDCd8);
   tcase_add_test(tc_core,test_check_OP_0Fh_RRCA);

   tcase_add_test(tc_core,test_check_OP_10h_STOP0);
   tcase_add_test(tc_core,test_check_OP_11h_LDDEd16);
   tcase_add_test(tc_core,test_check_OP_12h_LDDEA);
   tcase_add_test(tc_core,test_check_OP_13h_INCDE);
   tcase_add_test(tc_core,test_check_OP_14h_INCD);
   tcase_add_test(tc_core,test_check_OP_15h_DECD);
   tcase_add_test(tc_core,test_check_OP_16h_LDd8);
   tcase_add_test(tc_core,test_check_OP_17h_RLA);
   tcase_add_test(tc_core,test_check_OP_18h_JRr8);
   tcase_add_test(tc_core,test_check_OP_19h_ADDHLDE);
   tcase_add_test(tc_core,test_check_OP_1Ah_LDADE);
   tcase_add_test(tc_core,test_check_OP_1Bh_DECDE);
   tcase_add_test(tc_core,test_check_OP_1Ch_INCE);
   tcase_add_test(tc_core,test_check_OP_1Dh_DECE);
   tcase_add_test(tc_core,test_check_OP_1Eh_LDEd8);
   tcase_add_test(tc_core,test_check_OP_1Fh_RRA);

   tcase_add_test(tc_core,test_check_OP_20h_JRNZr8);
   tcase_add_test(tc_core,test_check_OP_21h_LDHLd16);
   tcase_add_test(tc_core,test_check_OP_22h_LDIHLA);
   tcase_add_test(tc_core,test_check_OP_23h_INCHL);
   tcase_add_test(tc_core,test_check_OP_24h_INCH);
   tcase_add_test(tc_core,test_check_OP_25h_DECH);
   tcase_add_test(tc_core,test_check_OP_26h_LDHd8);
   tcase_add_test(tc_core,test_check_OP_27h_DAA);
   tcase_add_test(tc_core,test_check_OP_28h_JRZr8);
   tcase_add_test(tc_core,test_check_OP_29h_ADDHLHL);
   tcase_add_test(tc_core,test_check_OP_2Ah_LDIAHL);
   tcase_add_test(tc_core,test_check_OP_2Bh_DECHL);
   tcase_add_test(tc_core,test_check_OP_2Ch_INCL);
   tcase_add_test(tc_core,test_check_OP_2Dh_DECL);
   tcase_add_test(tc_core,test_check_OP_2Eh_LDLd8);
   tcase_add_test(tc_core,test_check_OP_2Fh_CPL);

   tcase_add_test(tc_core,test_check_OP_30h_JRNCr8);
   tcase_add_test(tc_core,test_check_OP_31h_LDSPd16);
   tcase_add_test(tc_core,test_check_OP_32h_LDDHLA);
   tcase_add_test(tc_core,test_check_OP_33h_INCSP);
   tcase_add_test(tc_core,test_check_OP_34h_INCHL);
   tcase_add_test(tc_core,test_check_OP_35h_DECHL);
   tcase_add_test(tc_core,test_check_OP_36h_LDHLd8);
   tcase_add_test(tc_core,test_check_OP_37h_SCF);
   tcase_add_test(tc_core,test_check_OP_38h_JRCr8);
   tcase_add_test(tc_core,test_check_OP_39h_ADDHLSP);
   tcase_add_test(tc_core,test_check_OP_3Ah_LDDAHL);
   tcase_add_test(tc_core,test_check_OP_3Bh_DECSP);
   tcase_add_test(tc_core,test_check_OP_3Ch_INCA);
   tcase_add_test(tc_core,test_check_OP_3Dh_DECA);
   tcase_add_test(tc_core,test_check_OP_3Eh_LDAd8);
   tcase_add_test(tc_core,test_check_OP_3Fh_CCF);

   tcase_add_test(tc_core,test_check_OP_40h_LDBB);
   tcase_add_test(tc_core,test_check_OP_41h_LDBC);
   tcase_add_test(tc_core,test_check_OP_42h_LDBD);
   tcase_add_test(tc_core,test_check_OP_43h_LDBE);
   tcase_add_test(tc_core,test_check_OP_44h_LDBH);
   tcase_add_test(tc_core,test_check_OP_45h_LDBL);
   tcase_add_test(tc_core,test_check_OP_46h_LDBHL);
   tcase_add_test(tc_core,test_check_OP_47h_LDBA);
   tcase_add_test(tc_core,test_check_OP_48h_LDCB);
   tcase_add_test(tc_core,test_check_OP_49h_LDCC);
   tcase_add_test(tc_core,test_check_OP_4Ah_LDCD);
   tcase_add_test(tc_core,test_check_OP_4Bh_LDCE);
   tcase_add_test(tc_core,test_check_OP_4Ch_LDCH);
   tcase_add_test(tc_core,test_check_OP_4Dh_LDCL);
   tcase_add_test(tc_core,test_check_OP_4Eh_LDCHL);
   tcase_add_test(tc_core,test_check_OP_4Fh_LDCA);

   tcase_add_test(tc_core,test_check_OP_50h_LDDB);
   tcase_add_test(tc_core,test_check_OP_51h_LDDC);
   tcase_add_test(tc_core,test_check_OP_52h_LDDD);
   tcase_add_test(tc_core,test_check_OP_53h_LDDE);
   tcase_add_test(tc_core,test_check_OP_54h_LDDH);
   tcase_add_test(tc_core,test_check_OP_55h_LDDL);
   tcase_add_test(tc_core,test_check_OP_56h_LDDHL);
   tcase_add_test(tc_core,test_check_OP_57h_LDDA);
   tcase_add_test(tc_core,test_check_OP_58h_LDEB);
   tcase_add_test(tc_core,test_check_OP_59h_LDEC);
   tcase_add_test(tc_core,test_check_OP_5Ah_LDED);
   tcase_add_test(tc_core,test_check_OP_5Bh_LDEE);
   tcase_add_test(tc_core,test_check_OP_5Ch_LDEH);
   tcase_add_test(tc_core,test_check_OP_5Dh_LDEL);
   tcase_add_test(tc_core,test_check_OP_5Eh_LDEHL);
   tcase_add_test(tc_core,test_check_OP_5Fh_LDEA);

   tcase_add_test(tc_core,test_check_OP_60h_LDHB);
   tcase_add_test(tc_core,test_check_OP_61h_LDHC);
   tcase_add_test(tc_core,test_check_OP_62h_LDHD);
   tcase_add_test(tc_core,test_check_OP_63h_LDHE);
   tcase_add_test(tc_core,test_check_OP_64h_LDHH);
   tcase_add_test(tc_core,test_check_OP_65h_LDHL);
   tcase_add_test(tc_core,test_check_OP_66h_LDHHL);
   tcase_add_test(tc_core,test_check_OP_67h_LDHA);
   tcase_add_test(tc_core,test_check_OP_68h_LDLB);
   tcase_add_test(tc_core,test_check_OP_69h_LDLC);
   tcase_add_test(tc_core,test_check_OP_6Ah_LDLD);
   tcase_add_test(tc_core,test_check_OP_6Bh_LDLE);
   tcase_add_test(tc_core,test_check_OP_6Ch_LDLH);
   tcase_add_test(tc_core,test_check_OP_6Dh_LDLL);
   tcase_add_test(tc_core,test_check_OP_6Eh_LDLHL);
   tcase_add_test(tc_core,test_check_OP_6Fh_LDLA);

   tcase_add_test(tc_core,test_check_OP_70h_LDHLB);
   tcase_add_test(tc_core,test_check_OP_71h_LDHLC);
   tcase_add_test(tc_core,test_check_OP_72h_LDHLD);
   tcase_add_test(tc_core,test_check_OP_73h_LDHLE);
   tcase_add_test(tc_core,test_check_OP_74h_LDHLH);
   tcase_add_test(tc_core,test_check_OP_75h_LDHLL);
   tcase_add_test(tc_core,test_check_OP_76h_HALT);
   tcase_add_test(tc_core,test_check_OP_77h_LDHLA);
   tcase_add_test(tc_core,test_check_OP_78h_LDAB);
   tcase_add_test(tc_core,test_check_OP_78h_LDAB);
   tcase_add_test(tc_core,test_check_OP_79h_LDAC);
   tcase_add_test(tc_core,test_check_OP_7Ah_LDAD);
   tcase_add_test(tc_core,test_check_OP_7Bh_LDAE);
   tcase_add_test(tc_core,test_check_OP_7Ch_LDAH);
   tcase_add_test(tc_core,test_check_OP_7Dh_LDAL);
   tcase_add_test(tc_core,test_check_OP_7Eh_LDAHL);
   tcase_add_test(tc_core,test_check_OP_7Fh_LDAA);

   tcase_add_test(tc_core,test_check_OP_80h_ADDAB);
   tcase_add_test(tc_core,test_check_OP_81h_ADDAC);
   tcase_add_test(tc_core,test_check_OP_82h_ADDAD);
   tcase_add_test(tc_core,test_check_OP_83h_ADDAE);
   tcase_add_test(tc_core,test_check_OP_84h_ADDAH);
   tcase_add_test(tc_core,test_check_OP_85h_ADDAL);
   tcase_add_test(tc_core,test_check_OP_86h_ADDAHL);
   tcase_add_test(tc_core,test_check_OP_87h_ADDAA);
   tcase_add_test(tc_core,test_check_OP_88h_ADCAB);
   tcase_add_test(tc_core,test_check_OP_89h_ADCAC);
   tcase_add_test(tc_core,test_check_OP_8Ah_ADCAD);
   tcase_add_test(tc_core,test_check_OP_8Bh_ADCAE);
   tcase_add_test(tc_core,test_check_OP_8Ch_ADCAH);
   tcase_add_test(tc_core,test_check_OP_8Dh_ADCAL);
   tcase_add_test(tc_core,test_check_OP_8Eh_ADCAHL);
   tcase_add_test(tc_core,test_check_OP_8Fh_ADCAA);

   tcase_add_test(tc_core,test_check_OP_90h_SUBB);
   tcase_add_test(tc_core,test_check_OP_91h_SUBC);
   tcase_add_test(tc_core,test_check_OP_92h_SUBD);
   tcase_add_test(tc_core,test_check_OP_93h_SUBE);
   tcase_add_test(tc_core,test_check_OP_94h_SUBH);
   tcase_add_test(tc_core,test_check_OP_95h_SUBL);
   tcase_add_test(tc_core,test_check_OP_96h_SUBHL);
   tcase_add_test(tc_core,test_check_OP_97h_SUBA);
   tcase_add_test(tc_core,test_check_OP_98h_SBCAB);
   tcase_add_test(tc_core,test_check_OP_99h_SBCAC);
   tcase_add_test(tc_core,test_check_OP_9Ah_SBCAD);
   tcase_add_test(tc_core,test_check_OP_9Bh_SBCAE);
   tcase_add_test(tc_core,test_check_OP_9Ch_SBCAH);
   tcase_add_test(tc_core,test_check_OP_9Dh_SBCAL);
   tcase_add_test(tc_core,test_check_OP_9Eh_SBCAHL);
   tcase_add_test(tc_core,test_check_OP_9Fh_SBCAA);

   tcase_add_test(tc_core,test_check_OP_A0h_ANDB);
   tcase_add_test(tc_core,test_check_OP_A1h_ANDC);
   tcase_add_test(tc_core,test_check_OP_A2h_ANDD);
   tcase_add_test(tc_core,test_check_OP_A3h_ANDE);
   tcase_add_test(tc_core,test_check_OP_A4h_ANDH);
   tcase_add_test(tc_core,test_check_OP_A5h_ANDL);
   tcase_add_test(tc_core,test_check_OP_A6h_ANDHL);
   tcase_add_test(tc_core,test_check_OP_A7h_ANDA);
   tcase_add_test(tc_core,test_check_OP_A8h_XORB);
   tcase_add_test(tc_core,test_check_OP_A9h_XORC);
   tcase_add_test(tc_core,test_check_OP_AAh_XORD);
   tcase_add_test(tc_core,test_check_OP_ABh_XORE);
   tcase_add_test(tc_core,test_check_OP_ACh_XORH);
   tcase_add_test(tc_core,test_check_OP_ADh_XORL);
   tcase_add_test(tc_core,test_check_OP_AEh_XORHL);
   tcase_add_test(tc_core,test_check_OP_AFh_XORA);

   tcase_add_test(tc_core,test_check_OP_B0h_ORB);
   tcase_add_test(tc_core,test_check_OP_B1h_ORC);
   tcase_add_test(tc_core,test_check_OP_B2h_ORD);
   tcase_add_test(tc_core,test_check_OP_B3h_ORE);
   tcase_add_test(tc_core,test_check_OP_B4h_ORH);
   tcase_add_test(tc_core,test_check_OP_B5h_ORL);
   tcase_add_test(tc_core,test_check_OP_B6h_ORHL);
   tcase_add_test(tc_core,test_check_OP_B7h_ORA);
   tcase_add_test(tc_core,test_check_OP_B8h_CPB);
   tcase_add_test(tc_core,test_check_OP_B9h_CPC);
   tcase_add_test(tc_core,test_check_OP_BAh_CPD);
   tcase_add_test(tc_core,test_check_OP_BBh_CPE);
   tcase_add_test(tc_core,test_check_OP_BCh_CPH);
   tcase_add_test(tc_core,test_check_OP_BDh_CPL);
   tcase_add_test(tc_core,test_check_OP_BEh_CPHL);
   tcase_add_test(tc_core,test_check_OP_BFh_CPA);

   tcase_add_test(tc_core,test_check_OP_C0h_RETNZ);
   tcase_add_test(tc_core,test_check_OP_C1h_POPBC);
   tcase_add_test(tc_core,test_check_OP_C2h_JPNZa16);
   tcase_add_test(tc_core,test_check_OP_C3h_JPa16);
   tcase_add_test(tc_core,test_check_OP_C4h_CALLNZa16);
   tcase_add_test(tc_core,test_check_OP_C5h_PUSHBC);
   tcase_add_test(tc_core,test_check_OP_C6h_ADDAd8);
   tcase_add_test(tc_core,test_check_OP_C7h_RST00H);
   tcase_add_test(tc_core,test_check_OP_C8h_RETZ);
   tcase_add_test(tc_core,test_check_OP_C9h_RET);
   tcase_add_test(tc_core,test_check_OP_CAh_JPZa16);
   tcase_add_test(tc_core,test_check_OP_CBh_PREFIXCB);
   tcase_add_test(tc_core,test_check_OP_CCh_CALLZa16);
   tcase_add_test(tc_core,test_check_OP_CDh_CALLa16);
   tcase_add_test(tc_core,test_check_OP_CEh_ADCAd8);
   tcase_add_test(tc_core,test_check_OP_CFh_RST08H);

   tcase_add_test(tc_core,test_check_OP_D0h_RETNC);
   tcase_add_test(tc_core,test_check_OP_D1h_POPDE);
   tcase_add_test(tc_core,test_check_OP_D2h_JPNCa16);
   tcase_add_test(tc_core,test_check_OP_D3h_INVALID);
   tcase_add_test(tc_core,test_check_OP_D4h_CALLNCa16);
   tcase_add_test(tc_core,test_check_OP_D5h_PUSHDE);
   tcase_add_test(tc_core,test_check_OP_D6h_SUBd8);
   tcase_add_test(tc_core,test_check_OP_D7h_RST10H);
   tcase_add_test(tc_core,test_check_OP_D8h_RETC);
   tcase_add_test(tc_core,test_check_OP_D9h_RETI);
   tcase_add_test(tc_core,test_check_OP_DAh_JPCa16);
   tcase_add_test(tc_core,test_check_OP_DBh_INVALID);
   tcase_add_test(tc_core,test_check_OP_DCh_CALLCa16);
   tcase_add_test(tc_core,test_check_OP_DDh_INVALID);
   tcase_add_test(tc_core,test_check_OP_DEh_SBCAd8);
   tcase_add_test(tc_core,test_check_OP_DFh_RST18H);

   tcase_add_test(tc_core,test_check_OP_E0h_LDHa8A);
   tcase_add_test(tc_core,test_check_OP_E1h_POPHL);
   tcase_add_test(tc_core,test_check_OP_E2h_LDHCA);
   tcase_add_test(tc_core,test_check_OP_E3h_INVALID);
   tcase_add_test(tc_core,test_check_OP_E4h_INVALID);
   tcase_add_test(tc_core,test_check_OP_E5h_PUSHHL);
   tcase_add_test(tc_core,test_check_OP_E6h_ANDd8);
   tcase_add_test(tc_core,test_check_OP_E7h_RST20H);
   tcase_add_test(tc_core,test_check_OP_E8h_ADDSPr8);
   tcase_add_test(tc_core,test_check_OP_E9h_JPHL);
   tcase_add_test(tc_core,test_check_OP_EAh_LDa16A);
   tcase_add_test(tc_core,test_check_OP_EBh_INVALID);
   tcase_add_test(tc_core,test_check_OP_ECh_INVALID);
   tcase_add_test(tc_core,test_check_OP_EDh_INVALID);
   tcase_add_test(tc_core,test_check_OP_EEh_XORd8);
   tcase_add_test(tc_core,test_check_OP_EFh_RST28H);

   tcase_add_test(tc_core,test_check_OP_F0h_LDHAa8);
   tcase_add_test(tc_core,test_check_OP_F1h_POPAF);
   tcase_add_test(tc_core,test_check_OP_F2h_LDAC);
   tcase_add_test(tc_core,test_check_OP_F3h_DI);
   tcase_add_test(tc_core,test_check_OP_F4h_INVALID);
   tcase_add_test(tc_core,test_check_OP_F5h_PUSHAF);
   tcase_add_test(tc_core,test_check_OP_F6h_ORd8);
   tcase_add_test(tc_core,test_check_OP_F7h_RST30H);
   tcase_add_test(tc_core,test_check_OP_F8h_LDHLSPr8);
   tcase_add_test(tc_core,test_check_OP_F9h_LDSPHL);
   tcase_add_test(tc_core,test_check_OP_FAh_LDAa16);
   tcase_add_test(tc_core,test_check_OP_FBh_EI);
   tcase_add_test(tc_core,test_check_OP_FCh_INVALID);
   tcase_add_test(tc_core,test_check_OP_FDh_INVALID);
   tcase_add_test(tc_core,test_check_OP_FEh_CPd8);
   tcase_add_test(tc_core,test_check_OP_FFh_RST38H);

   // CB prefix opcodes
   tcase_add_test(tc_core,test_check_CB_OP_00h_RLCB);
   tcase_add_test(tc_core,test_check_CB_OP_01h_RLCC);
   tcase_add_test(tc_core,test_check_CB_OP_02h_RLCD);
   tcase_add_test(tc_core,test_check_CB_OP_03h_RLCE);
   tcase_add_test(tc_core,test_check_CB_OP_04h_RLCH);
   tcase_add_test(tc_core,test_check_CB_OP_05h_RLCL);
   tcase_add_test(tc_core,test_check_CB_OP_06h_RLCHL);
   tcase_add_test(tc_core,test_check_CB_OP_07h_RLCA);
   tcase_add_test(tc_core,test_check_CB_OP_08h_RRCB);
   tcase_add_test(tc_core,test_check_CB_OP_09h_RRCC);
   tcase_add_test(tc_core,test_check_CB_OP_0Ah_RRCD);
   tcase_add_test(tc_core,test_check_CB_OP_0Bh_RRCE);
   tcase_add_test(tc_core,test_check_CB_OP_0Ch_RRCH);
   tcase_add_test(tc_core,test_check_CB_OP_0Dh_RRCL);
   tcase_add_test(tc_core,test_check_CB_OP_0Eh_RRCHL);
   tcase_add_test(tc_core,test_check_CB_OP_0Fh_RRCA);

   tcase_add_test(tc_core,test_check_CB_OP_10h_RLB);
   tcase_add_test(tc_core,test_check_CB_OP_11h_RLC);
   tcase_add_test(tc_core,test_check_CB_OP_12h_RLD);
   tcase_add_test(tc_core,test_check_CB_OP_13h_RLE);
   tcase_add_test(tc_core,test_check_CB_OP_14h_RLH);
   tcase_add_test(tc_core,test_check_CB_OP_15h_RLL);
   tcase_add_test(tc_core,test_check_CB_OP_16h_RLHL);
   tcase_add_test(tc_core,test_check_CB_OP_17h_RLA);
   tcase_add_test(tc_core,test_check_CB_OP_18h_RRB);
   tcase_add_test(tc_core,test_check_CB_OP_19h_RRC);
   tcase_add_test(tc_core,test_check_CB_OP_1Ah_RRD);
   tcase_add_test(tc_core,test_check_CB_OP_1Bh_RRE);
   tcase_add_test(tc_core,test_check_CB_OP_1Ch_RRH);
   tcase_add_test(tc_core,test_check_CB_OP_1Dh_RRL);
   tcase_add_test(tc_core,test_check_CB_OP_1Eh_RRHL);
   tcase_add_test(tc_core,test_check_CB_OP_1Fh_RRA);

   tcase_add_test(tc_core,test_check_CB_OP_20h_SLAB);
   tcase_add_test(tc_core,test_check_CB_OP_21h_SLAC);
   tcase_add_test(tc_core,test_check_CB_OP_22h_SLAD);
   tcase_add_test(tc_core,test_check_CB_OP_23h_SLAE);
   tcase_add_test(tc_core,test_check_CB_OP_24h_SLAH);
   tcase_add_test(tc_core,test_check_CB_OP_25h_SLAL);
   tcase_add_test(tc_core,test_check_CB_OP_26h_SLAHL);
   tcase_add_test(tc_core,test_check_CB_OP_27h_SLAA);
   tcase_add_test(tc_core,test_check_CB_OP_28h_SRAB);
   tcase_add_test(tc_core,test_check_CB_OP_29h_SRAC);
   tcase_add_test(tc_core,test_check_CB_OP_2Ah_SRAD);
   tcase_add_test(tc_core,test_check_CB_OP_2Bh_SRAE);
   tcase_add_test(tc_core,test_check_CB_OP_2Ch_SRAH);
   tcase_add_test(tc_core,test_check_CB_OP_2Dh_SRAL);
   tcase_add_test(tc_core,test_check_CB_OP_2Eh_SRAHL);
   tcase_add_test(tc_core,test_check_CB_OP_2Fh_SRAA);

   tcase_add_test(tc_core,test_check_CB_OP_30h_SWAPB);
   tcase_add_test(tc_core,test_check_CB_OP_31h_SWAPC);
   tcase_add_test(tc_core,test_check_CB_OP_32h_SWAPD);
   tcase_add_test(tc_core,test_check_CB_OP_33h_SWAPE);
   tcase_add_test(tc_core,test_check_CB_OP_34h_SWAPH);
   tcase_add_test(tc_core,test_check_CB_OP_35h_SWAPL);
   tcase_add_test(tc_core,test_check_CB_OP_36h_SWAPHL);
   tcase_add_test(tc_core,test_check_CB_OP_37h_SWAPA);
   tcase_add_test(tc_core,test_check_CB_OP_38h_SRLB);
   tcase_add_test(tc_core,test_check_CB_OP_39h_SRLC);
   tcase_add_test(tc_core,test_check_CB_OP_3Ah_SRLD);
   tcase_add_test(tc_core,test_check_CB_OP_3Bh_SRLE);
   tcase_add_test(tc_core,test_check_CB_OP_3Ch_SRLH);
   tcase_add_test(tc_core,test_check_CB_OP_3Dh_SRLL);
   tcase_add_test(tc_core,test_check_CB_OP_3Eh_SRLHL);
   tcase_add_test(tc_core,test_check_CB_OP_3Fh_SRLA);

   tcase_add_test(tc_core,test_check_CB_OP_40h_BIT0B);
   tcase_add_test(tc_core,test_check_CB_OP_41h_BIT0C);
   tcase_add_test(tc_core,test_check_CB_OP_42h_BIT0D);
   tcase_add_test(tc_core,test_check_CB_OP_43h_BIT0E);
   tcase_add_test(tc_core,test_check_CB_OP_44h_BIT0H);
   tcase_add_test(tc_core,test_check_CB_OP_45h_BIT0L);
   tcase_add_test(tc_core,test_check_CB_OP_46h_BIT0HL);
   tcase_add_test(tc_core,test_check_CB_OP_47h_BIT0A);
   tcase_add_test(tc_core,test_check_CB_OP_48h_BIT1B);
   tcase_add_test(tc_core,test_check_CB_OP_49h_BIT1C);
   tcase_add_test(tc_core,test_check_CB_OP_4Ah_BIT1D);
   tcase_add_test(tc_core,test_check_CB_OP_4Bh_BIT1E);
   tcase_add_test(tc_core,test_check_CB_OP_4Ch_BIT1H);
   tcase_add_test(tc_core,test_check_CB_OP_4Dh_BIT1L);
   tcase_add_test(tc_core,test_check_CB_OP_4Eh_BIT1HL);
   tcase_add_test(tc_core,test_check_CB_OP_4Fh_BIT1A);

   tcase_add_test(tc_core,test_check_CB_OP_50h_BIT2B);
   tcase_add_test(tc_core,test_check_CB_OP_51h_BIT2C);
   tcase_add_test(tc_core,test_check_CB_OP_52h_BIT2D);
   tcase_add_test(tc_core,test_check_CB_OP_53h_BIT2E);
   tcase_add_test(tc_core,test_check_CB_OP_54h_BIT2H);
   tcase_add_test(tc_core,test_check_CB_OP_55h_BIT2L);
   tcase_add_test(tc_core,test_check_CB_OP_56h_BIT2HL);
   tcase_add_test(tc_core,test_check_CB_OP_57h_BIT2A);
   tcase_add_test(tc_core,test_check_CB_OP_58h_BIT3B);
   tcase_add_test(tc_core,test_check_CB_OP_59h_BIT3C);
   tcase_add_test(tc_core,test_check_CB_OP_5Ah_BIT3D);
   tcase_add_test(tc_core,test_check_CB_OP_5Bh_BIT3E);
   tcase_add_test(tc_core,test_check_CB_OP_5Ch_BIT3H);
   tcase_add_test(tc_core,test_check_CB_OP_5Dh_BIT3L);
   tcase_add_test(tc_core,test_check_CB_OP_5Eh_BIT3HL);
   tcase_add_test(tc_core,test_check_CB_OP_5Fh_BIT3A);

   tcase_add_test(tc_core,test_check_CB_OP_60h_BIT4B);
   tcase_add_test(tc_core,test_check_CB_OP_61h_BIT4C);
   tcase_add_test(tc_core,test_check_CB_OP_62h_BIT4D);
   tcase_add_test(tc_core,test_check_CB_OP_63h_BIT4E);
   tcase_add_test(tc_core,test_check_CB_OP_64h_BIT4H);
   tcase_add_test(tc_core,test_check_CB_OP_65h_BIT4L);
   tcase_add_test(tc_core,test_check_CB_OP_66h_BIT4HL);
   tcase_add_test(tc_core,test_check_CB_OP_67h_BIT4A);
   tcase_add_test(tc_core,test_check_CB_OP_68h_BIT5B);
   tcase_add_test(tc_core,test_check_CB_OP_69h_BIT5C);
   tcase_add_test(tc_core,test_check_CB_OP_6Ah_BIT5D);
   tcase_add_test(tc_core,test_check_CB_OP_6Bh_BIT5E);
   tcase_add_test(tc_core,test_check_CB_OP_6Ch_BIT5H);
   tcase_add_test(tc_core,test_check_CB_OP_6Dh_BIT5L);
   tcase_add_test(tc_core,test_check_CB_OP_6Eh_BIT5HL);
   tcase_add_test(tc_core,test_check_CB_OP_6Fh_BIT5A);

   tcase_add_test(tc_core,test_check_CB_OP_70h_BIT6B);
   tcase_add_test(tc_core,test_check_CB_OP_71h_BIT6C);
   tcase_add_test(tc_core,test_check_CB_OP_72h_BIT6D);
   tcase_add_test(tc_core,test_check_CB_OP_73h_BIT6E);
   tcase_add_test(tc_core,test_check_CB_OP_74h_BIT6H);
   tcase_add_test(tc_core,test_check_CB_OP_75h_BIT6L);
   tcase_add_test(tc_core,test_check_CB_OP_76h_BIT6HL);
   tcase_add_test(tc_core,test_check_CB_OP_77h_BIT6A);
   tcase_add_test(tc_core,test_check_CB_OP_78h_BIT7B);
   tcase_add_test(tc_core,test_check_CB_OP_79h_BIT7C);
   tcase_add_test(tc_core,test_check_CB_OP_7Ah_BIT7D);
   tcase_add_test(tc_core,test_check_CB_OP_7Bh_BIT7E);
   tcase_add_test(tc_core,test_check_CB_OP_7Ch_BIT7H);
   tcase_add_test(tc_core,test_check_CB_OP_7Dh_BIT7L);
   tcase_add_test(tc_core,test_check_CB_OP_7Eh_BIT7HL);
   tcase_add_test(tc_core,test_check_CB_OP_7Fh_BIT7A);

   tcase_add_test(tc_core,test_check_CB_OP_80h_RES0B);
   tcase_add_test(tc_core,test_check_CB_OP_81h_RES0C);
   tcase_add_test(tc_core,test_check_CB_OP_82h_RES0D);
   tcase_add_test(tc_core,test_check_CB_OP_83h_RES0E);
   tcase_add_test(tc_core,test_check_CB_OP_84h_RES0H);
   tcase_add_test(tc_core,test_check_CB_OP_85h_RES0L);
   tcase_add_test(tc_core,test_check_CB_OP_86h_RES0HL);
   tcase_add_test(tc_core,test_check_CB_OP_87h_RES0A);
   tcase_add_test(tc_core,test_check_CB_OP_88h_RES1B);
   tcase_add_test(tc_core,test_check_CB_OP_89h_RES1C);
   tcase_add_test(tc_core,test_check_CB_OP_8Ah_RES1D);
   tcase_add_test(tc_core,test_check_CB_OP_8Bh_RES1E);
   tcase_add_test(tc_core,test_check_CB_OP_8Ch_RES1H);
   tcase_add_test(tc_core,test_check_CB_OP_8Dh_RES1L);
   tcase_add_test(tc_core,test_check_CB_OP_8Eh_RES1HL);
   tcase_add_test(tc_core,test_check_CB_OP_8Fh_RES1A);

   tcase_add_test(tc_core,test_check_CB_OP_90h_RES2B);
   tcase_add_test(tc_core,test_check_CB_OP_91h_RES2C);
   tcase_add_test(tc_core,test_check_CB_OP_92h_RES2D);
   tcase_add_test(tc_core,test_check_CB_OP_93h_RES2E);
   tcase_add_test(tc_core,test_check_CB_OP_94h_RES2H);
   tcase_add_test(tc_core,test_check_CB_OP_95h_RES2L);
   tcase_add_test(tc_core,test_check_CB_OP_96h_RES2HL);
   tcase_add_test(tc_core,test_check_CB_OP_97h_RES2A);
   tcase_add_test(tc_core,test_check_CB_OP_98h_RES3B);
   tcase_add_test(tc_core,test_check_CB_OP_99h_RES3C);
   tcase_add_test(tc_core,test_check_CB_OP_9Ah_RES3D);
   tcase_add_test(tc_core,test_check_CB_OP_9Bh_RES3E);
   tcase_add_test(tc_core,test_check_CB_OP_9Ch_RES3H);
   tcase_add_test(tc_core,test_check_CB_OP_9Dh_RES3L);
   tcase_add_test(tc_core,test_check_CB_OP_9Eh_RES3HL);
   tcase_add_test(tc_core,test_check_CB_OP_9Fh_RES3A);

   tcase_add_test(tc_core,test_check_CB_OP_A0h_RES4B);
   tcase_add_test(tc_core,test_check_CB_OP_A1h_RES4C);
   tcase_add_test(tc_core,test_check_CB_OP_A2h_RES4D);
   tcase_add_test(tc_core,test_check_CB_OP_A3h_RES4E);
   tcase_add_test(tc_core,test_check_CB_OP_A4h_RES4H);
   tcase_add_test(tc_core,test_check_CB_OP_A5h_RES4L);
   tcase_add_test(tc_core,test_check_CB_OP_A6h_RES4HL);
   tcase_add_test(tc_core,test_check_CB_OP_A7h_RES4A);
   tcase_add_test(tc_core,test_check_CB_OP_A8h_RES5B);
   tcase_add_test(tc_core,test_check_CB_OP_A9h_RES5C);
   tcase_add_test(tc_core,test_check_CB_OP_AAh_RES5D);
   tcase_add_test(tc_core,test_check_CB_OP_ABh_RES5E);
   tcase_add_test(tc_core,test_check_CB_OP_ACh_RES5H);
   tcase_add_test(tc_core,test_check_CB_OP_ADh_RES5L);
   tcase_add_test(tc_core,test_check_CB_OP_AEh_RES5HL);
   tcase_add_test(tc_core,test_check_CB_OP_AFh_RES5A);

   tcase_add_test(tc_core,test_check_CB_OP_B0h_RES6B);
   tcase_add_test(tc_core,test_check_CB_OP_B1h_RES6C);
   tcase_add_test(tc_core,test_check_CB_OP_B2h_RES6D);
   tcase_add_test(tc_core,test_check_CB_OP_B3h_RES6E);
   tcase_add_test(tc_core,test_check_CB_OP_B4h_RES6H);
   tcase_add_test(tc_core,test_check_CB_OP_B5h_RES6L);
   tcase_add_test(tc_core,test_check_CB_OP_B6h_RES6HL);
   tcase_add_test(tc_core,test_check_CB_OP_B7h_RES6A);
   tcase_add_test(tc_core,test_check_CB_OP_B8h_RES7B);
   tcase_add_test(tc_core,test_check_CB_OP_B9h_RES7C);
   tcase_add_test(tc_core,test_check_CB_OP_BAh_RES7D);
   tcase_add_test(tc_core,test_check_CB_OP_BBh_RES7E);
   tcase_add_test(tc_core,test_check_CB_OP_BCh_RES7H);
   tcase_add_test(tc_core,test_check_CB_OP_BDh_RES7L);
   tcase_add_test(tc_core,test_check_CB_OP_BEh_RES7HL);
   tcase_add_test(tc_core,test_check_CB_OP_BFh_RES7A);

   tcase_add_test(tc_core,test_check_CB_OP_C0h_SET0B);
   tcase_add_test(tc_core,test_check_CB_OP_C1h_SET0C);
   tcase_add_test(tc_core,test_check_CB_OP_C2h_SET0D);
   tcase_add_test(tc_core,test_check_CB_OP_C3h_SET0E);
   tcase_add_test(tc_core,test_check_CB_OP_C4h_SET0H);
   tcase_add_test(tc_core,test_check_CB_OP_C5h_SET0L);
   tcase_add_test(tc_core,test_check_CB_OP_C6h_SET0HL);
   tcase_add_test(tc_core,test_check_CB_OP_C7h_SET0A);
   tcase_add_test(tc_core,test_check_CB_OP_C8h_SET1B);
   tcase_add_test(tc_core,test_check_CB_OP_C9h_SET1C);
   tcase_add_test(tc_core,test_check_CB_OP_CAh_SET1D);
   tcase_add_test(tc_core,test_check_CB_OP_CBh_SET1E);
   tcase_add_test(tc_core,test_check_CB_OP_CCh_SET1H);
   tcase_add_test(tc_core,test_check_CB_OP_CDh_SET1L);
   tcase_add_test(tc_core,test_check_CB_OP_CEh_SET1HL);
   tcase_add_test(tc_core,test_check_CB_OP_CFh_SET1A);

   tcase_add_test(tc_core,test_check_CB_OP_D0h_SET2B);
   tcase_add_test(tc_core,test_check_CB_OP_D1h_SET2C);
   tcase_add_test(tc_core,test_check_CB_OP_D2h_SET2D);
   tcase_add_test(tc_core,test_check_CB_OP_D3h_SET2E);
   tcase_add_test(tc_core,test_check_CB_OP_D4h_SET2H);
   tcase_add_test(tc_core,test_check_CB_OP_D5h_SET2L);
   tcase_add_test(tc_core,test_check_CB_OP_D6h_SET2HL);
   tcase_add_test(tc_core,test_check_CB_OP_D7h_SET2A);
   tcase_add_test(tc_core,test_check_CB_OP_D8h_SET3B);
   tcase_add_test(tc_core,test_check_CB_OP_D9h_SET3C);
   tcase_add_test(tc_core,test_check_CB_OP_DAh_SET3D);
   tcase_add_test(tc_core,test_check_CB_OP_DBh_SET3E);
   tcase_add_test(tc_core,test_check_CB_OP_DCh_SET3H);
   tcase_add_test(tc_core,test_check_CB_OP_DDh_SET3L);
   tcase_add_test(tc_core,test_check_CB_OP_DEh_SET3HL);
   tcase_add_test(tc_core,test_check_CB_OP_DFh_SET3A);

   tcase_add_test(tc_core,test_check_CB_OP_E0h_SET4B);
   tcase_add_test(tc_core,test_check_CB_OP_E1h_SET4C);
   tcase_add_test(tc_core,test_check_CB_OP_E2h_SET4D);
   tcase_add_test(tc_core,test_check_CB_OP_E3h_SET4E);
   tcase_add_test(tc_core,test_check_CB_OP_E4h_SET4H);
   tcase_add_test(tc_core,test_check_CB_OP_E5h_SET4L);
   tcase_add_test(tc_core,test_check_CB_OP_E6h_SET4HL);
   tcase_add_test(tc_core,test_check_CB_OP_E7h_SET4A);
   tcase_add_test(tc_core,test_check_CB_OP_E8h_SET5B);
   tcase_add_test(tc_core,test_check_CB_OP_E9h_SET5C);
   tcase_add_test(tc_core,test_check_CB_OP_EAh_SET5D);
   tcase_add_test(tc_core,test_check_CB_OP_EBh_SET5E);
   tcase_add_test(tc_core,test_check_CB_OP_ECh_SET5H);
   tcase_add_test(tc_core,test_check_CB_OP_EDh_SET5L);
   tcase_add_test(tc_core,test_check_CB_OP_EEh_SET5HL);
   tcase_add_test(tc_core,test_check_CB_OP_EFh_SET5A);

   tcase_add_test(tc_core,test_check_CB_OP_F0h_SET6B);
   tcase_add_test(tc_core,test_check_CB_OP_F1h_SET6C);
   tcase_add_test(tc_core,test_check_CB_OP_F2h_SET6D);
   tcase_add_test(tc_core,test_check_CB_OP_F3h_SET6E);
   tcase_add_test(tc_core,test_check_CB_OP_F4h_SET6H);
   tcase_add_test(tc_core,test_check_CB_OP_F5h_SET6L);
   tcase_add_test(tc_core,test_check_CB_OP_F6h_SET6HL);
   tcase_add_test(tc_core,test_check_CB_OP_F7h_SET6A);
   tcase_add_test(tc_core,test_check_CB_OP_F8h_SET7B);
   tcase_add_test(tc_core,test_check_CB_OP_F9h_SET7C);
   tcase_add_test(tc_core,test_check_CB_OP_FAh_SET7D);
   tcase_add_test(tc_core,test_check_CB_OP_FBh_SET7E);
   tcase_add_test(tc_core,test_check_CB_OP_FCh_SET7H);
   tcase_add_test(tc_core,test_check_CB_OP_FDh_SET7L);
   tcase_add_test(tc_core,test_check_CB_OP_FEh_SET7HL);
   tcase_add_test(tc_core,test_check_CB_OP_FFh_SET7A);

   suite_add_tcase(s,tc_core);

   return s;
}

int main(void)
{
   // Random seed
   int random_seed = time(NULL);
   srand(random_seed);

   int number_failed;
   Suite *s = add_suite();
   SRunner *sr = srunner_create(s);
   srunner_run_all(sr, CK_NORMAL);
   number_failed = srunner_ntests_failed(sr);
   srunner_free(sr);
   return (number_failed == 0) ? 0 : 1;
}
