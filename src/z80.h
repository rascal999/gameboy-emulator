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
int OP_21h_LDHLnn(Memory * memory, Z80 * z80);
int OP_22h_LDIHLA(Memory * memory, Z80 * z80);
int OP_23h_LDDHLA(Memory * memory, Z80 * z80);
int OP_24h_LDBD(Memory * memory, Z80 * z80);
int OP_25h_LDDD(Memory * memory, Z80 * z80);
int OP_26h_LDHD(Memory * memory, Z80 * z80);
int OP_27h_LDHLD(Memory * memory, Z80 * z80);
int OP_28h_ADDAD(Memory * memory, Z80 * z80);
int OP_31h_JRNCn(Memory * memory, Z80 * z80);
int OP_AFh_XORA(Memory * memory, Z80 * z80);
int OP_FFh_RST38h(Memory * memory, Z80 * z80);
