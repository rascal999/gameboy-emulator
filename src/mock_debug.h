#ifdef UNITTEST_OPCODES
   #ifndef _INCL_MEMORY
      #define _INCL_MEMORY
      #include "mock_memory.h"
   #endif
   #ifndef _INCL_Z80
      #define _INCL_Z80
      #include "mock_z80.h"
   #endif
#else
   #ifndef _INCL_MEMORY
      #define _INCL_MEMORY
      #include "memory.h"
   #endif
   #ifndef _INCL_Z80
      #define _INCL_Z80
      #include "z80.h"
   #endif
#endif

typedef struct
{
   int instructionSize;
   char stringInstruction[16];
} Debug;

int DebugAll(Z80 * z80, Memory * memory, Debug * debug);
int DebugNextInstructionSize(uint8_t opcode);
