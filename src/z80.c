#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#ifndef _INCL_STDINT
   #define _INCL_STDINT
   #include <stdint.h>
#endif
#ifndef _INCL_STRING
   #define _INCL_STRING
   #include <string.h>
#endif

#ifdef UNITTEST_OPCODES
   #ifndef _INCL_DEBUG
      #define _INCL_DEBUG
      #include "mock_debug.h"
   #endif
   #ifndef _INCL_Z80
      #define _INCL_Z80
      #include "mock_z80.h"
   #endif
   #ifndef _INCL_ERROR
      #define _INCL_ERROR
      #include "mock_error.h"
   #endif
#else
   #ifndef _INCL_DEBUG
      #define _INCL_DEBUG
      #include "debug.h"
   #endif
   #ifndef _INCL_Z80
      #define _INCL_Z80
      #include "z80.h"
   #endif
   #ifndef _INCL_ERROR
      #define _INCL_ERROR
      #include "error.h"
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

int InitZ80(Z80 * z80, Registers * registers, Opcodes * op, Opcodes * cb_op)
{
   /* http://www.devrs.com/gb/files/gbspec.txt */
printf("sizeof(Opcodes) == %x\n",sizeof(Opcodes));
   op = malloc(sizeof(Opcodes) * 0x100);
   cb_op = malloc(sizeof(Opcodes) * 0x100);
   z80->op = op;
   z80->cb_op = cb_op;

   InitZ80OpcodeStats(z80,registers,op,cb_op);

   z80->r = registers;
   z80->regA = 0x01;
   z80->regB = 0x00;
   z80->regC = 0x13;
   z80->regD = 0x00;
   z80->regE = 0xD8;
   z80->regH = 0x01;
   z80->regL = 0x4D;
   z80->regF = 0xB0;
   z80->regPC = 0x00;
   z80->regSP = 0xFFFE;

   return 0;
}

int InitZ80OpcodeStats(Z80 * z80, Registers * registers, Opcodes * op, Opcodes * cb_op)
{
   // Opcode sizes and tick counts

   // Zero tick count denotes variable
   // count which will need to be determined
   // in opcode function
   z80->op[0x0].size = 0x1; z80->op[0x0].ticks = 0x4; strncpy(z80->op[0x0].name,"NOP",1023);
   z80->op[0x1].size = 0x3; z80->op[0x1].ticks = 0xc; strncpy(z80->op[0x1].name,"LD BC,d16",1023);
   z80->op[0x2].size = 0x1; z80->op[0x2].ticks = 0x8; strncpy(z80->op[0x2].name,"LD (BC),A",1023);
   z80->op[0x3].size = 0x1; z80->op[0x3].ticks = 0x8; strncpy(z80->op[0x3].name,"INC BC",1023);
   z80->op[0x4].size = 0x1; z80->op[0x4].ticks = 0x4; strncpy(z80->op[0x4].name,"INC B",1023);
   z80->op[0x5].size = 0x1; z80->op[0x5].ticks = 0x4; strncpy(z80->op[0x5].name,"DEC B",1023);
   z80->op[0x6].size = 0x2; z80->op[0x6].ticks = 0x8; strncpy(z80->op[0x6].name,"LD B,d8",1023);
   z80->op[0x7].size = 0x1; z80->op[0x7].ticks = 0x4; strncpy(z80->op[0x7].name,"RLCA",1023);
   z80->op[0x8].size = 0x3; z80->op[0x8].ticks = 0x14; strncpy(z80->op[0x8].name,"LD (a16),SP",1023);
   z80->op[0x9].size = 0x1; z80->op[0x9].ticks = 0x8; strncpy(z80->op[0x9].name,"ADD HL,BC",1023);
   z80->op[0xa].size = 0x1; z80->op[0xa].ticks = 0x8; strncpy(z80->op[0xa].name,"LD A,(BC)",1023);
   z80->op[0xb].size = 0x1; z80->op[0xb].ticks = 0x8; strncpy(z80->op[0xb].name,"DEC BC",1023);
   z80->op[0xc].size = 0x1; z80->op[0xc].ticks = 0x4; strncpy(z80->op[0xc].name,"INC C",1023);
   z80->op[0xd].size = 0x1; z80->op[0xd].ticks = 0x4; strncpy(z80->op[0xd].name,"DEC C",1023);
   z80->op[0xe].size = 0x2; z80->op[0xe].ticks = 0x8; strncpy(z80->op[0xe].name,"LD C,d8",1023);
   z80->op[0xf].size = 0x1; z80->op[0xf].ticks = 0x4; strncpy(z80->op[0xf].name,"RRCA",1023);
   z80->op[0x10].size = 0x2; z80->op[0x10].ticks = 0x4; strncpy(z80->op[0x10].name,"STOP 0",1023);
   z80->op[0x11].size = 0x3; z80->op[0x11].ticks = 0xc; strncpy(z80->op[0x11].name,"LD DE,d16",1023);
   z80->op[0x12].size = 0x1; z80->op[0x12].ticks = 0x8; strncpy(z80->op[0x12].name,"LD (DE),A",1023);
   z80->op[0x13].size = 0x1; z80->op[0x13].ticks = 0x8; strncpy(z80->op[0x13].name,"INC DE",1023);
   z80->op[0x14].size = 0x1; z80->op[0x14].ticks = 0x4; strncpy(z80->op[0x14].name,"INC D",1023);
   z80->op[0x15].size = 0x1; z80->op[0x15].ticks = 0x4; strncpy(z80->op[0x15].name,"DEC D",1023);
   z80->op[0x16].size = 0x2; z80->op[0x16].ticks = 0x8; strncpy(z80->op[0x16].name,"LD D,d8",1023);
   z80->op[0x17].size = 0x1; z80->op[0x17].ticks = 0x4; strncpy(z80->op[0x17].name,"RLA",1023);
   z80->op[0x18].size = 0x2; z80->op[0x18].ticks = 0xc; strncpy(z80->op[0x18].name,"JR r8",1023);
   z80->op[0x19].size = 0x1; z80->op[0x19].ticks = 0x8; strncpy(z80->op[0x19].name,"ADD HL,DE",1023);
   z80->op[0x1a].size = 0x1; z80->op[0x1a].ticks = 0x8; strncpy(z80->op[0x1a].name,"LD A,(DE)",1023);
   z80->op[0x1b].size = 0x1; z80->op[0x1b].ticks = 0x8; strncpy(z80->op[0x1b].name,"DEC DE",1023);
   z80->op[0x1c].size = 0x1; z80->op[0x1c].ticks = 0x4; strncpy(z80->op[0x1c].name,"INC E",1023);
   z80->op[0x1d].size = 0x1; z80->op[0x1d].ticks = 0x4; strncpy(z80->op[0x1d].name,"DEC E",1023);
   z80->op[0x1e].size = 0x2; z80->op[0x1e].ticks = 0x8; strncpy(z80->op[0x1e].name,"LD E,d8",1023);
   z80->op[0x1f].size = 0x1; z80->op[0x1f].ticks = 0x4; strncpy(z80->op[0x1f].name,"RRA",1023);
   z80->op[0x20].size = 0x2; z80->op[0x20].ticks = 0x0; strncpy(z80->op[0x20].name,"JR NZ,r8",1023);
   z80->op[0x21].size = 0x3; z80->op[0x21].ticks = 0xc; strncpy(z80->op[0x21].name,"LD HL,d16",1023);
   z80->op[0x22].size = 0x1; z80->op[0x22].ticks = 0x8; strncpy(z80->op[0x22].name,"LD (HL+),A",1023);
   z80->op[0x23].size = 0x1; z80->op[0x23].ticks = 0x8; strncpy(z80->op[0x23].name,"INC HL",1023);
   z80->op[0x24].size = 0x1; z80->op[0x24].ticks = 0x4; strncpy(z80->op[0x24].name,"INC H",1023);
   z80->op[0x25].size = 0x1; z80->op[0x25].ticks = 0x4; strncpy(z80->op[0x25].name,"DEC H",1023);
   z80->op[0x26].size = 0x2; z80->op[0x26].ticks = 0x8; strncpy(z80->op[0x26].name,"LD H,d8",1023);
   z80->op[0x27].size = 0x1; z80->op[0x27].ticks = 0x4; strncpy(z80->op[0x27].name,"DAA",1023);
   z80->op[0x28].size = 0x2; z80->op[0x28].ticks = 0x0; strncpy(z80->op[0x28].name,"JR Z,r8",1023);
   z80->op[0x29].size = 0x1; z80->op[0x29].ticks = 0x8; strncpy(z80->op[0x29].name,"ADD HL,HL",1023);
   z80->op[0x2a].size = 0x1; z80->op[0x2a].ticks = 0x8; strncpy(z80->op[0x2a].name,"LD A,(HL+)",1023);
   z80->op[0x2b].size = 0x1; z80->op[0x2b].ticks = 0x8; strncpy(z80->op[0x2b].name,"DEC HL",1023);
   z80->op[0x2c].size = 0x1; z80->op[0x2c].ticks = 0x4; strncpy(z80->op[0x2c].name,"INC L",1023);
   z80->op[0x2d].size = 0x1; z80->op[0x2d].ticks = 0x4; strncpy(z80->op[0x2d].name,"DEC L",1023);
   z80->op[0x2e].size = 0x2; z80->op[0x2e].ticks = 0x8; strncpy(z80->op[0x2e].name,"LD L,d8",1023);
   z80->op[0x2f].size = 0x1; z80->op[0x2f].ticks = 0x4; strncpy(z80->op[0x2f].name,"CPL",1023);
   z80->op[0x30].size = 0x2; z80->op[0x30].ticks = 0x0; strncpy(z80->op[0x30].name,"JR NC,r8",1023);
   z80->op[0x31].size = 0x3; z80->op[0x31].ticks = 0xc; strncpy(z80->op[0x31].name,"LD SP,d16",1023);
   z80->op[0x32].size = 0x1; z80->op[0x32].ticks = 0x8; strncpy(z80->op[0x32].name,"LD (HL-),A",1023);
   z80->op[0x33].size = 0x1; z80->op[0x33].ticks = 0x8; strncpy(z80->op[0x33].name,"INC SP",1023);
   z80->op[0x34].size = 0x1; z80->op[0x34].ticks = 0xc; strncpy(z80->op[0x34].name,"INC (HL)",1023);
   z80->op[0x35].size = 0x1; z80->op[0x35].ticks = 0xc; strncpy(z80->op[0x35].name,"DEC (HL)",1023);
   z80->op[0x36].size = 0x2; z80->op[0x36].ticks = 0xc; strncpy(z80->op[0x36].name,"LD (HL),d8",1023);
   z80->op[0x37].size = 0x1; z80->op[0x37].ticks = 0x4; strncpy(z80->op[0x37].name,"SCF",1023);
   z80->op[0x38].size = 0x2; z80->op[0x38].ticks = 0x0; strncpy(z80->op[0x38].name,"JR C,r8",1023);
   z80->op[0x39].size = 0x1; z80->op[0x39].ticks = 0x8; strncpy(z80->op[0x39].name,"ADD HL,SP",1023);
   z80->op[0x3a].size = 0x1; z80->op[0x3a].ticks = 0x8; strncpy(z80->op[0x3a].name,"LD A,(HL-)",1023);
   z80->op[0x3b].size = 0x1; z80->op[0x3b].ticks = 0x8; strncpy(z80->op[0x3b].name,"DEC SP",1023);
   z80->op[0x3c].size = 0x1; z80->op[0x3c].ticks = 0x4; strncpy(z80->op[0x3c].name,"INC A",1023);
   z80->op[0x3d].size = 0x1; z80->op[0x3d].ticks = 0x4; strncpy(z80->op[0x3d].name,"DEC A",1023);
   z80->op[0x3e].size = 0x2; z80->op[0x3e].ticks = 0x8; strncpy(z80->op[0x3e].name,"LD A,d8",1023);
   z80->op[0x3f].size = 0x1; z80->op[0x3f].ticks = 0x4; strncpy(z80->op[0x3f].name,"CCF",1023);
   z80->op[0x40].size = 0x1; z80->op[0x40].ticks = 0x4; strncpy(z80->op[0x40].name,"LD B,B",1023);
   z80->op[0x41].size = 0x1; z80->op[0x41].ticks = 0x4; strncpy(z80->op[0x41].name,"LD B,C",1023);
   z80->op[0x42].size = 0x1; z80->op[0x42].ticks = 0x4; strncpy(z80->op[0x42].name,"LD B,D",1023);
   z80->op[0x43].size = 0x1; z80->op[0x43].ticks = 0x4; strncpy(z80->op[0x43].name,"LD B,E",1023);
   z80->op[0x44].size = 0x1; z80->op[0x44].ticks = 0x4; strncpy(z80->op[0x44].name,"LD B,H",1023);
   z80->op[0x45].size = 0x1; z80->op[0x45].ticks = 0x4; strncpy(z80->op[0x45].name,"LD B,L",1023);
   z80->op[0x46].size = 0x1; z80->op[0x46].ticks = 0x8; strncpy(z80->op[0x46].name,"LD B,(HL)",1023);
   z80->op[0x47].size = 0x1; z80->op[0x47].ticks = 0x4; strncpy(z80->op[0x47].name,"LD B,A",1023);
   z80->op[0x48].size = 0x1; z80->op[0x48].ticks = 0x4; strncpy(z80->op[0x48].name,"LD C,B",1023);
   z80->op[0x49].size = 0x1; z80->op[0x49].ticks = 0x4; strncpy(z80->op[0x49].name,"LD C,C",1023);
   z80->op[0x4a].size = 0x1; z80->op[0x4a].ticks = 0x4; strncpy(z80->op[0x4a].name,"LD C,D",1023);
   z80->op[0x4b].size = 0x1; z80->op[0x4b].ticks = 0x4; strncpy(z80->op[0x4b].name,"LD C,E",1023);
   z80->op[0x4c].size = 0x1; z80->op[0x4c].ticks = 0x4; strncpy(z80->op[0x4c].name,"LD C,H",1023);
   z80->op[0x4d].size = 0x1; z80->op[0x4d].ticks = 0x4; strncpy(z80->op[0x4d].name,"LD C,L",1023);
   z80->op[0x4e].size = 0x1; z80->op[0x4e].ticks = 0x8; strncpy(z80->op[0x4e].name,"LD C,(HL)",1023);
   z80->op[0x4f].size = 0x1; z80->op[0x4f].ticks = 0x4; strncpy(z80->op[0x4f].name,"LD C,A",1023);
   z80->op[0x50].size = 0x1; z80->op[0x50].ticks = 0x4; strncpy(z80->op[0x50].name,"LD D,B",1023);
   z80->op[0x51].size = 0x1; z80->op[0x51].ticks = 0x4; strncpy(z80->op[0x51].name,"LD D,C",1023);
   z80->op[0x52].size = 0x1; z80->op[0x52].ticks = 0x4; strncpy(z80->op[0x52].name,"LD D,D",1023);
   z80->op[0x53].size = 0x1; z80->op[0x53].ticks = 0x4; strncpy(z80->op[0x53].name,"LD D,E",1023);
   z80->op[0x54].size = 0x1; z80->op[0x54].ticks = 0x4; strncpy(z80->op[0x54].name,"LD D,H",1023);
   z80->op[0x55].size = 0x1; z80->op[0x55].ticks = 0x4; strncpy(z80->op[0x55].name,"LD D,L",1023);
   z80->op[0x56].size = 0x1; z80->op[0x56].ticks = 0x8; strncpy(z80->op[0x56].name,"LD D,(HL)",1023);
   z80->op[0x57].size = 0x1; z80->op[0x57].ticks = 0x4; strncpy(z80->op[0x57].name,"LD D,A",1023);
   z80->op[0x58].size = 0x1; z80->op[0x58].ticks = 0x4; strncpy(z80->op[0x58].name,"LD E,B",1023);
   z80->op[0x59].size = 0x1; z80->op[0x59].ticks = 0x4; strncpy(z80->op[0x59].name,"LD E,C",1023);
   z80->op[0x5a].size = 0x1; z80->op[0x5a].ticks = 0x4; strncpy(z80->op[0x5a].name,"LD E,D",1023);
   z80->op[0x5b].size = 0x1; z80->op[0x5b].ticks = 0x4; strncpy(z80->op[0x5b].name,"LD E,E",1023);
   z80->op[0x5c].size = 0x1; z80->op[0x5c].ticks = 0x4; strncpy(z80->op[0x5c].name,"LD E,H",1023);
   z80->op[0x5d].size = 0x1; z80->op[0x5d].ticks = 0x4; strncpy(z80->op[0x5d].name,"LD E,L",1023);
   z80->op[0x5e].size = 0x1; z80->op[0x5e].ticks = 0x8; strncpy(z80->op[0x5e].name,"LD E,(HL)",1023);
   z80->op[0x5f].size = 0x1; z80->op[0x5f].ticks = 0x4; strncpy(z80->op[0x5f].name,"LD E,A",1023);
   z80->op[0x60].size = 0x1; z80->op[0x60].ticks = 0x4; strncpy(z80->op[0x60].name,"LD H,B",1023);
   z80->op[0x61].size = 0x1; z80->op[0x61].ticks = 0x4; strncpy(z80->op[0x61].name,"LD H,C",1023);
   z80->op[0x62].size = 0x1; z80->op[0x62].ticks = 0x4; strncpy(z80->op[0x62].name,"LD H,D",1023);
   z80->op[0x63].size = 0x1; z80->op[0x63].ticks = 0x4; strncpy(z80->op[0x63].name,"LD H,E",1023);
   z80->op[0x64].size = 0x1; z80->op[0x64].ticks = 0x4; strncpy(z80->op[0x64].name,"LD H,H",1023);
   z80->op[0x65].size = 0x1; z80->op[0x65].ticks = 0x4; strncpy(z80->op[0x65].name,"LD H,L",1023);
   z80->op[0x66].size = 0x1; z80->op[0x66].ticks = 0x8; strncpy(z80->op[0x66].name,"LD H,(HL)",1023);
   z80->op[0x67].size = 0x1; z80->op[0x67].ticks = 0x4; strncpy(z80->op[0x67].name,"LD H,A",1023);
   z80->op[0x68].size = 0x1; z80->op[0x68].ticks = 0x4; strncpy(z80->op[0x68].name,"LD L,B",1023);
   z80->op[0x69].size = 0x1; z80->op[0x69].ticks = 0x4; strncpy(z80->op[0x69].name,"LD L,C",1023);
   z80->op[0x6a].size = 0x1; z80->op[0x6a].ticks = 0x4; strncpy(z80->op[0x6a].name,"LD L,D",1023);
   z80->op[0x6b].size = 0x1; z80->op[0x6b].ticks = 0x4; strncpy(z80->op[0x6b].name,"LD L,E",1023);
   z80->op[0x6c].size = 0x1; z80->op[0x6c].ticks = 0x4; strncpy(z80->op[0x6c].name,"LD L,H",1023);
   z80->op[0x6d].size = 0x1; z80->op[0x6d].ticks = 0x4; strncpy(z80->op[0x6d].name,"LD L,L",1023);
   z80->op[0x6e].size = 0x1; z80->op[0x6e].ticks = 0x8; strncpy(z80->op[0x6e].name,"LD L,(HL)",1023);
   z80->op[0x6f].size = 0x1; z80->op[0x6f].ticks = 0x4; strncpy(z80->op[0x6f].name,"LD L,A",1023);
   z80->op[0x70].size = 0x1; z80->op[0x70].ticks = 0x8; strncpy(z80->op[0x70].name,"LD (HL),B",1023);
   z80->op[0x71].size = 0x1; z80->op[0x71].ticks = 0x8; strncpy(z80->op[0x71].name,"LD (HL),C",1023);
   z80->op[0x72].size = 0x1; z80->op[0x72].ticks = 0x8; strncpy(z80->op[0x72].name,"LD (HL),D",1023);
   z80->op[0x73].size = 0x1; z80->op[0x73].ticks = 0x8; strncpy(z80->op[0x73].name,"LD (HL),E",1023);
   z80->op[0x74].size = 0x1; z80->op[0x74].ticks = 0x8; strncpy(z80->op[0x74].name,"LD (HL),H",1023);
   z80->op[0x75].size = 0x1; z80->op[0x75].ticks = 0x8; strncpy(z80->op[0x75].name,"LD (HL),L",1023);
   z80->op[0x76].size = 0x1; z80->op[0x76].ticks = 0x4; strncpy(z80->op[0x76].name,"HALT",1023);
   z80->op[0x77].size = 0x1; z80->op[0x77].ticks = 0x8; strncpy(z80->op[0x77].name,"LD (HL),A",1023);
   z80->op[0x78].size = 0x1; z80->op[0x78].ticks = 0x4; strncpy(z80->op[0x78].name,"LD A,B",1023);
   z80->op[0x79].size = 0x1; z80->op[0x79].ticks = 0x4; strncpy(z80->op[0x79].name,"LD A,C",1023);
   z80->op[0x7a].size = 0x1; z80->op[0x7a].ticks = 0x4; strncpy(z80->op[0x7a].name,"LD A,D",1023);
   z80->op[0x7b].size = 0x1; z80->op[0x7b].ticks = 0x4; strncpy(z80->op[0x7b].name,"LD A,E",1023);
   z80->op[0x7c].size = 0x1; z80->op[0x7c].ticks = 0x4; strncpy(z80->op[0x7c].name,"LD A,H",1023);
   z80->op[0x7d].size = 0x1; z80->op[0x7d].ticks = 0x4; strncpy(z80->op[0x7d].name,"LD A,L",1023);
   z80->op[0x7e].size = 0x1; z80->op[0x7e].ticks = 0x8; strncpy(z80->op[0x7e].name,"LD A,(HL)",1023);
   z80->op[0x7f].size = 0x1; z80->op[0x7f].ticks = 0x4; strncpy(z80->op[0x7f].name,"LD A,A",1023);
   z80->op[0x80].size = 0x1; z80->op[0x80].ticks = 0x4; strncpy(z80->op[0x80].name,"ADD A,B",1023);
   z80->op[0x81].size = 0x1; z80->op[0x81].ticks = 0x4; strncpy(z80->op[0x81].name,"ADD A,C",1023);
   z80->op[0x82].size = 0x1; z80->op[0x82].ticks = 0x4; strncpy(z80->op[0x82].name,"ADD A,D",1023);
   z80->op[0x83].size = 0x1; z80->op[0x83].ticks = 0x4; strncpy(z80->op[0x83].name,"ADD A,E",1023);
   z80->op[0x84].size = 0x1; z80->op[0x84].ticks = 0x4; strncpy(z80->op[0x84].name,"ADD A,H",1023);
   z80->op[0x85].size = 0x1; z80->op[0x85].ticks = 0x4; strncpy(z80->op[0x85].name,"ADD A,L",1023);
   z80->op[0x86].size = 0x1; z80->op[0x86].ticks = 0x8; strncpy(z80->op[0x86].name,"ADD A,(HL)",1023);
   z80->op[0x87].size = 0x1; z80->op[0x87].ticks = 0x4; strncpy(z80->op[0x87].name,"ADD A,A",1023);
   z80->op[0x88].size = 0x1; z80->op[0x88].ticks = 0x4; strncpy(z80->op[0x88].name,"ADC A,B",1023);
   z80->op[0x89].size = 0x1; z80->op[0x89].ticks = 0x4; strncpy(z80->op[0x89].name,"ADC A,C",1023);
   z80->op[0x8a].size = 0x1; z80->op[0x8a].ticks = 0x4; strncpy(z80->op[0x8a].name,"ADC A,D",1023);
   z80->op[0x8b].size = 0x1; z80->op[0x8b].ticks = 0x4; strncpy(z80->op[0x8b].name,"ADC A,E",1023);
   z80->op[0x8c].size = 0x1; z80->op[0x8c].ticks = 0x4; strncpy(z80->op[0x8c].name,"ADC A,H",1023);
   z80->op[0x8d].size = 0x1; z80->op[0x8d].ticks = 0x4; strncpy(z80->op[0x8d].name,"ADC A,L",1023);
   z80->op[0x8e].size = 0x1; z80->op[0x8e].ticks = 0x8; strncpy(z80->op[0x8e].name,"ADC A,(HL)",1023);
   z80->op[0x8f].size = 0x1; z80->op[0x8f].ticks = 0x4; strncpy(z80->op[0x8f].name,"ADC A,A",1023);
   z80->op[0x90].size = 0x1; z80->op[0x90].ticks = 0x4; strncpy(z80->op[0x90].name,"SUB B",1023);
   z80->op[0x91].size = 0x1; z80->op[0x91].ticks = 0x4; strncpy(z80->op[0x91].name,"SUB C",1023);
   z80->op[0x92].size = 0x1; z80->op[0x92].ticks = 0x4; strncpy(z80->op[0x92].name,"SUB D",1023);
   z80->op[0x93].size = 0x1; z80->op[0x93].ticks = 0x4; strncpy(z80->op[0x93].name,"SUB E",1023);
   z80->op[0x94].size = 0x1; z80->op[0x94].ticks = 0x4; strncpy(z80->op[0x94].name,"SUB H",1023);
   z80->op[0x95].size = 0x1; z80->op[0x95].ticks = 0x4; strncpy(z80->op[0x95].name,"SUB L",1023);
   z80->op[0x96].size = 0x1; z80->op[0x96].ticks = 0x8; strncpy(z80->op[0x96].name,"SUB (HL)",1023);
   z80->op[0x97].size = 0x1; z80->op[0x97].ticks = 0x4; strncpy(z80->op[0x97].name,"SUB A",1023);
   z80->op[0x98].size = 0x1; z80->op[0x98].ticks = 0x4; strncpy(z80->op[0x98].name,"SBC A,B",1023);
   z80->op[0x99].size = 0x1; z80->op[0x99].ticks = 0x4; strncpy(z80->op[0x99].name,"SBC A,C",1023);
   z80->op[0x9a].size = 0x1; z80->op[0x9a].ticks = 0x4; strncpy(z80->op[0x9a].name,"SBC A,D",1023);
   z80->op[0x9b].size = 0x1; z80->op[0x9b].ticks = 0x4; strncpy(z80->op[0x9b].name,"SBC A,E",1023);
   z80->op[0x9c].size = 0x1; z80->op[0x9c].ticks = 0x4; strncpy(z80->op[0x9c].name,"SBC A,H",1023);
   z80->op[0x9d].size = 0x1; z80->op[0x9d].ticks = 0x4; strncpy(z80->op[0x9d].name,"SBC A,L",1023);
   z80->op[0x9e].size = 0x1; z80->op[0x9e].ticks = 0x8; strncpy(z80->op[0x9e].name,"SBC A,(HL)",1023);
   z80->op[0x9f].size = 0x1; z80->op[0x9f].ticks = 0x4; strncpy(z80->op[0x9f].name,"SBC A,A",1023);
   z80->op[0xa0].size = 0x1; z80->op[0xa0].ticks = 0x4; strncpy(z80->op[0xa0].name,"AND B",1023);
   z80->op[0xa1].size = 0x1; z80->op[0xa1].ticks = 0x4; strncpy(z80->op[0xa1].name,"AND C",1023);
   z80->op[0xa2].size = 0x1; z80->op[0xa2].ticks = 0x4; strncpy(z80->op[0xa2].name,"AND D",1023);
   z80->op[0xa3].size = 0x1; z80->op[0xa3].ticks = 0x4; strncpy(z80->op[0xa3].name,"AND E",1023);
   z80->op[0xa4].size = 0x1; z80->op[0xa4].ticks = 0x4; strncpy(z80->op[0xa4].name,"AND H",1023);
   z80->op[0xa5].size = 0x1; z80->op[0xa5].ticks = 0x4; strncpy(z80->op[0xa5].name,"AND L",1023);
   z80->op[0xa6].size = 0x1; z80->op[0xa6].ticks = 0x8; strncpy(z80->op[0xa6].name,"AND (HL)",1023);
   z80->op[0xa7].size = 0x1; z80->op[0xa7].ticks = 0x4; strncpy(z80->op[0xa7].name,"AND A",1023);
   z80->op[0xa8].size = 0x1; z80->op[0xa8].ticks = 0x4; strncpy(z80->op[0xa8].name,"XOR B",1023);
   z80->op[0xa9].size = 0x1; z80->op[0xa9].ticks = 0x4; strncpy(z80->op[0xa9].name,"XOR C",1023);
   z80->op[0xaa].size = 0x1; z80->op[0xaa].ticks = 0x4; strncpy(z80->op[0xaa].name,"XOR D",1023);
   z80->op[0xab].size = 0x1; z80->op[0xab].ticks = 0x4; strncpy(z80->op[0xab].name,"XOR E",1023);
   z80->op[0xac].size = 0x1; z80->op[0xac].ticks = 0x4; strncpy(z80->op[0xac].name,"XOR H",1023);
   z80->op[0xad].size = 0x1; z80->op[0xad].ticks = 0x4; strncpy(z80->op[0xad].name,"XOR L",1023);
   z80->op[0xae].size = 0x1; z80->op[0xae].ticks = 0x8; strncpy(z80->op[0xae].name,"XOR (HL)",1023);
   z80->op[0xaf].size = 0x1; z80->op[0xaf].ticks = 0x4; strncpy(z80->op[0xaf].name,"XOR A",1023);
   z80->op[0xb0].size = 0x1; z80->op[0xb0].ticks = 0x4; strncpy(z80->op[0xb0].name,"OR B",1023);
   z80->op[0xb1].size = 0x1; z80->op[0xb1].ticks = 0x4; strncpy(z80->op[0xb1].name,"OR C",1023);
   z80->op[0xb2].size = 0x1; z80->op[0xb2].ticks = 0x4; strncpy(z80->op[0xb2].name,"OR D",1023);
   z80->op[0xb3].size = 0x1; z80->op[0xb3].ticks = 0x4; strncpy(z80->op[0xb3].name,"OR E",1023);
   z80->op[0xb4].size = 0x1; z80->op[0xb4].ticks = 0x4; strncpy(z80->op[0xb4].name,"OR H",1023);
   z80->op[0xb5].size = 0x1; z80->op[0xb5].ticks = 0x4; strncpy(z80->op[0xb5].name,"OR L",1023);
   z80->op[0xb6].size = 0x1; z80->op[0xb6].ticks = 0x8; strncpy(z80->op[0xb6].name,"OR (HL)",1023);
   z80->op[0xb7].size = 0x1; z80->op[0xb7].ticks = 0x4; strncpy(z80->op[0xb7].name,"OR A",1023);
   z80->op[0xb8].size = 0x1; z80->op[0xb8].ticks = 0x4; strncpy(z80->op[0xb8].name,"CP B",1023);
   z80->op[0xb9].size = 0x1; z80->op[0xb9].ticks = 0x4; strncpy(z80->op[0xb9].name,"CP C",1023);
   z80->op[0xba].size = 0x1; z80->op[0xba].ticks = 0x4; strncpy(z80->op[0xba].name,"CP D",1023);
   z80->op[0xbb].size = 0x1; z80->op[0xbb].ticks = 0x4; strncpy(z80->op[0xbb].name,"CP E",1023);
   z80->op[0xbc].size = 0x1; z80->op[0xbc].ticks = 0x4; strncpy(z80->op[0xbc].name,"CP H",1023);
   z80->op[0xbd].size = 0x1; z80->op[0xbd].ticks = 0x4; strncpy(z80->op[0xbd].name,"CP L",1023);
   z80->op[0xbe].size = 0x1; z80->op[0xbe].ticks = 0x8; strncpy(z80->op[0xbe].name,"CP (HL)",1023);
   z80->op[0xbf].size = 0x1; z80->op[0xbf].ticks = 0x4; strncpy(z80->op[0xbf].name,"CP A",1023);
   z80->op[0xc0].size = 0x1; z80->op[0xc0].ticks = 0x0; strncpy(z80->op[0xc0].name,"RET NZ",1023);
   z80->op[0xc1].size = 0x1; z80->op[0xc1].ticks = 0xc; strncpy(z80->op[0xc1].name,"POP BC",1023);
   z80->op[0xc2].size = 0x3; z80->op[0xc2].ticks = 0x0; strncpy(z80->op[0xc2].name,"JP NZ,a16",1023);
   z80->op[0xc3].size = 0x3; z80->op[0xc3].ticks = 0x10; strncpy(z80->op[0xc3].name,"JP a16",1023);
   z80->op[0xc4].size = 0x3; z80->op[0xc4].ticks = 0x0; strncpy(z80->op[0xc4].name,"CALL NZ,a16",1023);
   z80->op[0xc5].size = 0x1; z80->op[0xc5].ticks = 0x10; strncpy(z80->op[0xc5].name,"PUSH BC",1023);
   z80->op[0xc6].size = 0x2; z80->op[0xc6].ticks = 0x8; strncpy(z80->op[0xc6].name,"ADD A,d8",1023);
   z80->op[0xc7].size = 0x1; z80->op[0xc7].ticks = 0x10; strncpy(z80->op[0xc7].name,"RST 00H",1023);
   z80->op[0xc8].size = 0x1; z80->op[0xc8].ticks = 0x0; strncpy(z80->op[0xc8].name,"RET Z",1023);
   z80->op[0xc9].size = 0x1; z80->op[0xc9].ticks = 0x10; strncpy(z80->op[0xc9].name,"RET",1023);
   z80->op[0xca].size = 0x3; z80->op[0xca].ticks = 0x0; strncpy(z80->op[0xca].name,"JP Z,a16",1023);
   z80->op[0xcb].size = 0x1; z80->op[0xcb].ticks = 0x4; strncpy(z80->op[0xcb].name,"PREFIX CB",1023);
   z80->op[0xcc].size = 0x3; z80->op[0xcc].ticks = 0x0; strncpy(z80->op[0xcc].name,"CALL Z,a16",1023);
   z80->op[0xcd].size = 0x3; z80->op[0xcd].ticks = 0x18; strncpy(z80->op[0xcd].name,"CALL a16",1023);
   z80->op[0xce].size = 0x2; z80->op[0xce].ticks = 0x8; strncpy(z80->op[0xce].name,"ADC A,d8",1023);
   z80->op[0xcf].size = 0x1; z80->op[0xcf].ticks = 0x10; strncpy(z80->op[0xcf].name,"RST 08H",1023);
   z80->op[0xd0].size = 0x1; z80->op[0xd0].ticks = 0x0; strncpy(z80->op[0xd0].name,"RET NC",1023);
   z80->op[0xd1].size = 0x1; z80->op[0xd1].ticks = 0xc; strncpy(z80->op[0xd1].name,"POP DE",1023);
   z80->op[0xd2].size = 0x3; z80->op[0xd2].ticks = 0x0; strncpy(z80->op[0xd2].name,"JP NC,a16",1023);
   z80->op[0xd3].size = 0x0; z80->op[0xd3].ticks = 0x0; strncpy(z80->op[0xd2].name,"INVALID",1023); // 0xd3 invalid
   z80->op[0xd4].size = 0x3; z80->op[0xd4].ticks = 0x0; strncpy(z80->op[0xd4].name,"CALL NC,a16",1023);
   z80->op[0xd5].size = 0x1; z80->op[0xd5].ticks = 0x10; strncpy(z80->op[0xd5].name,"PUSH DE",1023);
   z80->op[0xd6].size = 0x2; z80->op[0xd6].ticks = 0x8; strncpy(z80->op[0xd6].name,"SUB d8",1023);
   z80->op[0xd7].size = 0x1; z80->op[0xd7].ticks = 0x10; strncpy(z80->op[0xd7].name,"RST 10H",1023);
   z80->op[0xd8].size = 0x1; z80->op[0xd8].ticks = 0x0; strncpy(z80->op[0xd8].name,"RET C",1023);
   z80->op[0xd9].size = 0x1; z80->op[0xd9].ticks = 0x10; strncpy(z80->op[0xd9].name,"RETI",1023);
   z80->op[0xda].size = 0x3; z80->op[0xda].ticks = 0x0; strncpy(z80->op[0xda].name,"JP C,a16",1023);
   z80->op[0xdb].size = 0x0; z80->op[0xdb].ticks = 0x0; strncpy(z80->op[0xd2].name,"INVALID",1023); // 0xdb invalid
   z80->op[0xdc].size = 0x3; z80->op[0xdc].ticks = 0x0; strncpy(z80->op[0xdc].name,"CALL C,a16",1023);
   z80->op[0xdd].size = 0x0; z80->op[0xdd].ticks = 0x0; strncpy(z80->op[0xd2].name,"INVALID",1023); // 0xdd invalid
   z80->op[0xde].size = 0x2; z80->op[0xde].ticks = 0x8; strncpy(z80->op[0xde].name,"SBC A,d8",1023);
   z80->op[0xdf].size = 0x1; z80->op[0xdf].ticks = 0x10; strncpy(z80->op[0xdf].name,"RST 18H",1023);
   z80->op[0xe0].size = 0x2; z80->op[0xe0].ticks = 0xc; strncpy(z80->op[0xe0].name,"LDH (a8),A",1023);
   z80->op[0xe1].size = 0x1; z80->op[0xe1].ticks = 0xc; strncpy(z80->op[0xe1].name,"POP HL",1023);
   z80->op[0xe2].size = 0x2; z80->op[0xe2].ticks = 0x8; strncpy(z80->op[0xe2].name,"LD (C),A",1023);
   z80->op[0xe3].size = 0x0; z80->op[0xe3].ticks = 0x0; strncpy(z80->op[0xd2].name,"INVALID",1023); // 0xe3 invalid
   z80->op[0xe4].size = 0x0; z80->op[0xe4].ticks = 0x0; strncpy(z80->op[0xd2].name,"INVALID",1023); // 0xe4 invalid
   z80->op[0xe5].size = 0x1; z80->op[0xe5].ticks = 0x10; strncpy(z80->op[0xe5].name,"PUSH HL",1023);
   z80->op[0xe6].size = 0x2; z80->op[0xe6].ticks = 0x8; strncpy(z80->op[0xe6].name,"AND d8",1023);
   z80->op[0xe7].size = 0x1; z80->op[0xe7].ticks = 0x10; strncpy(z80->op[0xe7].name,"RST 20H",1023);
   z80->op[0xe8].size = 0x2; z80->op[0xe8].ticks = 0x10; strncpy(z80->op[0xe8].name,"ADD SP,r8",1023);
   z80->op[0xe9].size = 0x1; z80->op[0xe9].ticks = 0x4; strncpy(z80->op[0xe9].name,"JP (HL)",1023);
   z80->op[0xea].size = 0x3; z80->op[0xea].ticks = 0x10; strncpy(z80->op[0xea].name,"LD (a16),A",1023);
   z80->op[0xeb].size = 0x0; z80->op[0xeb].ticks = 0x0; strncpy(z80->op[0xd2].name,"INVALID",1023); // 0xeb invalid
   z80->op[0xec].size = 0x0; z80->op[0xec].ticks = 0x0; strncpy(z80->op[0xd2].name,"INVALID",1023); // 0xec invalid
   z80->op[0xed].size = 0x0; z80->op[0xed].ticks = 0x0; strncpy(z80->op[0xd2].name,"INVALID",1023); // 0xed invalid
   z80->op[0xee].size = 0x2; z80->op[0xee].ticks = 0x8; strncpy(z80->op[0xee].name,"XOR d8",1023);
   z80->op[0xef].size = 0x1; z80->op[0xef].ticks = 0x10; strncpy(z80->op[0xef].name,"RST 28H",1023);
   z80->op[0xf0].size = 0x2; z80->op[0xf0].ticks = 0xc; strncpy(z80->op[0xf0].name,"LDH A,(a8)",1023);
   z80->op[0xf1].size = 0x1; z80->op[0xf1].ticks = 0xc; strncpy(z80->op[0xf1].name,"POP AF",1023);
   z80->op[0xf2].size = 0x2; z80->op[0xf2].ticks = 0x8; strncpy(z80->op[0xf2].name,"LD A,(C)",1023);
   z80->op[0xf3].size = 0x1; z80->op[0xf3].ticks = 0x4; strncpy(z80->op[0xf3].name,"DI",1023);
   z80->op[0xf4].size = 0x0; z80->op[0xf4].ticks = 0x0; strncpy(z80->op[0xd2].name,"INVALID",1023); // 0xf4 invalid
   z80->op[0xf5].size = 0x1; z80->op[0xf5].ticks = 0x10; strncpy(z80->op[0xf5].name,"PUSH AF",1023);
   z80->op[0xf6].size = 0x2; z80->op[0xf6].ticks = 0x8; strncpy(z80->op[0xf6].name,"OR d8",1023);
   z80->op[0xf7].size = 0x1; z80->op[0xf7].ticks = 0x10; strncpy(z80->op[0xf7].name,"RST 30H",1023);
   z80->op[0xf8].size = 0x2; z80->op[0xf8].ticks = 0xc; strncpy(z80->op[0xf8].name,"LD HL,SP+r8",1023);
   z80->op[0xf9].size = 0x1; z80->op[0xf9].ticks = 0x8; strncpy(z80->op[0xf9].name,"LD SP,HL",1023);
   z80->op[0xfa].size = 0x3; z80->op[0xfa].ticks = 0x10; strncpy(z80->op[0xfa].name,"LD A,(a16)",1023);
   z80->op[0xfb].size = 0x1; z80->op[0xfb].ticks = 0x4; strncpy(z80->op[0xfb].name,"EI",1023);
   z80->op[0xfc].size = 0x0; z80->op[0xfc].ticks = 0x0; strncpy(z80->op[0xd2].name,"INVALID",1023); // 0xfc invalid
   z80->op[0xfd].size = 0x0; z80->op[0xfd].ticks = 0x0; strncpy(z80->op[0xd2].name,"INVALID",1023); // 0xfd invalid
   z80->op[0xfe].size = 0x2; z80->op[0xfe].ticks = 0x8; strncpy(z80->op[0xfe].name,"CP d8",1023);
   z80->op[0xff].size = 0x1; z80->op[0xff].ticks = 0x10; strncpy(z80->op[0xff].name,"RST 38H",1023);

   //CB prefixed ops. Fortuneately, they are all the same size and tick
   z80->cb_op[0x0].size = 0x2; z80->cb_op[0x0].ticks = 0x8; z80->cb_op[0x1].size = 0x2; z80->cb_op[0x1].ticks = 0x8;
   z80->cb_op[0x2].size = 0x2; z80->cb_op[0x2].ticks = 0x8; z80->cb_op[0x3].size = 0x2; z80->cb_op[0x3].ticks = 0x8;
   z80->cb_op[0x4].size = 0x2; z80->cb_op[0x4].ticks = 0x8; z80->cb_op[0x5].size = 0x2; z80->cb_op[0x5].ticks = 0x8;
   z80->cb_op[0x6].size = 0x2; z80->cb_op[0x6].ticks = 0x8; z80->cb_op[0x7].size = 0x2; z80->cb_op[0x7].ticks = 0x8;
   z80->cb_op[0x8].size = 0x2; z80->cb_op[0x8].ticks = 0x8; z80->cb_op[0x9].size = 0x2; z80->cb_op[0x9].ticks = 0x8;
   z80->cb_op[0xa].size = 0x2; z80->cb_op[0xa].ticks = 0x8; z80->cb_op[0xb].size = 0x2; z80->cb_op[0xb].ticks = 0x8;
   z80->cb_op[0xc].size = 0x2; z80->cb_op[0xc].ticks = 0x8; z80->cb_op[0xd].size = 0x2; z80->cb_op[0xd].ticks = 0x8;
   z80->cb_op[0xe].size = 0x2; z80->cb_op[0xe].ticks = 0x8; z80->cb_op[0xf].size = 0x2; z80->cb_op[0xf].ticks = 0x8;
   z80->cb_op[0x10].size = 0x2; z80->cb_op[0x10].ticks = 0x8; z80->cb_op[0x11].size = 0x2; z80->cb_op[0x11].ticks = 0x8;
   z80->cb_op[0x12].size = 0x2; z80->cb_op[0x12].ticks = 0x8; z80->cb_op[0x13].size = 0x2; z80->cb_op[0x13].ticks = 0x8;
   z80->cb_op[0x14].size = 0x2; z80->cb_op[0x14].ticks = 0x8; z80->cb_op[0x15].size = 0x2; z80->cb_op[0x15].ticks = 0x8;
   z80->cb_op[0x16].size = 0x2; z80->cb_op[0x16].ticks = 0x8; z80->cb_op[0x17].size = 0x2; z80->cb_op[0x17].ticks = 0x8;
   z80->cb_op[0x18].size = 0x2; z80->cb_op[0x18].ticks = 0x8; z80->cb_op[0x19].size = 0x2; z80->cb_op[0x19].ticks = 0x8;
   z80->cb_op[0x1a].size = 0x2; z80->cb_op[0x1a].ticks = 0x8; z80->cb_op[0x1b].size = 0x2; z80->cb_op[0x1b].ticks = 0x8;
   z80->cb_op[0x1c].size = 0x2; z80->cb_op[0x1c].ticks = 0x8; z80->cb_op[0x1d].size = 0x2; z80->cb_op[0x1d].ticks = 0x8;
   z80->cb_op[0x1e].size = 0x2; z80->cb_op[0x1e].ticks = 0x8; z80->cb_op[0x1f].size = 0x2; z80->cb_op[0x1f].ticks = 0x8;
   z80->cb_op[0x20].size = 0x2; z80->cb_op[0x20].ticks = 0x8; z80->cb_op[0x21].size = 0x2; z80->cb_op[0x21].ticks = 0x8;
   z80->cb_op[0x22].size = 0x2; z80->cb_op[0x22].ticks = 0x8; z80->cb_op[0x23].size = 0x2; z80->cb_op[0x23].ticks = 0x8;
   z80->cb_op[0x24].size = 0x2; z80->cb_op[0x24].ticks = 0x8; z80->cb_op[0x25].size = 0x2; z80->cb_op[0x25].ticks = 0x8;
   z80->cb_op[0x26].size = 0x2; z80->cb_op[0x26].ticks = 0x8; z80->cb_op[0x27].size = 0x2; z80->cb_op[0x27].ticks = 0x8;
   z80->cb_op[0x28].size = 0x2; z80->cb_op[0x28].ticks = 0x8; z80->cb_op[0x29].size = 0x2; z80->cb_op[0x29].ticks = 0x8;
   z80->cb_op[0x2a].size = 0x2; z80->cb_op[0x2a].ticks = 0x8; z80->cb_op[0x2b].size = 0x2; z80->cb_op[0x2b].ticks = 0x8;
   z80->cb_op[0x2c].size = 0x2; z80->cb_op[0x2c].ticks = 0x8; z80->cb_op[0x2d].size = 0x2; z80->cb_op[0x2d].ticks = 0x8;
   z80->cb_op[0x2e].size = 0x2; z80->cb_op[0x2e].ticks = 0x8; z80->cb_op[0x2f].size = 0x2; z80->cb_op[0x2f].ticks = 0x8;
   z80->cb_op[0x30].size = 0x2; z80->cb_op[0x30].ticks = 0x8; z80->cb_op[0x31].size = 0x2; z80->cb_op[0x31].ticks = 0x8;
   z80->cb_op[0x32].size = 0x2; z80->cb_op[0x32].ticks = 0x8; z80->cb_op[0x33].size = 0x2; z80->cb_op[0x33].ticks = 0x8;
   z80->cb_op[0x34].size = 0x2; z80->cb_op[0x34].ticks = 0x8; z80->cb_op[0x35].size = 0x2; z80->cb_op[0x35].ticks = 0x8;
   z80->cb_op[0x36].size = 0x2; z80->cb_op[0x36].ticks = 0x8; z80->cb_op[0x37].size = 0x2; z80->cb_op[0x37].ticks = 0x8;
   z80->cb_op[0x38].size = 0x2; z80->cb_op[0x38].ticks = 0x8; z80->cb_op[0x39].size = 0x2; z80->cb_op[0x39].ticks = 0x8;
   z80->cb_op[0x3a].size = 0x2; z80->cb_op[0x3a].ticks = 0x8; z80->cb_op[0x3b].size = 0x2; z80->cb_op[0x3b].ticks = 0x8;
   z80->cb_op[0x3c].size = 0x2; z80->cb_op[0x3c].ticks = 0x8; z80->cb_op[0x3d].size = 0x2; z80->cb_op[0x3d].ticks = 0x8;
   z80->cb_op[0x3e].size = 0x2; z80->cb_op[0x3e].ticks = 0x8; z80->cb_op[0x3f].size = 0x2; z80->cb_op[0x3f].ticks = 0x8;
   z80->cb_op[0x40].size = 0x2; z80->cb_op[0x40].ticks = 0x8; z80->cb_op[0x41].size = 0x2; z80->cb_op[0x41].ticks = 0x8;
   z80->cb_op[0x42].size = 0x2; z80->cb_op[0x42].ticks = 0x8; z80->cb_op[0x43].size = 0x2; z80->cb_op[0x43].ticks = 0x8;
   z80->cb_op[0x44].size = 0x2; z80->cb_op[0x44].ticks = 0x8; z80->cb_op[0x45].size = 0x2; z80->cb_op[0x45].ticks = 0x8;
   z80->cb_op[0x46].size = 0x2; z80->cb_op[0x46].ticks = 0x8; z80->cb_op[0x47].size = 0x2; z80->cb_op[0x47].ticks = 0x8;
   z80->cb_op[0x48].size = 0x2; z80->cb_op[0x48].ticks = 0x8; z80->cb_op[0x49].size = 0x2; z80->cb_op[0x49].ticks = 0x8;
   z80->cb_op[0x4a].size = 0x2; z80->cb_op[0x4a].ticks = 0x8; z80->cb_op[0x4b].size = 0x2; z80->cb_op[0x4b].ticks = 0x8;
   z80->cb_op[0x4c].size = 0x2; z80->cb_op[0x4c].ticks = 0x8; z80->cb_op[0x4d].size = 0x2; z80->cb_op[0x4d].ticks = 0x8;
   z80->cb_op[0x4e].size = 0x2; z80->cb_op[0x4e].ticks = 0x8; z80->cb_op[0x4f].size = 0x2; z80->cb_op[0x4f].ticks = 0x8;
   z80->cb_op[0x50].size = 0x2; z80->cb_op[0x50].ticks = 0x8; z80->cb_op[0x51].size = 0x2; z80->cb_op[0x51].ticks = 0x8;
   z80->cb_op[0x52].size = 0x2; z80->cb_op[0x52].ticks = 0x8; z80->cb_op[0x53].size = 0x2; z80->cb_op[0x53].ticks = 0x8;
   z80->cb_op[0x54].size = 0x2; z80->cb_op[0x54].ticks = 0x8; z80->cb_op[0x55].size = 0x2; z80->cb_op[0x55].ticks = 0x8;
   z80->cb_op[0x56].size = 0x2; z80->cb_op[0x56].ticks = 0x8; z80->cb_op[0x57].size = 0x2; z80->cb_op[0x57].ticks = 0x8;
   z80->cb_op[0x58].size = 0x2; z80->cb_op[0x58].ticks = 0x8; z80->cb_op[0x59].size = 0x2; z80->cb_op[0x59].ticks = 0x8;
   z80->cb_op[0x5a].size = 0x2; z80->cb_op[0x5a].ticks = 0x8; z80->cb_op[0x5b].size = 0x2; z80->cb_op[0x5b].ticks = 0x8;
   z80->cb_op[0x5c].size = 0x2; z80->cb_op[0x5c].ticks = 0x8; z80->cb_op[0x5d].size = 0x2; z80->cb_op[0x5d].ticks = 0x8;
   z80->cb_op[0x5e].size = 0x2; z80->cb_op[0x5e].ticks = 0x8; z80->cb_op[0x5f].size = 0x2; z80->cb_op[0x5f].ticks = 0x8;
   z80->cb_op[0x60].size = 0x2; z80->cb_op[0x60].ticks = 0x8; z80->cb_op[0x61].size = 0x2; z80->cb_op[0x61].ticks = 0x8;
   z80->cb_op[0x62].size = 0x2; z80->cb_op[0x62].ticks = 0x8; z80->cb_op[0x63].size = 0x2; z80->cb_op[0x63].ticks = 0x8;
   z80->cb_op[0x64].size = 0x2; z80->cb_op[0x64].ticks = 0x8; z80->cb_op[0x65].size = 0x2; z80->cb_op[0x65].ticks = 0x8;
   z80->cb_op[0x66].size = 0x2; z80->cb_op[0x66].ticks = 0x8; z80->cb_op[0x67].size = 0x2; z80->cb_op[0x67].ticks = 0x8;
   z80->cb_op[0x68].size = 0x2; z80->cb_op[0x68].ticks = 0x8; z80->cb_op[0x69].size = 0x2; z80->cb_op[0x69].ticks = 0x8;
   z80->cb_op[0x6a].size = 0x2; z80->cb_op[0x6a].ticks = 0x8; z80->cb_op[0x6b].size = 0x2; z80->cb_op[0x6b].ticks = 0x8;
   z80->cb_op[0x6c].size = 0x2; z80->cb_op[0x6c].ticks = 0x8; z80->cb_op[0x6d].size = 0x2; z80->cb_op[0x6d].ticks = 0x8;
   z80->cb_op[0x6e].size = 0x2; z80->cb_op[0x6e].ticks = 0x8; z80->cb_op[0x6f].size = 0x2; z80->cb_op[0x6f].ticks = 0x8;
   z80->cb_op[0x70].size = 0x2; z80->cb_op[0x70].ticks = 0x8; z80->cb_op[0x71].size = 0x2; z80->cb_op[0x71].ticks = 0x8;
   z80->cb_op[0x72].size = 0x2; z80->cb_op[0x72].ticks = 0x8; z80->cb_op[0x73].size = 0x2; z80->cb_op[0x73].ticks = 0x8;
   z80->cb_op[0x74].size = 0x2; z80->cb_op[0x74].ticks = 0x8; z80->cb_op[0x75].size = 0x2; z80->cb_op[0x75].ticks = 0x8;
   z80->cb_op[0x76].size = 0x2; z80->cb_op[0x76].ticks = 0x8; z80->cb_op[0x77].size = 0x2; z80->cb_op[0x77].ticks = 0x8;
   z80->cb_op[0x78].size = 0x2; z80->cb_op[0x78].ticks = 0x8; z80->cb_op[0x79].size = 0x2; z80->cb_op[0x79].ticks = 0x8;
   z80->cb_op[0x7a].size = 0x2; z80->cb_op[0x7a].ticks = 0x8; z80->cb_op[0x7b].size = 0x2; z80->cb_op[0x7b].ticks = 0x8;
   z80->cb_op[0x7c].size = 0x2; z80->cb_op[0x7c].ticks = 0x8; z80->cb_op[0x7d].size = 0x2; z80->cb_op[0x7d].ticks = 0x8;
   z80->cb_op[0x7e].size = 0x2; z80->cb_op[0x7e].ticks = 0x8; z80->cb_op[0x7f].size = 0x2; z80->cb_op[0x7f].ticks = 0x8;
   z80->cb_op[0x80].size = 0x2; z80->cb_op[0x80].ticks = 0x8; z80->cb_op[0x81].size = 0x2; z80->cb_op[0x81].ticks = 0x8;
   z80->cb_op[0x82].size = 0x2; z80->cb_op[0x82].ticks = 0x8; z80->cb_op[0x83].size = 0x2; z80->cb_op[0x83].ticks = 0x8;
   z80->cb_op[0x84].size = 0x2; z80->cb_op[0x84].ticks = 0x8; z80->cb_op[0x85].size = 0x2; z80->cb_op[0x85].ticks = 0x8;
   z80->cb_op[0x86].size = 0x2; z80->cb_op[0x86].ticks = 0x8; z80->cb_op[0x87].size = 0x2; z80->cb_op[0x87].ticks = 0x8;
   z80->cb_op[0x88].size = 0x2; z80->cb_op[0x88].ticks = 0x8; z80->cb_op[0x89].size = 0x2; z80->cb_op[0x89].ticks = 0x8;
   z80->cb_op[0x8a].size = 0x2; z80->cb_op[0x8a].ticks = 0x8; z80->cb_op[0x8b].size = 0x2; z80->cb_op[0x8b].ticks = 0x8;
   z80->cb_op[0x8c].size = 0x2; z80->cb_op[0x8c].ticks = 0x8; z80->cb_op[0x8d].size = 0x2; z80->cb_op[0x8d].ticks = 0x8;
   z80->cb_op[0x8e].size = 0x2; z80->cb_op[0x8e].ticks = 0x8; z80->cb_op[0x8f].size = 0x2; z80->cb_op[0x8f].ticks = 0x8;
   z80->cb_op[0x90].size = 0x2; z80->cb_op[0x90].ticks = 0x8; z80->cb_op[0x91].size = 0x2; z80->cb_op[0x91].ticks = 0x8;
   z80->cb_op[0x92].size = 0x2; z80->cb_op[0x92].ticks = 0x8; z80->cb_op[0x93].size = 0x2; z80->cb_op[0x93].ticks = 0x8;
   z80->cb_op[0x94].size = 0x2; z80->cb_op[0x94].ticks = 0x8; z80->cb_op[0x95].size = 0x2; z80->cb_op[0x95].ticks = 0x8;
   z80->cb_op[0x96].size = 0x2; z80->cb_op[0x96].ticks = 0x8; z80->cb_op[0x97].size = 0x2; z80->cb_op[0x97].ticks = 0x8;
   z80->cb_op[0x98].size = 0x2; z80->cb_op[0x98].ticks = 0x8; z80->cb_op[0x99].size = 0x2; z80->cb_op[0x99].ticks = 0x8;
   z80->cb_op[0x9a].size = 0x2; z80->cb_op[0x9a].ticks = 0x8; z80->cb_op[0x9b].size = 0x2; z80->cb_op[0x9b].ticks = 0x8;
   z80->cb_op[0x9c].size = 0x2; z80->cb_op[0x9c].ticks = 0x8; z80->cb_op[0x9d].size = 0x2; z80->cb_op[0x9d].ticks = 0x8;
   z80->cb_op[0x9e].size = 0x2; z80->cb_op[0x9e].ticks = 0x8; z80->cb_op[0x9f].size = 0x2; z80->cb_op[0x9f].ticks = 0x8;
   z80->cb_op[0xa0].size = 0x2; z80->cb_op[0xa0].ticks = 0x8; z80->cb_op[0xa1].size = 0x2; z80->cb_op[0xa1].ticks = 0x8;
   z80->cb_op[0xa2].size = 0x2; z80->cb_op[0xa2].ticks = 0x8; z80->cb_op[0xa3].size = 0x2; z80->cb_op[0xa3].ticks = 0x8;
   z80->cb_op[0xa4].size = 0x2; z80->cb_op[0xa4].ticks = 0x8; z80->cb_op[0xa5].size = 0x2; z80->cb_op[0xa5].ticks = 0x8;
   z80->cb_op[0xa6].size = 0x2; z80->cb_op[0xa6].ticks = 0x8; z80->cb_op[0xa7].size = 0x2; z80->cb_op[0xa7].ticks = 0x8;
   z80->cb_op[0xa8].size = 0x2; z80->cb_op[0xa8].ticks = 0x8; z80->cb_op[0xa9].size = 0x2; z80->cb_op[0xa9].ticks = 0x8;
   z80->cb_op[0xaa].size = 0x2; z80->cb_op[0xaa].ticks = 0x8; z80->cb_op[0xab].size = 0x2; z80->cb_op[0xab].ticks = 0x8;
   z80->cb_op[0xac].size = 0x2; z80->cb_op[0xac].ticks = 0x8; z80->cb_op[0xad].size = 0x2; z80->cb_op[0xad].ticks = 0x8;
   z80->cb_op[0xae].size = 0x2; z80->cb_op[0xae].ticks = 0x8; z80->cb_op[0xaf].size = 0x2; z80->cb_op[0xaf].ticks = 0x8;
   z80->cb_op[0xb0].size = 0x2; z80->cb_op[0xb0].ticks = 0x8; z80->cb_op[0xb1].size = 0x2; z80->cb_op[0xb1].ticks = 0x8;
   z80->cb_op[0xb2].size = 0x2; z80->cb_op[0xb2].ticks = 0x8; z80->cb_op[0xb3].size = 0x2; z80->cb_op[0xb3].ticks = 0x8;
   z80->cb_op[0xb4].size = 0x2; z80->cb_op[0xb4].ticks = 0x8; z80->cb_op[0xb5].size = 0x2; z80->cb_op[0xb5].ticks = 0x8;
   z80->cb_op[0xb6].size = 0x2; z80->cb_op[0xb6].ticks = 0x8; z80->cb_op[0xb7].size = 0x2; z80->cb_op[0xb7].ticks = 0x8;
   z80->cb_op[0xb8].size = 0x2; z80->cb_op[0xb8].ticks = 0x8; z80->cb_op[0xb9].size = 0x2; z80->cb_op[0xb9].ticks = 0x8;
   z80->cb_op[0xba].size = 0x2; z80->cb_op[0xba].ticks = 0x8; z80->cb_op[0xbb].size = 0x2; z80->cb_op[0xbb].ticks = 0x8;
   z80->cb_op[0xbc].size = 0x2; z80->cb_op[0xbc].ticks = 0x8; z80->cb_op[0xbd].size = 0x2; z80->cb_op[0xbd].ticks = 0x8;
   z80->cb_op[0xbe].size = 0x2; z80->cb_op[0xbe].ticks = 0x8; z80->cb_op[0xbf].size = 0x2; z80->cb_op[0xbf].ticks = 0x8;
   z80->cb_op[0xc0].size = 0x2; z80->cb_op[0xc0].ticks = 0x8; z80->cb_op[0xc1].size = 0x2; z80->cb_op[0xc1].ticks = 0x8;
   z80->cb_op[0xc2].size = 0x2; z80->cb_op[0xc2].ticks = 0x8; z80->cb_op[0xc3].size = 0x2; z80->cb_op[0xc3].ticks = 0x8;
   z80->cb_op[0xc4].size = 0x2; z80->cb_op[0xc4].ticks = 0x8; z80->cb_op[0xc5].size = 0x2; z80->cb_op[0xc5].ticks = 0x8;
   z80->cb_op[0xc6].size = 0x2; z80->cb_op[0xc6].ticks = 0x8; z80->cb_op[0xc7].size = 0x2; z80->cb_op[0xc7].ticks = 0x8;
   z80->cb_op[0xc8].size = 0x2; z80->cb_op[0xc8].ticks = 0x8; z80->cb_op[0xc9].size = 0x2; z80->cb_op[0xc9].ticks = 0x8;
   z80->cb_op[0xca].size = 0x2; z80->cb_op[0xca].ticks = 0x8; z80->cb_op[0xcb].size = 0x2; z80->cb_op[0xcb].ticks = 0x8;
   z80->cb_op[0xcc].size = 0x2; z80->cb_op[0xcc].ticks = 0x8; z80->cb_op[0xcd].size = 0x2; z80->cb_op[0xcd].ticks = 0x8;
   z80->cb_op[0xce].size = 0x2; z80->cb_op[0xce].ticks = 0x8; z80->cb_op[0xcf].size = 0x2; z80->cb_op[0xcf].ticks = 0x8;
   z80->cb_op[0xd0].size = 0x2; z80->cb_op[0xd0].ticks = 0x8; z80->cb_op[0xd1].size = 0x2; z80->cb_op[0xd1].ticks = 0x8;
   z80->cb_op[0xd2].size = 0x2; z80->cb_op[0xd2].ticks = 0x8; z80->cb_op[0xd3].size = 0x2; z80->cb_op[0xd3].ticks = 0x8;
   z80->cb_op[0xd4].size = 0x2; z80->cb_op[0xd4].ticks = 0x8; z80->cb_op[0xd5].size = 0x2; z80->cb_op[0xd5].ticks = 0x8;
   z80->cb_op[0xd6].size = 0x2; z80->cb_op[0xd6].ticks = 0x8; z80->cb_op[0xd7].size = 0x2; z80->cb_op[0xd7].ticks = 0x8;
   z80->cb_op[0xd8].size = 0x2; z80->cb_op[0xd8].ticks = 0x8; z80->cb_op[0xd9].size = 0x2; z80->cb_op[0xd9].ticks = 0x8;
   z80->cb_op[0xda].size = 0x2; z80->cb_op[0xda].ticks = 0x8; z80->cb_op[0xdb].size = 0x2; z80->cb_op[0xdb].ticks = 0x8;
   z80->cb_op[0xdc].size = 0x2; z80->cb_op[0xdc].ticks = 0x8; z80->cb_op[0xdd].size = 0x2; z80->cb_op[0xdd].ticks = 0x8;
   z80->cb_op[0xde].size = 0x2; z80->cb_op[0xde].ticks = 0x8; z80->cb_op[0xdf].size = 0x2; z80->cb_op[0xdf].ticks = 0x8;
   z80->cb_op[0xe0].size = 0x2; z80->cb_op[0xe0].ticks = 0x8; z80->cb_op[0xe1].size = 0x2; z80->cb_op[0xe1].ticks = 0x8;
   z80->cb_op[0xe2].size = 0x2; z80->cb_op[0xe2].ticks = 0x8; z80->cb_op[0xe3].size = 0x2; z80->cb_op[0xe3].ticks = 0x8;
   z80->cb_op[0xe4].size = 0x2; z80->cb_op[0xe4].ticks = 0x8; z80->cb_op[0xe5].size = 0x2; z80->cb_op[0xe5].ticks = 0x8;
   z80->cb_op[0xe6].size = 0x2; z80->cb_op[0xe6].ticks = 0x8; z80->cb_op[0xe7].size = 0x2; z80->cb_op[0xe7].ticks = 0x8;
   z80->cb_op[0xe8].size = 0x2; z80->cb_op[0xe8].ticks = 0x8; z80->cb_op[0xe9].size = 0x2; z80->cb_op[0xe9].ticks = 0x8;
   z80->cb_op[0xea].size = 0x2; z80->cb_op[0xea].ticks = 0x8; z80->cb_op[0xeb].size = 0x2; z80->cb_op[0xeb].ticks = 0x8;
   z80->cb_op[0xec].size = 0x2; z80->cb_op[0xec].ticks = 0x8; z80->cb_op[0xed].size = 0x2; z80->cb_op[0xed].ticks = 0x8;
   z80->cb_op[0xee].size = 0x2; z80->cb_op[0xee].ticks = 0x8; z80->cb_op[0xef].size = 0x2; z80->cb_op[0xef].ticks = 0x8;
   z80->cb_op[0xf0].size = 0x2; z80->cb_op[0xf0].ticks = 0x8; z80->cb_op[0xf1].size = 0x2; z80->cb_op[0xf1].ticks = 0x8;
   z80->cb_op[0xf2].size = 0x2; z80->cb_op[0xf2].ticks = 0x8; z80->cb_op[0xf3].size = 0x2; z80->cb_op[0xf3].ticks = 0x8;
   z80->cb_op[0xf4].size = 0x2; z80->cb_op[0xf4].ticks = 0x8; z80->cb_op[0xf5].size = 0x2; z80->cb_op[0xf5].ticks = 0x8;
   z80->cb_op[0xf6].size = 0x2; z80->cb_op[0xf6].ticks = 0x8; z80->cb_op[0xf7].size = 0x2; z80->cb_op[0xf7].ticks = 0x8;
   z80->cb_op[0xf8].size = 0x2; z80->cb_op[0xf8].ticks = 0x8; z80->cb_op[0xf9].size = 0x2; z80->cb_op[0xf9].ticks = 0x8;
   z80->cb_op[0xfa].size = 0x2; z80->cb_op[0xfa].ticks = 0x8; z80->cb_op[0xfb].size = 0x2; z80->cb_op[0xfb].ticks = 0x8;
   z80->cb_op[0xfc].size = 0x2; z80->cb_op[0xfc].ticks = 0x8; z80->cb_op[0xfd].size = 0x2; z80->cb_op[0xfd].ticks = 0x8;
   z80->cb_op[0xfe].size = 0x2; z80->cb_op[0xfe].ticks = 0x8; z80->cb_op[0xff].size = 0x2; z80->cb_op[0xff].ticks = 0x8;

   return 0;
}

int ResetZ80(Z80 * z80, Registers * registers, Opcodes * op, Opcodes * cb_op)
{
   InitZ80(z80,registers,op,cb_op);

   return 0;
}

int Dispatch(Memory * memory, Z80 * z80)
{
   while(1)
   {
      /*Fetch(memory,z80);*/
      Execute(memory,z80);
   }

   /* Testing register manipulation */
   z80->regA = 1;

   return 0;
}

int Fetch(Memory * memory, Z80 * z80)
{
   /* Fetch correct number of bytes for instruction and decode */
   /* switch(memory->addr[z80->regPC] & 0x00FF)
   {
   } */
   return 0; 
}

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  math_pow_uint8
 *  Description:  Return 8-bit unsigned value of value (power of) pow
 *                Only works with positive numbers for which the answer
 *                does not exceed 255
 * =====================================================================================
 */
   uint8_t
math_pow_uint8 ( uint8_t value, uint8_t pow )
{
   int i;
   uint8_t tmp = value;

   if ( pow < 1 ) {
      return 1;
   }

   for ( i = 1; i < pow ; i++ )
   {
      value = value * tmp;
   }

   return value;
}

int8_t ensure_8b_signed(int8_t value)
{
   return (int8_t) value;
}

int CB_BIT(Memory * memory, Z80 * z80, uint8_t parameters)
{
   uint8_t bitTest;
   uint8_t cpuRegisterBit;
   uint16_t tmp_z80_F = z80->regF;

   cpuRegisterBit = (z80->r->r[(parameters & 0xF)] >> ((parameters & 0xF0) >> 4)) & 0x1;

   // Zero subtract flag and set half carry
   z80->regF = 0x20;

   // Preserve carry
   z80->regF = z80->regF | (tmp_z80_F & 0x10);

   if (cpuRegisterBit == 0x0)
   {
      // Zero flag
      z80->regF = z80->regF | 0x80;
   }

   z80->ticks = 8;

   return 0;
}

int CB_RES(Memory * memory, Z80 * z80, uint8_t parameters)
{
   char regName;
   uint8_t bitReset;
   uint8_t cpuRegister;
   uint8_t bitMask;

   z80->r->r[(parameters & 0xF)] = z80->r->r[(parameters & 0xF)] & math_pow_uint8(2,(((parameters & 0xF0) >> 4) & 0xF));

   z80->ticks = 8; 

   return 0;
}

int CB_SET(Memory * memory, Z80 * z80, uint8_t parameters)
{
   char regName;
   uint8_t bitSet;
   uint8_t cpuRegister;
   uint8_t bitMask;
 
   z80->r->r[(parameters & 0xF)] = (z80->r->r[(parameters & 0xF)] | math_pow_uint8(2,(((parameters & 0xF0) >> 4) & 0xF)));

   z80->ticks = 8; 

   return 0;
}

int CB_RLC(Memory * memory, Z80 * z80, uint8_t parameters)
{
   // Unset F register (flags)
   z80->regF = 0x0;

   // Set carry flag (0x10)
   z80->regF = z80->regF | ((z80->r->r[(parameters & 0xF)] >> 7) & 0x1) << 1;

   // Zero flag
   if (z80->r->r[(parameters & 0xF)] == 0)
   {
      z80->regF = z80->regF | 0x80;
   }

   // Rotate register, add carry bit, and ensure 8 bits
   z80->r->r[(parameters & 0xF)] = (((z80->r->r[(parameters & 0xF)] << 1) + ((z80->regF >> 5) & 0x1)) & 0xFF);

   z80->ticks = 8;

   return 0;
}

int CB_RRC(Memory * memory, Z80 * z80, uint8_t parameters)
{
   // Unset F register (flags)
   z80->regF = 0x0;

   // Set carry flag (0x10)
   z80->regF = z80->regF | (z80->r->r[(parameters & 0xF)] & 0x1) << 1;

   // Zero flag
   if (z80->r->r[(parameters & 0xF)] == 0)
   {
      z80->regF = z80->regF | 0x80;
   }

   // Rotate register, add carry bit, and ensure 8 bits
   z80->r->r[(parameters & 0xF)] = (z80->r->r[(parameters & 0xF)] >> 1) + (((z80->regF >> 5) & 0x1) << 7) & 0xFF;

   z80->ticks = 8;

   return 0;
}

int HertzToMilliseconds(int Hertz)
{
   int ms = (Hertz / 1) * 1000;
   usleep(ms);

   return 0;
}

int decrementHL(Z80 * z80)
{
   uint16_t tmpHL;

   tmpHL = (z80->regH << 8) + z80->regL;
   tmpHL--;

   z80->regH = (tmpHL & 0xFF00) >> 8;
   z80->regL = (tmpHL & 0xFF);

   return 0;
}

int incrementHL(Z80 * z80)
{
   uint16_t tmpHL;

   tmpHL = (z80->regH << 8) + z80->regL;
   tmpHL++;

   z80->regH = (tmpHL & 0xFF00) >> 8;
   z80->regL = (tmpHL & 0xFF);

   return 0;
}

int calculateAdditionFlags(Memory * memory, Z80 * z80, uint8_t dest, uint8_t oldDest, uint8_t oldSrc)
{
   // Flags
   if (((dest & 0xFF) < oldDest) | ((dest & 0xFF) < oldSrc))
   {
      // Carry
      z80->regF = 0x10;
   }

   if ((dest & 0xFF) == 0x00)
   {
      // Zero flag
      z80->regF = z80->regF | 0x80;
   }

   if (((oldSrc & 0xF) + (oldDest & 0xF)) & 0x10)
   {
      // Half-carry
      z80->regF = z80->regF | 0x20;
   }

   return 0;
}

int calculateSubtractionFlags(Memory * memory, Z80 * z80, uint8_t dest, uint8_t oldDest, uint8_t oldSrc)
{
   // Flags
   if (((dest & 0xFF) > oldDest) | ((dest & 0xFF) > oldSrc))
   {
      // Carry
      z80->regF = 0x10;
   }

   if ((dest & 0xFF) == 0x00)
   {
      // Zero flag
      z80->regF = z80->regF | 0x80;
   }

   if (((oldSrc & 0xF) - (oldDest & 0xF)) & 0x10)
   {
      // Half-carry
      z80->regF = z80->regF | 0x20;
   }

   //Subtract
   z80->regF = z80->regF | 0x40;

   return 0;
}

int calculateAndFlags(Memory * memory, Z80 * z80, uint8_t dest)
{
   z80->regF = 0x00;

   if ((dest & 0xFF) == 0x00)
   {
      // Zero flag
      z80->regF = z80->regF | 0x80;
   }

   // Half-carry
   z80->regF = z80->regF | 0x20;

   return 0;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  OP_LDXD8
 *  Description:  Load immediate into register X
 * =====================================================================================
 */
int OP_LDXD8(Memory * memory, Z80 * z80, uint8_t x)
{
   z80->r->r[(x & 0xF)] = rb(memory,(z80->regPC)) & 0xFF;

   z80->regPC = z80->regPC + 1;
   z80->ticks = 8;

   return 0;
}

int OP_LDXY(Memory * memory, Z80 * z80, uint8_t x)
{
   z80->r->r[((x & 0xF0) >> 4)] = z80->r->r[(x & 0xF)];

   z80->ticks = 4;

   return 0;
}

int OP_LDHLX(Memory * memory, Z80 * z80, uint8_t x)
{
   wb(memory,(z80->regH << 8) + z80->regL,z80->r->r[x & 0xF]);

   z80->ticks = 8;

   return 0;
}

/* OPCODES */
int OP_00h_NOP(Memory * memory, Z80 * z80)
{
   z80->ticks = 4;

   return 0;
}

int OP_INCX(Memory * memory, Z80 * z80, uint8_t x)
{
   uint8_t oldRegValue = z80->r->r[x & 0xF];

   z80->r->r[x & 0xF]++;

   // Zero flag
   if (z80->r->r[x & 0xF] == 0x0)
   {
      z80->regF = z80->regF | 0x80;
   }

   // Half carry
   // If 0xF on oldRegValue, then set H flag
   if ((oldRegValue & 0xF) & 0xF)
   {
      z80->regF = z80->regF | 0x20;
   }

   // Set N flag to 0x0;
   z80->regF = z80->regF & 0xB0;

   z80->ticks = 4;

   return 0;
}

int OP_20h_JRNZn(Memory * memory, Z80 * z80)
{
   int8_t i;

   i = (int8_t) rb(memory,(z80->regPC)) & 0xFF;

   z80->regPC++;

   if ((z80->regF & 0x80) == 0x00)
   {
      z80->regPC = (z80->regPC + (int8_t) i) & 0xFF;
      z80->ticks = 12;
   } else {
      z80->ticks = 8;
   }

   return 0;
}

int OP_21h_LDHLnn(Memory * memory, Z80 * z80)
{
   z80->regH = rb(memory,(z80->regPC+1));
   z80->regL = rb(memory,(z80->regPC));
   z80->regPC = z80->regPC + 2;
   z80->ticks = 12;

   return 0;
}

int OP_22h_LDIHLA(Memory * memory, Z80 * z80)
{
   uint16_t tmp;

   wb(memory,(z80->regH << 8) + z80->regL,z80->regA);
   tmp = (z80->regH << 8) + z80->regL;

   incrementHL(z80);
   z80->ticks = 8;

   return 0;
}

int OP_31h_LDSPnn(Memory * memory, Z80 * z80)
{
   z80->regSP = (uint16_t) rw(memory,z80->regPC);
   z80->regPC = (uint16_t) z80->regPC + (uint16_t) 2;
   z80->ticks = 12;

   return 0;
}

int OP_32h_LDDHLA(Memory * memory, Z80 * z80)
{
   uint16_t tmp;

   // BUG?
   wb(memory,(z80->regH << 8) + z80->regL,z80->regA);
   tmp = (z80->regH << 8) + z80->regL;

   decrementHL(z80);
   z80->ticks = 8;

   return 0;
}

int OP_72h_LDHLD(Memory * memory, Z80 * z80)
{
   wb(memory,(z80->regH << 8) + z80->regL,z80->regD);

   z80->ticks = 8;

   return 0;
}

int OP_80h_ADDAB(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regB;

   z80->regA = z80->regA + z80->regB;

   uint8_t dest = z80->regA;

   calculateAdditionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->ticks = 4;

   return 0;
}

int OP_81h_ADDAC(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regC;

   z80->regA = z80->regA + z80->regC;

   uint8_t dest = z80->regA;

   calculateAdditionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->ticks = 4;

   return 0;
}

int OP_82h_ADDAD(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regD;

   z80->regA = z80->regA + z80->regD;

   uint8_t dest = z80->regA;

   calculateAdditionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->ticks = 4;

   return 0;
}

int OP_83h_ADDAE(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regE;

   z80->regA = (z80->regA + z80->regE) & 0xFF;

   uint8_t dest = z80->regA;

   calculateAdditionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->ticks = 4;

   return 0;
}

int OP_84h_ADDAH(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regH;

   z80->regA = z80->regA + z80->regH;

   uint8_t dest = z80->regA;

   calculateAdditionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->ticks = 4;

   return 0;
}

int OP_85h_ADDAL(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regL;

   z80->regA = z80->regA + z80->regL;

   uint8_t dest = z80->regA;

   calculateAdditionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->ticks = 4;

   return 0;
}

int OP_87h_ADDAA(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regA;

   z80->regA = z80->regA + z80->regA;

   uint8_t dest = z80->regA;

   calculateAdditionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->ticks = 4;

   return 0;
}

int OP_88h_ADCAB(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regB;

   z80->regA = (z80->regA + z80->regB) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateAdditionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->regA = z80->regA + ((z80->regF & 0x10) >> 4) & 0xFF;

   z80->ticks = 4;

   return 0;
}

int OP_89h_ADCAC(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regC;

   z80->regA = (z80->regA + z80->regC) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateAdditionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->regA = z80->regA + ((z80->regF & 0x10) >> 4) & 0xFF;

   z80->ticks = 4;

   return 0;
}

int OP_8Ah_ADCAD(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regD;

   z80->regA = (z80->regA + z80->regD) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateAdditionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->regA = z80->regA + ((z80->regF & 0x10) >> 4) & 0xFF;

   z80->ticks = 4;

   return 0;
}

int OP_8Bh_ADCAE(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regE;

   z80->regA = (z80->regA + z80->regE) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateAdditionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->regA = z80->regA + ((z80->regF & 0x10) >> 4) & 0xFF;

   z80->ticks = 4;

   return 0;
}

int OP_8Ch_ADCAH(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regH;

   z80->regA = (z80->regA + z80->regH) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateAdditionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->regA = z80->regA + ((z80->regF & 0x10) >> 4) & 0xFF;

   z80->ticks = 4;

   return 0;
}

int OP_8Dh_ADCAL(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regL;

   z80->regA = (z80->regA + z80->regL) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateAdditionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->regA = z80->regA + ((z80->regF & 0x10) >> 4) & 0xFF;

   z80->ticks = 4;

   return 0;
}

int OP_8Fh_ADCAA(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regA;

   z80->regA = (z80->regA + z80->regA) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateAdditionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->regA = z80->regA + ((z80->regF & 0x10) >> 4) & 0xFF;

   z80->ticks = 4;

   return 0;
}

int OP_90h_SUBB(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regB;

   z80->regA = (z80->regA - z80->regB) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateSubtractionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->ticks = 4;

   return 0;
}

int OP_91h_SUBC(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regC;

   z80->regA = (z80->regA - z80->regC) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateSubtractionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->ticks = 4;

   return 0;
}

int OP_92h_SUBD(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regD;

   z80->regA = (z80->regA - z80->regD) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateSubtractionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->ticks = 4;

   return 0;
}

int OP_93h_SUBE(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regE;

   z80->regA = (z80->regA - z80->regE) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateSubtractionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->ticks = 4;

   return 0;
}

int OP_94h_SUBH(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regH;

   z80->regA = (z80->regA - z80->regH) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateSubtractionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->ticks = 4;

   return 0;
}

int OP_95h_SUBL(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regL;

   z80->regA = (z80->regA - z80->regL) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateSubtractionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->ticks = 4;

   return 0;
}

int OP_97h_SUBA(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regA;

   z80->regA = (z80->regA - z80->regA) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateSubtractionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->ticks = 4;

   return 0;
}

int OP_98h_SBCAB(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regB;
   z80->regA = (z80->regA - z80->regB) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateSubtractionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->regA = z80->regA - ((z80->regF & 0x10) >> 4) & 0xFF;

   z80->ticks = 4;

   return 0;
}

int OP_99h_SBCAC(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regC;
   z80->regA = (z80->regA - z80->regC) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateSubtractionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->regA = z80->regA - ((z80->regF & 0x10) >> 4) & 0xFF;

   z80->ticks = 4;

   return 0;
}

int OP_9Ah_SBCAD(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regD;
   z80->regA = (z80->regA - z80->regD) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateSubtractionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->regA = z80->regA - ((z80->regF & 0x10) >> 4) & 0xFF;

   z80->ticks = 4;

   return 0;
}

int OP_9Bh_SBCAE(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regE;
   z80->regA = (z80->regA - z80->regE) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateSubtractionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->regA = z80->regA - ((z80->regF & 0x10) >> 4) & 0xFF;

   z80->ticks = 4;

   return 0;
}

int OP_9Ch_SBCAH(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regH;
   z80->regA = (z80->regA - z80->regH) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateSubtractionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->regA = z80->regA - ((z80->regF & 0x10) >> 4) & 0xFF;

   z80->ticks = 4;

   return 0;
}

int OP_9Dh_SBCAL(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regL;
   z80->regA = (z80->regA - z80->regL) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateSubtractionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->regA = z80->regA - ((z80->regF & 0x10) >> 4) & 0xFF;

   z80->ticks = 4;

   return 0;
}

int OP_9Fh_SBCAA(Memory * memory, Z80 * z80)
{
   uint8_t oldDest = z80->regA;
   uint8_t oldSrc = z80->regL;
   z80->regA = (z80->regA - z80->regA) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateSubtractionFlags(memory,z80,dest,oldDest,oldSrc);

   z80->regA = z80->regA - ((z80->regF & 0x10) >> 4) & 0xFF;

   z80->ticks = 4;

   return 0;
}

int OP_A0h_ANDB(Memory * memory, Z80 * z80)
{
   z80->regA = (z80->regA & z80->regB) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateAndFlags(memory,z80,dest);

   z80->ticks = 4;

   return 0;
}

int OP_A1h_ANDC(Memory * memory, Z80 * z80)
{
   z80->regA = (z80->regA & z80->regC) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateAndFlags(memory,z80,dest);

   z80->ticks = 4;

   return 0;
}

int OP_A2h_ANDD(Memory * memory, Z80 * z80)
{
   z80->regA = (z80->regA & z80->regD) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateAndFlags(memory,z80,dest);

   z80->ticks = 4;

   return 0;
}

int OP_A3h_ANDE(Memory * memory, Z80 * z80)
{
   z80->regA = (z80->regA & z80->regE) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateAndFlags(memory,z80,dest);

   z80->ticks = 4;

   return 0;
}

int OP_A4h_ANDH(Memory * memory, Z80 * z80)
{
   z80->regA = (z80->regA & z80->regH) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateAndFlags(memory,z80,dest);

   z80->ticks = 4;

   return 0;
}

int OP_A5h_ANDL(Memory * memory, Z80 * z80)
{
   z80->regA = (z80->regA & z80->regL) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateAndFlags(memory,z80,dest);

   z80->ticks = 4;

   return 0;
}

int OP_A7h_ANDA(Memory * memory, Z80 * z80)
{
   z80->regA = (z80->regA & z80->regA) & 0xFF;

   uint8_t dest = z80->regA & 0xFF;

   calculateAndFlags(memory,z80,dest);

   z80->ticks = 4;

   return 0;
}

int OP_AFh_XORA(Memory * memory, Z80 * z80)
{
   z80->regA = 0;
   z80->regF = 0x80;
   z80->ticks = 4;

   return 0;
}

int OP_E0h_LDHAn(Memory * memory, Z80 * z80)
{
   wb(memory,(0xff00 + rb(memory,z80->regPC)),z80->regA);

   z80->regPC = z80->regPC + 1;
   z80->ticks = 12;

   return 0;
}

int OP_E2h_LDHCA(Memory * memory, Z80 * z80)
{
   wb(memory,(0xff00 + z80->regC),z80->regA);
   z80->ticks = 8;

   return 0;
}

int OP_CBh_PREFIXCB(Memory * memory, Z80 * z80)
{
   ExecuteCB(memory,z80);

   return 0;
}

int OP_FFh_RST38h(Memory * memory, Z80 * z80)
{
   z80->regSP--;
   z80->regSP = z80->regPC;
   z80->regSP--;
   z80->regPC = 0x38;
   z80->ticks = 16;

   return 0;
}

int Execute(Memory * memory, Z80 * z80)
{
   int callDebug = 1;
   uint16_t tmp;

   Debug debug;
   Error err;

   //usleep(50000);

   if (callDebug == 1) printf("rb %x\n",rb(memory,(z80->regPC)));

   if (callDebug == 1)
   {
      debug.instructionSize = 1;
      DebugAll(z80, memory, &debug);
   }

   /* switch((memory->addr[z80->regPC] & 0xFF00) >> 8) */
   switch(rb(memory,(z80->regPC++)))
   {
      case 0x00: OP_00h_NOP(memory,z80); break;

      case 0x04: OP_INCX(memory,z80,(uint8_t) 0x1); break;
      case 0x06: OP_LDXD8(memory,z80,(uint8_t) 0x1); break;
      case 0x0C: OP_INCX(memory,z80,(uint8_t) 0x2); break;
      case 0x0E: OP_LDXD8(memory,z80,(uint8_t) 0x2); break;
      case 0x14: OP_INCX(memory,z80,(uint8_t) 0x3); break;
      case 0x16: OP_LDXD8(memory,z80,(uint8_t) 0x3); break;
      case 0x1C: OP_INCX(memory,z80,(uint8_t) 0x4); break;
      case 0x1E: OP_LDXD8(memory,z80,(uint8_t) 0x4); break;
      case 0x26: OP_LDXD8(memory,z80,(uint8_t) 0x6); break;
      case 0x2E: OP_LDXD8(memory,z80,(uint8_t) 0x7); break;
      case 0x3E: OP_LDXD8(memory,z80,(uint8_t) 0x0); break;

      case 0x20: OP_20h_JRNZn(memory,z80); break;
      case 0x21: OP_21h_LDHLnn(memory,z80); break;
      case 0x22: OP_22h_LDIHLA(memory,z80); break;
      case 0x24: OP_INCX(memory,z80,(uint8_t) 0x6); break;
      case 0x2C: OP_INCX(memory,z80,(uint8_t) 0x7); break;
      case 0x31: OP_31h_LDSPnn(memory,z80); break;
      case 0x32: OP_32h_LDDHLA(memory,z80); break;

      case 0x40: OP_LDXY(memory,z80,0x11); break;
      case 0x41: OP_LDXY(memory,z80,0x12); break;
      case 0x42: OP_LDXY(memory,z80,0x13); break;
      case 0x43: OP_LDXY(memory,z80,0x14); break;
      case 0x44: OP_LDXY(memory,z80,0x16); break;
      case 0x45: OP_LDXY(memory,z80,0x17); break;
      case 0x50: OP_LDXY(memory,z80,0x31); break;
      case 0x51: OP_LDXY(memory,z80,0x32); break;
      case 0x52: OP_LDXY(memory,z80,0x33); break;
      case 0x53: OP_LDXY(memory,z80,0x34); break;
      case 0x54: OP_LDXY(memory,z80,0x36); break;
      case 0x55: OP_LDXY(memory,z80,0x37); break;
      case 0x60: OP_LDXY(memory,z80,0x61); break;
      case 0x61: OP_LDXY(memory,z80,0x62); break;
      case 0x62: OP_LDXY(memory,z80,0x63); break;
      case 0x63: OP_LDXY(memory,z80,0x64); break;
      case 0x64: OP_LDXY(memory,z80,0x66); break;
      case 0x65: OP_LDXY(memory,z80,0x67); break;

      case 0x70: OP_LDHLX(memory,z80,0x1); break;
      case 0x71: OP_LDHLX(memory,z80,0x2); break;
      case 0x72: OP_LDHLX(memory,z80,0x3); break;
      case 0x73: OP_LDHLX(memory,z80,0x4); break;
      case 0x74: OP_LDHLX(memory,z80,0x6); break;
      case 0x75: OP_LDHLX(memory,z80,0x7); break;
      case 0x77: OP_LDHLX(memory,z80,0x0); break;

      case 0xAF: OP_AFh_XORA(memory,z80); break;

      case 0xE0: OP_E0h_LDHAn(memory,z80); break;
      case 0xE2: OP_E2h_LDHCA(memory,z80); break;

      // CB prefixed opcodes
      case 0xCB: OP_CBh_PREFIXCB(memory,z80); break;
      case 0xFF: OP_FFh_RST38h(memory,z80); break;

      default:
         err.code = 20;
         exiterror(&err);
      break;
   }

   // Reset after acting on ticks
   z80->ticks = 0;

   return 0;
}

int ExecuteCB(Memory * memory, Z80 * z80)
{
   int callDebug = 1;
   uint16_t tmp;

   Debug debug;
   Error err;

   //usleep(50000);

   if (callDebug == 1) printf("rb %x\n",rb(memory,(z80->regPC)));

   if (callDebug == 1)
   {
      debug.instructionSize = 1;
      DebugAll(z80, memory, &debug);
   }

   /* switch((memory->addr[z80->regPC] & 0xFF00) >> 8) */
   switch(rb(memory,(z80->regPC++)))
   {
      // NEED TO DEVELOP TEST CODE AND SORT OUT
      /*case 0x00: OP_CB_00h_RLCB(memory,z80); break;
      case 0x21: OP_CB_21h_SLAC(memory,z80); break;
      case 0x22: OP_CB_22h_SLAD(memory,z80); break;
      case 0x31: OP_CB_31h_SLAPB(memory,z80); break;*/
      // a = 0 b = 1 c = 2 d = 3 e = 4 f = 5 h = 6 l = 7
      //case 0x40: OP_CB_40h_BIT0B(memory,z80); break;
      case 0x40: CB_BIT(memory,z80,0x01); break;
      case 0x41: CB_BIT(memory,z80,0x02); break;
      case 0x42: CB_BIT(memory,z80,0x03); break;
      case 0x43: CB_BIT(memory,z80,0x04); break;
      case 0x44: CB_BIT(memory,z80,0x06); break;
      case 0x45: CB_BIT(memory,z80,0x07); break;
      case 0x47: CB_BIT(memory,z80,0x00); break;
      case 0x7c: CB_BIT(memory,z80,0x76); break;
      /*case 0x40: CB_BIT(memory,z80,0x01); break;
      case 0x40: CB_BIT(memory,z80,0x01); break;
      case 0x41: OP_CB_41h_BIT0C(memory,z80); break;
      case 0x42: OP_CB_42h_BIT0D(memory,z80); break;
      case 0x43: OP_CB_43h_BIT0E(memory,z80); break;
      case 0x44: OP_CB_44h_BIT0H(memory,z80); break;
      case 0x45: OP_CB_45h_BIT0L(memory,z80); break;
      case 0x50: OP_CB_50h_BIT2B(memory,z80); break;
      case 0x51: OP_CB_51h_BIT2C(memory,z80); break;
      case 0x52: OP_CB_52h_BIT2D(memory,z80); break;
      case 0x53: OP_CB_53h_BIT2E(memory,z80); break;
      case 0x54: OP_CB_54h_BIT2H(memory,z80); break;
      case 0x55: OP_CB_55h_L(memory,z80); break;
      case 0x60: OP_CB_60h_LDHB(memory,z80); break;
      case 0x61: OP_CB_61h_LDHC(memory,z80); break;
      case 0x62: OP_CB_62h_LDHD(memory,z80); break;
      case 0x63: OP_CB_63h_LDHE(memory,z80); break;
      case 0x64: OP_CB_64h_LDHH(memory,z80); break;
      case 0x65: OP_CB_65h_LDHL(memory,z80); break;
      case 0xAF: OP_CB_AFh_XORA(memory,z80); break;
      case 0xFF: OP_CB_FFh_RST38h(memory,z80); break;*/

      default:
         err.code = 20;
         exiterror(&err);
      break;
   }

   // Reset after acting on ticks
   z80->ticks = 0;

   return 0;
}
