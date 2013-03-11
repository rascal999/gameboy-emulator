/*
 * =====================================================================================
 *
 *       Filename:  opcode_wrappers.c
 *
 *    Description:  Opcode function wrappers which are pointed to by Opcode struct, call.
 *
 *        Version:  1.0
 *        Created:  07/02/13 13:59:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aidan Marlin (aidan.marlin+github@gmail.com), 
 *   Organization:  
 *
 * =====================================================================================
 */

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

int OP_not_implemented(Memory * memory, Z80 * z80)
{
   printf("This opcode has not been implemented\n");
   fflush(stdout);

   return 1;
}

int OP_invalid(Memory * memory, Z80 * z80)
{
   printf("This opcode is invalid\n");
   fflush(stdout);

   return 2;
}

int OP_00h_NOP_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_00h_NOP(memory,z80);

   return retValue;
}

int OP_01h_LDBCa16_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_01h_LDBCd16(memory,z80);

   return retValue;
}

int OP_02h_LDBCA_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_02h_LDBCA(memory,z80);

   return retValue;
}

int OP_03h_INCBC_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_03h_INCBC(memory,z80);

   return retValue;
}

int OP_04h_INCB_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_INCX(memory,z80,(uint8_t) 0x1);

   return retValue;
}

int OP_05h_DECB_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_DECX(memory,z80,0x1);

   return retValue;
}

int OP_06h_LDBd8_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_LDXd8(memory,z80,0x1);

   return retValue;
}

int OP_07h_RLCA_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_07h_RLCA(memory,z80);

   return retValue;
}

int OP_08h_LDnnSP_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_08h_LDnnSP(memory,z80);

   return retValue;
}

int OP_09h_ADDHLBC_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_09h_ADDHLBC(memory,z80);

   return retValue;
}

int OP_0Ah_LDABC_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_0Ah_LDABC(memory,z80);

   return retValue;
}

int OP_0Bh_DECBC_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_0Bh_DECBC(memory,z80);

   return retValue;
}

int OP_0Ch_INCC_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_INCX(memory,z80,(uint8_t) 0x2);

   return retValue;
}

int OP_0Dh_DECC_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_DECX(memory,z80,0x2);

   return retValue;
}

int OP_0Eh_LDCd8_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_LDXd8(memory,z80,(uint8_t) 0x2);

   return retValue;
}

int OP_0Fh_RRCA_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_0Fh_RRCA(memory,z80);

   return retValue;
}


int OP_10h_STOP0_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_10h_STOP0(memory,z80);

   return retValue;
}

int OP_11h_LDDEa16_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_LDXd16(memory,z80,0x3);

   return retValue;
}

int OP_12h_LDDEA_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_12h_LDDEA(memory,z80);

   return retValue;
}

int OP_13h_INCDE_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_13h_INCDE(memory,z80);

   return retValue;
}

int OP_14h_INCD_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_14h_INCD(memory,z80);

   return retValue;
}

int OP_15h_DECD_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_15h_DECD(memory,z80);

   return retValue;
}

int OP_16h_LDd8_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_16h_LDd8(memory,z80);

   return retValue;
}

int OP_17h_RLA_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_RLX(memory,z80,0x0);

   return retValue;
}

int OP_18h_JRr8_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_18h_JRr8(memory,z80);

   return retValue;
}

int OP_19h_ADDHLDE_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_19h_ADDHLDE(memory,z80);

   return retValue;
}

int OP_1Ah_LDADE_wrapper(Memory * memory, Z80 * z80)
{
   // D register starts at 0x3, hence the argument
   int retValue = OP_LDXYZ(memory,z80,0x0,0x3);

   return retValue;
}

int OP_1Bh_DECDE_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_1Bh_DECDE(memory,z80);

   return retValue;
}

int OP_1Ch_INCE_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_1Ch_INCE(memory,z80);

   return retValue;
}

int OP_1Dh_DECE_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_1Dh_DECE(memory,z80);

   return retValue;
}

int OP_1Eh_LDEd8_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_1Eh_LDEd8(memory,z80);

   return retValue;
}

int OP_1Fh_RRA_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_1Fh_RRA(memory,z80);

   return retValue;
}

int OP_20h_JRNZr8_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_20h_JRNZr8(memory,z80);

   return retValue;
}

int OP_21h_LDHLd16_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_21h_LDHLd16(memory,z80);

   return retValue;
}

int OP_22h_LDIHLA_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_22h_LDIHLA(memory,z80);

   return retValue;
}

int OP_23h_INCHL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_23h_INCHL(memory,z80);

   return retValue;
}

int OP_24h_INCH_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_24h_INCH(memory,z80);

   return retValue;
}

int OP_25h_DECH_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_25h_DECH(memory,z80);

   return retValue;
}

int OP_26h_LDHd8_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_26h_LDHd8(memory,z80);

   return retValue;
}

int OP_27h_DAA_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_27h_DAA(memory,z80);

   return retValue;
}

int OP_28h_JRZr8_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_28h_JRZr8(memory,z80);

   return retValue;
}

int OP_29h_ADDHLHL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_29h_ADDHLHL(memory,z80);

   return retValue;
}

int OP_2Ah_LDIAHL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_2Ah_LDIAHL(memory,z80);

   return retValue;
}

int OP_2Bh_DECHL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_2Bh_DECHL(memory,z80);

   return retValue;
}

int OP_2Ch_INCL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_2Ch_INCL(memory,z80);

   return retValue;
}

int OP_2Dh_DECL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_2Dh_DECL(memory,z80);

   return retValue;
}

int OP_2Eh_LDLd8_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_LDXd8(memory,z80,(uint8_t) 0x7);

   return retValue;
}

int OP_2Fh_CPL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_2Fh_CPL(memory,z80);

   return retValue;
}


int OP_30h_JRNCr8_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_30h_JRNCr8(memory,z80);

   return retValue;
}

int OP_31h_LDSPd16_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_31h_LDSPd16(memory,z80);

   return retValue;
}

int OP_32h_LDDHLA_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_32h_LDDHLA(memory,z80);

   return retValue;
}

int OP_33h_INCSP_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_33h_INCSP(memory,z80);

   return retValue;
}

int OP_34h_INCHL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_34h_INCHL(memory,z80);

   return retValue;
}

int OP_35h_DECHL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_35h_DECHL(memory,z80);

   return retValue;
}

int OP_36h_LDHLd8_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_36h_LDHLd8(memory,z80);

   return retValue;
}

int OP_37h_SCF_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_37h_SCF(memory,z80);

   return retValue;
}

int OP_38h_JRCr8_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_38h_JRCr8(memory,z80);

   return retValue;
}

int OP_39h_ADDHLSP_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_39h_ADDHLSP(memory,z80);

   return retValue;
}

int OP_3Ah_LDDAHL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_3Ah_LDDAHL(memory,z80);

   return retValue;
}

int OP_3Bh_DECSP_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_3Bh_DECSP(memory,z80);

   return retValue;
}

int OP_3Ch_INCA_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_3Ch_INCA(memory,z80);

   return retValue;
}

int OP_3Dh_DECA_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_DECX(memory,z80,0x0);

   return retValue;
}

int OP_3Eh_LDAd8_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_LDXd8(memory,z80,(uint8_t) 0x0);

   return retValue;
}

int OP_3Fh_CCF_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_3Fh_CCF(memory,z80);

   return retValue;
}


int OP_40h_LDBB_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_40h_LDBB(memory,z80);

   return retValue;
}

int OP_41h_LDBC_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_41h_LDBC(memory,z80);

   return retValue;
}

int OP_42h_LDBD_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_42h_LDBD(memory,z80);

   return retValue;
}

int OP_43h_LDBE_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_43h_LDBE(memory,z80);

   return retValue;
}

int OP_44h_LDBH_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_44h_LDBH(memory,z80);

   return retValue;
}

int OP_45h_LDBL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_45h_LDBL(memory,z80);

   return retValue;
}

int OP_46h_LDBHL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_46h_LDBHL(memory,z80);

   return retValue;
}

int OP_47h_LDBA_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_47h_LDBA(memory,z80);

   return retValue;
}

int OP_48h_LDCB_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_48h_LDCB(memory,z80);

   return retValue;
}

int OP_49h_LDC_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_49h_LDC(memory,z80);

   return retValue;
}

int OP_4Ah_LDCD_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_4Ah_LDCD(memory,z80);

   return retValue;
}

int OP_4Bh_LDCE_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_4Bh_LDCE(memory,z80);

   return retValue;
}

int OP_4Ch_LDCH_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_4Ch_LDCH(memory,z80);

   return retValue;
}

int OP_4Dh_LDCL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_4Dh_LDCL(memory,z80);

   return retValue;
}

int OP_4Eh_LDCHL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_4Eh_LDCHL(memory,z80);

   return retValue;
}

int OP_4Fh_LDCA_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_LDXY(memory,z80,0x20);

   return retValue;
}

int OP_50h_LDDB_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_50h_LDDB(memory,z80);

   return retValue;
}

int OP_51h_LDDC_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_51h_LDDC(memory,z80);

   return retValue;
}

int OP_52h_LDDD_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_52h_LDDD(memory,z80);

   return retValue;
}

int OP_53h_LDDE_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_53h_LDDE(memory,z80);

   return retValue;
}

int OP_54h_LDDH_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_54h_LDDH(memory,z80);

   return retValue;
}

int OP_55h_LDDL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_55h_LDDL(memory,z80);

   return retValue;
}

int OP_56h_LDDHL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_56h_LDDHL(memory,z80);

   return retValue;
}

int OP_57h_LDDA_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_LDXY(memory,z80,0x30);

   return retValue;
}

int OP_58h_LDEB_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_58h_LDEB(memory,z80);

   return retValue;
}

int OP_59h_LDEC_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_59h_LDEC(memory,z80);

   return retValue;
}

int OP_5Ah_LDED_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_5Ah_LDED(memory,z80);

   return retValue;
}

int OP_5Bh_LDEE_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_5Bh_LDEE(memory,z80);

   return retValue;
}

int OP_5Ch_LDEH_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_5Ch_LDEH(memory,z80);

   return retValue;
}

int OP_5Dh_LDEL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_5Dh_LDEL(memory,z80);

   return retValue;
}

int OP_5Eh_LDEHL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_5Eh_LDEHL(memory,z80);

   return retValue;
}

int OP_5Fh_LDEA_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_5Fh_LDEA(memory,z80);

   return retValue;
}


int OP_60h_LDHB_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_60h_LDHB(memory,z80);

   return retValue;
}

int OP_61h_LDHC_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_61h_LDHC(memory,z80);

   return retValue;
}

int OP_62h_LDHD_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_62h_LDHD(memory,z80);

   return retValue;
}

int OP_63h_LDHE_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_63h_LDHE(memory,z80);

   return retValue;
}

int OP_64h_LDHH_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_64h_LDHH(memory,z80);

   return retValue;
}

int OP_65h_LDHL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_65h_LDHL(memory,z80);

   return retValue;
}

int OP_66h_LDHHL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_66h_LDHHL(memory,z80);

   return retValue;
}

int OP_67h_LDHA_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_LDXY(memory,z80,0x60);

   return retValue;
}

int OP_68h_LDLB_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_68h_LDLB(memory,z80);

   return retValue;
}

int OP_69h_LDLC_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_69h_LDLC(memory,z80);

   return retValue;
}

int OP_6Ah_LDLD_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_6Ah_LDLD(memory,z80);

   return retValue;
}

int OP_6Bh_LDLE_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_6Bh_LDLE(memory,z80);

   return retValue;
}

int OP_6Ch_LDLH_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_6Ch_LDLH(memory,z80);

   return retValue;
}

int OP_6Dh_LDLL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_6Dh_LDLL(memory,z80);

   return retValue;
}

int OP_6Eh_LDLHL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_6Eh_LDLHL(memory,z80);

   return retValue;
}

int OP_6Fh_LDLA_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_6Fh_LDLA(memory,z80);

   return retValue;
}

int OP_70h_LDHLB_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_LDHLX(memory,z80,0x1);

   return retValue;
}

int OP_71h_LDHLC_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_LDHLX(memory,z80,0x2);

   return retValue;
}

int OP_72h_LDHLD_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_LDHLX(memory,z80,0x3);

   return retValue;
}

int OP_73h_LDHLE_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_LDHLX(memory,z80,0x4);

   return retValue;
}

int OP_74h_LDHLH_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_LDHLX(memory,z80,0x6);

   return retValue;
}

int OP_75h_LDHLL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_LDHLX(memory,z80,0x7);

   return retValue;
}

int OP_76h_HALT_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_76h_HALT(memory,z80);

   return retValue;
}

int OP_77h_LDHLA_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_LDHLX(memory,z80,0x0);

   return retValue;
}

int OP_78h_LDAB_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_78h_LDAB(memory,z80);

   return retValue;
}

int OP_79h_LDAC_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_79h_LDAC(memory,z80);

   return retValue;
}

int OP_7Ah_LDAD_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_7Ah_LDAD(memory,z80);

   return retValue;
}

int OP_7Bh_LDAE_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_LDXY(memory,z80,0x04);

   return retValue;
}

int OP_7Ch_LDAH_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_7Ch_LDAH(memory,z80);

   return retValue;
}

int OP_7Dh_LDAL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_7Dh_LDAL(memory,z80);

   return retValue;
}

int OP_7Eh_LDAHL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_7Eh_LDAHL(memory,z80);

   return retValue;
}

int OP_7Fh_LDAA_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_7Fh_LDAA(memory,z80);

   return retValue;
}


int OP_80h_ADDAB_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_80h_ADDAB(memory,z80);

   return retValue;
}

int OP_81h_ADDAC_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_81h_ADDAC(memory,z80);

   return retValue;
}

int OP_82h_ADDAD_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_82h_ADDAD(memory,z80);

   return retValue;
}

int OP_83h_ADDAE_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_83h_ADDAE(memory,z80);

   return retValue;
}

int OP_84h_ADDAH_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_84h_ADDAH(memory,z80);

   return retValue;
}

int OP_85h_ADDAL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_85h_ADDAL(memory,z80);

   return retValue;
}

int OP_86h_ADDAHL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_86h_ADDAHL(memory,z80);

   return retValue;
}

int OP_87h_ADDAA_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_87h_ADDAA(memory,z80);

   return retValue;
}

int OP_88h_ADCAB_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_88h_ADCAB(memory,z80);

   return retValue;
}

int OP_89h_ADCAC_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_89h_ADCAC(memory,z80);

   return retValue;
}

int OP_8Ah_ADCAD_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_8Ah_ADCAD(memory,z80);

   return retValue;
}

int OP_8Bh_ADCAE_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_8Bh_ADCAE(memory,z80);

   return retValue;
}

int OP_8Ch_ADCAH_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_8Ch_ADCAH(memory,z80);

   return retValue;
}

int OP_8Dh_ADCAL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_8Dh_ADCAL(memory,z80);

   return retValue;
}

int OP_8Eh_ADCAHL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_8Eh_ADCAHL(memory,z80);

   return retValue;
}

int OP_8Fh_ADCAA_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_8Fh_ADCAA(memory,z80);

   return retValue;
}


int OP_90h_SUBB_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_90h_SUBB(memory,z80);

   return retValue;
}

int OP_91h_SUBC_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_91h_SUBC(memory,z80);

   return retValue;
}

int OP_92h_SUBD_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_92h_SUBD(memory,z80);

   return retValue;
}

int OP_93h_SUBE_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_93h_SUBE(memory,z80);

   return retValue;
}

int OP_94h_SUBH_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_94h_SUBH(memory,z80);

   return retValue;
}

int OP_95h_SUBL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_95h_SUBL(memory,z80);

   return retValue;
}

int OP_96h_SUBHL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_96h_SUBHL(memory,z80);

   return retValue;
}

int OP_97h_SUBA_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_97h_SUBA(memory,z80);

   return retValue;
}

int OP_98h_SBCAB_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_98h_SBCAB(memory,z80);

   return retValue;
}

int OP_99h_SBCAC_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_99h_SBCAC(memory,z80);

   return retValue;
}

int OP_9Ah_SBCAD_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_9Ah_SBCAD(memory,z80);

   return retValue;
}

int OP_9Bh_SBCAE_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_9Bh_SBCAE(memory,z80);

   return retValue;
}

int OP_9Ch_SBCAH_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_9Ch_SBCAH(memory,z80);

   return retValue;
}

int OP_9Dh_SBCAL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_9Dh_SBCAL(memory,z80);

   return retValue;
}

int OP_9Eh_SBCAHL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_9Eh_SBCAHL(memory,z80);

   return retValue;
}

int OP_9Fh_SBCAA_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_9Fh_SBCAA(memory,z80);

   return retValue;
}


int OP_A0h_ANDB_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_A0h_ANDB(memory,z80);

   return retValue;
}

int OP_A1h_ANDC_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_A1h_ANDC(memory,z80);

   return retValue;
}

int OP_A2h_ANDD_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_A2h_ANDD(memory,z80);

   return retValue;
}

int OP_A3h_ANDE_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_A3h_ANDE(memory,z80);

   return retValue;
}

int OP_A4h_ANDH_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_A4h_ANDH(memory,z80);

   return retValue;
}

int OP_A5h_ANDL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_A5h_ANDL(memory,z80);

   return retValue;
}

int OP_A6h_ANDHL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_A6h_ANDHL(memory,z80);

   return retValue;
}

int OP_A7h_ANDA_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_A7h_ANDA(memory,z80);

   return retValue;
}

int OP_A8h_XORB_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_A8h_XORB(memory,z80);

   return retValue;
}

int OP_A9h_XORC_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_A9h_XORC(memory,z80);

   return retValue;
}

int OP_AAh_XORD_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_AAh_XORD(memory,z80);

   return retValue;
}

int OP_ABh_XORE_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_ABh_XORE(memory,z80);

   return retValue;
}

int OP_ACh_XORH_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_ACh_XORH(memory,z80);

   return retValue;
}

int OP_ADh_XORL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_ADh_XORL(memory,z80);

   return retValue;
}

int OP_AEh_XORHL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_AEh_XORHL(memory,z80);

   return retValue;
}

int OP_AFh_XORA_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_AFh_XORA(memory,z80);

   return retValue;
}


int OP_B0h_ORB_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_B0h_ORB(memory,z80);

   return retValue;
}

int OP_B1h_ORC_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_B1h_ORC(memory,z80);

   return retValue;
}

int OP_B2h_ORD_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_B2h_ORD(memory,z80);

   return retValue;
}

int OP_B3h_ORE_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_B3h_ORE(memory,z80);

   return retValue;
}

int OP_B4h_ORH_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_B4h_ORH(memory,z80);

   return retValue;
}

int OP_B5h_ORL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_B5h_ORL(memory,z80);

   return retValue;
}

int OP_B6h_ORHL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_B6h_ORHL(memory,z80);

   return retValue;
}

int OP_B7h_ORA_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_B7h_ORA(memory,z80);

   return retValue;
}

int OP_B8h_CPB_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_B8h_CPB(memory,z80);

   return retValue;
}

int OP_B9h_CPC_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_B9h_CPC(memory,z80);

   return retValue;
}

int OP_BAh_CPD_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_BAh_CPD(memory,z80);

   return retValue;
}

int OP_BBh_CPE_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_BBh_CPE(memory,z80);

   return retValue;
}

int OP_BCh_CPH_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_BCh_CPH(memory,z80);

   return retValue;
}

int OP_BDh_CPL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_BDh_CPL(memory,z80);

   return retValue;
}

int OP_BEh_CPHL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_BEh_CPHL(memory,z80);

   return retValue;
}

int OP_BFh_CPA_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_BFh_CPA(memory,z80);

   return retValue;
}


int OP_C0h_RETNZ_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_C0h_RETNZ(memory,z80);

   return retValue;
}

int OP_C1h_POPBC_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_POPXY(memory,z80,0x12);

   return retValue;
}

int OP_C2h_JPNZa16_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_C2h_JPNZa16(memory,z80);

   return retValue;
}

int OP_C3h_JPa16_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_C3h_JPa16(memory,z80);

   return retValue;
}

int OP_C4h_CALLNZa16_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_C4h_CALLNZa16(memory,z80);

   return retValue;
}

int OP_C5h_PUSHBC_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_PUSHXY(memory,z80,0x12);

   return retValue;
}

int OP_C6h_ADDAd8_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_C6h_ADDAd8(memory,z80);

   return retValue;
}

int OP_C7h_RST00H_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_C7h_RST00H(memory,z80);

   return retValue;
}

int OP_C8h_RETZ_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_C8h_RETZ(memory,z80);

   return retValue;
}

int OP_C9h_RET_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_C9h_RET(memory,z80);

   return retValue;
}

int OP_CAh_JPZa16_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_CAh_JPZa16(memory,z80);

   return retValue;
}

int OP_CBh_PREFIXCB_wrapper(Memory * memory, Z80 * z80)
{
   //int retValue = OP_CBh_PREFIXCB(memory,z80);

   //return retValue;
   // I think we can just return 0 here because op pointer is checked
   z80->op_call = z80->cb_op;

   return 0;
}

int OP_CCh_CALLZa16_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_CCh_CALLZa16(memory,z80);

   return retValue;
}

int OP_CDh_CALLa16_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_CDh_CALLa16(memory,z80);

   return retValue;
}

int OP_CEh_ADCAd8_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_CEh_ADCAd8(memory,z80);

   return retValue;
}

int OP_CFh_RST08H_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_CFh_RST08H(memory,z80);

   return retValue;
}


int OP_D0h_RETNC_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_D0h_RETNC(memory,z80);

   return retValue;
}

int OP_D1h_POPDE_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_D1h_POPDE(memory,z80);

   return retValue;
}

int OP_D2h_JPNCa16_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_D2h_JPNCa16(memory,z80);

   return retValue;
}

int OP_D3h_INVALID_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_D3h_INVALID(memory,z80);

   return retValue;
}

int OP_D4h_CALLNCa16_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_D4h_CALLNCa16(memory,z80);

   return retValue;
}

int OP_D5h_PUSHDE_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_D5h_PUSHDE(memory,z80);

   return retValue;
}

int OP_D6h_SUBd8_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_D6h_SUBd8(memory,z80);

   return retValue;
}

int OP_D7h_RST10H_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_D7h_RST10H(memory,z80);

   return retValue;
}

int OP_D8h_RETC_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_D8h_RETC(memory,z80);

   return retValue;
}

int OP_D9h_RETI_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_D9h_RETI(memory,z80);

   return retValue;
}

int OP_DAh_JPCa16_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_DAh_JPCa16(memory,z80);

   return retValue;
}

int OP_DBh_INVALID_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_DBh_INVALID(memory,z80);

   return retValue;
}

int OP_DCh_CALLCa16_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_DCh_CALLCa16(memory,z80);

   return retValue;
}

int OP_DDh_INVALID_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_DDh_INVALID(memory,z80);

   return retValue;
}

int OP_DEh_SBCAd8_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_DEh_SBCAd8(memory,z80);

   return retValue;
}

int OP_DFh_RST18H_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_DFh_RST18H(memory,z80);

   return retValue;
}


int OP_E0h_LDHa8A_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_E0h_LDHa8A(memory,z80);

   return retValue;
}

int OP_E1h_POPHL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_E1h_POPHL(memory,z80);

   return retValue;
}

int OP_E2h_LDHCA_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_E2h_LDHCA(memory,z80);

   return retValue;
}

int OP_E3h_INVALID_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_E3h_INVALID(memory,z80);

   return retValue;
}

int OP_E4h_INVALID_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_E4h_INVALID(memory,z80);

   return retValue;
}

int OP_E5h_PUSHHL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_E5h_PUSHHL(memory,z80);

   return retValue;
}

int OP_E6h_ANDd8_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_E6h_ANDd8(memory,z80);

   return retValue;
}

int OP_E7h_RST20H_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_E7h_RST20H(memory,z80);

   return retValue;
}

int OP_E8h_ADDSPr8_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_E8h_ADDSPr8(memory,z80);

   return retValue;
}

int OP_E9h_JPHL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_E9h_JPHL(memory,z80);

   return retValue;
}

int OP_EAh_LDa16A_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_EAh_LDa16A(memory,z80);

   return retValue;
}

int OP_EBh_INVALID_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_EBh_INVALID(memory,z80);

   return retValue;
}

int OP_ECh_INVALID_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_ECh_INVALID(memory,z80);

   return retValue;
}

int OP_EDh_INVALID_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_EDh_INVALID(memory,z80);

   return retValue;
}

int OP_EEh_XORd8_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_EEh_XORd8(memory,z80);

   return retValue;
}

int OP_EFh_RST28H_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_EFh_RST28H(memory,z80);

   return retValue;
}


int OP_F0h_LDHAa8_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_F0h_LDHAa8(memory,z80);

   return retValue;
}

int OP_F1h_POPAF_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_F1h_POPAF(memory,z80);

   return retValue;
}

int OP_F2h_LDAC_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_F2h_LDAC(memory,z80);

   return retValue;
}

int OP_F3h_DI_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_F3h_DI(memory,z80);

   return retValue;
}

int OP_F4h_INVALID_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_F4h_INVALID(memory,z80);

   return retValue;
}

int OP_F5h_PUSHAF_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_F5h_PUSHAF(memory,z80);

   return retValue;
}

int OP_F6h_ORd8_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_F6h_ORd8(memory,z80);

   return retValue;
}

int OP_F7h_RST30H_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_F7h_RST30H(memory,z80);

   return retValue;
}

int OP_F8h_LDHLSPr8_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_F8h_LDHLSPr8(memory,z80);

   return retValue;
}

int OP_F9h_LDSPHL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_F9h_LDSPHL(memory,z80);

   return retValue;
}

int OP_FAh_LDAa16_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_FAh_LDAa16(memory,z80);

   return retValue;
}

int OP_FBh_EI_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_FBh_EI(memory,z80);

   return retValue;
}

int OP_FCh_INVALID_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_FCh_INVALID(memory,z80);

   return retValue;
}

int OP_FDh_INVALID_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_FDh_INVALID(memory,z80);

   return retValue;
}

int OP_FEh_CPd8_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_FEh_CPd8(memory,z80);

   return retValue;
}

int OP_FFh_RST38H_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_FFh_RST38H(memory,z80);

   return retValue;
}

//
//
//
// CB Prefix
//
//
//

int CB_OP_00h_RLCB_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_00h_RLCB(memory,z80);

   return retValue;
}

int CB_OP_01h_RLCC_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_01h_RLCC(memory,z80);

   return retValue;
}

int CB_OP_02h_RLCD_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_02h_RLCD(memory,z80);

   return retValue;
}

int CB_OP_03h_RLCE_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_03h_RLCE(memory,z80);

   return retValue;
}

int CB_OP_04h_RLCH_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_04h_RLCH(memory,z80);

   return retValue;
}

int CB_OP_05h_RLCL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_05h_RLCL(memory,z80);

   return retValue;
}

int CB_OP_06h_RLCHL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_06h_RLCHL(memory,z80);

   return retValue;
}

int CB_OP_07h_RLCA_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_07h_RLCA(memory,z80);

   return retValue;
}

int CB_OP_08h_RRCB_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_08h_RRCB(memory,z80);

   return retValue;
}

int CB_OP_09h_RRCC_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_09h_RRCC(memory,z80);

   return retValue;
}

int CB_OP_0Ah_RRCD_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_0Ah_RRCD(memory,z80);

   return retValue;
}

int CB_OP_0Bh_RRCE_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_0Bh_RRCE(memory,z80);

   return retValue;
}

int CB_OP_0Ch_RRCH_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_0Ch_RRCH(memory,z80);

   return retValue;
}

int CB_OP_0Dh_RRCL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_0Dh_RRCL(memory,z80);

   return retValue;
}

int CB_OP_0Eh_RRCHL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_0Eh_RRCHL(memory,z80);

   return retValue;
}

int CB_OP_0Fh_RRCA_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_0Fh_RRCA(memory,z80);

   return retValue;
}


int CB_OP_10h_RLB_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_10h_RLB(memory,z80);

   return retValue;
}

int CB_OP_11h_RLC_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_RLX(memory,z80,0x2);

   return retValue;
}

int CB_OP_12h_RLD_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_12h_RLD(memory,z80);

   return retValue;
}

int CB_OP_13h_RLE_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_13h_RLE(memory,z80);

   return retValue;
}

int CB_OP_14h_RLH_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_14h_RLH(memory,z80);

   return retValue;
}

int CB_OP_15h_RLL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_15h_RLL(memory,z80);

   return retValue;
}

int CB_OP_16h_RLHL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_16h_RLHL(memory,z80);

   return retValue;
}

int CB_OP_17h_RLA_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_17h_RLA(memory,z80);

   return retValue;
}

int CB_OP_18h_RRB_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_18h_RRB(memory,z80);

   return retValue;
}

int CB_OP_19h_RRC_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_19h_RRC(memory,z80);

   return retValue;
}

int CB_OP_1Ah_RRD_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_1Ah_RRD(memory,z80);

   return retValue;
}

int CB_OP_1Bh_RRE_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_1Bh_RRE(memory,z80);

   return retValue;
}

int CB_OP_1Ch_RRH_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_1Ch_RRH(memory,z80);

   return retValue;
}

int CB_OP_1Dh_RRL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_1Dh_RRL(memory,z80);

   return retValue;
}

int CB_OP_1Eh_RRHL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_1Eh_RRHL(memory,z80);

   return retValue;
}

int CB_OP_1Fh_RRA_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_1Fh_RRA(memory,z80);

   return retValue;
}


int CB_OP_20h_SLAB_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_20h_SLAB(memory,z80);

   return retValue;
}

int CB_OP_21h_SLAC_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_21h_SLAC(memory,z80);

   return retValue;
}

int CB_OP_22h_SLAD_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_22h_SLAD(memory,z80);

   return retValue;
}

int CB_OP_23h_SLAE_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_23h_SLAE(memory,z80);

   return retValue;
}

int CB_OP_24h_SLAH_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_24h_SLAH(memory,z80);

   return retValue;
}

int CB_OP_25h_SLAL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_25h_SLAL(memory,z80);

   return retValue;
}

int CB_OP_26h_SLAHL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_26h_SLAHL(memory,z80);

   return retValue;
}

int CB_OP_27h_SLAA_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_27h_SLAA(memory,z80);

   return retValue;
}

int CB_OP_28h_SRAB_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_28h_SRAB(memory,z80);

   return retValue;
}

int CB_OP_29h_SRAC_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_29h_SRAC(memory,z80);

   return retValue;
}

int CB_OP_2Ah_SRAD_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_2Ah_SRAD(memory,z80);

   return retValue;
}

int CB_OP_2Bh_SRAE_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_2Bh_SRAE(memory,z80);

   return retValue;
}

int CB_OP_2Ch_SRAH_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_2Ch_SRAH(memory,z80);

   return retValue;
}

int CB_OP_2Dh_SRAL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_2Dh_SRAL(memory,z80);

   return retValue;
}

int CB_OP_2Eh_SRAHL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_2Eh_SRAHL(memory,z80);

   return retValue;
}

int CB_OP_2Fh_SRAA_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_2Fh_SRAA(memory,z80);

   return retValue;
}


int CB_OP_30h_SWAPB_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_30h_SWAPB(memory,z80);

   return retValue;
}

int CB_OP_31h_SWAPC_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_31h_SWAPC(memory,z80);

   return retValue;
}

int CB_OP_32h_SWAPD_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_32h_SWAPD(memory,z80);

   return retValue;
}

int CB_OP_33h_SWAPE_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_33h_SWAPE(memory,z80);

   return retValue;
}

int CB_OP_34h_SWAPH_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_34h_SWAPH(memory,z80);

   return retValue;
}

int CB_OP_35h_SWAPL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_35h_SWAPL(memory,z80);

   return retValue;
}

int CB_OP_36h_SWAPHL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_36h_SWAPHL(memory,z80);

   return retValue;
}

int CB_OP_37h_SWAPA_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_37h_SWAPA(memory,z80);

   return retValue;
}

int CB_OP_38h_SRLB_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_38h_SRLB(memory,z80);

   return retValue;
}

int CB_OP_39h_SRLC_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_39h_SRLC(memory,z80);

   return retValue;
}

int CB_OP_3Ah_SRLD_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_3Ah_SRLD(memory,z80);

   return retValue;
}

int CB_OP_3Bh_SRLE_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_3Bh_SRLE(memory,z80);

   return retValue;
}

int CB_OP_3Ch_SRLH_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_3Ch_SRLH(memory,z80);

   return retValue;
}

int CB_OP_3Dh_SRLL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_3Dh_SRLL(memory,z80);

   return retValue;
}

int CB_OP_3Eh_SRLHL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_3Eh_SRLHL(memory,z80);

   return retValue;
}

int CB_OP_3Fh_SRLA_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_3Fh_SRLA(memory,z80);

   return retValue;
}


int CB_OP_40h_BIT0B_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_BIT(memory,z80,0x01);

   return retValue;
}

int CB_OP_41h_BIT0C_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_BIT(memory,z80,0x02);

   return retValue;
}

int CB_OP_42h_BIT0D_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_BIT(memory,z80,0x03);

   return retValue;
}

int CB_OP_43h_BIT0E_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_BIT(memory,z80,0x04);

   return retValue;
}

int CB_OP_44h_BIT0H_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_BIT(memory,z80,0x06);

   return retValue;
}

int CB_OP_45h_BIT0L_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_BIT(memory,z80,0x07);

   return retValue;
}

int CB_OP_46h_BIT0HL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_46h_BIT0HL(memory,z80);

   return retValue;
}

int CB_OP_47h_BIT0A_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_BIT(memory,z80,0x00);

   return retValue;
}

int CB_OP_48h_BIT1B_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_48h_BIT1B(memory,z80);

   return retValue;
}

int CB_OP_49h_BIT1C_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_49h_BIT1C(memory,z80);

   return retValue;
}

int CB_OP_4Ah_BIT1D_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_4Ah_BIT1D(memory,z80);

   return retValue;
}

int CB_OP_4Bh_BIT1E_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_4Bh_BIT1E(memory,z80);

   return retValue;
}

int CB_OP_4Ch_BIT1H_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_4Ch_BIT1H(memory,z80);

   return retValue;
}

int CB_OP_4Dh_BIT1L_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_4Dh_BIT1L(memory,z80);

   return retValue;
}

int CB_OP_4Eh_BIT1HL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_4Eh_BIT1HL(memory,z80);

   return retValue;
}

int CB_OP_4Fh_BIT1A_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_4Fh_BIT1A(memory,z80);

   return retValue;
}


int CB_OP_50h_BIT2B_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_50h_BIT2B(memory,z80);

   return retValue;
}

int CB_OP_51h_BIT2C_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_51h_BIT2C(memory,z80);

   return retValue;
}

int CB_OP_52h_BIT2D_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_52h_BIT2D(memory,z80);

   return retValue;
}

int CB_OP_53h_BIT2E_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_53h_BIT2E(memory,z80);

   return retValue;
}

int CB_OP_54h_BIT2H_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_54h_BIT2H(memory,z80);

   return retValue;
}

int CB_OP_55h_BIT2L_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_55h_BIT2L(memory,z80);

   return retValue;
}

int CB_OP_56h_BIT2HL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_56h_BIT2HL(memory,z80);

   return retValue;
}

int CB_OP_57h_BIT2A_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_57h_BIT2A(memory,z80);

   return retValue;
}

int CB_OP_58h_BIT3B_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_58h_BIT3B(memory,z80);

   return retValue;
}

int CB_OP_59h_BIT3C_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_59h_BIT3C(memory,z80);

   return retValue;
}

int CB_OP_5Ah_BIT3D_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_5Ah_BIT3D(memory,z80);

   return retValue;
}

int CB_OP_5Bh_BIT3E_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_5Bh_BIT3E(memory,z80);

   return retValue;
}

int CB_OP_5Ch_BIT3H_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_5Ch_BIT3H(memory,z80);

   return retValue;
}

int CB_OP_5Dh_BIT3L_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_5Dh_BIT3L(memory,z80);

   return retValue;
}

int CB_OP_5Eh_BIT3HL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_5Eh_BIT3HL(memory,z80);

   return retValue;
}

int CB_OP_5Fh_BIT3A_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_5Fh_BIT3A(memory,z80);

   return retValue;
}


int CB_OP_60h_BIT4B_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_60h_BIT4B(memory,z80);

   return retValue;
}

int CB_OP_61h_BIT4C_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_61h_BIT4C(memory,z80);

   return retValue;
}

int CB_OP_62h_BIT4D_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_62h_BIT4D(memory,z80);

   return retValue;
}

int CB_OP_63h_BIT4E_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_63h_BIT4E(memory,z80);

   return retValue;
}

int CB_OP_64h_BIT4H_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_64h_BIT4H(memory,z80);

   return retValue;
}

int CB_OP_65h_BIT4L_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_65h_BIT4L(memory,z80);

   return retValue;
}

int CB_OP_66h_BIT4HL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_66h_BIT4HL(memory,z80);

   return retValue;
}

int CB_OP_67h_BIT4A_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_67h_BIT4A(memory,z80);

   return retValue;
}

int CB_OP_68h_BIT5B_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_68h_BIT5B(memory,z80);

   return retValue;
}

int CB_OP_69h_BIT5C_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_69h_BIT5C(memory,z80);

   return retValue;
}

int CB_OP_6Ah_BIT5D_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_6Ah_BIT5D(memory,z80);

   return retValue;
}

int CB_OP_6Bh_BIT5E_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_6Bh_BIT5E(memory,z80);

   return retValue;
}

int CB_OP_6Ch_BIT5H_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_6Ch_BIT5H(memory,z80);

   return retValue;
}

int CB_OP_6Dh_BIT5L_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_6Dh_BIT5L(memory,z80);

   return retValue;
}

int CB_OP_6Eh_BIT5HL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_6Eh_BIT5HL(memory,z80);

   return retValue;
}

int CB_OP_6Fh_BIT5A_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_6Fh_BIT5A(memory,z80);

   return retValue;
}


int CB_OP_70h_BIT6B_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_70h_BIT6B(memory,z80);

   return retValue;
}

int CB_OP_71h_BIT6C_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_71h_BIT6C(memory,z80);

   return retValue;
}

int CB_OP_72h_BIT6D_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_72h_BIT6D(memory,z80);

   return retValue;
}

int CB_OP_73h_BIT6E_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_73h_BIT6E(memory,z80);

   return retValue;
}

int CB_OP_74h_BIT6H_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_74h_BIT6H(memory,z80);

   return retValue;
}

int CB_OP_75h_BIT6L_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_75h_BIT6L(memory,z80);

   return retValue;
}

int CB_OP_76h_BIT6HL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_76h_BIT6HL(memory,z80);

   return retValue;
}

int CB_OP_77h_BIT6A_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_77h_BIT6A(memory,z80);

   return retValue;
}

int CB_OP_78h_BIT7B_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_78h_BIT7B(memory,z80);

   return retValue;
}

int CB_OP_79h_BIT7C_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_79h_BIT7C(memory,z80);

   return retValue;
}

int CB_OP_7Ah_BIT7D_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_7Ah_BIT7D(memory,z80);

   return retValue;
}

int CB_OP_7Bh_BIT7E_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_7Bh_BIT7E(memory,z80);

   return retValue;
}

int CB_OP_7Ch_BIT7H_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_BIT(memory,z80,0x76);

   return retValue;
}

int CB_OP_7Dh_BIT7L_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_7Dh_BIT7L(memory,z80);

   return retValue;
}

int CB_OP_7Eh_BIT7HL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_7Eh_BIT7HL(memory,z80);

   return retValue;
}

int CB_OP_7Fh_BIT7A_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_7Fh_BIT7A(memory,z80);

   return retValue;
}


int CB_OP_80h_RES0B_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_80h_RES0B(memory,z80);

   return retValue;
}

int CB_OP_81h_RES0C_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_81h_RES0C(memory,z80);

   return retValue;
}

int CB_OP_82h_RES0D_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_82h_RES0D(memory,z80);

   return retValue;
}

int CB_OP_83h_RES0E_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_83h_RES0E(memory,z80);

   return retValue;
}

int CB_OP_84h_RES0H_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_84h_RES0H(memory,z80);

   return retValue;
}

int CB_OP_85h_RES0L_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_85h_RES0L(memory,z80);

   return retValue;
}

int CB_OP_86h_RES0HL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_86h_RES0HL(memory,z80);

   return retValue;
}

int CB_OP_87h_RES0A_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_87h_RES0A(memory,z80);

   return retValue;
}

int CB_OP_88h_RES1B_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_88h_RES1B(memory,z80);

   return retValue;
}

int CB_OP_89h_RES1C_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_89h_RES1C(memory,z80);

   return retValue;
}

int CB_OP_8Ah_RES1D_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_8Ah_RES1D(memory,z80);

   return retValue;
}

int CB_OP_8Bh_RES1E_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_8Bh_RES1E(memory,z80);

   return retValue;
}

int CB_OP_8Ch_RES1H_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_8Ch_RES1H(memory,z80);

   return retValue;
}

int CB_OP_8Dh_RES1L_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_8Dh_RES1L(memory,z80);

   return retValue;
}

int CB_OP_8Eh_RES1HL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_8Eh_RES1HL(memory,z80);

   return retValue;
}

int CB_OP_8Fh_RES1A_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_8Fh_RES1A(memory,z80);

   return retValue;
}


int CB_OP_90h_RES2B_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_90h_RES2B(memory,z80);

   return retValue;
}

int CB_OP_91h_RES2C_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_91h_RES2C(memory,z80);

   return retValue;
}

int CB_OP_92h_RES2D_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_92h_RES2D(memory,z80);

   return retValue;
}

int CB_OP_93h_RES2E_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_93h_RES2E(memory,z80);

   return retValue;
}

int CB_OP_94h_RES2H_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_94h_RES2H(memory,z80);

   return retValue;
}

int CB_OP_95h_RES2L_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_95h_RES2L(memory,z80);

   return retValue;
}

int CB_OP_96h_RES2HL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_96h_RES2HL(memory,z80);

   return retValue;
}

int CB_OP_97h_RES2A_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_97h_RES2A(memory,z80);

   return retValue;
}

int CB_OP_98h_RES3B_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_98h_RES3B(memory,z80);

   return retValue;
}

int CB_OP_99h_RES3C_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_99h_RES3C(memory,z80);

   return retValue;
}

int CB_OP_9Ah_RES3D_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_9Ah_RES3D(memory,z80);

   return retValue;
}

int CB_OP_9Bh_RES3E_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_9Bh_RES3E(memory,z80);

   return retValue;
}

int CB_OP_9Ch_RES3H_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_9Ch_RES3H(memory,z80);

   return retValue;
}

int CB_OP_9Dh_RES3L_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_9Dh_RES3L(memory,z80);

   return retValue;
}

int CB_OP_9Eh_RES3HL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_9Eh_RES3HL(memory,z80);

   return retValue;
}

int CB_OP_9Fh_RES3A_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_9Fh_RES3A(memory,z80);

   return retValue;
}


int CB_OP_A0h_RES4B_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_A0h_RES4B(memory,z80);

   return retValue;
}

int CB_OP_A1h_RES4C_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_A1h_RES4C(memory,z80);

   return retValue;
}

int CB_OP_A2h_RES4D_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_A2h_RES4D(memory,z80);

   return retValue;
}

int CB_OP_A3h_RES4E_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_A3h_RES4E(memory,z80);

   return retValue;
}

int CB_OP_A4h_RES4H_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_A4h_RES4H(memory,z80);

   return retValue;
}

int CB_OP_A5h_RES4L_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_A5h_RES4L(memory,z80);

   return retValue;
}

int CB_OP_A6h_RES4HL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_A6h_RES4HL(memory,z80);

   return retValue;
}

int CB_OP_A7h_RES4A_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_A7h_RES4A(memory,z80);

   return retValue;
}

int CB_OP_A8h_RES5B_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_A8h_RES5B(memory,z80);

   return retValue;
}

int CB_OP_A9h_RES5C_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_A9h_RES5C(memory,z80);

   return retValue;
}

int CB_OP_AAh_RES5D_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_AAh_RES5D(memory,z80);

   return retValue;
}

int CB_OP_ABh_RES5E_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_ABh_RES5E(memory,z80);

   return retValue;
}

int CB_OP_ACh_RES5H_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_ACh_RES5H(memory,z80);

   return retValue;
}

int CB_OP_ADh_RES5L_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_ADh_RES5L(memory,z80);

   return retValue;
}

int CB_OP_AEh_RES5HL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_AEh_RES5HL(memory,z80);

   return retValue;
}

int CB_OP_AFh_RES5A_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_AFh_RES5A(memory,z80);

   return retValue;
}


int CB_OP_B0h_RES6B_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_B0h_RES6B(memory,z80);

   return retValue;
}

int CB_OP_B1h_RES6C_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_B1h_RES6C(memory,z80);

   return retValue;
}

int CB_OP_B2h_RES6D_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_B2h_RES6D(memory,z80);

   return retValue;
}

int CB_OP_B3h_RES6E_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_B3h_RES6E(memory,z80);

   return retValue;
}

int CB_OP_B4h_RES6H_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_B4h_RES6H(memory,z80);

   return retValue;
}

int CB_OP_B5h_RES6L_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_B5h_RES6L(memory,z80);

   return retValue;
}

int CB_OP_B6h_RES6HL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_B6h_RES6HL(memory,z80);

   return retValue;
}

int CB_OP_B7h_RES6A_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_B7h_RES6A(memory,z80);

   return retValue;
}

int CB_OP_B8h_RES7B_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_B8h_RES7B(memory,z80);

   return retValue;
}

int CB_OP_B9h_RES7C_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_B9h_RES7C(memory,z80);

   return retValue;
}

int CB_OP_BAh_RES7D_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_BAh_RES7D(memory,z80);

   return retValue;
}

int CB_OP_BBh_RES7E_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_BBh_RES7E(memory,z80);

   return retValue;
}

int CB_OP_BCh_RES7H_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_BCh_RES7H(memory,z80);

   return retValue;
}

int CB_OP_BDh_RES7L_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_BDh_RES7L(memory,z80);

   return retValue;
}

int CB_OP_BEh_RES7HL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_BEh_RES7HL(memory,z80);

   return retValue;
}

int CB_OP_BFh_RES7A_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_BFh_RES7A(memory,z80);

   return retValue;
}


int CB_OP_C0h_SET0B_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_C0h_SET0B(memory,z80);

   return retValue;
}

int CB_OP_C1h_SET0C_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_C1h_SET0C(memory,z80);

   return retValue;
}

int CB_OP_C2h_SET0D_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_C2h_SET0D(memory,z80);

   return retValue;
}

int CB_OP_C3h_SET0E_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_C3h_SET0E(memory,z80);

   return retValue;
}

int CB_OP_C4h_SET0H_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_C4h_SET0H(memory,z80);

   return retValue;
}

int CB_OP_C5h_SET0L_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_C5h_SET0L(memory,z80);

   return retValue;
}

int CB_OP_C6h_SET0HL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_C6h_SET0HL(memory,z80);

   return retValue;
}

int CB_OP_C7h_SET0A_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_C7h_SET0A(memory,z80);

   return retValue;
}

int CB_OP_C8h_SET1B_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_C8h_SET1B(memory,z80);

   return retValue;
}

int CB_OP_C9h_SET1C_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_C9h_SET1C(memory,z80);

   return retValue;
}

int CB_OP_CAh_SET1D_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_CAh_SET1D(memory,z80);

   return retValue;
}

int CB_OP_CBh_SET1E_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_CBh_SET1E(memory,z80);

   return retValue;
}

int CB_OP_CCh_SET1H_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_CCh_SET1H(memory,z80);

   return retValue;
}

int CB_OP_CDh_SET1L_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_CDh_SET1L(memory,z80);

   return retValue;
}

int CB_OP_CEh_SET1HL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_CEh_SET1HL(memory,z80);

   return retValue;
}

int CB_OP_CFh_SET1A_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_CFh_SET1A(memory,z80);

   return retValue;
}


int CB_OP_D0h_SET2B_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_D0h_SET2B(memory,z80);

   return retValue;
}

int CB_OP_D1h_SET2C_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_D1h_SET2C(memory,z80);

   return retValue;
}

int CB_OP_D2h_SET2D_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_D2h_SET2D(memory,z80);

   return retValue;
}

int CB_OP_D3h_SET2E_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_D3h_SET2E(memory,z80);

   return retValue;
}

int CB_OP_D4h_SET2H_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_D4h_SET2H(memory,z80);

   return retValue;
}

int CB_OP_D5h_SET2L_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_D5h_SET2L(memory,z80);

   return retValue;
}

int CB_OP_D6h_SET2HL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_D6h_SET2HL(memory,z80);

   return retValue;
}

int CB_OP_D7h_SET2A_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_D7h_SET2A(memory,z80);

   return retValue;
}

int CB_OP_D8h_SET3B_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_D8h_SET3B(memory,z80);

   return retValue;
}

int CB_OP_D9h_SET3C_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_D9h_SET3C(memory,z80);

   return retValue;
}

int CB_OP_DAh_SET3D_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_DAh_SET3D(memory,z80);

   return retValue;
}

int CB_OP_DBh_SET3E_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_DBh_SET3E(memory,z80);

   return retValue;
}

int CB_OP_DCh_SET3H_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_DCh_SET3H(memory,z80);

   return retValue;
}

int CB_OP_DDh_SET3L_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_DDh_SET3L(memory,z80);

   return retValue;
}

int CB_OP_DEh_SET3HL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_DEh_SET3HL(memory,z80);

   return retValue;
}

int CB_OP_DFh_SET3A_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_DFh_SET3A(memory,z80);

   return retValue;
}


int CB_OP_E0h_SET4B_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_E0h_SET4B(memory,z80);

   return retValue;
}

int CB_OP_E1h_SET4C_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_E1h_SET4C(memory,z80);

   return retValue;
}

int CB_OP_E2h_SET4D_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_E2h_SET4D(memory,z80);

   return retValue;
}

int CB_OP_E3h_SET4E_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_E3h_SET4E(memory,z80);

   return retValue;
}

int CB_OP_E4h_SET4H_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_E4h_SET4H(memory,z80);

   return retValue;
}

int CB_OP_E5h_SET4L_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_E5h_SET4L(memory,z80);

   return retValue;
}

int CB_OP_E6h_SET4HL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_E6h_SET4HL(memory,z80);

   return retValue;
}

int CB_OP_E7h_SET4A_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_E7h_SET4A(memory,z80);

   return retValue;
}

int CB_OP_E8h_SET5B_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_E8h_SET5B(memory,z80);

   return retValue;
}

int CB_OP_E9h_SET5C_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_E9h_SET5C(memory,z80);

   return retValue;
}

int CB_OP_EAh_SET5D_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_EAh_SET5D(memory,z80);

   return retValue;
}

int CB_OP_EBh_SET5E_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_EBh_SET5E(memory,z80);

   return retValue;
}

int CB_OP_ECh_SET5H_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_ECh_SET5H(memory,z80);

   return retValue;
}

int CB_OP_EDh_SET5L_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_EDh_SET5L(memory,z80);

   return retValue;
}

int CB_OP_EEh_SET5HL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_EEh_SET5HL(memory,z80);

   return retValue;
}

int CB_OP_EFh_SET5A_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_EFh_SET5A(memory,z80);

   return retValue;
}


int CB_OP_F0h_SET6B_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_F0h_SET6B(memory,z80);

   return retValue;
}

int CB_OP_F1h_SET6C_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_F1h_SET6C(memory,z80);

   return retValue;
}

int CB_OP_F2h_SET6D_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_F2h_SET6D(memory,z80);

   return retValue;
}

int CB_OP_F3h_SET6E_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_F3h_SET6E(memory,z80);

   return retValue;
}

int CB_OP_F4h_SET6H_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_F4h_SET6H(memory,z80);

   return retValue;
}

int CB_OP_F5h_SET6L_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_F5h_SET6L(memory,z80);

   return retValue;
}

int CB_OP_F6h_SET6HL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_F6h_SET6HL(memory,z80);

   return retValue;
}

int CB_OP_F7h_SET6A_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_F7h_SET6A(memory,z80);

   return retValue;
}

int CB_OP_F8h_SET7B_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_F8h_SET7B(memory,z80);

   return retValue;
}

int CB_OP_F9h_SET7C_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_F9h_SET7C(memory,z80);

   return retValue;
}

int CB_OP_FAh_SET7D_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_FAh_SET7D(memory,z80);

   return retValue;
}

int CB_OP_FBh_SET7E_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_FBh_SET7E(memory,z80);

   return retValue;
}

int CB_OP_FCh_SET7H_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_FCh_SET7H(memory,z80);

   return retValue;
}

int CB_OP_FDh_SET7L_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_FDh_SET7L(memory,z80);

   return retValue;
}

int CB_OP_FEh_SET7HL_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_FEh_SET7HL(memory,z80);

   return retValue;
}

int CB_OP_FFh_SET7A_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = CB_OP_FFh_SET7A(memory,z80);

   return retValue;
}
