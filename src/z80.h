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
   #define UNIT_TEST 1
#else
   #define UNIT_TEST 0
#endif

#include "cartridge.h"
#include "debug.h"
//#include "display.h"
#include "error.h"
#include "memory.h"
#include "opcode_attributes.h"
#include "opcode_wrappers.h"
//#include "rom.h"
//#include "timer.h"
//#include "z80.h"

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

typedef struct
{
   uint8_t size;
   uint8_t ticks;
   char name[1024];
   // Function pointer
   int (*call)();
} Opcodes;

typedef struct
{
   uint8_t r[0x8];
/*   uint8_t A;
   uint8_t B;
   uint8_t C;
   uint8_t D;
   uint8_t E;
   uint8_t H;
   uint8_t L;
   uint8_t F; */
   uint16_t r16[0x2];
/*   uint16_t PC;
   uint16_t SP; */
} Registers;

struct Z80
{
   Opcodes * op;
   Opcodes * cb_op;
   Opcodes * op_call;

   Registers * r;

   /* CPU ticks of last instruction */
   uint16_t ticks;
};

int InitZ80(Z80 * z80, Registers * registers, Opcodes * op, Opcodes * cb_op);
int InitZ80OpcodeStats(Z80 * z80, Registers * registers);
int ResetZ80(Z80 * z80, Registers * registers, Opcodes * op, Opcodes * cb_op);
int Dispatch(Memory * memory, Z80 * z80);
int Fetch(Memory * memory, Z80 * z80);
int8_t ensure_8b_signed(int8_t value);
int CB_BIT(Memory * memory, Z80 * z80, uint8_t parameters);
int CB_RES(Memory * memory, Z80 * z80, uint8_t parameters);
int CB_SET(Memory * memory, Z80 * z80, uint8_t parameters);
int CB_RLC(Memory * memory, Z80 * z80, uint8_t parameters);
int CB_RRC(Memory * memory, Z80 * z80, uint8_t parameters);
int HertzToMilliseconds(int Hertz);
int decrementHL(Z80 * z80);
int incrementHL(Z80 * z80);
int calculateAdditionFlags(Memory * memory, Z80 * z80, uint8_t dest, uint8_t oldDest, uint8_t oldSrc);
int calculateSubtractionFlags(Memory * memory, Z80 * z80, uint8_t dest, uint8_t oldDest, uint8_t oldSrc);
int calculateAndFlags(Memory * memory, Z80 * z80, uint8_t dest);

int OP_LDXd8(Memory * memory, Z80 * z80, uint8_t x);
int OP_LDXd16(Memory * memory, Z80 * z80, uint8_t x);
int OP_LDXY(Memory * memory, Z80 * z80, uint8_t x);
int OP_LDXYZ(Memory * memory, Z80 * z80, uint8_t x, uint8_t yz);
int OP_LDHLX(Memory * memory, Z80 * z80, uint8_t x);
int OP_INCX(Memory * memory, Z80 * z80, uint8_t x);

int OP_00h_NOP(Memory * memory, Z80 * z80);
int OP_01h_LDBCd16(Memory * memory, Z80 * z80);
int OP_02h_LDBCA(Memory * memory, Z80 * z80);
int OP_03h_INCBC(Memory * memory, Z80 * z80);
int OP_04h_INCB(Memory * memory, Z80 * z80);
int OP_05h_DECB(Memory * memory, Z80 * z80);
int OP_06h_LDBd8(Memory * memory, Z80 * z80);
int OP_07h_RLCA(Memory * memory, Z80 * z80);
int OP_08h_LDnnSP(Memory * memory, Z80 * z80);
int OP_09h_ADDHLBC(Memory * memory, Z80 * z80);
int OP_0Ah_LDABC(Memory * memory, Z80 * z80);
int OP_0Bh_DECBC(Memory * memory, Z80 * z80);
int OP_0Ch_INCC(Memory * memory, Z80 * z80);
int OP_0Dh_DECC(Memory * memory, Z80 * z80);
int OP_0Eh_LDCd8(Memory * memory, Z80 * z80);
int OP_0Fh_RRCA(Memory * memory, Z80 * z80);

int OP_10h_STOP0(Memory * memory, Z80 * z80);
int OP_11h_LDDEd16(Memory * memory, Z80 * z80);
int OP_12h_LDDEA(Memory * memory, Z80 * z80);
int OP_13h_INCDE(Memory * memory, Z80 * z80);
int OP_14h_INCD(Memory * memory, Z80 * z80);
int OP_15h_DECD(Memory * memory, Z80 * z80);
int OP_16h_LDd8(Memory * memory, Z80 * z80);
int OP_17h_RLA(Memory * memory, Z80 * z80);
int OP_18h_JRr8(Memory * memory, Z80 * z80);
int OP_19h_ADDHLDE(Memory * memory, Z80 * z80);
int OP_1Ah_LDADE(Memory * memory, Z80 * z80);
int OP_1Bh_DECDE(Memory * memory, Z80 * z80);
int OP_1Ch_INCE(Memory * memory, Z80 * z80);
int OP_1Dh_DECE(Memory * memory, Z80 * z80);
int OP_1Eh_LDEd8(Memory * memory, Z80 * z80);
int OP_1Fh_RRA(Memory * memory, Z80 * z80);

int OP_20h_JRNZr8(Memory * memory, Z80 * z80);
int OP_21h_LDHLd16(Memory * memory, Z80 * z80);
int OP_22h_LDIHLA(Memory * memory, Z80 * z80);
int OP_23h_INCHL(Memory * memory, Z80 * z80);
int OP_24h_INCH(Memory * memory, Z80 * z80);
int OP_25h_DECH(Memory * memory, Z80 * z80);
int OP_26h_LDHd8(Memory * memory, Z80 * z80);
int OP_27h_DAA(Memory * memory, Z80 * z80);
int OP_28h_JRZr8(Memory * memory, Z80 * z80);
int OP_29h_ADDHLHL(Memory * memory, Z80 * z80);
int OP_2Ah_LDIAHL(Memory * memory, Z80 * z80);
int OP_2Bh_DECHL(Memory * memory, Z80 * z80);
int OP_2Ch_INCL(Memory * memory, Z80 * z80);
int OP_2Dh_DECL(Memory * memory, Z80 * z80);
int OP_2Eh_LDLd8(Memory * memory, Z80 * z80);
int OP_2Fh_CPL(Memory * memory, Z80 * z80);

int OP_30h_JRNCr8(Memory * memory, Z80 * z80);
int OP_31h_LDSPd16(Memory * memory, Z80 * z80);
int OP_32h_LDDHLA(Memory * memory, Z80 * z80);
int OP_33h_INCSP(Memory * memory, Z80 * z80);
int OP_34h_INCHL(Memory * memory, Z80 * z80);
int OP_35h_DECHL(Memory * memory, Z80 * z80);
int OP_36h_LDHLd8(Memory * memory, Z80 * z80);
int OP_37h_SCF(Memory * memory, Z80 * z80);
int OP_38h_JRCr8(Memory * memory, Z80 * z80);
int OP_39h_ADDHLSP(Memory * memory, Z80 * z80);
int OP_3Ah_LDDAHL(Memory * memory, Z80 * z80);
int OP_3Bh_DECSP(Memory * memory, Z80 * z80);
int OP_3Ch_INCA(Memory * memory, Z80 * z80);
int OP_3Dh_DECA(Memory * memory, Z80 * z80);
int OP_3Eh_LDAd8(Memory * memory, Z80 * z80);
int OP_3Fh_CCF(Memory * memory, Z80 * z80);

int OP_40h_LDBB(Memory * memory, Z80 * z80);
int OP_41h_LDBC(Memory * memory, Z80 * z80);
int OP_42h_LDBD(Memory * memory, Z80 * z80);
int OP_43h_LDBE(Memory * memory, Z80 * z80);
int OP_44h_LDBH(Memory * memory, Z80 * z80);
int OP_45h_LDBL(Memory * memory, Z80 * z80);
int OP_46h_LDBHL(Memory * memory, Z80 * z80);
int OP_47h_LDBA(Memory * memory, Z80 * z80);
int OP_48h_LDCB(Memory * memory, Z80 * z80);
int OP_49h_LDC(Memory * memory, Z80 * z80);
int OP_4Ah_LDCD(Memory * memory, Z80 * z80);
int OP_4Bh_LDCE(Memory * memory, Z80 * z80);
int OP_4Ch_LDCH(Memory * memory, Z80 * z80);
int OP_4Dh_LDCL(Memory * memory, Z80 * z80);
int OP_4Eh_LDCHL(Memory * memory, Z80 * z80);
int OP_4Fh_LDCA(Memory * memory, Z80 * z80);

int OP_50h_LDDB(Memory * memory, Z80 * z80);
int OP_51h_LDDC(Memory * memory, Z80 * z80);
int OP_52h_LDDD(Memory * memory, Z80 * z80);
int OP_53h_LDDE(Memory * memory, Z80 * z80);
int OP_54h_LDDH(Memory * memory, Z80 * z80);
int OP_55h_LDDL(Memory * memory, Z80 * z80);
int OP_56h_LDDHL(Memory * memory, Z80 * z80);
int OP_57h_LDDA(Memory * memory, Z80 * z80);
int OP_58h_LDEB(Memory * memory, Z80 * z80);
int OP_59h_LDEC(Memory * memory, Z80 * z80);
int OP_5Ah_LDED(Memory * memory, Z80 * z80);
int OP_5Bh_LDEE(Memory * memory, Z80 * z80);
int OP_5Ch_LDEH(Memory * memory, Z80 * z80);
int OP_5Dh_LDEL(Memory * memory, Z80 * z80);
int OP_5Eh_LDEHL(Memory * memory, Z80 * z80);
int OP_5Fh_LDEA(Memory * memory, Z80 * z80);

int OP_60h_LDHB(Memory * memory, Z80 * z80);
int OP_61h_LDHC(Memory * memory, Z80 * z80);
int OP_62h_LDHD(Memory * memory, Z80 * z80);
int OP_63h_LDHE(Memory * memory, Z80 * z80);
int OP_64h_LDHH(Memory * memory, Z80 * z80);
int OP_65h_LDHL(Memory * memory, Z80 * z80);
int OP_66h_LDHHL(Memory * memory, Z80 * z80);
int OP_67h_LDHA(Memory * memory, Z80 * z80);
int OP_68h_LDLB(Memory * memory, Z80 * z80);
int OP_69h_LDLC(Memory * memory, Z80 * z80);
int OP_6Ah_LDLD(Memory * memory, Z80 * z80);
int OP_6Bh_LDLE(Memory * memory, Z80 * z80);
int OP_6Ch_LDLH(Memory * memory, Z80 * z80);
int OP_6Dh_LDLL(Memory * memory, Z80 * z80);
int OP_6Eh_LDLHL(Memory * memory, Z80 * z80);
int OP_6Fh_LDLA(Memory * memory, Z80 * z80);

int OP_70h_LDHLB(Memory * memory, Z80 * z80);
int OP_71h_LDHLC(Memory * memory, Z80 * z80);
int OP_72h_LDHLD(Memory * memory, Z80 * z80);
int OP_73h_LDHLE(Memory * memory, Z80 * z80);
int OP_74h_LDHLH(Memory * memory, Z80 * z80);
int OP_75h_LDHLL(Memory * memory, Z80 * z80);
int OP_76h_HALT(Memory * memory, Z80 * z80);
int OP_77h_LDHLA(Memory * memory, Z80 * z80);
int OP_78h_LDAB(Memory * memory, Z80 * z80);
int OP_79h_LDAC(Memory * memory, Z80 * z80);
int OP_7Ah_LDAD(Memory * memory, Z80 * z80);
int OP_7Bh_LDAE(Memory * memory, Z80 * z80);
int OP_7Ch_LDAH(Memory * memory, Z80 * z80);
int OP_7Dh_LDAL(Memory * memory, Z80 * z80);
int OP_7Eh_LDAHL(Memory * memory, Z80 * z80);
int OP_7Fh_LDAA(Memory * memory, Z80 * z80);

int OP_80h_ADDAB(Memory * memory, Z80 * z80);
int OP_81h_ADDAC(Memory * memory, Z80 * z80);
int OP_82h_ADDAD(Memory * memory, Z80 * z80);
int OP_83h_ADDAE(Memory * memory, Z80 * z80);
int OP_84h_ADDAH(Memory * memory, Z80 * z80);
int OP_85h_ADDAL(Memory * memory, Z80 * z80);
int OP_86h_ADDAHL(Memory * memory, Z80 * z80);
int OP_87h_ADDAA(Memory * memory, Z80 * z80);
int OP_88h_ADCAB(Memory * memory, Z80 * z80);
int OP_89h_ADCAC(Memory * memory, Z80 * z80);
int OP_8Ah_ADCAD(Memory * memory, Z80 * z80);
int OP_8Bh_ADCAE(Memory * memory, Z80 * z80);
int OP_8Ch_ADCAH(Memory * memory, Z80 * z80);
int OP_8Dh_ADCAL(Memory * memory, Z80 * z80);
int OP_8Eh_ADCAHL(Memory * memory, Z80 * z80);
int OP_8Fh_ADCAA(Memory * memory, Z80 * z80);

int OP_90h_SUBB(Memory * memory, Z80 * z80);
int OP_91h_SUBC(Memory * memory, Z80 * z80);
int OP_92h_SUBD(Memory * memory, Z80 * z80);
int OP_93h_SUBE(Memory * memory, Z80 * z80);
int OP_94h_SUBH(Memory * memory, Z80 * z80);
int OP_95h_SUBL(Memory * memory, Z80 * z80);
int OP_96h_SUBHL(Memory * memory, Z80 * z80);
int OP_97h_SUBA(Memory * memory, Z80 * z80);
int OP_98h_SBCAB(Memory * memory, Z80 * z80);
int OP_99h_SBCAC(Memory * memory, Z80 * z80);
int OP_9Ah_SBCAD(Memory * memory, Z80 * z80);
int OP_9Bh_SBCAE(Memory * memory, Z80 * z80);
int OP_9Ch_SBCAH(Memory * memory, Z80 * z80);
int OP_9Dh_SBCAL(Memory * memory, Z80 * z80);
int OP_9Eh_SBCAHL(Memory * memory, Z80 * z80);
int OP_9Fh_SBCAA(Memory * memory, Z80 * z80);

int OP_A0h_ANDB(Memory * memory, Z80 * z80);
int OP_A1h_ANDC(Memory * memory, Z80 * z80);
int OP_A2h_ANDD(Memory * memory, Z80 * z80);
int OP_A3h_ANDE(Memory * memory, Z80 * z80);
int OP_A4h_ANDH(Memory * memory, Z80 * z80);
int OP_A5h_ANDL(Memory * memory, Z80 * z80);
int OP_A6h_ANDHL(Memory * memory, Z80 * z80);
int OP_A7h_ANDA(Memory * memory, Z80 * z80);
int OP_A8h_XORB(Memory * memory, Z80 * z80);
int OP_A9h_XORC(Memory * memory, Z80 * z80);
int OP_AAh_XORD(Memory * memory, Z80 * z80);
int OP_ABh_XORE(Memory * memory, Z80 * z80);
int OP_ACh_XORH(Memory * memory, Z80 * z80);
int OP_ADh_XORL(Memory * memory, Z80 * z80);
int OP_AEh_XORHL(Memory * memory, Z80 * z80);
int OP_AFh_XORA(Memory * memory, Z80 * z80);

int OP_B0h_ORB(Memory * memory, Z80 * z80);
int OP_B1h_ORC(Memory * memory, Z80 * z80);
int OP_B2h_ORD(Memory * memory, Z80 * z80);
int OP_B3h_ORE(Memory * memory, Z80 * z80);
int OP_B4h_ORH(Memory * memory, Z80 * z80);
int OP_B5h_ORL(Memory * memory, Z80 * z80);
int OP_B6h_ORHL(Memory * memory, Z80 * z80);
int OP_B7h_ORA(Memory * memory, Z80 * z80);
int OP_B8h_CPB(Memory * memory, Z80 * z80);
int OP_B9h_CPC(Memory * memory, Z80 * z80);
int OP_BAh_CPD(Memory * memory, Z80 * z80);
int OP_BBh_CPE(Memory * memory, Z80 * z80);
int OP_BCh_CPH(Memory * memory, Z80 * z80);
int OP_BDh_CPL(Memory * memory, Z80 * z80);
int OP_BEh_CPHL(Memory * memory, Z80 * z80);
int OP_BFh_CPA(Memory * memory, Z80 * z80);

int OP_C0h_RETNZ(Memory * memory, Z80 * z80);
int OP_C1h_POPBC(Memory * memory, Z80 * z80);
int OP_C2h_JPNZa16(Memory * memory, Z80 * z80);
int OP_C3h_JPa16(Memory * memory, Z80 * z80);
int OP_C4h_CALLNZa16(Memory * memory, Z80 * z80);
int OP_C5h_PUSHBC(Memory * memory, Z80 * z80);
int OP_C6h_ADDAd8(Memory * memory, Z80 * z80);
int OP_C7h_RST00H(Memory * memory, Z80 * z80);
int OP_C8h_RETZ(Memory * memory, Z80 * z80);
int OP_C9h_RET(Memory * memory, Z80 * z80);
int OP_CAh_JPZa16(Memory * memory, Z80 * z80);
int OP_CBh_PREFIXCB(Memory * memory, Z80 * z80);
int OP_CCh_CALLZa16(Memory * memory, Z80 * z80);
int OP_CDh_CALLa16(Memory * memory, Z80 * z80);
int OP_CEh_ADCAd8(Memory * memory, Z80 * z80);
int OP_CFh_RST08H(Memory * memory, Z80 * z80);

int OP_D0h_RETNC(Memory * memory, Z80 * z80);
int OP_D1h_POPDE(Memory * memory, Z80 * z80);
int OP_D2h_JPNCa16(Memory * memory, Z80 * z80);
int OP_D3h_INVALID(Memory * memory, Z80 * z80);
int OP_D4h_CALLNCa16(Memory * memory, Z80 * z80);
int OP_D5h_PUSHDE(Memory * memory, Z80 * z80);
int OP_D6h_SUBd8(Memory * memory, Z80 * z80);
int OP_D7h_RST10H(Memory * memory, Z80 * z80);
int OP_D8h_RETC(Memory * memory, Z80 * z80);
int OP_D9h_RETI(Memory * memory, Z80 * z80);
int OP_DAh_JPCa16(Memory * memory, Z80 * z80);
int OP_DBh_INVALID(Memory * memory, Z80 * z80);
int OP_DCh_CALLCa16(Memory * memory, Z80 * z80);
int OP_DDh_INVALID(Memory * memory, Z80 * z80);
int OP_DEh_SBCAd8(Memory * memory, Z80 * z80);
int OP_DFh_RST18H(Memory * memory, Z80 * z80);

int OP_E0h_LDHa8A(Memory * memory, Z80 * z80);
int OP_E1h_POPHL(Memory * memory, Z80 * z80);
int OP_E2h_LDHCA(Memory * memory, Z80 * z80);
int OP_E3h_INVALID(Memory * memory, Z80 * z80);
int OP_E4h_INVALID(Memory * memory, Z80 * z80);
int OP_E5h_PUSHHL(Memory * memory, Z80 * z80);
int OP_E6h_ANDd8(Memory * memory, Z80 * z80);
int OP_E7h_RST20H(Memory * memory, Z80 * z80);
int OP_E8h_ADDSPr8(Memory * memory, Z80 * z80);
int OP_E9h_JPHL(Memory * memory, Z80 * z80);
int OP_EAh_LDnnA(Memory * memory, Z80 * z80);
int OP_EBh_INVALID(Memory * memory, Z80 * z80);
int OP_ECh_INVALID(Memory * memory, Z80 * z80);
int OP_EDh_INVALID(Memory * memory, Z80 * z80);
int OP_EEh_XORd8(Memory * memory, Z80 * z80);
int OP_EFh_RST28H(Memory * memory, Z80 * z80);

int OP_F0h_LDHAa8(Memory * memory, Z80 * z80);
int OP_F1h_POPAF(Memory * memory, Z80 * z80);
int OP_F2h_LDAC(Memory * memory, Z80 * z80);
int OP_F3h_DI(Memory * memory, Z80 * z80);
int OP_F4h_INVALID(Memory * memory, Z80 * z80);
int OP_F5h_PUSHAF(Memory * memory, Z80 * z80);
int OP_F6h_ORd8(Memory * memory, Z80 * z80);
int OP_F7h_RST30H(Memory * memory, Z80 * z80);
int OP_F8h_LDHLSPr8(Memory * memory, Z80 * z80);
int OP_F9h_LDSPHL(Memory * memory, Z80 * z80);
int OP_FAh_LDAa16(Memory * memory, Z80 * z80);
int OP_FBh_EI(Memory * memory, Z80 * z80);
int OP_FCh_INVALID(Memory * memory, Z80 * z80);
int OP_FDh_INVALID(Memory * memory, Z80 * z80);
int OP_FEh_CPd8(Memory * memory, Z80 * z80);
int OP_FFh_RST38H(Memory * memory, Z80 * z80);

// CB Prefix

int CB_OP_00h_RLCB(Memory * memory, Z80 * z80);
int CB_OP_01h_RLCC(Memory * memory, Z80 * z80);
int CB_OP_02h_RLCD(Memory * memory, Z80 * z80);
int CB_OP_03h_RLCE(Memory * memory, Z80 * z80);
int CB_OP_04h_RLCH(Memory * memory, Z80 * z80);
int CB_OP_05h_RLCL(Memory * memory, Z80 * z80);
int CB_OP_06h_RLCHL(Memory * memory, Z80 * z80);
int CB_OP_07h_RLCA(Memory * memory, Z80 * z80);
int CB_OP_08h_RRCB(Memory * memory, Z80 * z80);
int CB_OP_09h_RRCC(Memory * memory, Z80 * z80);
int CB_OP_0Ah_RRCD(Memory * memory, Z80 * z80);
int CB_OP_0Bh_RRCE(Memory * memory, Z80 * z80);
int CB_OP_0Ch_RRCH(Memory * memory, Z80 * z80);
int CB_OP_0Dh_RRCL(Memory * memory, Z80 * z80);
int CB_OP_0Eh_RRCHL(Memory * memory, Z80 * z80);
int CB_OP_0Fh_RRCA(Memory * memory, Z80 * z80);

int CB_OP_10h_RLB(Memory * memory, Z80 * z80);
int CB_OP_11h_RLC(Memory * memory, Z80 * z80);
int CB_OP_12h_RLD(Memory * memory, Z80 * z80);
int CB_OP_13h_RLE(Memory * memory, Z80 * z80);
int CB_OP_14h_RLH(Memory * memory, Z80 * z80);
int CB_OP_15h_RLL(Memory * memory, Z80 * z80);
int CB_OP_16h_RLHL(Memory * memory, Z80 * z80);
int CB_OP_17h_RLA(Memory * memory, Z80 * z80);
int CB_OP_18h_RRB(Memory * memory, Z80 * z80);
int CB_OP_19h_RRC(Memory * memory, Z80 * z80);
int CB_OP_1Ah_RRD(Memory * memory, Z80 * z80);
int CB_OP_1Bh_RRE(Memory * memory, Z80 * z80);
int CB_OP_1Ch_RRH(Memory * memory, Z80 * z80);
int CB_OP_1Dh_RRL(Memory * memory, Z80 * z80);
int CB_OP_1Eh_RRHL(Memory * memory, Z80 * z80);
int CB_OP_1Fh_RRA(Memory * memory, Z80 * z80);

int CB_OP_20h_SLAB(Memory * memory, Z80 * z80);
int CB_OP_21h_SLAC(Memory * memory, Z80 * z80);
int CB_OP_22h_SLAD(Memory * memory, Z80 * z80);
int CB_OP_23h_SLAE(Memory * memory, Z80 * z80);
int CB_OP_24h_SLAH(Memory * memory, Z80 * z80);
int CB_OP_25h_SLAL(Memory * memory, Z80 * z80);
int CB_OP_26h_SLAHL(Memory * memory, Z80 * z80);
int CB_OP_27h_SLAA(Memory * memory, Z80 * z80);
int CB_OP_28h_SRAB(Memory * memory, Z80 * z80);
int CB_OP_29h_SRAC(Memory * memory, Z80 * z80);
int CB_OP_2Ah_SRAD(Memory * memory, Z80 * z80);
int CB_OP_2Bh_SRAE(Memory * memory, Z80 * z80);
int CB_OP_2Ch_SRAH(Memory * memory, Z80 * z80);
int CB_OP_2Dh_SRAL(Memory * memory, Z80 * z80);
int CB_OP_2Eh_SRAHL(Memory * memory, Z80 * z80);
int CB_OP_2Fh_SRAA(Memory * memory, Z80 * z80);

int CB_OP_30h_SWAPB(Memory * memory, Z80 * z80);
int CB_OP_31h_SWAPC(Memory * memory, Z80 * z80);
int CB_OP_32h_SWAPD(Memory * memory, Z80 * z80);
int CB_OP_33h_SWAPE(Memory * memory, Z80 * z80);
int CB_OP_34h_SWAPH(Memory * memory, Z80 * z80);
int CB_OP_35h_SWAPL(Memory * memory, Z80 * z80);
int CB_OP_36h_SWAPHL(Memory * memory, Z80 * z80);
int CB_OP_37h_SWAPA(Memory * memory, Z80 * z80);
int CB_OP_38h_SRLB(Memory * memory, Z80 * z80);
int CB_OP_39h_SRLC(Memory * memory, Z80 * z80);
int CB_OP_3Ah_SRLD(Memory * memory, Z80 * z80);
int CB_OP_3Bh_SRLE(Memory * memory, Z80 * z80);
int CB_OP_3Ch_SRLH(Memory * memory, Z80 * z80);
int CB_OP_3Dh_SRLL(Memory * memory, Z80 * z80);
int CB_OP_3Eh_SRLHL(Memory * memory, Z80 * z80);
int CB_OP_3Fh_SRLA(Memory * memory, Z80 * z80);

int CB_OP_40h_BIT0B(Memory * memory, Z80 * z80);
int CB_OP_41h_BIT0C(Memory * memory, Z80 * z80);
int CB_OP_42h_BIT0D(Memory * memory, Z80 * z80);
int CB_OP_43h_BIT0E(Memory * memory, Z80 * z80);
int CB_OP_44h_BIT0H(Memory * memory, Z80 * z80);
int CB_OP_45h_BIT0L(Memory * memory, Z80 * z80);
int CB_OP_46h_BIT0HL(Memory * memory, Z80 * z80);
int CB_OP_47h_BIT0A(Memory * memory, Z80 * z80);
int CB_OP_48h_BIT1B(Memory * memory, Z80 * z80);
int CB_OP_49h_BIT1C(Memory * memory, Z80 * z80);
int CB_OP_4Ah_BIT1D(Memory * memory, Z80 * z80);
int CB_OP_4Bh_BIT1E(Memory * memory, Z80 * z80);
int CB_OP_4Ch_BIT1H(Memory * memory, Z80 * z80);
int CB_OP_4Dh_BIT1L(Memory * memory, Z80 * z80);
int CB_OP_4Eh_BIT1HL(Memory * memory, Z80 * z80);
int CB_OP_4Fh_BIT1A(Memory * memory, Z80 * z80);

int CB_OP_50h_BIT2B(Memory * memory, Z80 * z80);
int CB_OP_51h_BIT2C(Memory * memory, Z80 * z80);
int CB_OP_52h_BIT2D(Memory * memory, Z80 * z80);
int CB_OP_53h_BIT2E(Memory * memory, Z80 * z80);
int CB_OP_54h_BIT2H(Memory * memory, Z80 * z80);
int CB_OP_55h_BIT2L(Memory * memory, Z80 * z80);
int CB_OP_56h_BIT2HL(Memory * memory, Z80 * z80);
int CB_OP_57h_BIT2A(Memory * memory, Z80 * z80);
int CB_OP_58h_BIT3B(Memory * memory, Z80 * z80);
int CB_OP_59h_BIT3C(Memory * memory, Z80 * z80);
int CB_OP_5Ah_BIT3D(Memory * memory, Z80 * z80);
int CB_OP_5Bh_BIT3E(Memory * memory, Z80 * z80);
int CB_OP_5Ch_BIT3H(Memory * memory, Z80 * z80);
int CB_OP_5Dh_BIT3L(Memory * memory, Z80 * z80);
int CB_OP_5Eh_BIT3HL(Memory * memory, Z80 * z80);
int CB_OP_5Fh_BIT3A(Memory * memory, Z80 * z80);

int CB_OP_60h_BIT4B(Memory * memory, Z80 * z80);
int CB_OP_61h_BIT4C(Memory * memory, Z80 * z80);
int CB_OP_62h_BIT4D(Memory * memory, Z80 * z80);
int CB_OP_63h_BIT4E(Memory * memory, Z80 * z80);
int CB_OP_64h_BIT4H(Memory * memory, Z80 * z80);
int CB_OP_65h_BIT4L(Memory * memory, Z80 * z80);
int CB_OP_66h_BIT4HL(Memory * memory, Z80 * z80);
int CB_OP_67h_BIT4A(Memory * memory, Z80 * z80);
int CB_OP_68h_BIT5B(Memory * memory, Z80 * z80);
int CB_OP_69h_BIT5C(Memory * memory, Z80 * z80);
int CB_OP_6Ah_BIT5D(Memory * memory, Z80 * z80);
int CB_OP_6Bh_BIT5E(Memory * memory, Z80 * z80);
int CB_OP_6Ch_BIT5H(Memory * memory, Z80 * z80);
int CB_OP_6Dh_BIT5L(Memory * memory, Z80 * z80);
int CB_OP_6Eh_BIT5HL(Memory * memory, Z80 * z80);
int CB_OP_6Fh_BIT5A(Memory * memory, Z80 * z80);

int CB_OP_70h_BIT6B(Memory * memory, Z80 * z80);
int CB_OP_71h_BIT6C(Memory * memory, Z80 * z80);
int CB_OP_72h_BIT6D(Memory * memory, Z80 * z80);
int CB_OP_73h_BIT6E(Memory * memory, Z80 * z80);
int CB_OP_74h_BIT6H(Memory * memory, Z80 * z80);
int CB_OP_75h_BIT6L(Memory * memory, Z80 * z80);
int CB_OP_76h_BIT6HL(Memory * memory, Z80 * z80);
int CB_OP_77h_BIT6A(Memory * memory, Z80 * z80);
int CB_OP_78h_BIT7B(Memory * memory, Z80 * z80);
int CB_OP_79h_BIT7C(Memory * memory, Z80 * z80);
int CB_OP_7Ah_BIT7D(Memory * memory, Z80 * z80);
int CB_OP_7Bh_BIT7E(Memory * memory, Z80 * z80);
int CB_OP_7Ch_BIT7H(Memory * memory, Z80 * z80);
int CB_OP_7Dh_BIT7L(Memory * memory, Z80 * z80);
int CB_OP_7Eh_BIT7HL(Memory * memory, Z80 * z80);
int CB_OP_7Fh_BIT7A(Memory * memory, Z80 * z80);

int CB_OP_80h_RES0B(Memory * memory, Z80 * z80);
int CB_OP_81h_RES0C(Memory * memory, Z80 * z80);
int CB_OP_82h_RES0D(Memory * memory, Z80 * z80);
int CB_OP_83h_RES0E(Memory * memory, Z80 * z80);
int CB_OP_84h_RES0H(Memory * memory, Z80 * z80);
int CB_OP_85h_RES0L(Memory * memory, Z80 * z80);
int CB_OP_86h_RES0HL(Memory * memory, Z80 * z80);
int CB_OP_87h_RES0A(Memory * memory, Z80 * z80);
int CB_OP_88h_RES1B(Memory * memory, Z80 * z80);
int CB_OP_89h_RES1C(Memory * memory, Z80 * z80);
int CB_OP_8Ah_RES1D(Memory * memory, Z80 * z80);
int CB_OP_8Bh_RES1E(Memory * memory, Z80 * z80);
int CB_OP_8Ch_RES1H(Memory * memory, Z80 * z80);
int CB_OP_8Dh_RES1L(Memory * memory, Z80 * z80);
int CB_OP_8Eh_RES1HL(Memory * memory, Z80 * z80);
int CB_OP_8Fh_RES1A(Memory * memory, Z80 * z80);

int CB_OP_90h_RES2B(Memory * memory, Z80 * z80);
int CB_OP_91h_RES2C(Memory * memory, Z80 * z80);
int CB_OP_92h_RES2D(Memory * memory, Z80 * z80);
int CB_OP_93h_RES2E(Memory * memory, Z80 * z80);
int CB_OP_94h_RES2H(Memory * memory, Z80 * z80);
int CB_OP_95h_RES2L(Memory * memory, Z80 * z80);
int CB_OP_96h_RES2HL(Memory * memory, Z80 * z80);
int CB_OP_97h_RES2A(Memory * memory, Z80 * z80);
int CB_OP_98h_RES3B(Memory * memory, Z80 * z80);
int CB_OP_99h_RES3C(Memory * memory, Z80 * z80);
int CB_OP_9Ah_RES3D(Memory * memory, Z80 * z80);
int CB_OP_9Bh_RES3E(Memory * memory, Z80 * z80);
int CB_OP_9Ch_RES3H(Memory * memory, Z80 * z80);
int CB_OP_9Dh_RES3L(Memory * memory, Z80 * z80);
int CB_OP_9Eh_RES3HL(Memory * memory, Z80 * z80);
int CB_OP_9Fh_RES3A(Memory * memory, Z80 * z80);

int CB_OP_A0h_RES4B(Memory * memory, Z80 * z80);
int CB_OP_A1h_RES4C(Memory * memory, Z80 * z80);
int CB_OP_A2h_RES4D(Memory * memory, Z80 * z80);
int CB_OP_A3h_RES4E(Memory * memory, Z80 * z80);
int CB_OP_A4h_RES4H(Memory * memory, Z80 * z80);
int CB_OP_A5h_RES4L(Memory * memory, Z80 * z80);
int CB_OP_A6h_RES4HL(Memory * memory, Z80 * z80);
int CB_OP_A7h_RES4A(Memory * memory, Z80 * z80);
int CB_OP_A8h_RES5B(Memory * memory, Z80 * z80);
int CB_OP_A9h_RES5C(Memory * memory, Z80 * z80);
int CB_OP_AAh_RES5D(Memory * memory, Z80 * z80);
int CB_OP_ABh_RES5E(Memory * memory, Z80 * z80);
int CB_OP_ACh_RES5H(Memory * memory, Z80 * z80);
int CB_OP_ADh_RES5L(Memory * memory, Z80 * z80);
int CB_OP_AEh_RES5HL(Memory * memory, Z80 * z80);
int CB_OP_AFh_RES5A(Memory * memory, Z80 * z80);

int CB_OP_B0h_RES6B(Memory * memory, Z80 * z80);
int CB_OP_B1h_RES6C(Memory * memory, Z80 * z80);
int CB_OP_B2h_RES6D(Memory * memory, Z80 * z80);
int CB_OP_B3h_RES6E(Memory * memory, Z80 * z80);
int CB_OP_B4h_RES6H(Memory * memory, Z80 * z80);
int CB_OP_B5h_RES6L(Memory * memory, Z80 * z80);
int CB_OP_B6h_RES6HL(Memory * memory, Z80 * z80);
int CB_OP_B7h_RES6A(Memory * memory, Z80 * z80);
int CB_OP_B8h_RES7B(Memory * memory, Z80 * z80);
int CB_OP_B9h_RES7C(Memory * memory, Z80 * z80);
int CB_OP_BAh_RES7D(Memory * memory, Z80 * z80);
int CB_OP_BBh_RES7E(Memory * memory, Z80 * z80);
int CB_OP_BCh_RES7H(Memory * memory, Z80 * z80);
int CB_OP_BDh_RES7L(Memory * memory, Z80 * z80);
int CB_OP_BEh_RES7HL(Memory * memory, Z80 * z80);
int CB_OP_BFh_RES7A(Memory * memory, Z80 * z80);

int CB_OP_C0h_SET0B(Memory * memory, Z80 * z80);
int CB_OP_C1h_SET0C(Memory * memory, Z80 * z80);
int CB_OP_C2h_SET0D(Memory * memory, Z80 * z80);
int CB_OP_C3h_SET0E(Memory * memory, Z80 * z80);
int CB_OP_C4h_SET0H(Memory * memory, Z80 * z80);
int CB_OP_C5h_SET0L(Memory * memory, Z80 * z80);
int CB_OP_C6h_SET0HL(Memory * memory, Z80 * z80);
int CB_OP_C7h_SET0A(Memory * memory, Z80 * z80);
int CB_OP_C8h_SET1B(Memory * memory, Z80 * z80);
int CB_OP_C9h_SET1C(Memory * memory, Z80 * z80);
int CB_OP_CAh_SET1D(Memory * memory, Z80 * z80);
int CB_OP_CBh_SET1E(Memory * memory, Z80 * z80);
int CB_OP_CCh_SET1H(Memory * memory, Z80 * z80);
int CB_OP_CDh_SET1L(Memory * memory, Z80 * z80);
int CB_OP_CEh_SET1HL(Memory * memory, Z80 * z80);
int CB_OP_CFh_SET1A(Memory * memory, Z80 * z80);

int CB_OP_D0h_SET2B(Memory * memory, Z80 * z80);
int CB_OP_D1h_SET2C(Memory * memory, Z80 * z80);
int CB_OP_D2h_SET2D(Memory * memory, Z80 * z80);
int CB_OP_D3h_SET2E(Memory * memory, Z80 * z80);
int CB_OP_D4h_SET2H(Memory * memory, Z80 * z80);
int CB_OP_D5h_SET2L(Memory * memory, Z80 * z80);
int CB_OP_D6h_SET2HL(Memory * memory, Z80 * z80);
int CB_OP_D7h_SET2A(Memory * memory, Z80 * z80);
int CB_OP_D8h_SET3B(Memory * memory, Z80 * z80);
int CB_OP_D9h_SET3C(Memory * memory, Z80 * z80);
int CB_OP_DAh_SET3D(Memory * memory, Z80 * z80);
int CB_OP_DBh_SET3E(Memory * memory, Z80 * z80);
int CB_OP_DCh_SET3H(Memory * memory, Z80 * z80);
int CB_OP_DDh_SET3L(Memory * memory, Z80 * z80);
int CB_OP_DEh_SET3HL(Memory * memory, Z80 * z80);
int CB_OP_DFh_SET3A(Memory * memory, Z80 * z80);

int CB_OP_E0h_SET4B(Memory * memory, Z80 * z80);
int CB_OP_E1h_SET4C(Memory * memory, Z80 * z80);
int CB_OP_E2h_SET4D(Memory * memory, Z80 * z80);
int CB_OP_E3h_SET4E(Memory * memory, Z80 * z80);
int CB_OP_E4h_SET4H(Memory * memory, Z80 * z80);
int CB_OP_E5h_SET4L(Memory * memory, Z80 * z80);
int CB_OP_E6h_SET4HL(Memory * memory, Z80 * z80);
int CB_OP_E7h_SET4A(Memory * memory, Z80 * z80);
int CB_OP_E8h_SET5B(Memory * memory, Z80 * z80);
int CB_OP_E9h_SET5C(Memory * memory, Z80 * z80);
int CB_OP_EAh_SET5D(Memory * memory, Z80 * z80);
int CB_OP_EBh_SET5E(Memory * memory, Z80 * z80);
int CB_OP_ECh_SET5H(Memory * memory, Z80 * z80);
int CB_OP_EDh_SET5L(Memory * memory, Z80 * z80);
int CB_OP_EEh_SET5HL(Memory * memory, Z80 * z80);
int CB_OP_EFh_SET5A(Memory * memory, Z80 * z80);

int CB_OP_F0h_SET6B(Memory * memory, Z80 * z80);
int CB_OP_F1h_SET6C(Memory * memory, Z80 * z80);
int CB_OP_F2h_SET6D(Memory * memory, Z80 * z80);
int CB_OP_F3h_SET6E(Memory * memory, Z80 * z80);
int CB_OP_F4h_SET6H(Memory * memory, Z80 * z80);
int CB_OP_F5h_SET6L(Memory * memory, Z80 * z80);
int CB_OP_F6h_SET6HL(Memory * memory, Z80 * z80);
int CB_OP_F7h_SET6A(Memory * memory, Z80 * z80);
int CB_OP_F8h_SET7B(Memory * memory, Z80 * z80);
int CB_OP_F9h_SET7C(Memory * memory, Z80 * z80);
int CB_OP_FAh_SET7D(Memory * memory, Z80 * z80);
int CB_OP_FBh_SET7E(Memory * memory, Z80 * z80);
int CB_OP_FCh_SET7H(Memory * memory, Z80 * z80);
int CB_OP_FDh_SET7L(Memory * memory, Z80 * z80);
int CB_OP_FEh_SET7HL(Memory * memory, Z80 * z80);
int CB_OP_FFh_SET7A(Memory * memory, Z80 * z80);

int Dispatch(Memory * memory, Z80 * z80);
int Fetch(Memory * memory, Z80 * z80);
int8_t ensure_8b_signed(int8_t value);

int CB_BIT(Memory * memory, Z80 * z80, uint8_t parameters);
int CB_RES(Memory * memory, Z80 * z80, uint8_t parameters);
int CB_SET(Memory * memory, Z80 * z80, uint8_t parameters);
int CB_RLC(Memory * memory, Z80 * z80, uint8_t parameters);
int CB_RRC(Memory * memory, Z80 * z80, uint8_t parameters);

int Execute(Memory * memory, Z80 * z80);
int ExecuteCB(Memory * memory, Z80 * z80);
int HertzToMilliseconds(int Hertz);
int decrementHL(Z80 * z80);
int incrementHL(Z80 * z80);
int calculateFlags(Memory * memory, Z80 * z80, uint8_t dest, uint8_t oldDest, uint8_t oldSrc);
int OP_LDXd8(Memory * memory, Z80 * z80, uint8_t x);
