#ifdef UNITTEST_OPCODES
   #ifndef _INCL_MEMORY
      #define _INCL_MEMORY
      #include "mock_memory.h"
   #endif
#else
   #ifndef _INCL_MEMORY
      #define _INCL_MEMORY
      #include "memory.h"
   #endif
#endif

int LoadGBROM(Memory * memory, char * GBROM);
