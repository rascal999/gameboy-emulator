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

int exiterror(Error * error)
{
   switch(error->code)
   {
      case 2:
         printf("Error 1: Cannot open file\n");
         exit(2);
      break;

      case 3:
         printf("Error 3: Error reading from file\n");
         exit(3);
      break;

      case 4:
         printf("Specify rom file\n");
         printf("Error 4: Incorrect number of arguments\n");
         exit(4);
      break;

      case 20:
         printf("Error 20: Missing opcode\n");
         exit(20);
      break;

      case 30:
         printf("Error 30: Unaddressable location\n");
         exit(30);
      break;
   }

   return 1;
}
