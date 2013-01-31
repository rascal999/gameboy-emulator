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
   #ifndef _INCL_DEBUG
      #define _INCL_DEBUG
      #include "../src/mock_debug.h"
   #endif
   #ifndef _INCL_Z80
      #define _INCL_Z80
      #include "../src/mock_z80.h"
   #endif
   #include "../src/mock_error.h"
#else
   #ifndef _INCL_DEBUG
      #define _INCL_DEBUG
      #include "../src/debug.h"
   #endif
   #ifndef _INCL_Z80
      #define _INCL_Z80
      #include "../src/z80.h"
   #endif
   #include "../src/error.h"
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

   fail_unless(z80->regPC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");
   fail_unless(z80->ticks == 4,"Ticks for opcode not registered or incorrect value");

   return 0;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ADDXY
 *  Description:  Add the contents of the Y register to the X register
 * =====================================================================================
 */
int ADDXY(Memory * memory, Z80 * z80, Z80 * old_z80, uint8_t regOrder, uint16_t tmp_z80_PC)
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
      case 0x0: oldSrc = old_z80->regA; fail_unless(dest == ((oldDest + oldSrc) & 0xFF),"Register %c does not equal register %c + register A",destName,destName); break;
      case 0x1: oldSrc = old_z80->regB; fail_unless(dest == ((oldDest + oldSrc) & 0xFF),"Register %c does not equal register %c + register B",destName,destName); break;
      case 0x2: oldSrc = old_z80->regC; fail_unless(dest == ((oldDest + oldSrc) & 0xFF),"Register %c does not equal register %c + register C",destName,destName); break;
      case 0x3: oldSrc = old_z80->regD; fail_unless(dest == ((oldDest + oldSrc) & 0xFF),"Register %c does not equal register %c + register D",destName,destName); break;
      case 0x4: oldSrc = old_z80->regE; fail_unless(dest == ((oldDest + oldSrc) & 0xFF),"Register %c does not equal register %c + register E",destName,destName); break;
      case 0x5: oldSrc = old_z80->regF; fail_unless(dest == ((oldDest + oldSrc) & 0xFF),"Register %c does not equal register %c + register F",destName,destName); break;
      case 0x6: oldSrc = old_z80->regH; fail_unless(dest == ((oldDest + oldSrc) & 0xFF),"Register %c does not equal register %c + register H",destName,destName); break;
      case 0x7: oldSrc = old_z80->regL; fail_unless(dest == ((oldDest + oldSrc) & 0xFF),"Register %c does not equal register %c + register L",destName,destName); break;
   }

   //dest = (oldDest + oldSrc) & 0xFF;

   // Flags
   if ((dest < oldDest) | (dest < oldSrc))
   {
      // Carry
      fail_unless((z80->regF & 0x10) == 0x10,"Carry flag should be set %x",z80->regF & 0x10);
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

   fail_unless(z80->regPC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");
   fail_unless(z80->ticks == 4,"Ticks for opcode not registered or incorrect value");

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

   fail_unless(z80->regPC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");
   fail_unless(z80->ticks == 4,"Ticks for opcode not registered or incorrect value");

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

   fail_unless(z80->regPC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");
   fail_unless(z80->ticks == 4,"Ticks for opcode not registered or incorrect value");

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

   fail_unless(z80->regPC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");
   fail_unless(z80->ticks == 4,"Ticks for opcode not registered or incorrect value");

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

   fail_unless(z80->regPC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");
   fail_unless(z80->ticks == 4,"Ticks for opcode not registered or incorrect value");

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

   fail_unless(z80->regPC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");
   fail_unless(z80->ticks == 8,"Ticks for opcode not registered or incorrect value");

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

   fail_unless(z80->regPC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");
   fail_unless(z80->ticks == 8,"Ticks for opcode not registered or incorrect value");

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

   fail_unless(z80->regPC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");
   fail_unless(z80->ticks == 8,"Ticks for opcode not registered or incorrect value");

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

   fail_unless(z80->regPC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");
   fail_unless(z80->ticks == 8,"Ticks for opcode not registered or incorrect value");

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

   fail_unless(z80->regPC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");
   fail_unless(z80->ticks == 8,"Ticks for opcode not registered or incorrect value");

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

   fail_unless(z80->regPC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");
   fail_unless(z80->ticks == 8,"Ticks for opcode not registered or incorrect value");

   return 0;
}

START_TEST (test_check_OP_00h_NOP)
{
   Memory memory;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers);
   InitMemory(&memory);

   int result = 0;
   uint8_t tmp_z80_PC = z80.regPC;

   result = OP_00h_NOP(&memory,&z80);

   fail_unless(z80.regPC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");
   fail_unless(result == 0,"Result was not 0");
   fail_unless(z80.ticks == 4,"Ticks for opcode not registered or incorrect value");
}
END_TEST

START_TEST (test_check_OP_INCX)
{
   Memory memory;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers);
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
         if ((((oldRegValue & 0xF) + 0x1) & 0xF) == 0xF)
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

         fail_unless(z80.regPC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");
         fail_unless(result == 0,"Result was not 0");
         fail_unless(z80.ticks == 4,"Ticks for opcode not registered or incorrect value");
      }
   }
}
END_TEST

START_TEST (test_check_OP_LDXD8)
{
   Memory memory;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers);
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

         result = OP_LDXD8(&memory,&z80,h);

         fail_unless((z80.r->r[h] & 0xFF) == rb(&memory,(tmp_z80_PC)) & 0xFF);
         fail_unless(z80.regPC == tmp_z80_PC + 1,"Program Counter should not be incremented by opcode function code");

         fail_unless(result == 0,"Result was not 0");
         fail_unless(z80.ticks == 8,"Ticks for opcode not registered or incorrect value");
      }
   }
}
END_TEST

START_TEST (test_check_OP_LDHLX)
{
   Memory memory;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers);
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
         fail_unless(z80.regPC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");

         fail_unless(result == 0,"Result was not 0");
printf("HERE -- HL addr content = %x\nHERE reg = %x\n",rb(&memory,(z80.regH << 8) + z80.regL),z80.r->r[reg]);
         fail_unless(rb(&memory,(z80.regH << 8) + z80.regL) == z80.r->r[reg],"Content at address pointed by HL does not match register.");
         fail_unless(z80.ticks == 8,"Ticks for opcode not registered or incorrect value");
      }
   }
}
END_TEST

START_TEST (test_check_OP_20h_JRNZn)
{
   Memory memory;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers);
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

         result = OP_20h_JRNZn(&memory,&z80);

         // Relative jump if last result is non-zero
         // If last result is non-zero, ticks == 12, else ticks == 8
         if ((z80.regF & 0x80) == 0x00)
         {
printf("*** k == %x\nz80.regPC == %x\nrb(&memory,tmp_z80_PC) + tmp_z80_PC == %x\n",k,z80.regPC - 1,rb(&memory,tmp_z80_PC) + tmp_z80_PC);
            fail_unless(((z80.regPC - 1) & 0xFF) == ((rb(&memory,tmp_z80_PC) + (int8_t) tmp_z80_PC) & 0xFF));
            fail_unless(z80.ticks == 12,"Ticks for opcode not registered or incorrect value");
         } else {
            fail_unless((z80.regPC - 1) == tmp_z80_PC,"Program Counter should be incremented by opcode function code");
            fail_unless(z80.ticks == 8,"Ticks for opcode not registered or incorrect value");
         }

         fail_unless(result == 0,"Result was not 0");
      }
   }
}
END_TEST

START_TEST (test_check_OP_21h_LDHLnn)
{
   Memory memory;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers);
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

         result = OP_21h_LDHLnn(&memory,&z80);
//printf("z80.regPC - 2 == %x\ntmp_z80_PC == %x\n",(z80.regPC - 2),tmp_z80_PC);
         fail_unless((uint16_t) (z80.regPC - 2) == (uint16_t) tmp_z80_PC,"Program Counter should be incremented by opcode function code");

         fail_unless(result == 0,"Result was not 0");
         //tmp_z80_PC is 0, and this byte is treated as an address
         fail_unless(z80.regH == rb(&memory,(tmp_z80_PC + 1)),"H register incorrect value");
         fail_unless(z80.regL == rb(&memory,(tmp_z80_PC)),"L register incorrect value");

         fail_unless(z80.ticks == 12,"Ticks for opcode not registered or incorrect value");
      }
   }
}
END_TEST

START_TEST (test_check_OP_22h_LDIHLA)
{
   Memory memory;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers);
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
         fail_unless(z80.regPC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");

         fail_unless(result == 0,"Result was not 0");
//printf("HL-1 addr content = %x\nA = %x\n",rb(&memory,(z80.regH << 8) + z80.regL - 1),z80.regA);
         fail_unless(rb(&memory,(z80.regH << 8) + z80.regL - 1) == z80.regA,"Content at address pointed by HL (-1 at this point) does not match A register.");
         fail_unless(z80.ticks == 8,"Ticks for opcode not registered or incorrect value");
      }
   }
}
END_TEST

START_TEST (test_check_OP_31h_LDSPnn)
{
   Memory memory;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers);
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

         result = OP_31h_LDSPnn(&memory,&z80);

         fail_unless((z80.regPC - 2) == tmp_z80_PC,"Program Counter should be incremented by opcode function code");

         fail_unless(result == 0,"Result was not 0");

         fail_unless(z80.ticks == 12,"Ticks for opcode not registered or incorrect value");

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

printf("z80.regSP == %x\n(rb(&memory,(tmp_z80_PC + 1)) << 8) == %x\nrb(&memory,(tmp_z80_PC)) == %x\n",z80.regSP,(rb(&memory,(tmp_z80_PC + 1)) << 8),rb(&memory,(tmp_z80_PC)));
printf("tmp_z80_PC == %x\n",tmp_z80_PC);
         fail_unless((uint16_t) z80.regSP == (uint16_t) (rb(&memory,((uint16_t) tmp_z80_PC + (uint16_t) 1)) << 8) + (uint16_t) rb(&memory,((uint16_t) tmp_z80_PC)),"SP register incorrect value");
      }
   }
}
END_TEST

START_TEST (test_check_OP_32h_LDDHLA)
{
   Memory memory;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers);
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
         fail_unless(z80.regPC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");

         fail_unless(result == 0,"Result was not 0");
         printf("HL+1 addr content = %x\nA = %x\n",rb(&memory,(z80.regH << 8) + z80.regL + 1),z80.regA);

         fail_unless(rb(&memory,(z80.regH << 8) + z80.regL + 1) == z80.regA,"Content at address pointed by HL (+1 at this point) does not match A register.");
         fail_unless(z80.ticks == 8,"Ticks for opcode not registered or incorrect value");
      }
   }
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

//int OP_48h_LDCB(Memory * memory, Z80 * z80);
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

//int OP_49h_LDCC(Memory * memory, Z80 * z80);
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

//int OP_4Ah_LDCD(Memory * memory, Z80 * z80);
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

//int OP_4Bh_LDCE(Memory * memory, Z80 * z80);
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

//int OP_4Ch_LDCH(Memory * memory, Z80 * z80);
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

//int OP_4Dh_LDCL(Memory * memory, Z80 * z80);
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

//int OP_4Fh_LDCA(Memory * memory, Z80 * z80);
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

//int OP_58h_LDEB(Memory * memory, Z80 * z80);
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

//int OP_59h_LDEC(Memory * memory, Z80 * z80);
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

//int OP_5Ah_LDED(Memory * memory, Z80 * z80);
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

//int OP_5Bh_LDEE(Memory * memory, Z80 * z80);
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

//int OP_5Ch_LDEH(Memory * memory, Z80 * z80);
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

//int OP_5Dh_LDEL(Memory * memory, Z80 * z80);
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

//int OP_5Fh_LDEA(Memory * memory, Z80 * z80);
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

//int OP_68h_LDLB(Memory * memory, Z80 * z80);
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

//int OP_69h_LDLC(Memory * memory, Z80 * z80);
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

//int OP_6Ah_LDLD(Memory * memory, Z80 * z80);
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

//int OP_6Bh_LDLE(Memory * memory, Z80 * z80);
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

//int OP_6Ch_LDLH(Memory * memory, Z80 * z80);
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

//int OP_6Dh_LDLL(Memory * memory, Z80 * z80);
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

//int OP_6Fh_LDLA(Memory * memory, Z80 * z80);
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

START_TEST (test_check_OP_72h_LDHLD)
{
   Memory memory;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers);
   InitMemory(&memory);

   int result = 0;
   uint8_t tmp_z80_PC = z80.regPC;
   uint8_t tmp_z80_HL = (z80.regH << 8) + z80.regL;

   z80.regD = 0xD;
   z80.regH = 0x8;
   z80.regL = 0x8;

   result = OP_72h_LDHLD(&memory,&z80);

   fail_unless(z80.regPC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");

   fail_unless(result == 0,"Result was not 0");
   fail_unless(rb(&memory,(z80.regH << 8) + z80.regL) == z80.regD,"Content of address held in HL register does not equal register D");
   fail_unless(z80.ticks == 8,"Ticks for opcode not registered or incorrect value");
}
END_TEST

//int OP_78h_LDAB(Memory * memory, Z80 * z80);
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

//int OP_79h_LDAC(Memory * memory, Z80 * z80);
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

//int OP_7Ah_LDAD(Memory * memory, Z80 * z80);
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

//int OP_7Bh_LDAE(Memory * memory, Z80 * z80);
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

//int OP_7Ch_LDAH(Memory * memory, Z80 * z80);
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

//int OP_7Dh_LDAL(Memory * memory, Z80 * z80);
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

//int OP_7Fh_LDAA(Memory * memory, Z80 * z80);
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

//int OP_80h_ADDAB(Memory * memory, Z80 * z80);
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

START_TEST (test_check_OP_CB_00h_RLCB)
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

START_TEST (test_check_OP_CB_01h_RLCC)
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

START_TEST (test_check_OP_CB_02h_RLCD)
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

START_TEST (test_check_OP_CB_03h_RLCE)
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

START_TEST (test_check_OP_CB_04h_RLCH)
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

START_TEST (test_check_OP_CB_05h_RLCL)
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

START_TEST (test_check_OP_CB_07h_RLCA)
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

START_TEST (test_check_OP_CB_08h_RRCB)
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

START_TEST (test_check_OP_CB_09h_RRCC)
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

START_TEST (test_check_OP_CB_0Ah_RRCD)
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

START_TEST (test_check_OP_CB_0Bh_RRCE)
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

START_TEST (test_check_OP_CB_0Ch_RRCH)
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

START_TEST (test_check_OP_CB_0Dh_RRCL)
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

START_TEST (test_check_OP_CB_0Fh_RRCA)
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

START_TEST (test_check_OP_CB_40h_BIT0B)
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

START_TEST (test_check_OP_CB_41h_BIT0C)
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

START_TEST (test_check_OP_CB_42h_BIT0D)
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

START_TEST (test_check_OP_CB_43h_BIT0E)
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

START_TEST (test_check_OP_CB_44h_BIT0H)
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

START_TEST (test_check_OP_CB_45h_BIT0L)
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

START_TEST (test_check_OP_CB_47h_BIT0A)
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

START_TEST (test_check_OP_CB_80h_RES0B)
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

START_TEST (test_check_OP_CB_81h_RES0C)
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

START_TEST (test_check_OP_CB_82h_RES0D)
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

START_TEST (test_check_OP_CB_83h_RES0E)
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

START_TEST (test_check_OP_CB_84h_RES0H)
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

START_TEST (test_check_OP_CB_85h_RES0L)
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

START_TEST (test_check_OP_CB_87h_RES0A)
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

START_TEST (test_check_OP_CB_88h_RES1B)
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

START_TEST (test_check_OP_CB_89h_RES1C)
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

START_TEST (test_check_OP_CB_8Ah_RES1D)
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

START_TEST (test_check_OP_CB_8Bh_RES1E)
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

START_TEST (test_check_OP_CB_8Ch_RES1H)
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

START_TEST (test_check_OP_CB_8Dh_RES1L)
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

START_TEST (test_check_OP_CB_8Fh_RES1A)
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

START_TEST (test_check_OP_CB_90h_RES2B)
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

START_TEST (test_check_OP_CB_91h_RES2C)
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

START_TEST (test_check_OP_CB_92h_RES2D)
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

START_TEST (test_check_OP_CB_93h_RES2E)
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

START_TEST (test_check_OP_CB_94h_RES2H)
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

START_TEST (test_check_OP_CB_95h_RES2L)
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

START_TEST (test_check_OP_CB_97h_RES2A)
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

START_TEST (test_check_OP_CB_98h_RES3B)
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

START_TEST (test_check_OP_CB_99h_RES3C)
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

START_TEST (test_check_OP_CB_9Ah_RES3D)
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

START_TEST (test_check_OP_CB_9Bh_RES3E)
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

START_TEST (test_check_OP_CB_9Ch_RES3H)
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

START_TEST (test_check_OP_CB_9Dh_RES3L)
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

START_TEST (test_check_OP_CB_9Fh_RES3A)
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

START_TEST (test_check_OP_CB_A0h_RES4B)
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

START_TEST (test_check_OP_CB_A1h_RES4C)
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

START_TEST (test_check_OP_CB_A2h_RES4D)
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

START_TEST (test_check_OP_CB_A3h_RES4E)
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

START_TEST (test_check_OP_CB_A4h_RES4H)
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

START_TEST (test_check_OP_CB_A5h_RES4L)
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

START_TEST (test_check_OP_CB_A7h_RES4A)
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

START_TEST (test_check_OP_CB_A8h_RES5B)
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

START_TEST (test_check_OP_CB_A9h_RES5C)
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

START_TEST (test_check_OP_CB_AAh_RES5D)
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

START_TEST (test_check_OP_CB_ABh_RES5E)
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

START_TEST (test_check_OP_CB_ACh_RES5H)
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

START_TEST (test_check_OP_CB_ADh_RES5L)
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

START_TEST (test_check_OP_CB_AFh_RES5A)
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

START_TEST (test_check_OP_CB_B0h_RES6B)
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

START_TEST (test_check_OP_CB_B1h_RES6C)
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

START_TEST (test_check_OP_CB_B2h_RES6D)
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

START_TEST (test_check_OP_CB_B3h_RES6E)
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

START_TEST (test_check_OP_CB_B4h_RES6H)
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

START_TEST (test_check_OP_CB_B5h_RES6L)
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

START_TEST (test_check_OP_CB_B7h_RES6A)
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

START_TEST (test_check_OP_CB_B8h_RES7B)
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

START_TEST (test_check_OP_CB_B9h_RES7C)
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

START_TEST (test_check_OP_CB_BAh_RES7D)
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

START_TEST (test_check_OP_CB_BBh_RES7E)
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

START_TEST (test_check_OP_CB_BCh_RES7H)
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

START_TEST (test_check_OP_CB_BDh_RES7L)
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

START_TEST (test_check_OP_CB_BFh_RES7A)
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

START_TEST (test_check_OP_CB_C0h_SET0B)
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

START_TEST (test_check_OP_CB_C1h_SET0C)
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

START_TEST (test_check_OP_CB_C2h_SET0D)
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

START_TEST (test_check_OP_CB_C3h_SET0E)
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

START_TEST (test_check_OP_CB_C4h_SET0H)
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

START_TEST (test_check_OP_CB_C5h_SET0L)
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

START_TEST (test_check_OP_CB_C7h_SET0A)
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

START_TEST (test_check_OP_CB_C8h_SET1B)
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

START_TEST (test_check_OP_CB_C9h_SET1C)
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

START_TEST (test_check_OP_CB_CAh_SET1D)
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

START_TEST (test_check_OP_CB_CBh_SET1E)
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

START_TEST (test_check_OP_CB_CCh_SET1H)
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

START_TEST (test_check_OP_CB_CDh_SET1L)
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

START_TEST (test_check_OP_CB_CFh_SET1A)
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

START_TEST (test_check_OP_CB_D0h_SET2B)
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

START_TEST (test_check_OP_CB_D1h_SET2C)
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

START_TEST (test_check_OP_CB_D2h_SET2D)
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

START_TEST (test_check_OP_CB_D3h_SET2E)
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

START_TEST (test_check_OP_CB_D4h_SET2H)
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

START_TEST (test_check_OP_CB_D5h_SET2L)
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

START_TEST (test_check_OP_CB_D7h_SET2A)
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

START_TEST (test_check_OP_CB_D8h_SET3B)
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

START_TEST (test_check_OP_CB_D9h_SET3C)
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

START_TEST (test_check_OP_CB_DAh_SET3D)
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

START_TEST (test_check_OP_CB_DBh_SET3E)
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

START_TEST (test_check_OP_CB_DCh_SET3H)
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

START_TEST (test_check_OP_CB_DDh_SET3L)
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

START_TEST (test_check_OP_CB_DFh_SET3A)
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

START_TEST (test_check_OP_CB_E0h_SET4B)
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

START_TEST (test_check_OP_CB_E1h_SET4C)
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

START_TEST (test_check_OP_CB_E2h_SET4D)
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

START_TEST (test_check_OP_CB_E3h_SET4E)
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

START_TEST (test_check_OP_CB_E4h_SET4H)
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

START_TEST (test_check_OP_CB_E5h_SET4L)
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

START_TEST (test_check_OP_CB_E7h_SET4A)
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

START_TEST (test_check_OP_CB_E8h_SET5B)
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

START_TEST (test_check_OP_CB_E9h_SET5C)
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

START_TEST (test_check_OP_CB_EAh_SET5D)
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

START_TEST (test_check_OP_CB_EBh_SET5E)
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

START_TEST (test_check_OP_CB_ECh_SET5H)
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

START_TEST (test_check_OP_CB_EDh_SET5L)
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

START_TEST (test_check_OP_CB_EFh_SET5A)
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

START_TEST (test_check_OP_CB_F0h_SET6B)
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

START_TEST (test_check_OP_CB_F1h_SET6C)
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

START_TEST (test_check_OP_CB_F2h_SET6D)
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

START_TEST (test_check_OP_CB_F3h_SET6E)
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

START_TEST (test_check_OP_CB_F4h_SET6H)
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

START_TEST (test_check_OP_CB_F5h_SET6L)
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

START_TEST (test_check_OP_CB_F7h_SET6A)
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

START_TEST (test_check_OP_CB_F8h_SET7B)
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

START_TEST (test_check_OP_CB_F9h_SET7C)
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

START_TEST (test_check_OP_CB_FAh_SET7D)
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

START_TEST (test_check_OP_CB_FBh_SET7E)
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

START_TEST (test_check_OP_CB_FCh_SET7H)
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

START_TEST (test_check_OP_CB_FDh_SET7L)
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

START_TEST (test_check_OP_CB_FFh_SET7A)
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

START_TEST (test_check_OP_AFh_XORA)
{
   Memory memory;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers);
   InitMemory(&memory);

   int result = 0;
   uint8_t tmp_z80_PC = z80.regPC;

   result = OP_AFh_XORA(&memory,&z80);

   fail_unless(z80.regPC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");

   fail_unless(result == 0,"Result was not 0");

   fail_unless(z80.ticks == 4,"Ticks for opcode not registered or incorrect value");
   fail_unless(z80.regA == 0,"A register should be 0");
   fail_unless(z80.regF == 0x80,"Zero flag should be set and all others reset");
}
END_TEST

START_TEST (test_check_OP_E0h_LDHAn)
{
   Memory memory;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers);
   InitMemory(&memory);

   int result = 0, i;
   uint8_t tmp_z80_PC = z80.regPC;

   for(i=0;i<0xFF;i++)
   {
      z80.regA = i;

      tmp_z80_PC = (z80.regPC & 0xFF);

      result = OP_E0h_LDHAn(&memory,&z80);

      fail_unless(z80.regPC == tmp_z80_PC + 0x1,"Program Counter should have been incremented by opcode function");

      fail_unless(result == 0,"Result was not 0");
printf("SEG PC == %x\nSEG rb == %x\nSEG addr == %x\n",z80.regPC & 0xFF,0xff00 + z80.regPC);
printf("fuck\n");
fflush( stdout );
      fail_unless(z80.ticks == 12,"Ticks for opcode not registered or incorrect value");
      fail_unless(z80.regA == rb(&memory,(0xff00 + (rb(&memory,(z80.regPC & 0xFF)) & 0xFF))));
   }
}
END_TEST

START_TEST (test_check_OP_E2h_LDHCA)
{
   Memory memory;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers);
   InitMemory(&memory);

   int result = 0;
   uint8_t tmp_z80_PC = z80.regPC;

   result = OP_E2h_LDHCA(&memory,&z80);

   fail_unless(z80.regPC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");

   fail_unless(result == 0,"Result was not 0");

   fail_unless(z80.ticks == 8,"Ticks for opcode not registered or incorrect value");
   fail_unless(z80.regA == rb(&memory,(0xff00 + z80.regC)));
}
END_TEST

Suite * add_suite(void)
{
   Suite * s = suite_create("Add");

   /* Core test case */
   TCase *tc_core = tcase_create("Core");
   tcase_add_test(tc_core,test_check_OP_00h_NOP);
   tcase_add_test(tc_core,test_check_OP_INCX);

   tcase_add_test(tc_core,test_check_OP_LDXD8);
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

   tcase_add_test(tc_core,test_check_OP_20h_JRNZn);
   tcase_add_test(tc_core,test_check_OP_21h_LDHLnn);
   tcase_add_test(tc_core,test_check_OP_22h_LDIHLA);
   tcase_add_test(tc_core,test_check_OP_31h_LDSPnn);
   tcase_add_test(tc_core,test_check_OP_32h_LDDHLA);
   tcase_add_test(tc_core,test_check_OP_40h_LDBB);
   tcase_add_test(tc_core,test_check_OP_41h_LDBC);
   tcase_add_test(tc_core,test_check_OP_42h_LDBD);
   tcase_add_test(tc_core,test_check_OP_43h_LDBE);
   tcase_add_test(tc_core,test_check_OP_44h_LDBH);
   tcase_add_test(tc_core,test_check_OP_45h_LDBL);
   tcase_add_test(tc_core,test_check_OP_48h_LDCB);
   tcase_add_test(tc_core,test_check_OP_49h_LDCC);
   tcase_add_test(tc_core,test_check_OP_4Ah_LDCD);
   tcase_add_test(tc_core,test_check_OP_4Bh_LDCE);
   tcase_add_test(tc_core,test_check_OP_4Ch_LDCH);
   tcase_add_test(tc_core,test_check_OP_4Dh_LDCL);
   tcase_add_test(tc_core,test_check_OP_4Fh_LDCA);
   tcase_add_test(tc_core,test_check_OP_50h_LDDB);
   tcase_add_test(tc_core,test_check_OP_51h_LDDC);
   tcase_add_test(tc_core,test_check_OP_52h_LDDD);
   tcase_add_test(tc_core,test_check_OP_53h_LDDE);
   tcase_add_test(tc_core,test_check_OP_54h_LDDH);
   tcase_add_test(tc_core,test_check_OP_55h_LDDL);
   tcase_add_test(tc_core,test_check_OP_58h_LDEB);
   tcase_add_test(tc_core,test_check_OP_59h_LDEC);
   tcase_add_test(tc_core,test_check_OP_5Ah_LDED);
   tcase_add_test(tc_core,test_check_OP_5Bh_LDEE);
   tcase_add_test(tc_core,test_check_OP_5Ch_LDEH);
   tcase_add_test(tc_core,test_check_OP_5Dh_LDEL);
   tcase_add_test(tc_core,test_check_OP_5Fh_LDEA);
   tcase_add_test(tc_core,test_check_OP_60h_LDHB);
   tcase_add_test(tc_core,test_check_OP_61h_LDHC);
   tcase_add_test(tc_core,test_check_OP_62h_LDHD);
   tcase_add_test(tc_core,test_check_OP_63h_LDHE);
   tcase_add_test(tc_core,test_check_OP_64h_LDHH);
   tcase_add_test(tc_core,test_check_OP_65h_LDHL);
   tcase_add_test(tc_core,test_check_OP_68h_LDLB);
   tcase_add_test(tc_core,test_check_OP_69h_LDLC);
   tcase_add_test(tc_core,test_check_OP_6Ah_LDLD);
   tcase_add_test(tc_core,test_check_OP_6Bh_LDLE);
   tcase_add_test(tc_core,test_check_OP_6Ch_LDLH);
   tcase_add_test(tc_core,test_check_OP_6Dh_LDLL);
   tcase_add_test(tc_core,test_check_OP_6Fh_LDLA);
   tcase_add_test(tc_core,test_check_OP_72h_LDHLD);
   tcase_add_test(tc_core,test_check_OP_78h_LDAB);
   tcase_add_test(tc_core,test_check_OP_79h_LDAC);
   tcase_add_test(tc_core,test_check_OP_7Ah_LDAD);
   tcase_add_test(tc_core,test_check_OP_7Bh_LDAE);
   tcase_add_test(tc_core,test_check_OP_7Ch_LDAH);
   tcase_add_test(tc_core,test_check_OP_7Dh_LDAL);
   tcase_add_test(tc_core,test_check_OP_7Fh_LDAA);
   tcase_add_test(tc_core,test_check_OP_80h_ADDAB);
   tcase_add_test(tc_core,test_check_OP_81h_ADDAC);
   tcase_add_test(tc_core,test_check_OP_82h_ADDAD);
   tcase_add_test(tc_core,test_check_OP_83h_ADDAE);
   tcase_add_test(tc_core,test_check_OP_84h_ADDAH);
   tcase_add_test(tc_core,test_check_OP_85h_ADDAL);
   tcase_add_test(tc_core,test_check_OP_87h_ADDAA);
   tcase_add_test(tc_core,test_check_OP_88h_ADCAB);
   tcase_add_test(tc_core,test_check_OP_89h_ADCAC);
   tcase_add_test(tc_core,test_check_OP_8Ah_ADCAD);
   tcase_add_test(tc_core,test_check_OP_8Bh_ADCAE);
   tcase_add_test(tc_core,test_check_OP_8Ch_ADCAH);
   tcase_add_test(tc_core,test_check_OP_8Dh_ADCAL);
   tcase_add_test(tc_core,test_check_OP_8Fh_ADCAA);
   tcase_add_test(tc_core,test_check_OP_90h_SUBB);
   tcase_add_test(tc_core,test_check_OP_91h_SUBC);
   tcase_add_test(tc_core,test_check_OP_92h_SUBD);
   tcase_add_test(tc_core,test_check_OP_93h_SUBE);
   tcase_add_test(tc_core,test_check_OP_94h_SUBH);
   tcase_add_test(tc_core,test_check_OP_95h_SUBL);
   tcase_add_test(tc_core,test_check_OP_97h_SUBA);
   tcase_add_test(tc_core,test_check_OP_98h_SBCAB);
   tcase_add_test(tc_core,test_check_OP_99h_SBCAC);
   tcase_add_test(tc_core,test_check_OP_9Ah_SBCAD);
   tcase_add_test(tc_core,test_check_OP_9Bh_SBCAE);
   tcase_add_test(tc_core,test_check_OP_9Ch_SBCAH);
   tcase_add_test(tc_core,test_check_OP_9Dh_SBCAL);
   tcase_add_test(tc_core,test_check_OP_9Fh_SBCAA);
   tcase_add_test(tc_core,test_check_OP_A0h_ANDB);
   tcase_add_test(tc_core,test_check_OP_A1h_ANDC);
   tcase_add_test(tc_core,test_check_OP_A2h_ANDD);
   tcase_add_test(tc_core,test_check_OP_A3h_ANDE);
   tcase_add_test(tc_core,test_check_OP_A4h_ANDH);
   tcase_add_test(tc_core,test_check_OP_A5h_ANDL);
   tcase_add_test(tc_core,test_check_OP_A7h_ANDA);

   // CB prefix opcodes
   tcase_add_test(tc_core,test_check_OP_CB_00h_RLCB);
   tcase_add_test(tc_core,test_check_OP_CB_01h_RLCC);
   tcase_add_test(tc_core,test_check_OP_CB_02h_RLCD);
   tcase_add_test(tc_core,test_check_OP_CB_03h_RLCE);
   tcase_add_test(tc_core,test_check_OP_CB_04h_RLCH);
   tcase_add_test(tc_core,test_check_OP_CB_05h_RLCL);
   tcase_add_test(tc_core,test_check_OP_CB_07h_RLCA);

   tcase_add_test(tc_core,test_check_OP_CB_08h_RRCB);
   tcase_add_test(tc_core,test_check_OP_CB_09h_RRCC);
   tcase_add_test(tc_core,test_check_OP_CB_0Ah_RRCD);
   tcase_add_test(tc_core,test_check_OP_CB_0Bh_RRCE);
   tcase_add_test(tc_core,test_check_OP_CB_0Ch_RRCH);
   tcase_add_test(tc_core,test_check_OP_CB_0Dh_RRCL);
   tcase_add_test(tc_core,test_check_OP_CB_0Fh_RRCA);

   tcase_add_test(tc_core,test_check_OP_CB_40h_BIT0B);
   tcase_add_test(tc_core,test_check_OP_CB_41h_BIT0C);
   tcase_add_test(tc_core,test_check_OP_CB_42h_BIT0D);
   tcase_add_test(tc_core,test_check_OP_CB_43h_BIT0E);
   tcase_add_test(tc_core,test_check_OP_CB_44h_BIT0H);
   tcase_add_test(tc_core,test_check_OP_CB_45h_BIT0L);
   tcase_add_test(tc_core,test_check_OP_CB_47h_BIT0A);

   tcase_add_test(tc_core,test_check_OP_CB_80h_RES0B);
   tcase_add_test(tc_core,test_check_OP_CB_81h_RES0C);
   tcase_add_test(tc_core,test_check_OP_CB_82h_RES0D);
   tcase_add_test(tc_core,test_check_OP_CB_83h_RES0E);
   tcase_add_test(tc_core,test_check_OP_CB_84h_RES0H);
   tcase_add_test(tc_core,test_check_OP_CB_85h_RES0L);
   tcase_add_test(tc_core,test_check_OP_CB_87h_RES0A);
   tcase_add_test(tc_core,test_check_OP_CB_88h_RES1B);
   tcase_add_test(tc_core,test_check_OP_CB_89h_RES1C);
   tcase_add_test(tc_core,test_check_OP_CB_8Ah_RES1D);
   tcase_add_test(tc_core,test_check_OP_CB_8Bh_RES1E);
   tcase_add_test(tc_core,test_check_OP_CB_8Ch_RES1H);
   tcase_add_test(tc_core,test_check_OP_CB_8Dh_RES1L);
   tcase_add_test(tc_core,test_check_OP_CB_8Fh_RES1A);
   tcase_add_test(tc_core,test_check_OP_CB_90h_RES2B);
   tcase_add_test(tc_core,test_check_OP_CB_91h_RES2C);
   tcase_add_test(tc_core,test_check_OP_CB_92h_RES2D);
   tcase_add_test(tc_core,test_check_OP_CB_93h_RES2E);
   tcase_add_test(tc_core,test_check_OP_CB_94h_RES2H);
   tcase_add_test(tc_core,test_check_OP_CB_95h_RES2L);
   tcase_add_test(tc_core,test_check_OP_CB_97h_RES2A);
   tcase_add_test(tc_core,test_check_OP_CB_98h_RES3B);
   tcase_add_test(tc_core,test_check_OP_CB_99h_RES3C);
   tcase_add_test(tc_core,test_check_OP_CB_9Ah_RES3D);
   tcase_add_test(tc_core,test_check_OP_CB_9Bh_RES3E);
   tcase_add_test(tc_core,test_check_OP_CB_9Ch_RES3H);
   tcase_add_test(tc_core,test_check_OP_CB_9Dh_RES3L);
   tcase_add_test(tc_core,test_check_OP_CB_9Fh_RES3A);
   tcase_add_test(tc_core,test_check_OP_CB_A0h_RES4B);
   tcase_add_test(tc_core,test_check_OP_CB_A1h_RES4C);
   tcase_add_test(tc_core,test_check_OP_CB_A2h_RES4D);
   tcase_add_test(tc_core,test_check_OP_CB_A3h_RES4E);
   tcase_add_test(tc_core,test_check_OP_CB_A4h_RES4H);
   tcase_add_test(tc_core,test_check_OP_CB_A5h_RES4L);
   tcase_add_test(tc_core,test_check_OP_CB_A7h_RES4A);
   tcase_add_test(tc_core,test_check_OP_CB_A8h_RES5B);
   tcase_add_test(tc_core,test_check_OP_CB_A9h_RES5C);
   tcase_add_test(tc_core,test_check_OP_CB_AAh_RES5D);
   tcase_add_test(tc_core,test_check_OP_CB_ABh_RES5E);
   tcase_add_test(tc_core,test_check_OP_CB_ACh_RES5H);
   tcase_add_test(tc_core,test_check_OP_CB_ADh_RES5L);
   tcase_add_test(tc_core,test_check_OP_CB_AFh_RES5A);
   tcase_add_test(tc_core,test_check_OP_CB_B0h_RES6B);
   tcase_add_test(tc_core,test_check_OP_CB_B1h_RES6C);
   tcase_add_test(tc_core,test_check_OP_CB_B2h_RES6D);
   tcase_add_test(tc_core,test_check_OP_CB_B3h_RES6E);
   tcase_add_test(tc_core,test_check_OP_CB_B4h_RES6H);
   tcase_add_test(tc_core,test_check_OP_CB_B5h_RES6L);
   tcase_add_test(tc_core,test_check_OP_CB_B7h_RES6A);
   tcase_add_test(tc_core,test_check_OP_CB_B8h_RES7B);
   tcase_add_test(tc_core,test_check_OP_CB_B9h_RES7C);
   tcase_add_test(tc_core,test_check_OP_CB_BAh_RES7D);
   tcase_add_test(tc_core,test_check_OP_CB_BBh_RES7E);
   tcase_add_test(tc_core,test_check_OP_CB_BCh_RES7H);
   tcase_add_test(tc_core,test_check_OP_CB_BDh_RES7L);
   tcase_add_test(tc_core,test_check_OP_CB_BFh_RES7A);

   tcase_add_test(tc_core,test_check_OP_CB_C0h_SET0B);
   tcase_add_test(tc_core,test_check_OP_CB_C1h_SET0C);
   tcase_add_test(tc_core,test_check_OP_CB_C2h_SET0D);
   tcase_add_test(tc_core,test_check_OP_CB_C3h_SET0E);
   tcase_add_test(tc_core,test_check_OP_CB_C4h_SET0H);
   tcase_add_test(tc_core,test_check_OP_CB_C5h_SET0L);
   tcase_add_test(tc_core,test_check_OP_CB_C7h_SET0A);
   tcase_add_test(tc_core,test_check_OP_CB_C8h_SET1B);
   tcase_add_test(tc_core,test_check_OP_CB_C9h_SET1C);
   tcase_add_test(tc_core,test_check_OP_CB_CAh_SET1D);
   tcase_add_test(tc_core,test_check_OP_CB_CBh_SET1E);
   tcase_add_test(tc_core,test_check_OP_CB_CCh_SET1H);
   tcase_add_test(tc_core,test_check_OP_CB_CDh_SET1L);
   tcase_add_test(tc_core,test_check_OP_CB_CFh_SET1A);
   tcase_add_test(tc_core,test_check_OP_CB_D0h_SET2B);
   tcase_add_test(tc_core,test_check_OP_CB_D1h_SET2C);
   tcase_add_test(tc_core,test_check_OP_CB_D2h_SET2D);
   tcase_add_test(tc_core,test_check_OP_CB_D3h_SET2E);
   tcase_add_test(tc_core,test_check_OP_CB_D4h_SET2H);
   tcase_add_test(tc_core,test_check_OP_CB_D5h_SET2L);
   tcase_add_test(tc_core,test_check_OP_CB_D7h_SET2A);
   tcase_add_test(tc_core,test_check_OP_CB_D8h_SET3B);
   tcase_add_test(tc_core,test_check_OP_CB_D9h_SET3C);
   tcase_add_test(tc_core,test_check_OP_CB_DAh_SET3D);
   tcase_add_test(tc_core,test_check_OP_CB_DBh_SET3E);
   tcase_add_test(tc_core,test_check_OP_CB_DCh_SET3H);
   tcase_add_test(tc_core,test_check_OP_CB_DDh_SET3L);
   tcase_add_test(tc_core,test_check_OP_CB_DFh_SET3A);
   tcase_add_test(tc_core,test_check_OP_CB_E0h_SET4B);
   tcase_add_test(tc_core,test_check_OP_CB_E1h_SET4C);
   tcase_add_test(tc_core,test_check_OP_CB_E2h_SET4D);
   tcase_add_test(tc_core,test_check_OP_CB_E3h_SET4E);
   tcase_add_test(tc_core,test_check_OP_CB_E4h_SET4H);
   tcase_add_test(tc_core,test_check_OP_CB_E5h_SET4L);
   tcase_add_test(tc_core,test_check_OP_CB_E7h_SET4A);
   tcase_add_test(tc_core,test_check_OP_CB_E8h_SET5B);
   tcase_add_test(tc_core,test_check_OP_CB_E9h_SET5C);
   tcase_add_test(tc_core,test_check_OP_CB_EAh_SET5D);
   tcase_add_test(tc_core,test_check_OP_CB_EBh_SET5E);
   tcase_add_test(tc_core,test_check_OP_CB_ECh_SET5H);
   tcase_add_test(tc_core,test_check_OP_CB_EDh_SET5L);
   tcase_add_test(tc_core,test_check_OP_CB_EFh_SET5A);
   tcase_add_test(tc_core,test_check_OP_CB_F0h_SET6B);
   tcase_add_test(tc_core,test_check_OP_CB_F1h_SET6C);
   tcase_add_test(tc_core,test_check_OP_CB_F2h_SET6D);
   tcase_add_test(tc_core,test_check_OP_CB_F3h_SET6E);
   tcase_add_test(tc_core,test_check_OP_CB_F4h_SET6H);
   tcase_add_test(tc_core,test_check_OP_CB_F5h_SET6L);
   tcase_add_test(tc_core,test_check_OP_CB_F7h_SET6A);
   tcase_add_test(tc_core,test_check_OP_CB_F8h_SET7B);
   tcase_add_test(tc_core,test_check_OP_CB_F9h_SET7C);
   tcase_add_test(tc_core,test_check_OP_CB_FAh_SET7D);
   tcase_add_test(tc_core,test_check_OP_CB_FBh_SET7E);
   tcase_add_test(tc_core,test_check_OP_CB_FCh_SET7H);
   tcase_add_test(tc_core,test_check_OP_CB_FDh_SET7L);
   tcase_add_test(tc_core,test_check_OP_CB_FFh_SET7A);

   tcase_add_test(tc_core,test_check_OP_AFh_XORA);
   tcase_add_test(tc_core,test_check_OP_E0h_LDHAn);
   tcase_add_test(tc_core,test_check_OP_E2h_LDHCA);
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
