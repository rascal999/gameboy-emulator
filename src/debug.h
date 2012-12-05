#ifndef _INCL_MEMORY
#define _INCL_MEMORY
#include "memory.h"
#endif
#ifndef _INCL_Z80
#define _INCL_Z80
#include "z80.h"
#endif

typedef struct
{
   int instructionSize;
   char stringInstruction[16];
} Debug;

int DebugAll(Z80 * z80, Memory * memory, Debug * debug);
int DebugNextInstructionSize(uint8_t opcode);
