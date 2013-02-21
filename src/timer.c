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
#include "display.h"
#include "error.h"
#include "memory.h"
#include "opcode_attributes.h"
#include "opcode_wrappers.h"
#include "rom.h"
#include "timer.h"
#include "z80.h"

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

/* Timers */
/* Read byte */
unsigned short rb_timer(Timers * timer, unsigned short addr)
{
   return 0;
}

/* Write byte */
int wb_timer(Timers * timer, unsigned short addr, unsigned char value)
{
   return 0;
}

/* Read word */
unsigned short rw_timer(Timers * timer, unsigned short addr)
{
   return 0;
}

/* Write word */
int ww_timer(Timers * timer, unsigned short addr, unsigned short value)
{
   return 0;
}
/* END Timers */

int InitTimers(Timers * timer)
{
   return 0;
}
