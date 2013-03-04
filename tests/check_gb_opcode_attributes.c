/*
 * =====================================================================================
 *
 *       Filename:  check_gb_opcode_attributes.c
 *
 *    Description:  Unit tests for opcode attributes
 *
 *        Version:  1.0
 *        Created:  04/03/13 13:02:58
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

START_TEST (test_check_OP_00h_NOP_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x00].size == 1);
   fail_unless(z80.op_call[0x00].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_01h_LDBCa16_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x01].size == 3);
   fail_unless(z80.op_call[0x01].ticks == 12);
}
END_TEST

START_TEST (test_check_OP_02h_LDBCA_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x02].size == 1);
   fail_unless(z80.op_call[0x02].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_03h_INCBC_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x03].size == 1);
   fail_unless(z80.op_call[0x03].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_04h_INCB_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x04].size == 1);
   fail_unless(z80.op_call[0x04].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_05h_DECB_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x05].size == 1);
   fail_unless(z80.op_call[0x05].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_06h_LDBd8_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x06].size == 2);
   fail_unless(z80.op_call[0x06].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_07h_RLCA_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x07].size == 1);
   fail_unless(z80.op_call[0x07].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_08h_LDnnSP_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x08].size == 3);
   fail_unless(z80.op_call[0x08].ticks == 20);
}
END_TEST

START_TEST (test_check_OP_09h_ADDHLBC_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x09].size == 1);
   fail_unless(z80.op_call[0x09].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_0Ah_LDABC_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x0a].size == 1);
   fail_unless(z80.op_call[0x0a].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_0Bh_DECBC_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x0b].size == 1);
   fail_unless(z80.op_call[0x0b].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_0Ch_INCC_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x0c].size == 1);
   fail_unless(z80.op_call[0x0c].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_0Dh_DECC_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x0d].size == 1);
   fail_unless(z80.op_call[0x0d].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_0Eh_LDCd8_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x0e].size == 2);
   fail_unless(z80.op_call[0x0e].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_0Fh_RRCA_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x0f].size == 1);
   fail_unless(z80.op_call[0x0f].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_10h_STOP0_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x10].size == 2);
   fail_unless(z80.op_call[0x10].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_11h_LDDEa16_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x11].size == 3);
   fail_unless(z80.op_call[0x11].ticks == 12);
}
END_TEST

START_TEST (test_check_OP_12h_LDDEA_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x12].size == 1);
   fail_unless(z80.op_call[0x12].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_13h_INCDE_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x13].size == 1);
   fail_unless(z80.op_call[0x13].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_14h_INCD_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x14].size == 1);
   fail_unless(z80.op_call[0x14].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_15h_DECD_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x15].size == 1);
   fail_unless(z80.op_call[0x15].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_16h_LDd8_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x16].size == 2);
   fail_unless(z80.op_call[0x16].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_17h_RLA_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x17].size == 1);
   fail_unless(z80.op_call[0x17].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_18h_JRd8_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x18].size == 2);
   fail_unless(z80.op_call[0x18].ticks == 12);
}
END_TEST

START_TEST (test_check_OP_19h_ADDHLDE_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x19].size == 1);
   fail_unless(z80.op_call[0x19].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_1Ah_LDADE_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x1a].size == 1);
   fail_unless(z80.op_call[0x1a].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_1Bh_DECDE_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x1b].size == 1);
   fail_unless(z80.op_call[0x1b].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_1Ch_INCE_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x1c].size == 1);
   fail_unless(z80.op_call[0x1c].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_1Dh_DECE_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x1d].size == 1);
   fail_unless(z80.op_call[0x1d].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_1Eh_LDEd8_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x1e].size == 2);
   fail_unless(z80.op_call[0x1e].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_1Fh_RRA_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x1f].size == 1);
   fail_unless(z80.op_call[0x1f].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_20h_JRNZr8_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x20].size == 2);
   fail_unless(z80.op_call[0x20].ticks == 0);
}
END_TEST

START_TEST (test_check_OP_21h_LDHLd16_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x21].size == 3);
   fail_unless(z80.op_call[0x21].ticks == 12);
}
END_TEST

START_TEST (test_check_OP_22h_LDIHLA_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x22].size == 1);
   fail_unless(z80.op_call[0x22].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_23h_INCHL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x23].size == 1);
   fail_unless(z80.op_call[0x23].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_24h_INCH_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x24].size == 1);
   fail_unless(z80.op_call[0x24].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_25h_DECH_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x25].size == 1);
   fail_unless(z80.op_call[0x25].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_26h_LDHd8_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x26].size == 2);
   fail_unless(z80.op_call[0x26].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_27h_DAA_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x27].size == 1);
   fail_unless(z80.op_call[0x27].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_28h_JRZd8_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x28].size == 2);
   fail_unless(z80.op_call[0x28].ticks == 0);
}
END_TEST

START_TEST (test_check_OP_29h_ADDHLHL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x29].size == 1);
   fail_unless(z80.op_call[0x29].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_2Ah_LDIAHL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x2a].size == 1);
   fail_unless(z80.op_call[0x2a].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_2Bh_DECHL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x2b].size == 1);
   fail_unless(z80.op_call[0x2b].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_2Ch_INCL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x2c].size == 1);
   fail_unless(z80.op_call[0x2c].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_2Dh_DECL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x2d].size == 1);
   fail_unless(z80.op_call[0x2d].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_2Eh_LDLd8_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x2e].size == 2);
   fail_unless(z80.op_call[0x2e].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_2Fh_CPL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x2f].size == 1);
   fail_unless(z80.op_call[0x2f].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_30h_JRNCd8_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x30].size == 2);
   fail_unless(z80.op_call[0x30].ticks == 0);
}
END_TEST

START_TEST (test_check_OP_31h_LDSPd16_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x31].size == 3);
   fail_unless(z80.op_call[0x31].ticks == 12);
}
END_TEST

START_TEST (test_check_OP_32h_LDDHLA_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x32].size == 1);
   fail_unless(z80.op_call[0x32].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_33h_INCSP_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x33].size == 1);
   fail_unless(z80.op_call[0x33].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_34h_INCHL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x34].size == 1);
   fail_unless(z80.op_call[0x34].ticks == 12);
}
END_TEST

START_TEST (test_check_OP_35h_DECHL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x35].size == 1);
   fail_unless(z80.op_call[0x35].ticks == 12);
}
END_TEST

START_TEST (test_check_OP_36h_LDHLd8_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x36].size == 2);
   fail_unless(z80.op_call[0x36].ticks == 12);
}
END_TEST

START_TEST (test_check_OP_37h_SCF_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x37].size == 1);
   fail_unless(z80.op_call[0x37].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_38h_JRCd8_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x38].size == 2);
   fail_unless(z80.op_call[0x38].ticks == 0);
}
END_TEST

START_TEST (test_check_OP_39h_ADDHLSP_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x39].size == 1);
   fail_unless(z80.op_call[0x39].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_3Ah_LDDAHL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x3a].size == 1);
   fail_unless(z80.op_call[0x3a].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_3Bh_DECSP_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x3b].size == 1);
   fail_unless(z80.op_call[0x3b].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_3Ch_INCA_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x3c].size == 1);
   fail_unless(z80.op_call[0x3c].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_3Dh_DECA_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x3d].size == 1);
   fail_unless(z80.op_call[0x3d].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_3Eh_LDAd8_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x3e].size == 2);
   fail_unless(z80.op_call[0x3e].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_3Fh_CCF_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x3f].size == 1);
   fail_unless(z80.op_call[0x3f].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_40h_LDBB_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x40].size == 1);
   fail_unless(z80.op_call[0x40].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_41h_LDBC_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x41].size == 1);
   fail_unless(z80.op_call[0x41].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_42h_LDBD_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x42].size == 1);
   fail_unless(z80.op_call[0x42].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_43h_LDBE_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x43].size == 1);
   fail_unless(z80.op_call[0x43].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_44h_LDBH_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x44].size == 1);
   fail_unless(z80.op_call[0x44].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_45h_LDBL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x45].size == 1);
   fail_unless(z80.op_call[0x45].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_46h_LDBHL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x46].size == 1);
   fail_unless(z80.op_call[0x46].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_47h_LDBA_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x47].size == 1);
   fail_unless(z80.op_call[0x47].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_48h_LDCB_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x48].size == 1);
   fail_unless(z80.op_call[0x48].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_49h_LDC_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x49].size == 1);
   fail_unless(z80.op_call[0x49].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_4Ah_LDCD_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x4a].size == 1);
   fail_unless(z80.op_call[0x4a].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_4Bh_LDCE_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x4b].size == 1);
   fail_unless(z80.op_call[0x4b].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_4Ch_LDCH_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x4c].size == 1);
   fail_unless(z80.op_call[0x4c].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_4Dh_LDCL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x4d].size == 1);
   fail_unless(z80.op_call[0x4d].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_4Eh_LDCHL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x4e].size == 1);
   fail_unless(z80.op_call[0x4e].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_4Fh_LDCA_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x4f].size == 1);
   fail_unless(z80.op_call[0x4f].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_50h_LDDB_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x50].size == 1);
   fail_unless(z80.op_call[0x50].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_51h_LDDC_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x51].size == 1);
   fail_unless(z80.op_call[0x51].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_52h_LDDD_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x52].size == 1);
   fail_unless(z80.op_call[0x52].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_53h_LDDE_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x53].size == 1);
   fail_unless(z80.op_call[0x53].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_54h_LDDH_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x54].size == 1);
   fail_unless(z80.op_call[0x54].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_55h_LDDL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x55].size == 1);
   fail_unless(z80.op_call[0x55].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_56h_LDDHL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x56].size == 1);
   fail_unless(z80.op_call[0x56].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_57h_LDDA_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x57].size == 1);
   fail_unless(z80.op_call[0x57].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_58h_LDEB_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x58].size == 1);
   fail_unless(z80.op_call[0x58].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_59h_LDEC_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x59].size == 1);
   fail_unless(z80.op_call[0x59].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_5Ah_LDED_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x5a].size == 1);
   fail_unless(z80.op_call[0x5a].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_5Bh_LDEE_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x5b].size == 1);
   fail_unless(z80.op_call[0x5b].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_5Ch_LDEH_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x5c].size == 1);
   fail_unless(z80.op_call[0x5c].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_5Dh_LDEL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x5d].size == 1);
   fail_unless(z80.op_call[0x5d].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_5Eh_LDEHL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x5e].size == 1);
   fail_unless(z80.op_call[0x5e].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_5Fh_LDEA_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x5f].size == 1);
   fail_unless(z80.op_call[0x5f].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_60h_LDHB_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x60].size == 1);
   fail_unless(z80.op_call[0x60].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_61h_LDHC_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x61].size == 1);
   fail_unless(z80.op_call[0x61].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_62h_LDHD_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x62].size == 1);
   fail_unless(z80.op_call[0x62].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_63h_LDHE_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x63].size == 1);
   fail_unless(z80.op_call[0x63].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_64h_LDHH_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x64].size == 1);
   fail_unless(z80.op_call[0x64].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_65h_LDHL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x65].size == 1);
   fail_unless(z80.op_call[0x65].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_66h_LDHHL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x66].size == 1);
   fail_unless(z80.op_call[0x66].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_67h_LDHA_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x67].size == 1);
   fail_unless(z80.op_call[0x67].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_68h_LDLB_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x68].size == 1);
   fail_unless(z80.op_call[0x68].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_69h_LDLC_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x69].size == 1);
   fail_unless(z80.op_call[0x69].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_6Ah_LDLD_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x6a].size == 1);
   fail_unless(z80.op_call[0x6a].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_6Bh_LDLE_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x6b].size == 1);
   fail_unless(z80.op_call[0x6b].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_6Ch_LDLH_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x6c].size == 1);
   fail_unless(z80.op_call[0x6c].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_6Dh_LDLL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x6d].size == 1);
   fail_unless(z80.op_call[0x6d].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_6Eh_LDLHL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x6e].size == 1);
   fail_unless(z80.op_call[0x6e].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_6Fh_LDLA_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x6f].size == 1);
   fail_unless(z80.op_call[0x6f].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_70h_LDHLB_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x70].size == 1);
   fail_unless(z80.op_call[0x70].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_71h_LDHLC_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x71].size == 1);
   fail_unless(z80.op_call[0x71].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_72h_LDHLD_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x72].size == 1);
   fail_unless(z80.op_call[0x72].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_73h_LDHLE_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x73].size == 1);
   fail_unless(z80.op_call[0x73].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_74h_LDHLH_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x74].size == 1);
   fail_unless(z80.op_call[0x74].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_75h_LDHLL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x75].size == 1);
   fail_unless(z80.op_call[0x75].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_76h_HALT_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x76].size == 1);
   fail_unless(z80.op_call[0x76].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_77h_LDHLA_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x77].size == 1);
   fail_unless(z80.op_call[0x77].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_78h_LDAB_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x78].size == 1);
   fail_unless(z80.op_call[0x78].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_79h_LDAC_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x79].size == 1);
   fail_unless(z80.op_call[0x79].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_7Ah_LDAD_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x7a].size == 1);
   fail_unless(z80.op_call[0x7a].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_7Bh_LDAE_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x7b].size == 1);
   fail_unless(z80.op_call[0x7b].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_7Ch_LDAH_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x7c].size == 1);
   fail_unless(z80.op_call[0x7c].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_7Dh_LDAL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x7d].size == 1);
   fail_unless(z80.op_call[0x7d].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_7Eh_LDAHL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x7e].size == 1);
   fail_unless(z80.op_call[0x7e].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_7Fh_LDAA_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x7f].size == 1);
   fail_unless(z80.op_call[0x7f].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_80h_ADDAB_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x80].size == 1);
   fail_unless(z80.op_call[0x80].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_81h_ADDAC_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x81].size == 1);
   fail_unless(z80.op_call[0x81].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_82h_ADDAD_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x82].size == 1);
   fail_unless(z80.op_call[0x82].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_83h_ADDAE_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x83].size == 1);
   fail_unless(z80.op_call[0x83].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_84h_ADDAH_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x84].size == 1);
   fail_unless(z80.op_call[0x84].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_85h_ADDAL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x85].size == 1);
   fail_unless(z80.op_call[0x85].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_86h_ADDAHL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x86].size == 1);
   fail_unless(z80.op_call[0x86].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_87h_ADDAA_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x87].size == 1);
   fail_unless(z80.op_call[0x87].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_88h_ADCAB_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x88].size == 1);
   fail_unless(z80.op_call[0x88].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_89h_ADCAC_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x89].size == 1);
   fail_unless(z80.op_call[0x89].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_8Ah_ADCAD_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x8a].size == 1);
   fail_unless(z80.op_call[0x8a].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_8Bh_ADCAE_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x8b].size == 1);
   fail_unless(z80.op_call[0x8b].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_8Ch_ADCAH_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x8c].size == 1);
   fail_unless(z80.op_call[0x8c].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_8Dh_ADCAL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x8d].size == 1);
   fail_unless(z80.op_call[0x8d].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_8Eh_ADCAHL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x8e].size == 1);
   fail_unless(z80.op_call[0x8e].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_8Fh_ADCAA_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x8f].size == 1);
   fail_unless(z80.op_call[0x8f].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_90h_SUBB_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x90].size == 1);
   fail_unless(z80.op_call[0x90].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_91h_SUBC_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x91].size == 1);
   fail_unless(z80.op_call[0x91].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_92h_SUBD_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x92].size == 1);
   fail_unless(z80.op_call[0x92].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_93h_SUBE_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x93].size == 1);
   fail_unless(z80.op_call[0x93].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_94h_SUBH_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x94].size == 1);
   fail_unless(z80.op_call[0x94].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_95h_SUBL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x95].size == 1);
   fail_unless(z80.op_call[0x95].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_96h_SUBHL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x96].size == 1);
   fail_unless(z80.op_call[0x96].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_97h_SUBA_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x97].size == 1);
   fail_unless(z80.op_call[0x97].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_98h_SBCAB_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x98].size == 1);
   fail_unless(z80.op_call[0x98].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_99h_SBCAC_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x99].size == 1);
   fail_unless(z80.op_call[0x99].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_9Ah_SBCAD_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x9a].size == 1);
   fail_unless(z80.op_call[0x9a].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_9Bh_SBCAE_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x9b].size == 1);
   fail_unless(z80.op_call[0x9b].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_9Ch_SBCAH_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x9c].size == 1);
   fail_unless(z80.op_call[0x9c].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_9Dh_SBCAL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x9d].size == 1);
   fail_unless(z80.op_call[0x9d].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_9Eh_SBCAHL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x9e].size == 1);
   fail_unless(z80.op_call[0x9e].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_9Fh_SBCAA_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0x9f].size == 1);
   fail_unless(z80.op_call[0x9f].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_A0h_ANDB_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xa0].size == 1);
   fail_unless(z80.op_call[0xa0].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_A1h_ANDC_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xa1].size == 1);
   fail_unless(z80.op_call[0xa1].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_A2h_ANDD_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xa2].size == 1);
   fail_unless(z80.op_call[0xa2].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_A3h_ANDE_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xa3].size == 1);
   fail_unless(z80.op_call[0xa3].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_A4h_ANDH_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xa4].size == 1);
   fail_unless(z80.op_call[0xa4].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_A5h_ANDL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xa5].size == 1);
   fail_unless(z80.op_call[0xa5].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_A6h_ANDHL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xa6].size == 1);
   fail_unless(z80.op_call[0xa6].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_A7h_ANDA_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xa7].size == 1);
   fail_unless(z80.op_call[0xa7].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_A8h_XORB_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xa8].size == 1);
   fail_unless(z80.op_call[0xa8].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_A9h_XORC_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xa9].size == 1);
   fail_unless(z80.op_call[0xa9].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_AAh_XORD_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xaa].size == 1);
   fail_unless(z80.op_call[0xaa].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_ABh_XORE_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xab].size == 1);
   fail_unless(z80.op_call[0xab].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_ACh_XORH_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xac].size == 1);
   fail_unless(z80.op_call[0xac].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_ADh_XORL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xad].size == 1);
   fail_unless(z80.op_call[0xad].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_AEh_XORHL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xae].size == 1);
   fail_unless(z80.op_call[0xae].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_AFh_XORA_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xaf].size == 1);
   fail_unless(z80.op_call[0xaf].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_B0h_ORB_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xb0].size == 1);
   fail_unless(z80.op_call[0xb0].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_B1h_ORC_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xb1].size == 1);
   fail_unless(z80.op_call[0xb1].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_B2h_ORD_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xb2].size == 1);
   fail_unless(z80.op_call[0xb2].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_B3h_ORE_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xb3].size == 1);
   fail_unless(z80.op_call[0xb3].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_B4h_ORH_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xb4].size == 1);
   fail_unless(z80.op_call[0xb4].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_B5h_ORL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xb5].size == 1);
   fail_unless(z80.op_call[0xb5].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_B6h_ORHL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xb6].size == 1);
   fail_unless(z80.op_call[0xb6].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_B7h_ORA_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xb7].size == 1);
   fail_unless(z80.op_call[0xb7].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_B8h_CPB_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xb8].size == 1);
   fail_unless(z80.op_call[0xb8].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_B9h_CPC_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xb9].size == 1);
   fail_unless(z80.op_call[0xb9].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_BAh_CPD_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xba].size == 1);
   fail_unless(z80.op_call[0xba].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_BBh_CPE_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xbb].size == 1);
   fail_unless(z80.op_call[0xbb].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_BCh_CPH_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xbc].size == 1);
   fail_unless(z80.op_call[0xbc].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_BDh_CPL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xbd].size == 1);
   fail_unless(z80.op_call[0xbd].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_BEh_CPHL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xbe].size == 1);
   fail_unless(z80.op_call[0xbe].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_BFh_CPA_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xbf].size == 1);
   fail_unless(z80.op_call[0xbf].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_C0h_RETNZ_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xc0].size == 1);
   fail_unless(z80.op_call[0xc0].ticks == 0);
}
END_TEST

START_TEST (test_check_OP_C1h_POPBC_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xc1].size == 1);
   fail_unless(z80.op_call[0xc1].ticks == 12);
}
END_TEST

START_TEST (test_check_OP_C2h_JPNZa16_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xc2].size == 3);
   fail_unless(z80.op_call[0xc2].ticks == 0);
}
END_TEST

START_TEST (test_check_OP_C3h_JPa16_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xc3].size == 3);
   fail_unless(z80.op_call[0xc3].ticks == 16);
}
END_TEST

START_TEST (test_check_OP_C4h_CALLNZa16_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xc4].size == 3);
   fail_unless(z80.op_call[0xc4].ticks == 0);
}
END_TEST

START_TEST (test_check_OP_C5h_PUSHBC_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xc5].size == 1);
   fail_unless(z80.op_call[0xc5].ticks == 16);
}
END_TEST

START_TEST (test_check_OP_C6h_ADDAd8_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xc6].size == 2);
   fail_unless(z80.op_call[0xc6].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_C7h_RST00H_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xc7].size == 1);
   fail_unless(z80.op_call[0xc7].ticks == 16);
}
END_TEST

START_TEST (test_check_OP_C8h_RETZ_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xc8].size == 1);
   fail_unless(z80.op_call[0xc8].ticks == 0);
}
END_TEST

START_TEST (test_check_OP_C9h_RET_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xc9].size == 1);
   fail_unless(z80.op_call[0xc9].ticks == 16);
}
END_TEST

START_TEST (test_check_OP_CAh_JPZa16_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xca].size == 3);
   fail_unless(z80.op_call[0xca].ticks == 0);
}
END_TEST

START_TEST (test_check_OP_CBh_PREFIXCB_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xcb].size == 1);
   fail_unless(z80.op_call[0xcb].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_CCh_CALLZa16_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xcc].size == 3);
   fail_unless(z80.op_call[0xcc].ticks == 0);
}
END_TEST

START_TEST (test_check_OP_CDh_CALLa16_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xcd].size == 3);
   fail_unless(z80.op_call[0xcd].ticks == 24);
}
END_TEST

START_TEST (test_check_OP_CEh_ADCAd8_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xce].size == 2);
   fail_unless(z80.op_call[0xce].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_CFh_RST08H_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xcf].size == 1);
   fail_unless(z80.op_call[0xcf].ticks == 16);
}
END_TEST

START_TEST (test_check_OP_D0h_RETNC_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xd0].size == 1);
   fail_unless(z80.op_call[0xd0].ticks == 0);
}
END_TEST

START_TEST (test_check_OP_D1h_POPDE_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xd1].size == 1);
   fail_unless(z80.op_call[0xd1].ticks == 12);
}
END_TEST

START_TEST (test_check_OP_D2h_JPNCa16_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xd2].size == 3);
   fail_unless(z80.op_call[0xd2].ticks == 0);
}
END_TEST

START_TEST (test_check_OP_D3h_INVALID_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xd3].size == 0);
   fail_unless(z80.op_call[0xd3].ticks == 0);
}
END_TEST

START_TEST (test_check_OP_D4h_CALLNCa16_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xd4].size == 3);
   fail_unless(z80.op_call[0xd4].ticks == 0);
}
END_TEST

START_TEST (test_check_OP_D5h_PUSHDE_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xd5].size == 1);
   fail_unless(z80.op_call[0xd5].ticks == 16);
}
END_TEST

START_TEST (test_check_OP_D6h_SUBd8_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xd6].size == 2);
   fail_unless(z80.op_call[0xd6].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_D7h_RST10H_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xd7].size == 1);
   fail_unless(z80.op_call[0xd7].ticks == 16);
}
END_TEST

START_TEST (test_check_OP_D8h_RETC_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xd8].size == 1);
   fail_unless(z80.op_call[0xd8].ticks == 0);
}
END_TEST

START_TEST (test_check_OP_D9h_RETI_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xd9].size == 1);
   fail_unless(z80.op_call[0xd9].ticks == 16);
}
END_TEST

START_TEST (test_check_OP_DAh_JPCa16_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xda].size == 3);
   fail_unless(z80.op_call[0xda].ticks == 0);
}
END_TEST

START_TEST (test_check_OP_DBh_INVALID_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xdb].size == 0);
   fail_unless(z80.op_call[0xdb].ticks == 0);
}
END_TEST

START_TEST (test_check_OP_DCh_CALLCa16_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xdc].size == 3);
   fail_unless(z80.op_call[0xdc].ticks == 0);
}
END_TEST

START_TEST (test_check_OP_DDh_INVALID_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xdd].size == 0);
   fail_unless(z80.op_call[0xdd].ticks == 0);
}
END_TEST

START_TEST (test_check_OP_DEh_SBCAd8_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xde].size == 2);
   fail_unless(z80.op_call[0xde].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_DFh_RST18H_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xdf].size == 1);
   fail_unless(z80.op_call[0xdf].ticks == 16);
}
END_TEST

START_TEST (test_check_OP_E0h_LDHa8A_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xe0].size == 2);
   fail_unless(z80.op_call[0xe0].ticks == 12);
}
END_TEST

START_TEST (test_check_OP_E1h_POPHL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xe1].size == 1);
   fail_unless(z80.op_call[0xe1].ticks == 12);
}
END_TEST

START_TEST (test_check_OP_E2h_LDHCA_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xe2].size == 2);
   fail_unless(z80.op_call[0xe2].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_E3h_INVALID_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xe3].size == 0);
   fail_unless(z80.op_call[0xe3].ticks == 0);
}
END_TEST

START_TEST (test_check_OP_E4h_INVALID_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xe4].size == 0);
   fail_unless(z80.op_call[0xe4].ticks == 0);
}
END_TEST

START_TEST (test_check_OP_E5h_PUSHHL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xe5].size == 1);
   fail_unless(z80.op_call[0xe5].ticks == 16);
}
END_TEST

START_TEST (test_check_OP_E6h_ANDd8_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xe6].size == 2);
   fail_unless(z80.op_call[0xe6].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_E7h_RST20H_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xe7].size == 1);
   fail_unless(z80.op_call[0xe7].ticks == 16);
}
END_TEST

START_TEST (test_check_OP_E8h_ADDSPd8_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xe8].size == 2);
   fail_unless(z80.op_call[0xe8].ticks == 16);
}
END_TEST

START_TEST (test_check_OP_E9h_JPHL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xe9].size == 1);
   fail_unless(z80.op_call[0xe9].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_EAh_LDnnA_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xea].size == 3);
   fail_unless(z80.op_call[0xea].ticks == 16);
}
END_TEST

START_TEST (test_check_OP_EBh_INVALID_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xeb].size == 0);
   fail_unless(z80.op_call[0xeb].ticks == 0);
}
END_TEST

START_TEST (test_check_OP_ECh_INVALID_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xec].size == 0);
   fail_unless(z80.op_call[0xec].ticks == 0);
}
END_TEST

START_TEST (test_check_OP_EDh_INVALID_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xed].size == 0);
   fail_unless(z80.op_call[0xed].ticks == 0);
}
END_TEST

START_TEST (test_check_OP_EEh_XORd8_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xee].size == 2);
   fail_unless(z80.op_call[0xee].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_EFh_RST28H_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xef].size == 1);
   fail_unless(z80.op_call[0xef].ticks == 16);
}
END_TEST

START_TEST (test_check_OP_F0h_LDHAd8_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xf0].size == 2);
   fail_unless(z80.op_call[0xf0].ticks == 12);
}
END_TEST

START_TEST (test_check_OP_F1h_POPAF_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xf1].size == 1);
   fail_unless(z80.op_call[0xf1].ticks == 12);
}
END_TEST

START_TEST (test_check_OP_F2h_LDAC_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xf2].size == 2);
   fail_unless(z80.op_call[0xf2].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_F3h_DI_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xf3].size == 1);
   fail_unless(z80.op_call[0xf3].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_F4h_INVALID_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xf4].size == 0);
   fail_unless(z80.op_call[0xf4].ticks == 0);
}
END_TEST

START_TEST (test_check_OP_F5h_PUSHAF_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xf5].size == 1);
   fail_unless(z80.op_call[0xf5].ticks == 16);
}
END_TEST

START_TEST (test_check_OP_F6h_ORd8_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xf6].size == 2);
   fail_unless(z80.op_call[0xf6].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_F7h_RST30H_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xf7].size == 1);
   fail_unless(z80.op_call[0xf7].ticks == 16);
}
END_TEST

START_TEST (test_check_OP_F8h_LDHLSPd8_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xf8].size == 2);
   fail_unless(z80.op_call[0xf8].ticks == 12);
}
END_TEST

START_TEST (test_check_OP_F9h_LDSPHL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xf9].size == 1);
   fail_unless(z80.op_call[0xf9].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_FAh_LDAa16_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xfa].size == 3);
   fail_unless(z80.op_call[0xfa].ticks == 16);
}
END_TEST

START_TEST (test_check_OP_FBh_EI_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xfb].size == 1);
   fail_unless(z80.op_call[0xfb].ticks == 4);
}
END_TEST

START_TEST (test_check_OP_FCh_INVALID_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xfc].size == 0);
   fail_unless(z80.op_call[0xfc].ticks == 0);
}
END_TEST

START_TEST (test_check_OP_FDh_INVALID_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xfd].size == 0);
   fail_unless(z80.op_call[0xfd].ticks == 0);
}
END_TEST

START_TEST (test_check_OP_FEh_CPd8_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xfe].size == 2);
   fail_unless(z80.op_call[0xfe].ticks == 8);
}
END_TEST

START_TEST (test_check_OP_FFh_RST38H_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   fail_unless(z80.op_call[0xff].size == 1);
   fail_unless(z80.op_call[0xff].ticks == 16);
}
END_TEST

// CB Prefix

START_TEST (test_check_CB_OP_00h_RLCB_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_01h_RLCC_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_02h_RLCD_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_03h_RLCE_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_04h_RLCH_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_05h_RLCL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_06h_RLCHL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_07h_RLCA_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_08h_RRCB_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_09h_RRCC_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_0Ah_RRCD_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_0Bh_RRCE_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_0Ch_RRCH_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_0Dh_RRCL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_0Eh_RRCHL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_0Fh_RRCA_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST


START_TEST (test_check_CB_OP_10h_RLB_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_11h_RLC_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_12h_RLD_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_13h_RLE_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_14h_RLH_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_15h_RLL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_16h_RLHL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_17h_RLA_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_18h_RRB_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_19h_RRC_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_1Ah_RRD_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_1Bh_RRE_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_1Ch_RRH_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_1Dh_RRL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_1Eh_RRHL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_1Fh_RRA_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST


START_TEST (test_check_CB_OP_20h_SLAB_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_21h_SLAC_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_22h_SLAD_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_23h_SLAE_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_24h_SLAH_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_25h_SLAL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_26h_SLAHL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_27h_SLAA_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_28h_SRAB_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_29h_SRAC_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_2Ah_SRAD_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_2Bh_SRAE_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_2Ch_SRAH_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_2Dh_SRAL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_2Eh_SRAHL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_2Fh_SRAA_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST


START_TEST (test_check_CB_OP_30h_SWAPB_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_31h_SWAPC_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_32h_SWAPD_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_33h_SWAPE_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_34h_SWAPH_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_35h_SWAPL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_36h_SWAPHL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_37h_SWAPA_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_38h_SRLB_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_39h_SRLC_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_3Ah_SRLD_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_3Bh_SRLE_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_3Ch_SRLH_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_3Dh_SRLL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_3Eh_SRLHL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_3Fh_SRLA_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST


START_TEST (test_check_CB_OP_40h_BIT0B_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_41h_BIT0C_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_42h_BIT0D_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_43h_BIT0E_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_44h_BIT0H_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_45h_BIT0L_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_46h_BIT0HL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_47h_BIT0A_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_48h_BIT1B_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_49h_BIT1C_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_4Ah_BIT1D_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_4Bh_BIT1E_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_4Ch_BIT1H_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_4Dh_BIT1L_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_4Eh_BIT1HL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_4Fh_BIT1A_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST


START_TEST (test_check_CB_OP_50h_BIT2B_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_51h_BIT2C_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_52h_BIT2D_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_53h_BIT2E_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_54h_BIT2H_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_55h_BIT2L_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_56h_BIT2HL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_57h_BIT2A_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_58h_BIT3B_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_59h_BIT3C_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_5Ah_BIT3D_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_5Bh_BIT3E_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_5Ch_BIT3H_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_5Dh_BIT3L_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_5Eh_BIT3HL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_5Fh_BIT3A_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST


START_TEST (test_check_CB_OP_60h_BIT4B_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_61h_BIT4C_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_62h_BIT4D_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_63h_BIT4E_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_64h_BIT4H_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_65h_BIT4L_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_66h_BIT4HL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_67h_BIT4A_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_68h_BIT5B_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_69h_BIT5C_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_6Ah_BIT5D_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_6Bh_BIT5E_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_6Ch_BIT5H_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_6Dh_BIT5L_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_6Eh_BIT5HL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_6Fh_BIT5A_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST


START_TEST (test_check_CB_OP_70h_BIT6B_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_71h_BIT6C_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_72h_BIT6D_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_73h_BIT6E_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_74h_BIT6H_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_75h_BIT6L_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_76h_BIT6HL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_77h_BIT6A_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_78h_BIT7B_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_79h_BIT7C_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_7Ah_BIT7D_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_7Bh_BIT7E_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_7Ch_BIT7H_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_7Dh_BIT7L_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_7Eh_BIT7HL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_7Fh_BIT7A_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST


START_TEST (test_check_CB_OP_80h_RES0B_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_81h_RES0C_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_82h_RES0D_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_83h_RES0E_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_84h_RES0H_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_85h_RES0L_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_86h_RES0HL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_87h_RES0A_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_88h_RES1B_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_89h_RES1C_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_8Ah_RES1D_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_8Bh_RES1E_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_8Ch_RES1H_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_8Dh_RES1L_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_8Eh_RES1HL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_8Fh_RES1A_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST


START_TEST (test_check_CB_OP_90h_RES2B_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_91h_RES2C_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_92h_RES2D_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_93h_RES2E_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_94h_RES2H_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_95h_RES2L_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_96h_RES2HL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_97h_RES2A_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_98h_RES3B_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_99h_RES3C_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_9Ah_RES3D_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_9Bh_RES3E_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_9Ch_RES3H_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_9Dh_RES3L_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_9Eh_RES3HL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_9Fh_RES3A_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST


START_TEST (test_check_CB_OP_A0h_RES4B_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_A1h_RES4C_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_A2h_RES4D_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_A3h_RES4E_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_A4h_RES4H_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_A5h_RES4L_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_A6h_RES4HL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_A7h_RES4A_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_A8h_RES5B_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_A9h_RES5C_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_AAh_RES5D_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_ABh_RES5E_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_ACh_RES5H_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_ADh_RES5L_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_AEh_RES5HL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_AFh_RES5A_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST


START_TEST (test_check_CB_OP_B0h_RES6B_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_B1h_RES6C_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_B2h_RES6D_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_B3h_RES6E_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_B4h_RES6H_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_B5h_RES6L_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_B6h_RES6HL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_B7h_RES6A_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_B8h_RES7B_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_B9h_RES7C_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_BAh_RES7D_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_BBh_RES7E_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_BCh_RES7H_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_BDh_RES7L_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_BEh_RES7HL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_BFh_RES7A_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST


START_TEST (test_check_CB_OP_C0h_SET0B_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_C1h_SET0C_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_C2h_SET0D_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_C3h_SET0E_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_C4h_SET0H_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_C5h_SET0L_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_C6h_SET0HL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_C7h_SET0A_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_C8h_SET1B_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_C9h_SET1C_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_CAh_SET1D_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_CBh_SET1E_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_CCh_SET1H_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_CDh_SET1L_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_CEh_SET1HL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_CFh_SET1A_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST


START_TEST (test_check_CB_OP_D0h_SET2B_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_D1h_SET2C_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_D2h_SET2D_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_D3h_SET2E_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_D4h_SET2H_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_D5h_SET2L_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_D6h_SET2HL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_D7h_SET2A_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_D8h_SET3B_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_D9h_SET3C_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_DAh_SET3D_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_DBh_SET3E_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_DCh_SET3H_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_DDh_SET3L_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_DEh_SET3HL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_DFh_SET3A_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST


START_TEST (test_check_CB_OP_E0h_SET4B_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_E1h_SET4C_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_E2h_SET4D_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_E3h_SET4E_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_E4h_SET4H_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_E5h_SET4L_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_E6h_SET4HL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_E7h_SET4A_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_E8h_SET5B_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_E9h_SET5C_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_EAh_SET5D_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_EBh_SET5E_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_ECh_SET5H_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_EDh_SET5L_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_EEh_SET5HL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_EFh_SET5A_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST


START_TEST (test_check_CB_OP_F0h_SET6B_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_F1h_SET6C_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_F2h_SET6D_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_F3h_SET6E_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_F4h_SET6H_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_F5h_SET6L_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_F6h_SET6HL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_F7h_SET6A_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_F8h_SET7B_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_F9h_SET7C_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_FAh_SET7D_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_FBh_SET7E_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_FCh_SET7H_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_FDh_SET7L_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_FEh_SET7HL_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

START_TEST (test_check_CB_OP_FFh_SET7A_attributes)
{
   Memory memory;
   Opcodes op;
   Opcodes cb_op;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers,&op,&cb_op);

   z80.op_call = z80.cb_op;

   fail_unless(z80.op_call[0x00].size == 2);
   fail_unless(z80.op_call[0x00].ticks == 8);
}
END_TEST

Suite * add_suite(void)
{
   Suite * s = suite_create("Add");

   /* Core test case */
   TCase *tc_core = tcase_create("Core");

   tcase_add_test(tc_core,test_check_OP_00h_NOP_attributes);
   tcase_add_test(tc_core,test_check_OP_00h_NOP_attributes);
   tcase_add_test(tc_core,test_check_OP_01h_LDBCa16_attributes);
   tcase_add_test(tc_core,test_check_OP_02h_LDBCA_attributes);
   tcase_add_test(tc_core,test_check_OP_03h_INCBC_attributes);
   tcase_add_test(tc_core,test_check_OP_04h_INCB_attributes);
   tcase_add_test(tc_core,test_check_OP_05h_DECB_attributes);
   tcase_add_test(tc_core,test_check_OP_06h_LDBd8_attributes);
   tcase_add_test(tc_core,test_check_OP_07h_RLCA_attributes);
   tcase_add_test(tc_core,test_check_OP_08h_LDnnSP_attributes);
   tcase_add_test(tc_core,test_check_OP_09h_ADDHLBC_attributes);
   tcase_add_test(tc_core,test_check_OP_0Ah_LDABC_attributes);
   tcase_add_test(tc_core,test_check_OP_0Bh_DECBC_attributes);
   tcase_add_test(tc_core,test_check_OP_0Ch_INCC_attributes);
   tcase_add_test(tc_core,test_check_OP_0Dh_DECC_attributes);
   tcase_add_test(tc_core,test_check_OP_0Eh_LDCd8_attributes);
   tcase_add_test(tc_core,test_check_OP_0Fh_RRCA_attributes);

   tcase_add_test(tc_core,test_check_OP_10h_STOP0_attributes);
   tcase_add_test(tc_core,test_check_OP_11h_LDDEa16_attributes);
   tcase_add_test(tc_core,test_check_OP_12h_LDDEA_attributes);
   tcase_add_test(tc_core,test_check_OP_13h_INCDE_attributes);
   tcase_add_test(tc_core,test_check_OP_14h_INCD_attributes);
   tcase_add_test(tc_core,test_check_OP_15h_DECD_attributes);
   tcase_add_test(tc_core,test_check_OP_16h_LDd8_attributes);
   tcase_add_test(tc_core,test_check_OP_17h_RLA_attributes);
   tcase_add_test(tc_core,test_check_OP_18h_JRd8_attributes);
   tcase_add_test(tc_core,test_check_OP_19h_ADDHLDE_attributes);
   tcase_add_test(tc_core,test_check_OP_1Ah_LDADE_attributes);
   tcase_add_test(tc_core,test_check_OP_1Bh_DECDE_attributes);
   tcase_add_test(tc_core,test_check_OP_1Ch_INCE_attributes);
   tcase_add_test(tc_core,test_check_OP_1Dh_DECE_attributes);
   tcase_add_test(tc_core,test_check_OP_1Eh_LDEd8_attributes);
   tcase_add_test(tc_core,test_check_OP_1Fh_RRA_attributes);

   tcase_add_test(tc_core,test_check_OP_20h_JRNZr8_attributes);
   tcase_add_test(tc_core,test_check_OP_21h_LDHLd16_attributes);
   tcase_add_test(tc_core,test_check_OP_22h_LDIHLA_attributes);
   tcase_add_test(tc_core,test_check_OP_23h_INCHL_attributes);
   tcase_add_test(tc_core,test_check_OP_24h_INCH_attributes);
   tcase_add_test(tc_core,test_check_OP_25h_DECH_attributes);
   tcase_add_test(tc_core,test_check_OP_26h_LDHd8_attributes);
   tcase_add_test(tc_core,test_check_OP_27h_DAA_attributes);
   tcase_add_test(tc_core,test_check_OP_28h_JRZd8_attributes);
   tcase_add_test(tc_core,test_check_OP_29h_ADDHLHL_attributes);
   tcase_add_test(tc_core,test_check_OP_2Ah_LDIAHL_attributes);
   tcase_add_test(tc_core,test_check_OP_2Bh_DECHL_attributes);
   tcase_add_test(tc_core,test_check_OP_2Ch_INCL_attributes);
   tcase_add_test(tc_core,test_check_OP_2Dh_DECL_attributes);
   tcase_add_test(tc_core,test_check_OP_2Eh_LDLd8_attributes);
   tcase_add_test(tc_core,test_check_OP_2Fh_CPL_attributes);

   tcase_add_test(tc_core,test_check_OP_30h_JRNCd8_attributes);
   tcase_add_test(tc_core,test_check_OP_31h_LDSPd16_attributes);
   tcase_add_test(tc_core,test_check_OP_32h_LDDHLA_attributes);
   tcase_add_test(tc_core,test_check_OP_33h_INCSP_attributes);
   tcase_add_test(tc_core,test_check_OP_34h_INCHL_attributes);
   tcase_add_test(tc_core,test_check_OP_35h_DECHL_attributes);
   tcase_add_test(tc_core,test_check_OP_36h_LDHLd8_attributes);
   tcase_add_test(tc_core,test_check_OP_37h_SCF_attributes);
   tcase_add_test(tc_core,test_check_OP_38h_JRCd8_attributes);
   tcase_add_test(tc_core,test_check_OP_39h_ADDHLSP_attributes);
   tcase_add_test(tc_core,test_check_OP_3Ah_LDDAHL_attributes);
   tcase_add_test(tc_core,test_check_OP_3Bh_DECSP_attributes);
   tcase_add_test(tc_core,test_check_OP_3Ch_INCA_attributes);
   tcase_add_test(tc_core,test_check_OP_3Dh_DECA_attributes);
   tcase_add_test(tc_core,test_check_OP_3Eh_LDAd8_attributes);
   tcase_add_test(tc_core,test_check_OP_3Fh_CCF_attributes);

   tcase_add_test(tc_core,test_check_OP_40h_LDBB_attributes);
   tcase_add_test(tc_core,test_check_OP_41h_LDBC_attributes);
   tcase_add_test(tc_core,test_check_OP_42h_LDBD_attributes);
   tcase_add_test(tc_core,test_check_OP_43h_LDBE_attributes);
   tcase_add_test(tc_core,test_check_OP_44h_LDBH_attributes);
   tcase_add_test(tc_core,test_check_OP_45h_LDBL_attributes);
   tcase_add_test(tc_core,test_check_OP_46h_LDBHL_attributes);
   tcase_add_test(tc_core,test_check_OP_47h_LDBA_attributes);
   tcase_add_test(tc_core,test_check_OP_48h_LDCB_attributes);
   tcase_add_test(tc_core,test_check_OP_49h_LDC_attributes);
   tcase_add_test(tc_core,test_check_OP_4Ah_LDCD_attributes);
   tcase_add_test(tc_core,test_check_OP_4Bh_LDCE_attributes);
   tcase_add_test(tc_core,test_check_OP_4Ch_LDCH_attributes);
   tcase_add_test(tc_core,test_check_OP_4Dh_LDCL_attributes);
   tcase_add_test(tc_core,test_check_OP_4Eh_LDCHL_attributes);
   tcase_add_test(tc_core,test_check_OP_4Fh_LDCA_attributes);

   tcase_add_test(tc_core,test_check_OP_50h_LDDB_attributes);
   tcase_add_test(tc_core,test_check_OP_51h_LDDC_attributes);
   tcase_add_test(tc_core,test_check_OP_52h_LDDD_attributes);
   tcase_add_test(tc_core,test_check_OP_53h_LDDE_attributes);
   tcase_add_test(tc_core,test_check_OP_54h_LDDH_attributes);
   tcase_add_test(tc_core,test_check_OP_55h_LDDL_attributes);
   tcase_add_test(tc_core,test_check_OP_56h_LDDHL_attributes);
   tcase_add_test(tc_core,test_check_OP_57h_LDDA_attributes);
   tcase_add_test(tc_core,test_check_OP_58h_LDEB_attributes);
   tcase_add_test(tc_core,test_check_OP_59h_LDEC_attributes);
   tcase_add_test(tc_core,test_check_OP_5Ah_LDED_attributes);
   tcase_add_test(tc_core,test_check_OP_5Bh_LDEE_attributes);
   tcase_add_test(tc_core,test_check_OP_5Ch_LDEH_attributes);
   tcase_add_test(tc_core,test_check_OP_5Dh_LDEL_attributes);
   tcase_add_test(tc_core,test_check_OP_5Eh_LDEHL_attributes);
   tcase_add_test(tc_core,test_check_OP_5Fh_LDEA_attributes);

   tcase_add_test(tc_core,test_check_OP_60h_LDHB_attributes);
   tcase_add_test(tc_core,test_check_OP_61h_LDHC_attributes);
   tcase_add_test(tc_core,test_check_OP_62h_LDHD_attributes);
   tcase_add_test(tc_core,test_check_OP_63h_LDHE_attributes);
   tcase_add_test(tc_core,test_check_OP_64h_LDHH_attributes);
   tcase_add_test(tc_core,test_check_OP_65h_LDHL_attributes);
   tcase_add_test(tc_core,test_check_OP_66h_LDHHL_attributes);
   tcase_add_test(tc_core,test_check_OP_67h_LDHA_attributes);
   tcase_add_test(tc_core,test_check_OP_68h_LDLB_attributes);
   tcase_add_test(tc_core,test_check_OP_69h_LDLC_attributes);
   tcase_add_test(tc_core,test_check_OP_6Ah_LDLD_attributes);
   tcase_add_test(tc_core,test_check_OP_6Bh_LDLE_attributes);
   tcase_add_test(tc_core,test_check_OP_6Ch_LDLH_attributes);
   tcase_add_test(tc_core,test_check_OP_6Dh_LDLL_attributes);
   tcase_add_test(tc_core,test_check_OP_6Eh_LDLHL_attributes);
   tcase_add_test(tc_core,test_check_OP_6Fh_LDLA_attributes);

   tcase_add_test(tc_core,test_check_OP_70h_LDHLB_attributes);
   tcase_add_test(tc_core,test_check_OP_71h_LDHLC_attributes);
   tcase_add_test(tc_core,test_check_OP_72h_LDHLD_attributes);
   tcase_add_test(tc_core,test_check_OP_73h_LDHLE_attributes);
   tcase_add_test(tc_core,test_check_OP_74h_LDHLH_attributes);
   tcase_add_test(tc_core,test_check_OP_75h_LDHLL_attributes);
   tcase_add_test(tc_core,test_check_OP_76h_HALT_attributes);
   tcase_add_test(tc_core,test_check_OP_77h_LDHLA_attributes);
   tcase_add_test(tc_core,test_check_OP_78h_LDAB_attributes);
   tcase_add_test(tc_core,test_check_OP_79h_LDAC_attributes);
   tcase_add_test(tc_core,test_check_OP_7Ah_LDAD_attributes);
   tcase_add_test(tc_core,test_check_OP_7Bh_LDAE_attributes);
   tcase_add_test(tc_core,test_check_OP_7Ch_LDAH_attributes);
   tcase_add_test(tc_core,test_check_OP_7Dh_LDAL_attributes);
   tcase_add_test(tc_core,test_check_OP_7Eh_LDAHL_attributes);
   tcase_add_test(tc_core,test_check_OP_7Fh_LDAA_attributes);

   tcase_add_test(tc_core,test_check_OP_80h_ADDAB_attributes);
   tcase_add_test(tc_core,test_check_OP_81h_ADDAC_attributes);
   tcase_add_test(tc_core,test_check_OP_82h_ADDAD_attributes);
   tcase_add_test(tc_core,test_check_OP_83h_ADDAE_attributes);
   tcase_add_test(tc_core,test_check_OP_84h_ADDAH_attributes);
   tcase_add_test(tc_core,test_check_OP_85h_ADDAL_attributes);
   tcase_add_test(tc_core,test_check_OP_86h_ADDAHL_attributes);
   tcase_add_test(tc_core,test_check_OP_87h_ADDAA_attributes);
   tcase_add_test(tc_core,test_check_OP_88h_ADCAB_attributes);
   tcase_add_test(tc_core,test_check_OP_89h_ADCAC_attributes);
   tcase_add_test(tc_core,test_check_OP_8Ah_ADCAD_attributes);
   tcase_add_test(tc_core,test_check_OP_8Bh_ADCAE_attributes);
   tcase_add_test(tc_core,test_check_OP_8Ch_ADCAH_attributes);
   tcase_add_test(tc_core,test_check_OP_8Dh_ADCAL_attributes);
   tcase_add_test(tc_core,test_check_OP_8Eh_ADCAHL_attributes);
   tcase_add_test(tc_core,test_check_OP_8Fh_ADCAA_attributes);

   tcase_add_test(tc_core,test_check_OP_90h_SUBB_attributes);
   tcase_add_test(tc_core,test_check_OP_91h_SUBC_attributes);
   tcase_add_test(tc_core,test_check_OP_92h_SUBD_attributes);
   tcase_add_test(tc_core,test_check_OP_93h_SUBE_attributes);
   tcase_add_test(tc_core,test_check_OP_94h_SUBH_attributes);
   tcase_add_test(tc_core,test_check_OP_95h_SUBL_attributes);
   tcase_add_test(tc_core,test_check_OP_96h_SUBHL_attributes);
   tcase_add_test(tc_core,test_check_OP_97h_SUBA_attributes);
   tcase_add_test(tc_core,test_check_OP_98h_SBCAB_attributes);
   tcase_add_test(tc_core,test_check_OP_99h_SBCAC_attributes);
   tcase_add_test(tc_core,test_check_OP_9Ah_SBCAD_attributes);
   tcase_add_test(tc_core,test_check_OP_9Bh_SBCAE_attributes);
   tcase_add_test(tc_core,test_check_OP_9Ch_SBCAH_attributes);
   tcase_add_test(tc_core,test_check_OP_9Dh_SBCAL_attributes);
   tcase_add_test(tc_core,test_check_OP_9Eh_SBCAHL_attributes);
   tcase_add_test(tc_core,test_check_OP_9Fh_SBCAA_attributes);

   tcase_add_test(tc_core,test_check_OP_A0h_ANDB_attributes);
   tcase_add_test(tc_core,test_check_OP_A1h_ANDC_attributes);
   tcase_add_test(tc_core,test_check_OP_A2h_ANDD_attributes);
   tcase_add_test(tc_core,test_check_OP_A3h_ANDE_attributes);
   tcase_add_test(tc_core,test_check_OP_A4h_ANDH_attributes);
   tcase_add_test(tc_core,test_check_OP_A5h_ANDL_attributes);
   tcase_add_test(tc_core,test_check_OP_A6h_ANDHL_attributes);
   tcase_add_test(tc_core,test_check_OP_A7h_ANDA_attributes);
   tcase_add_test(tc_core,test_check_OP_A8h_XORB_attributes);
   tcase_add_test(tc_core,test_check_OP_A9h_XORC_attributes);
   tcase_add_test(tc_core,test_check_OP_AAh_XORD_attributes);
   tcase_add_test(tc_core,test_check_OP_ABh_XORE_attributes);
   tcase_add_test(tc_core,test_check_OP_ACh_XORH_attributes);
   tcase_add_test(tc_core,test_check_OP_ADh_XORL_attributes);
   tcase_add_test(tc_core,test_check_OP_AEh_XORHL_attributes);
   tcase_add_test(tc_core,test_check_OP_AFh_XORA_attributes);

   tcase_add_test(tc_core,test_check_OP_B0h_ORB_attributes);
   tcase_add_test(tc_core,test_check_OP_B1h_ORC_attributes);
   tcase_add_test(tc_core,test_check_OP_B2h_ORD_attributes);
   tcase_add_test(tc_core,test_check_OP_B3h_ORE_attributes);
   tcase_add_test(tc_core,test_check_OP_B4h_ORH_attributes);
   tcase_add_test(tc_core,test_check_OP_B5h_ORL_attributes);
   tcase_add_test(tc_core,test_check_OP_B6h_ORHL_attributes);
   tcase_add_test(tc_core,test_check_OP_B7h_ORA_attributes);
   tcase_add_test(tc_core,test_check_OP_B8h_CPB_attributes);
   tcase_add_test(tc_core,test_check_OP_B9h_CPC_attributes);
   tcase_add_test(tc_core,test_check_OP_BAh_CPD_attributes);
   tcase_add_test(tc_core,test_check_OP_BBh_CPE_attributes);
   tcase_add_test(tc_core,test_check_OP_BCh_CPH_attributes);
   tcase_add_test(tc_core,test_check_OP_BDh_CPL_attributes);
   tcase_add_test(tc_core,test_check_OP_BEh_CPHL_attributes);
   tcase_add_test(tc_core,test_check_OP_BFh_CPA_attributes);

   tcase_add_test(tc_core,test_check_OP_C0h_RETNZ_attributes);
   tcase_add_test(tc_core,test_check_OP_C1h_POPBC_attributes);
   tcase_add_test(tc_core,test_check_OP_C2h_JPNZa16_attributes);
   tcase_add_test(tc_core,test_check_OP_C3h_JPa16_attributes);
   tcase_add_test(tc_core,test_check_OP_C4h_CALLNZa16_attributes);
   tcase_add_test(tc_core,test_check_OP_C5h_PUSHBC_attributes);
   tcase_add_test(tc_core,test_check_OP_C6h_ADDAd8_attributes);
   tcase_add_test(tc_core,test_check_OP_C7h_RST00H_attributes);
   tcase_add_test(tc_core,test_check_OP_C8h_RETZ_attributes);
   tcase_add_test(tc_core,test_check_OP_C9h_RET_attributes);
   tcase_add_test(tc_core,test_check_OP_CAh_JPZa16_attributes);
   tcase_add_test(tc_core,test_check_OP_CBh_PREFIXCB_attributes);
   tcase_add_test(tc_core,test_check_OP_CCh_CALLZa16_attributes);
   tcase_add_test(tc_core,test_check_OP_CDh_CALLa16_attributes);
   tcase_add_test(tc_core,test_check_OP_CEh_ADCAd8_attributes);
   tcase_add_test(tc_core,test_check_OP_CFh_RST08H_attributes);

   tcase_add_test(tc_core,test_check_OP_D0h_RETNC_attributes);
   tcase_add_test(tc_core,test_check_OP_D1h_POPDE_attributes);
   tcase_add_test(tc_core,test_check_OP_D2h_JPNCa16_attributes);
   tcase_add_test(tc_core,test_check_OP_D3h_INVALID_attributes);
   tcase_add_test(tc_core,test_check_OP_D4h_CALLNCa16_attributes);
   tcase_add_test(tc_core,test_check_OP_D5h_PUSHDE_attributes);
   tcase_add_test(tc_core,test_check_OP_D6h_SUBd8_attributes);
   tcase_add_test(tc_core,test_check_OP_D7h_RST10H_attributes);
   tcase_add_test(tc_core,test_check_OP_D8h_RETC_attributes);
   tcase_add_test(tc_core,test_check_OP_D9h_RETI_attributes);
   tcase_add_test(tc_core,test_check_OP_DAh_JPCa16_attributes);
   tcase_add_test(tc_core,test_check_OP_DBh_INVALID_attributes);
   tcase_add_test(tc_core,test_check_OP_DCh_CALLCa16_attributes);
   tcase_add_test(tc_core,test_check_OP_DDh_INVALID_attributes);
   tcase_add_test(tc_core,test_check_OP_DEh_SBCAd8_attributes);
   tcase_add_test(tc_core,test_check_OP_DFh_RST18H_attributes);

   tcase_add_test(tc_core,test_check_OP_E0h_LDHa8A_attributes);
   tcase_add_test(tc_core,test_check_OP_E1h_POPHL_attributes);
   tcase_add_test(tc_core,test_check_OP_E2h_LDHCA_attributes);
   tcase_add_test(tc_core,test_check_OP_E3h_INVALID_attributes);
   tcase_add_test(tc_core,test_check_OP_E4h_INVALID_attributes);
   tcase_add_test(tc_core,test_check_OP_E5h_PUSHHL_attributes);
   tcase_add_test(tc_core,test_check_OP_E6h_ANDd8_attributes);
   tcase_add_test(tc_core,test_check_OP_E7h_RST20H_attributes);
   tcase_add_test(tc_core,test_check_OP_E8h_ADDSPd8_attributes);
   tcase_add_test(tc_core,test_check_OP_E9h_JPHL_attributes);
   tcase_add_test(tc_core,test_check_OP_EAh_LDnnA_attributes);
   tcase_add_test(tc_core,test_check_OP_EBh_INVALID_attributes);
   tcase_add_test(tc_core,test_check_OP_ECh_INVALID_attributes);
   tcase_add_test(tc_core,test_check_OP_EDh_INVALID_attributes);
   tcase_add_test(tc_core,test_check_OP_EEh_XORd8_attributes);
   tcase_add_test(tc_core,test_check_OP_EFh_RST28H_attributes);

   tcase_add_test(tc_core,test_check_OP_F0h_LDHAd8_attributes);
   tcase_add_test(tc_core,test_check_OP_F1h_POPAF_attributes);
   tcase_add_test(tc_core,test_check_OP_F2h_LDAC_attributes);
   tcase_add_test(tc_core,test_check_OP_F3h_DI_attributes);
   tcase_add_test(tc_core,test_check_OP_F4h_INVALID_attributes);
   tcase_add_test(tc_core,test_check_OP_F5h_PUSHAF_attributes);
   tcase_add_test(tc_core,test_check_OP_F6h_ORd8_attributes);
   tcase_add_test(tc_core,test_check_OP_F7h_RST30H_attributes);
   tcase_add_test(tc_core,test_check_OP_F8h_LDHLSPd8_attributes);
   tcase_add_test(tc_core,test_check_OP_F9h_LDSPHL_attributes);
   tcase_add_test(tc_core,test_check_OP_FAh_LDAa16_attributes);
   tcase_add_test(tc_core,test_check_OP_FBh_EI_attributes);
   tcase_add_test(tc_core,test_check_OP_FCh_INVALID_attributes);
   tcase_add_test(tc_core,test_check_OP_FDh_INVALID_attributes);
   tcase_add_test(tc_core,test_check_OP_FEh_CPd8_attributes);
   tcase_add_test(tc_core,test_check_OP_FFh_RST38H_attributes);

// CB Prefix

   tcase_add_test(tc_core,test_check_CB_OP_00h_RLCB_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_01h_RLCC_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_02h_RLCD_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_03h_RLCE_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_04h_RLCH_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_05h_RLCL_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_06h_RLCHL_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_07h_RLCA_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_08h_RRCB_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_09h_RRCC_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_0Ah_RRCD_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_0Bh_RRCE_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_0Ch_RRCH_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_0Dh_RRCL_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_0Eh_RRCHL_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_0Fh_RRCA_attributes);

   tcase_add_test(tc_core,test_check_CB_OP_10h_RLB_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_11h_RLC_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_12h_RLD_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_13h_RLE_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_14h_RLH_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_15h_RLL_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_16h_RLHL_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_17h_RLA_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_18h_RRB_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_19h_RRC_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_1Ah_RRD_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_1Bh_RRE_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_1Ch_RRH_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_1Dh_RRL_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_1Eh_RRHL_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_1Fh_RRA_attributes);

   tcase_add_test(tc_core,test_check_CB_OP_20h_SLAB_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_21h_SLAC_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_22h_SLAD_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_23h_SLAE_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_24h_SLAH_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_25h_SLAL_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_26h_SLAHL_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_27h_SLAA_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_28h_SRAB_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_29h_SRAC_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_2Ah_SRAD_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_2Bh_SRAE_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_2Ch_SRAH_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_2Dh_SRAL_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_2Eh_SRAHL_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_2Fh_SRAA_attributes);

   tcase_add_test(tc_core,test_check_CB_OP_30h_SWAPB_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_31h_SWAPC_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_32h_SWAPD_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_33h_SWAPE_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_34h_SWAPH_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_35h_SWAPL_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_36h_SWAPHL_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_37h_SWAPA_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_38h_SRLB_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_39h_SRLC_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_3Ah_SRLD_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_3Bh_SRLE_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_3Ch_SRLH_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_3Dh_SRLL_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_3Eh_SRLHL_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_3Fh_SRLA_attributes);

   tcase_add_test(tc_core,test_check_CB_OP_40h_BIT0B_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_41h_BIT0C_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_42h_BIT0D_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_43h_BIT0E_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_44h_BIT0H_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_45h_BIT0L_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_46h_BIT0HL_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_47h_BIT0A_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_48h_BIT1B_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_49h_BIT1C_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_4Ah_BIT1D_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_4Bh_BIT1E_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_4Ch_BIT1H_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_4Dh_BIT1L_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_4Eh_BIT1HL_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_4Fh_BIT1A_attributes);

   tcase_add_test(tc_core,test_check_CB_OP_50h_BIT2B_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_51h_BIT2C_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_52h_BIT2D_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_53h_BIT2E_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_54h_BIT2H_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_55h_BIT2L_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_56h_BIT2HL_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_57h_BIT2A_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_58h_BIT3B_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_59h_BIT3C_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_5Ah_BIT3D_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_5Bh_BIT3E_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_5Ch_BIT3H_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_5Dh_BIT3L_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_5Eh_BIT3HL_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_5Fh_BIT3A_attributes);

   tcase_add_test(tc_core,test_check_CB_OP_60h_BIT4B_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_61h_BIT4C_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_62h_BIT4D_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_63h_BIT4E_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_64h_BIT4H_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_65h_BIT4L_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_66h_BIT4HL_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_67h_BIT4A_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_68h_BIT5B_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_69h_BIT5C_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_6Ah_BIT5D_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_6Bh_BIT5E_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_6Ch_BIT5H_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_6Dh_BIT5L_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_6Eh_BIT5HL_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_6Fh_BIT5A_attributes);

   tcase_add_test(tc_core,test_check_CB_OP_70h_BIT6B_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_71h_BIT6C_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_72h_BIT6D_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_73h_BIT6E_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_74h_BIT6H_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_75h_BIT6L_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_76h_BIT6HL_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_77h_BIT6A_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_78h_BIT7B_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_79h_BIT7C_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_7Ah_BIT7D_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_7Bh_BIT7E_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_7Ch_BIT7H_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_7Dh_BIT7L_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_7Eh_BIT7HL_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_7Fh_BIT7A_attributes);

   tcase_add_test(tc_core,test_check_CB_OP_80h_RES0B_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_81h_RES0C_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_82h_RES0D_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_83h_RES0E_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_84h_RES0H_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_85h_RES0L_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_86h_RES0HL_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_87h_RES0A_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_88h_RES1B_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_89h_RES1C_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_8Ah_RES1D_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_8Bh_RES1E_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_8Ch_RES1H_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_8Dh_RES1L_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_8Eh_RES1HL_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_8Fh_RES1A_attributes);

   tcase_add_test(tc_core,test_check_CB_OP_90h_RES2B_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_91h_RES2C_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_92h_RES2D_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_93h_RES2E_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_94h_RES2H_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_95h_RES2L_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_96h_RES2HL_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_97h_RES2A_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_98h_RES3B_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_99h_RES3C_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_9Ah_RES3D_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_9Bh_RES3E_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_9Ch_RES3H_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_9Dh_RES3L_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_9Eh_RES3HL_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_9Fh_RES3A_attributes);

   tcase_add_test(tc_core,test_check_CB_OP_A0h_RES4B_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_A1h_RES4C_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_A2h_RES4D_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_A3h_RES4E_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_A4h_RES4H_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_A5h_RES4L_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_A6h_RES4HL_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_A7h_RES4A_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_A8h_RES5B_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_A9h_RES5C_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_AAh_RES5D_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_ABh_RES5E_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_ACh_RES5H_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_ADh_RES5L_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_AEh_RES5HL_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_AFh_RES5A_attributes);

   tcase_add_test(tc_core,test_check_CB_OP_B0h_RES6B_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_B1h_RES6C_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_B2h_RES6D_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_B3h_RES6E_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_B4h_RES6H_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_B5h_RES6L_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_B6h_RES6HL_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_B7h_RES6A_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_B8h_RES7B_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_B9h_RES7C_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_BAh_RES7D_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_BBh_RES7E_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_BCh_RES7H_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_BDh_RES7L_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_BEh_RES7HL_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_BFh_RES7A_attributes);

   tcase_add_test(tc_core,test_check_CB_OP_C0h_SET0B_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_C1h_SET0C_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_C2h_SET0D_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_C3h_SET0E_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_C4h_SET0H_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_C5h_SET0L_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_C6h_SET0HL_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_C7h_SET0A_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_C8h_SET1B_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_C9h_SET1C_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_CAh_SET1D_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_CBh_SET1E_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_CCh_SET1H_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_CDh_SET1L_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_CEh_SET1HL_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_CFh_SET1A_attributes);

   tcase_add_test(tc_core,test_check_CB_OP_D0h_SET2B_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_D1h_SET2C_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_D2h_SET2D_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_D3h_SET2E_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_D4h_SET2H_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_D5h_SET2L_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_D6h_SET2HL_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_D7h_SET2A_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_D8h_SET3B_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_D9h_SET3C_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_DAh_SET3D_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_DBh_SET3E_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_DCh_SET3H_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_DDh_SET3L_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_DEh_SET3HL_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_DFh_SET3A_attributes);

   tcase_add_test(tc_core,test_check_CB_OP_E0h_SET4B_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_E1h_SET4C_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_E2h_SET4D_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_E3h_SET4E_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_E4h_SET4H_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_E5h_SET4L_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_E6h_SET4HL_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_E7h_SET4A_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_E8h_SET5B_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_E9h_SET5C_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_EAh_SET5D_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_EBh_SET5E_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_ECh_SET5H_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_EDh_SET5L_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_EEh_SET5HL_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_EFh_SET5A_attributes);

   tcase_add_test(tc_core,test_check_CB_OP_F0h_SET6B_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_F1h_SET6C_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_F2h_SET6D_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_F3h_SET6E_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_F4h_SET6H_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_F5h_SET6L_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_F6h_SET6HL_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_F7h_SET6A_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_F8h_SET7B_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_F9h_SET7C_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_FAh_SET7D_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_FBh_SET7E_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_FCh_SET7H_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_FDh_SET7L_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_FEh_SET7HL_attributes);
   tcase_add_test(tc_core,test_check_CB_OP_FFh_SET7A_attributes);

   suite_add_tcase(s,tc_core);

   return s;
}

int main(void)
{
   int number_failed;
   Suite *s = add_suite();
   SRunner *sr = srunner_create(s);
   srunner_run_all(sr, CK_NORMAL);
   number_failed = srunner_ntests_failed(sr);
   srunner_free(sr);
   return (number_failed == 0) ? 0 : 1;
}
