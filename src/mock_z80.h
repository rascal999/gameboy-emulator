#ifdef UNITTEST_OPCODES
   #ifndef _INCL_MEMORY
      #define _INCL_MEMORY
      #include "mock_memory.h"
   #endif
#else
   #ifndef _INCL_MEMORY
      #define _INCL_MEMORY
      #include "memory.h"
   #endif
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
#endif

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
   Registers * r;

   /* CPU ticks of last instruction */
   uint16_t ticks;
};

int InitZ80(Z80 * z80, Registers * registers);
int ResetZ80(Z80 * z80, Registers * registers);
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

int OP_LDXD8(Memory * memory, Z80 * z80, uint8_t x);
int OP_LDXY(Memory * memory, Z80 * z80, uint8_t x);
int OP_LDHLX(Memory * memory, Z80 * z80, uint8_t x);
int OP_00h_NOP(Memory * memory, Z80 * z80);
int OP_INCX(Memory * memory, Z80 * z80, uint8_t x);

int OP_20h_JRNZn(Memory * memory, Z80 * z80);
int OP_21h_LDHLnn(Memory * memory, Z80 * z80);
int OP_22h_LDIHLA(Memory * memory, Z80 * z80);
int OP_31h_LDSPnn(Memory * memory, Z80 * z80);
int OP_32h_LDDHLA(Memory * memory, Z80 * z80);
int OP_72h_LDHLD(Memory * memory, Z80 * z80);
int OP_80h_ADDAB(Memory * memory, Z80 * z80);
int OP_81h_ADDAC(Memory * memory, Z80 * z80);
int OP_82h_ADDAD(Memory * memory, Z80 * z80);
int OP_83h_ADDAE(Memory * memory, Z80 * z80);
int OP_84h_ADDAH(Memory * memory, Z80 * z80);
int OP_85h_ADDAL(Memory * memory, Z80 * z80);
int OP_87h_ADDAA(Memory * memory, Z80 * z80);
int OP_88h_ADCAB(Memory * memory, Z80 * z80);
int OP_89h_ADCAC(Memory * memory, Z80 * z80);
int OP_8Ah_ADCAD(Memory * memory, Z80 * z80);
int OP_8Bh_ADCAE(Memory * memory, Z80 * z80);
int OP_8Ch_ADCAH(Memory * memory, Z80 * z80);
int OP_8Dh_ADCAL(Memory * memory, Z80 * z80);
int OP_8Fh_ADCAA(Memory * memory, Z80 * z80);

int OP_90h_SUBB(Memory * memory, Z80 * z80);
int OP_91h_SUBC(Memory * memory, Z80 * z80);
int OP_92h_SUBD(Memory * memory, Z80 * z80);
int OP_93h_SUBE(Memory * memory, Z80 * z80);
int OP_94h_SUBH(Memory * memory, Z80 * z80);
int OP_95h_SUBL(Memory * memory, Z80 * z80);
int OP_97h_SUBA(Memory * memory, Z80 * z80);

int OP_98h_SBCAB(Memory * memory, Z80 * z80);

int InitZ80(Z80 * z80, Registers * registers);
int ResetZ80(Z80 * z80, Registers * registers);
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
int OP_LDXD8(Memory * memory, Z80 * z80, uint8_t x);
