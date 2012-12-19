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
int OP_04h_LDBB(Memory * memory, Z80 * z80);
int OP_05h_LDDB(Memory * memory, Z80 * z80);
int OP_06h_LDHB(Memory * memory, Z80 * z80);
int OP_14h_LDBC(Memory * memory, Z80 * z80);
int OP_15h_LDDC(Memory * memory, Z80 * z80);
int OP_16h_LDHC(Memory * memory, Z80 * z80);
int OP_21h_LDHLnn(Memory * memory, Z80 * z80);
int OP_22h_LDIHLA(Memory * memory, Z80 * z80);
int OP_23h_LDDHLA(Memory * memory, Z80 * z80);
int OP_24h_LDBD(Memory * memory, Z80 * z80);
int OP_25h_LDDD(Memory * memory, Z80 * z80);
int OP_26h_LDHD(Memory * memory, Z80 * z80);
int OP_27h_LDHLD(Memory * memory, Z80 * z80);
int OP_28h_ADDAD(Memory * memory, Z80 * z80);
int OP_31h_JRNCn(Memory * memory, Z80 * z80);
int OP_34h_LDBE(Memory * memory, Z80 * z80);
int OP_35h_LDDE(Memory * memory, Z80 * z80);
int OP_36h_LDHE(Memory * memory, Z80 * z80);
int OP_44h_LDBH(Memory * memory, Z80 * z80);
int OP_45h_LDDH(Memory * memory, Z80 * z80);
int OP_46h_LDHH(Memory * memory, Z80 * z80);
int OP_54h_LDBL(Memory * memory, Z80 * z80);
int OP_55h_LDDL(Memory * memory, Z80 * z80);
int OP_56h_LDHL(Memory * memory, Z80 * z80);

int OP_84h_LDCB(Memory * memory, Z80 * z80);
int OP_85h_LDEB(Memory * memory, Z80 * z80);
int OP_86h_LDLB(Memory * memory, Z80 * z80);
int OP_87h_LDAB(Memory * memory, Z80 * z80);
int OP_94h_LDCC(Memory * memory, Z80 * z80);
int OP_95h_LDEC(Memory * memory, Z80 * z80);
int OP_96h_LDLC(Memory * memory, Z80 * z80);
int OP_97h_LDAC(Memory * memory, Z80 * z80);
int OP_A4h_LDCD(Memory * memory, Z80 * z80);
int OP_A5h_LDED(Memory * memory, Z80 * z80);
int OP_A6h_LDLD(Memory * memory, Z80 * z80);
int OP_A7h_LDAD(Memory * memory, Z80 * z80);
int OP_B4h_LDCE(Memory * memory, Z80 * z80);
int OP_B5h_LDEE(Memory * memory, Z80 * z80);
int OP_B6h_LDLE(Memory * memory, Z80 * z80);
int OP_B7h_LDAE(Memory * memory, Z80 * z80);
int OP_C4h_LDCH(Memory * memory, Z80 * z80);
int OP_C5h_LDEH(Memory * memory, Z80 * z80);
int OP_C6h_LDLH(Memory * memory, Z80 * z80);
int OP_C7h_LDAH(Memory * memory, Z80 * z80);
int OP_D4h_LDCL(Memory * memory, Z80 * z80);
int OP_D5h_LDEL(Memory * memory, Z80 * z80);
int OP_D6h_LDLL(Memory * memory, Z80 * z80);
int OP_D7h_LDAL(Memory * memory, Z80 * z80);
int OP_F4h_LDCA(Memory * memory, Z80 * z80);
int OP_F5h_LDEA(Memory * memory, Z80 * z80);
int OP_F6h_LDLA(Memory * memory, Z80 * z80);
int OP_F7h_LDAA(Memory * memory, Z80 * z80);

int OP_AFh_XORA(Memory * memory, Z80 * z80);
int OP_FFh_RST38h(Memory * memory, Z80 * z80);
