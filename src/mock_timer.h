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
//   #include "mock_cartridge.h"
//   #include "mock_debug.h"
//   #include "mock_display.h"
//   #include "mock_error.h"
//   #include "mock_memory.h"
//   #include "mock_opcode_attributes.h"
//   #include "mock_opcode_wrappers.h"
//   #include "mock_rom.h"
//   #include "mock_timer.h"
//   #include "mock_z80.h"
#else
//   #include "cartridge.h"
//   #include "debug.h"
//   #include "display.h"
//   #include "error.h"
//   #include "memory.h"
//   #include "opcode_attributes.h"
//   #include "opcode_wrappers.h"
//   #include "rom.h"
//   #include "timer.h"
//   #include "z80.h"
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

typedef struct
{
   /*
      FF04 - DIV - Divider Register (R/W)
      FF05 - TIMA - Timer counter (R/W)
      FF06 - TMA - Timer Modulo (R/W)
      FF07 - TAC - Timer Control (R/W)
      INT 50 - Timer Interrupt
   */

   unsigned short div;
   unsigned short tima;
   unsigned short tma;
   unsigned short tac;
} Timers;

/* Timers */
/* Read byte */
unsigned short rb_timer(Timers * timer, unsigned short addr);

/* Write byte */
int wb_timer(Timers * timer, unsigned short addr, unsigned char value);

/* Read word */
unsigned short rw_timer(Timers * timer, unsigned short addr);

/* Write word */
int ww_timer(Timers * timer, unsigned short addr, unsigned short value);
/* END Timers */

int InitTimers(Timers * timer);
