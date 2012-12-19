#ifndef _INCL_MEMORY
   #define _INCL_MEMORY
   #include "memory.h"
#endif

typedef struct
{
   uint8_t A;
   uint8_t B;
   uint8_t C;
   uint8_t D;
   uint8_t E;
   uint8_t H;
   uint8_t L;
   uint8_t F; /* Flag */
   uint16_t PC;
   uint16_t SP;
} Registers;

struct Z80
{
   Registers * r;

   /* CPU ticks of last instruction */
   uint16_t ticks;
};

int InitZ80(Z80 * z80, Registers * registers);
int ResetZ80(Z80 * z80, Registers * registers);
int Dispatch(Memory * memory, Z80 * z80);
int Fetch(Memory * memory, Z80 * z80);
int Execute(Memory * memory, Z80 * z80);
int HertzToMilliseconds(int Hertz);
int decrementHL(Z80 * z80);
int incrementHL(Z80 * z80);

/* Opcodes */
int OP_00h_NOP(Memory * memory, Z80 * z80);
int OP_40h_LDBB(Memory * memory, Z80 * z80);
int OP_50h_LDDB(Memory * memory, Z80 * z80);
int OP_60h_LDHB(Memory * memory, Z80 * z80);
int OP_41h_LDBC(Memory * memory, Z80 * z80);
int OP_51h_LDDC(Memory * memory, Z80 * z80);
int OP_61h_LDHC(Memory * memory, Z80 * z80);
int OP_21h_LDHLnn(Memory * memory, Z80 * z80);
int OP_22h_LDIHLA(Memory * memory, Z80 * z80);
int OP_32h_LDDHLA(Memory * memory, Z80 * z80);
int OP_42h_LDBD(Memory * memory, Z80 * z80);
int OP_52h_LDDD(Memory * memory, Z80 * z80);
int OP_62h_LDHD(Memory * memory, Z80 * z80);
int OP_72h_LDHLD(Memory * memory, Z80 * z80);
int OP_82h_ADDAD(Memory * memory, Z80 * z80);
int OP_31h_JRNCn(Memory * memory, Z80 * z80);
int OP_43h_LDBE(Memory * memory, Z80 * z80);
int OP_53h_LDDE(Memory * memory, Z80 * z80);
int OP_63h_LDHE(Memory * memory, Z80 * z80);
int OP_44h_LDBH(Memory * memory, Z80 * z80);
int OP_54h_LDDH(Memory * memory, Z80 * z80);
int OP_64h_LDHH(Memory * memory, Z80 * z80);
int OP_45h_LDBL(Memory * memory, Z80 * z80);
int OP_55h_LDDL(Memory * memory, Z80 * z80);
int OP_65h_LDHL(Memory * memory, Z80 * z80);

int OP_48h_LDCB(Memory * memory, Z80 * z80);
int OP_58h_LDEB(Memory * memory, Z80 * z80);
int OP_68h_LDLB(Memory * memory, Z80 * z80);
int OP_78h_LDAB(Memory * memory, Z80 * z80);
int OP_49h_LDCC(Memory * memory, Z80 * z80);
int OP_59h_LDEC(Memory * memory, Z80 * z80);
int OP_69h_LDLC(Memory * memory, Z80 * z80);
int OP_79h_LDAC(Memory * memory, Z80 * z80);
int OP_4Ah_LDCD(Memory * memory, Z80 * z80);
int OP_5Ah_LDED(Memory * memory, Z80 * z80);
int OP_6Ah_LDLD(Memory * memory, Z80 * z80);
int OP_7Ah_LDAD(Memory * memory, Z80 * z80);
int OP_4Bh_LDCE(Memory * memory, Z80 * z80);
int OP_5Bh_LDEE(Memory * memory, Z80 * z80);
int OP_6Bh_LDLE(Memory * memory, Z80 * z80);
int OP_7Bh_LDAE(Memory * memory, Z80 * z80);
int OP_4Ch_LDCH(Memory * memory, Z80 * z80);
int OP_5Ch_LDEH(Memory * memory, Z80 * z80);
int OP_6Ch_LDLH(Memory * memory, Z80 * z80);
int OP_7Ch_LDAH(Memory * memory, Z80 * z80);
int OP_4Dh_LDCL(Memory * memory, Z80 * z80);
int OP_5Dh_LDEL(Memory * memory, Z80 * z80);
int OP_6Dh_LDLL(Memory * memory, Z80 * z80);
int OP_7Dh_LDAL(Memory * memory, Z80 * z80);
int OP_4Fh_LDCA(Memory * memory, Z80 * z80);
int OP_5Fh_LDEA(Memory * memory, Z80 * z80);
int OP_6Fh_LDLA(Memory * memory, Z80 * z80);
int OP_7Fh_LDAA(Memory * memory, Z80 * z80);

int OP_AFh_XORA(Memory * memory, Z80 * z80);
int OP_FFh_RST38h(Memory * memory, Z80 * z80);
