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

   Registers * r;

   /* CPU ticks of last instruction */
   uint16_t ticks;
};

int InitZ80(Z80 * z80, Registers * registers, Opcodes * cb, Opcodes * cb_op);
int InitZ80OpcodeStats(Z80 * z80, Registers * registers, Opcodes * op, Opcodes * cb_op);
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
