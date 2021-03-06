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

int LoadGBROM(Memory * memory, char * GBROM)
{
   int bufSize = 2048;
   int bufSizeRead = 0;
   int i = 0;
   int k = 0;
   int fd = 0;

   uint8_t buf[bufSize];
   Error error;

   printf("Loading GB ROM ...\n");

   if ((fd = open(GBROM,O_RDONLY)) == 0)
   {
      error.code = 2;
      exiterror(&error);
   }

   while((bufSizeRead=read(fd,buf,bufSize))>0)
   {
      for(k=0;k<bufSizeRead;k++)
      {
         memory->bios_rom[i] = buf[i];
         i++;
      }
   }

   if (bufSizeRead == -1)
   {
      error.code = 3;
      exiterror(&error);
   }

   return 0;
}
