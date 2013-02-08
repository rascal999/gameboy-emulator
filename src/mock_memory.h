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

typedef struct Z80 Z80;

typedef struct
{
   uint8_t addr[0x10000]; /* 16 bit address buffer. Mem size of 65 536 */

   /*
      0000-3FFF   16KB ROM Bank 00     (in cartridge, fixed at bank 00)
      4000-7FFF   16KB ROM Bank 01..NN (in cartridge, switchable bank number)
      8000-9FFF   8KB Video RAM (VRAM) (switchable bank 0-1 in CGB Mode)
      A000-BFFF   8KB External RAM     (in cartridge, switchable bank, if any)
      C000-CFFF   4KB Work RAM Bank 0 (WRAM)
      D000-DFFF   4KB Work RAM Bank 1 (WRAM)  (switchable bank 1-7 in CGB Mode)
      E000-FDFF   Same as C000-DDFF (ECHO)    (typically not used)
      FE00-FE9F   Sprite Attribute Table (OAM)
      FEA0-FEFF   Not Usable
      FF00-FF7F   I/O Ports
      FF80-FFFE   High RAM (HRAM)
      FFFF        Interrupt Enable Register
   */

   uint8_t bios_rom[0x100];
   uint8_t bank0[0x4000];
   uint8_t bankNNN[0x4000];
   uint8_t vram[0x2000];
   uint8_t eram[0x2000];
   uint8_t wram0[0x1000];
   uint8_t wram1[0x1000];
   uint8_t wram_shadow[0x1E00];
   uint8_t sat[0xA0];
   uint8_t io_ports[0x80];
   uint8_t hram[0x80];

   uint8_t div; /* Divider */
   uint8_t tima; /* Timer Counter */
   uint8_t tma; /* Timer Modulo */
   uint8_t tac; /* Control */

   int bios_rom_loaded;
   int tmp;
} Memory;

/* MMU */
/* Read byte */
uint8_t rb(Memory * mem, uint16_t addr);

/* Write byte */
int wb(Memory * mem, uint16_t addr, uint8_t value);

/* Read word */
uint16_t rw(Memory * mem, uint16_t addr);

/* Write word */
int ww(Memory * mem, Z80 * z80, uint16_t addr, uint16_t value);
/* END MMU */

int InitMemory(Memory * memory);
