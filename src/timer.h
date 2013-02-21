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
