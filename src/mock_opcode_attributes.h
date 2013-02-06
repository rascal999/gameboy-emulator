#ifdef UNITTEST_OPCODES
   #ifndef _INCL_Z80
      #define _INCL_Z80
      #include "mock_z80.h"
   #endif
#else
   #ifndef _INCL_Z80
      #define _INCL_Z80
      #include "z80.h"
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
   #define regPC r->r16[0x0]
   #define regSP r->r16[0x1]
#endif

int InitZ80OpcodeStats(Z80 * z80, Registers * registers, Opcodes * op, Opcodes * cb_op);
