#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#ifdef UNITTEST_OPCODES
   #include "mock_error.h"
   #include "mock_rom.h"
   #ifndef _INCL_MEMORY
      #define _INCL_MEMORY
      #include "mock_memory.h"
   #endif
#else
   #include "error.h"
   #include "rom.h"
   #ifndef _INCL_MEMORY
      #define _INCL_MEMORY
      #include "memory.h"
   #endif
#endif

#ifndef _INCL_STDINT
   #define _INCL_STDINT
   #include <stdint.h>
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
