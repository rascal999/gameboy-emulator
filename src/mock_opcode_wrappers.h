#pragma once

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
//   #include "mock_opcode_wrappers.h"
   #include "mock_z80.h"
#else
   #include "cartridge.h"
   #include "debug.h"
   #include "display.h"
   #include "error.h"
   #include "memory.h"
   #include "opcode_attributes.h"
//   #include "opcode_wrappers.h"
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

int OP_not_implemented(Memory * memory, Z80 * z80);
int OP_invalid(Memory * memory, Z80 * z80);
int OP_00h_NOP_wrapper(Memory * memory, Z80 * z80);
int OP_01h_LDBCnn_wrapper(Memory * memory, Z80 * z80);
int OP_02h_LDBCA_wrapper(Memory * memory, Z80 * z80);
int OP_03h_INCBC_wrapper(Memory * memory, Z80 * z80);
int OP_04h_INCB_wrapper(Memory * memory, Z80 * z80);
int OP_05h_DECB_wrapper(Memory * memory, Z80 * z80);
int OP_06h_LDBn_wrapper(Memory * memory, Z80 * z80);
int OP_07h_RLCA_wrapper(Memory * memory, Z80 * z80);
int OP_08h_LDnnSP_wrapper(Memory * memory, Z80 * z80);
int OP_09h_ADDHLBC_wrapper(Memory * memory, Z80 * z80);
int OP_0Ah_LDABC_wrapper(Memory * memory, Z80 * z80);
int OP_0Bh_DECBC_wrapper(Memory * memory, Z80 * z80);
int OP_0Ch_INCC_wrapper(Memory * memory, Z80 * z80);
int OP_0Dh_DECC_wrapper(Memory * memory, Z80 * z80);
int OP_0Eh_LDCn_wrapper(Memory * memory, Z80 * z80);
int OP_0Fh_RRCA_wrapper(Memory * memory, Z80 * z80);

int OP_10h_STOP0_wrapper(Memory * memory, Z80 * z80);
int OP_11h_LDDEnn_wrapper(Memory * memory, Z80 * z80);
int OP_12h_LDDEA_wrapper(Memory * memory, Z80 * z80);
int OP_13h_INCDE_wrapper(Memory * memory, Z80 * z80);
int OP_14h_INCD_wrapper(Memory * memory, Z80 * z80);
int OP_15h_DECD_wrapper(Memory * memory, Z80 * z80);
int OP_16h_LDn_wrapper(Memory * memory, Z80 * z80);
int OP_17h_RLA_wrapper(Memory * memory, Z80 * z80);
int OP_18h_JRn_wrapper(Memory * memory, Z80 * z80);
int OP_19h_ADDHLDE_wrapper(Memory * memory, Z80 * z80);
int OP_1Ah_LDADE_wrapper(Memory * memory, Z80 * z80);
int OP_1Bh_DECDE_wrapper(Memory * memory, Z80 * z80);
int OP_1Ch_INCE_wrapper(Memory * memory, Z80 * z80);
int OP_1Dh_DECE_wrapper(Memory * memory, Z80 * z80);
int OP_1Eh_LDEn_wrapper(Memory * memory, Z80 * z80);
int OP_1Fh_RRA_wrapper(Memory * memory, Z80 * z80);

int OP_20h_JRNZn_wrapper(Memory * memory, Z80 * z80);
int OP_21h_LDHLnn_wrapper(Memory * memory, Z80 * z80);
int OP_22h_LDIHLA_wrapper(Memory * memory, Z80 * z80);
int OP_23h_INCHL_wrapper(Memory * memory, Z80 * z80);
int OP_24h_INCH_wrapper(Memory * memory, Z80 * z80);
int OP_25h_DECH_wrapper(Memory * memory, Z80 * z80);
int OP_26h_LDHn_wrapper(Memory * memory, Z80 * z80);
int OP_27h_DAA_wrapper(Memory * memory, Z80 * z80);
int OP_28h_JRZn_wrapper(Memory * memory, Z80 * z80);
int OP_29h_ADDHLHL_wrapper(Memory * memory, Z80 * z80);
int OP_2Ah_LDIAHL_wrapper(Memory * memory, Z80 * z80);
int OP_2Bh_DECHL_wrapper(Memory * memory, Z80 * z80);
int OP_2Ch_INCL_wrapper(Memory * memory, Z80 * z80);
int OP_2Dh_DECL_wrapper(Memory * memory, Z80 * z80);
int OP_2Eh_LDLn_wrapper(Memory * memory, Z80 * z80);
int OP_2Fh_CPL_wrapper(Memory * memory, Z80 * z80);

int OP_30h_JRNCn_wrapper(Memory * memory, Z80 * z80);
int OP_31h_LDSPnn_wrapper(Memory * memory, Z80 * z80);
int OP_32h_LDDHLA_wrapper(Memory * memory, Z80 * z80);
int OP_33h_INCSP_wrapper(Memory * memory, Z80 * z80);
int OP_34h_INCHL_wrapper(Memory * memory, Z80 * z80);
int OP_35h_DECHL_wrapper(Memory * memory, Z80 * z80);
int OP_36h_LDHLn_wrapper(Memory * memory, Z80 * z80);
int OP_37h_SCF_wrapper(Memory * memory, Z80 * z80);
int OP_38h_JRCn_wrapper(Memory * memory, Z80 * z80);
int OP_39h_ADDHLSP_wrapper(Memory * memory, Z80 * z80);
int OP_3Ah_LDDAHL_wrapper(Memory * memory, Z80 * z80);
int OP_3Bh_DECSP_wrapper(Memory * memory, Z80 * z80);
int OP_3Ch_INCA_wrapper(Memory * memory, Z80 * z80);
int OP_3Dh_DECA_wrapper(Memory * memory, Z80 * z80);
int OP_3Eh_LDAn_wrapper(Memory * memory, Z80 * z80);
int OP_3Fh_CCF_wrapper(Memory * memory, Z80 * z80);

int OP_40h_LDBB_wrapper(Memory * memory, Z80 * z80);
int OP_41h_LDBC_wrapper(Memory * memory, Z80 * z80);
int OP_42h_LDBD_wrapper(Memory * memory, Z80 * z80);
int OP_43h_LDBE_wrapper(Memory * memory, Z80 * z80);
int OP_44h_LDBH_wrapper(Memory * memory, Z80 * z80);
int OP_45h_LDBL_wrapper(Memory * memory, Z80 * z80);
int OP_46h_LDBHL_wrapper(Memory * memory, Z80 * z80);
int OP_47h_LDBA_wrapper(Memory * memory, Z80 * z80);
int OP_48h_LDCB_wrapper(Memory * memory, Z80 * z80);
int OP_49h_LDC_wrapper(Memory * memory, Z80 * z80);
int OP_4Ah_LDCD_wrapper(Memory * memory, Z80 * z80);
int OP_4Bh_LDCE_wrapper(Memory * memory, Z80 * z80);
int OP_4Ch_LDCH_wrapper(Memory * memory, Z80 * z80);
int OP_4Dh_LDCL_wrapper(Memory * memory, Z80 * z80);
int OP_4Eh_LDCHL_wrapper(Memory * memory, Z80 * z80);
int OP_4Fh_LDCA_wrapper(Memory * memory, Z80 * z80);

int OP_50h_LDDB_wrapper(Memory * memory, Z80 * z80);
int OP_51h_LDDC_wrapper(Memory * memory, Z80 * z80);
int OP_52h_LDDD_wrapper(Memory * memory, Z80 * z80);
int OP_53h_LDDE_wrapper(Memory * memory, Z80 * z80);
int OP_54h_LDDH_wrapper(Memory * memory, Z80 * z80);
int OP_55h_LDDL_wrapper(Memory * memory, Z80 * z80);
int OP_56h_LDDHL_wrapper(Memory * memory, Z80 * z80);
int OP_57h_LDDA_wrapper(Memory * memory, Z80 * z80);
int OP_58h_LDEB_wrapper(Memory * memory, Z80 * z80);
int OP_59h_LDEC_wrapper(Memory * memory, Z80 * z80);
int OP_5Ah_LDED_wrapper(Memory * memory, Z80 * z80);
int OP_5Bh_LDEE_wrapper(Memory * memory, Z80 * z80);
int OP_5Ch_LDEH_wrapper(Memory * memory, Z80 * z80);
int OP_5Dh_LDEL_wrapper(Memory * memory, Z80 * z80);
int OP_5Eh_LDEHL_wrapper(Memory * memory, Z80 * z80);
int OP_5Fh_LDEA_wrapper(Memory * memory, Z80 * z80);

int OP_60h_LDHB_wrapper(Memory * memory, Z80 * z80);
int OP_61h_LDHC_wrapper(Memory * memory, Z80 * z80);
int OP_62h_LDHD_wrapper(Memory * memory, Z80 * z80);
int OP_63h_LDHE_wrapper(Memory * memory, Z80 * z80);
int OP_64h_LDHH_wrapper(Memory * memory, Z80 * z80);
int OP_65h_LDHL_wrapper(Memory * memory, Z80 * z80);
int OP_66h_LDHHL_wrapper(Memory * memory, Z80 * z80);
int OP_67h_LDHA_wrapper(Memory * memory, Z80 * z80);
int OP_68h_LDLB_wrapper(Memory * memory, Z80 * z80);
int OP_69h_LDLC_wrapper(Memory * memory, Z80 * z80);
int OP_6Ah_LDLD_wrapper(Memory * memory, Z80 * z80);
int OP_6Bh_LDLE_wrapper(Memory * memory, Z80 * z80);
int OP_6Ch_LDLH_wrapper(Memory * memory, Z80 * z80);
int OP_6Dh_LDLL_wrapper(Memory * memory, Z80 * z80);
int OP_6Eh_LDLHL_wrapper(Memory * memory, Z80 * z80);
int OP_6Fh_LDLA_wrapper(Memory * memory, Z80 * z80);

int OP_70h_LDHLB_wrapper(Memory * memory, Z80 * z80);
int OP_71h_LDHLC_wrapper(Memory * memory, Z80 * z80);
int OP_72h_LDHLD_wrapper(Memory * memory, Z80 * z80);
int OP_73h_LDHLE_wrapper(Memory * memory, Z80 * z80);
int OP_74h_LDHLH_wrapper(Memory * memory, Z80 * z80);
int OP_75h_LDHLL_wrapper(Memory * memory, Z80 * z80);
int OP_76h_HALT_wrapper(Memory * memory, Z80 * z80);
int OP_77h_LDHLA_wrapper(Memory * memory, Z80 * z80);
int OP_78h_LDAB_wrapper(Memory * memory, Z80 * z80);
int OP_79h_LDAC_wrapper(Memory * memory, Z80 * z80);
int OP_7Ah_LDAD_wrapper(Memory * memory, Z80 * z80);
int OP_7Bh_LDAE_wrapper(Memory * memory, Z80 * z80);
int OP_7Ch_LDAH_wrapper(Memory * memory, Z80 * z80);
int OP_7Dh_LDAL_wrapper(Memory * memory, Z80 * z80);
int OP_7Eh_LDAHL_wrapper(Memory * memory, Z80 * z80);
int OP_7Fh_LDAA_wrapper(Memory * memory, Z80 * z80);

int OP_80h_ADDAB_wrapper(Memory * memory, Z80 * z80);
int OP_81h_ADDAC_wrapper(Memory * memory, Z80 * z80);
int OP_82h_ADDAD_wrapper(Memory * memory, Z80 * z80);
int OP_83h_ADDAE_wrapper(Memory * memory, Z80 * z80);
int OP_84h_ADDAH_wrapper(Memory * memory, Z80 * z80);
int OP_85h_ADDAL_wrapper(Memory * memory, Z80 * z80);
int OP_86h_ADDAHL_wrapper(Memory * memory, Z80 * z80);
int OP_87h_ADDAA_wrapper(Memory * memory, Z80 * z80);
int OP_88h_ADCAB_wrapper(Memory * memory, Z80 * z80);
int OP_89h_ADCAC_wrapper(Memory * memory, Z80 * z80);
int OP_8Ah_ADCAD_wrapper(Memory * memory, Z80 * z80);
int OP_8Bh_ADCAE_wrapper(Memory * memory, Z80 * z80);
int OP_8Ch_ADCAH_wrapper(Memory * memory, Z80 * z80);
int OP_8Dh_ADCAL_wrapper(Memory * memory, Z80 * z80);
int OP_8Eh_ADCAHL_wrapper(Memory * memory, Z80 * z80);
int OP_8Fh_ADCAA_wrapper(Memory * memory, Z80 * z80);

int OP_90h_SUBB_wrapper(Memory * memory, Z80 * z80);
int OP_91h_SUBC_wrapper(Memory * memory, Z80 * z80);
int OP_92h_SUBD_wrapper(Memory * memory, Z80 * z80);
int OP_93h_SUBE_wrapper(Memory * memory, Z80 * z80);
int OP_94h_SUBH_wrapper(Memory * memory, Z80 * z80);
int OP_95h_SUBL_wrapper(Memory * memory, Z80 * z80);
int OP_96h_SUBHL_wrapper(Memory * memory, Z80 * z80);
int OP_97h_SUBA_wrapper(Memory * memory, Z80 * z80);
int OP_98h_SBCAB_wrapper(Memory * memory, Z80 * z80);
int OP_99h_SBCAC_wrapper(Memory * memory, Z80 * z80);
int OP_9Ah_SBCAD_wrapper(Memory * memory, Z80 * z80);
int OP_9Bh_SBCAE_wrapper(Memory * memory, Z80 * z80);
int OP_9Ch_SBCAH_wrapper(Memory * memory, Z80 * z80);
int OP_9Dh_SBCAL_wrapper(Memory * memory, Z80 * z80);
int OP_9Eh_SBCAHL_wrapper(Memory * memory, Z80 * z80);
int OP_9Fh_SBCAA_wrapper(Memory * memory, Z80 * z80);

int OP_A0h_ANDB_wrapper(Memory * memory, Z80 * z80);
int OP_A1h_ANDC_wrapper(Memory * memory, Z80 * z80);
int OP_A2h_ANDD_wrapper(Memory * memory, Z80 * z80);
int OP_A3h_ANDE_wrapper(Memory * memory, Z80 * z80);
int OP_A4h_ANDH_wrapper(Memory * memory, Z80 * z80);
int OP_A5h_ANDL_wrapper(Memory * memory, Z80 * z80);
int OP_A6h_ANDHL_wrapper(Memory * memory, Z80 * z80);
int OP_A7h_ANDA_wrapper(Memory * memory, Z80 * z80);
int OP_A8h_XORB_wrapper(Memory * memory, Z80 * z80);
int OP_A9h_XORC_wrapper(Memory * memory, Z80 * z80);
int OP_AAh_XORD_wrapper(Memory * memory, Z80 * z80);
int OP_ABh_XORE_wrapper(Memory * memory, Z80 * z80);
int OP_ACh_XORH_wrapper(Memory * memory, Z80 * z80);
int OP_ADh_XORL_wrapper(Memory * memory, Z80 * z80);
int OP_AEh_XORHL_wrapper(Memory * memory, Z80 * z80);
int OP_AFh_XORA_wrapper(Memory * memory, Z80 * z80);

int OP_B0h_ORB_wrapper(Memory * memory, Z80 * z80);
int OP_B1h_ORC_wrapper(Memory * memory, Z80 * z80);
int OP_B2h_ORD_wrapper(Memory * memory, Z80 * z80);
int OP_B3h_ORE_wrapper(Memory * memory, Z80 * z80);
int OP_B4h_ORH_wrapper(Memory * memory, Z80 * z80);
int OP_B5h_ORL_wrapper(Memory * memory, Z80 * z80);
int OP_B6h_ORHL_wrapper(Memory * memory, Z80 * z80);
int OP_B7h_ORA_wrapper(Memory * memory, Z80 * z80);
int OP_B8h_CPB_wrapper(Memory * memory, Z80 * z80);
int OP_B9h_CPC_wrapper(Memory * memory, Z80 * z80);
int OP_BAh_CPD_wrapper(Memory * memory, Z80 * z80);
int OP_BBh_CPE_wrapper(Memory * memory, Z80 * z80);
int OP_BCh_CPH_wrapper(Memory * memory, Z80 * z80);
int OP_BDh_CPL_wrapper(Memory * memory, Z80 * z80);
int OP_BEh_CPHL_wrapper(Memory * memory, Z80 * z80);
int OP_BFh_CPA_wrapper(Memory * memory, Z80 * z80);

int OP_C0h_RETNZ_wrapper(Memory * memory, Z80 * z80);
int OP_C1h_POPBC_wrapper(Memory * memory, Z80 * z80);
int OP_C2h_JPNZnn_wrapper(Memory * memory, Z80 * z80);
int OP_C3h_JPnn_wrapper(Memory * memory, Z80 * z80);
int OP_C4h_CALLNZnn_wrapper(Memory * memory, Z80 * z80);
int OP_C5h_PUSHBC_wrapper(Memory * memory, Z80 * z80);
int OP_C6h_ADDAn_wrapper(Memory * memory, Z80 * z80);
int OP_C7h_RST00H_wrapper(Memory * memory, Z80 * z80);
int OP_C8h_RETZ_wrapper(Memory * memory, Z80 * z80);
int OP_C9h_RET_wrapper(Memory * memory, Z80 * z80);
int OP_CAh_JPZnn_wrapper(Memory * memory, Z80 * z80);
int OP_CBh_PREFIXCB_wrapper(Memory * memory, Z80 * z80);
int OP_CCh_CALLZnn_wrapper(Memory * memory, Z80 * z80);
int OP_CDh_CALLnn_wrapper(Memory * memory, Z80 * z80);
int OP_CEh_ADCAn_wrapper(Memory * memory, Z80 * z80);
int OP_CFh_RST08H_wrapper(Memory * memory, Z80 * z80);

int OP_D0h_RETNC_wrapper(Memory * memory, Z80 * z80);
int OP_D1h_POPDE_wrapper(Memory * memory, Z80 * z80);
int OP_D2h_JPNCnn_wrapper(Memory * memory, Z80 * z80);
int OP_D3h_INVALID_wrapper(Memory * memory, Z80 * z80);
int OP_D4h_CALLNCnn_wrapper(Memory * memory, Z80 * z80);
int OP_D5h_PUSHDE_wrapper(Memory * memory, Z80 * z80);
int OP_D6h_SUBn_wrapper(Memory * memory, Z80 * z80);
int OP_D7h_RST10H_wrapper(Memory * memory, Z80 * z80);
int OP_D8h_RETC_wrapper(Memory * memory, Z80 * z80);
int OP_D9h_RETI_wrapper(Memory * memory, Z80 * z80);
int OP_DAh_JPCnn_wrapper(Memory * memory, Z80 * z80);
int OP_DBh_INVALID_wrapper(Memory * memory, Z80 * z80);
int OP_DCh_CALLCnn_wrapper(Memory * memory, Z80 * z80);
int OP_DDh_INVALID_wrapper(Memory * memory, Z80 * z80);
int OP_DEh_SBCAn_wrapper(Memory * memory, Z80 * z80);
int OP_DFh_RST18H_wrapper(Memory * memory, Z80 * z80);

int OP_E0h_LDHnA_wrapper(Memory * memory, Z80 * z80);
int OP_E1h_POPHL_wrapper(Memory * memory, Z80 * z80);
int OP_E2h_LDCA_wrapper(Memory * memory, Z80 * z80);
int OP_E3h_INVALID_wrapper(Memory * memory, Z80 * z80);
int OP_E4h_INVALID_wrapper(Memory * memory, Z80 * z80);
int OP_E5h_PUSHHL_wrapper(Memory * memory, Z80 * z80);
int OP_E6h_ANDn_wrapper(Memory * memory, Z80 * z80);
int OP_E7h_RST20H_wrapper(Memory * memory, Z80 * z80);
int OP_E8h_ADDSPn_wrapper(Memory * memory, Z80 * z80);
int OP_E9h_JPHL_wrapper(Memory * memory, Z80 * z80);
int OP_EAh_LDnnA_wrapper(Memory * memory, Z80 * z80);
int OP_EBh_INVALID_wrapper(Memory * memory, Z80 * z80);
int OP_ECh_INVALID_wrapper(Memory * memory, Z80 * z80);
int OP_EDh_INVALID_wrapper(Memory * memory, Z80 * z80);
int OP_EEh_XORn_wrapper(Memory * memory, Z80 * z80);
int OP_EFh_RST28H_wrapper(Memory * memory, Z80 * z80);

int OP_F0h_LDHAn_wrapper(Memory * memory, Z80 * z80);
int OP_F1h_POPAF_wrapper(Memory * memory, Z80 * z80);
int OP_F2h_LDAC_wrapper(Memory * memory, Z80 * z80);
int OP_F3h_DI_wrapper(Memory * memory, Z80 * z80);
int OP_F4h_INVALID_wrapper(Memory * memory, Z80 * z80);
int OP_F5h_PUSHAF_wrapper(Memory * memory, Z80 * z80);
int OP_F6h_ORn_wrapper(Memory * memory, Z80 * z80);
int OP_F7h_RST30H_wrapper(Memory * memory, Z80 * z80);
int OP_F8h_LDHLSPn_wrapper(Memory * memory, Z80 * z80);
int OP_F9h_LDSPHL_wrapper(Memory * memory, Z80 * z80);
int OP_FAh_LDAnn_wrapper(Memory * memory, Z80 * z80);
int OP_FBh_EI_wrapper(Memory * memory, Z80 * z80);
int OP_FCh_INVALID_wrapper(Memory * memory, Z80 * z80);
int OP_FDh_INVALID_wrapper(Memory * memory, Z80 * z80);
int OP_FEh_CPn_wrapper(Memory * memory, Z80 * z80);
int OP_FFh_RST38H_wrapper(Memory * memory, Z80 * z80);
