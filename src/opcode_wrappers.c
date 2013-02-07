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
   #include "mock_cartridge.h"
   #include "mock_debug.h"
   #include "mock_display.h"
   #include "mock_error.h"
   #include "mock_memory.h"
   #include "mock_opcode_attributes.h"
   #include "mock_opcode_wrappers.h"
   #include "mock_z80.h"
#else
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

int OP_00h_NOP_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_00h_NOP(memory,z80);

   return retValue;
}

int OP_20h_JRNZn_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_20h_JRNZn(memory,z80);

   return retValue;
}

int OP_21h_LDHLnn_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_21h_LDHLnn(memory,z80);

   return retValue;
}

int OP_22h_LDIHLA_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_22h_LDIHLA(memory,z80);

   return retValue;
}

int OP_31h_LDSPnn_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_31h_LDSPnn(memory,z80);

   return retValue;
}

int OP_32h_LDDHLA_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_32h_LDDHLA(memory,z80);

   return retValue;
}

int OP_72h_LDHLD_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_72h_LDHLD(memory,z80);

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

int OP_A7h_ANDA_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_A7h_ANDA(memory,z80);

   return retValue;
}

int OP_AFh_XORA_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_AFh_XORA(memory,z80);

   return retValue;
}

int OP_E0h_LDHAn_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_E0h_LDHAn(memory,z80);

   return retValue;
}

int OP_E2h_LDHCA_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_E2h_LDHCA(memory,z80);

   return retValue;
}

int OP_CBh_PREFIXCB_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_CBh_PREFIXCB(memory,z80);

   return retValue;
}

int OP_FFh_RST38h_wrapper(Memory * memory, Z80 * z80)
{
   int retValue = OP_FFh_RST38h(memory,z80);

   return retValue;
}
