#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#ifndef _INCL_CARTRIDGE
   #define _INCL_CARTRIDGE
   #include "cartridge.h"
#endif
#ifndef _INCL_ERROR
   #define _INCL_ERROR
   #include "error.h"
#endif
#ifndef _INCL_Z80
   #define _INCL_Z80
   #include "z80.h"
#endif
#ifndef _INCL_MEMORY
   #define _INCL_MEMORY
   #include "memory.h"
#endif

int LoadCartridge(char * ROM, Cartridge * cartridge)
{
   int bufSize = 512;
   int bufSizeRead = 0;
   //int i = 0;
   //int k = 0;
   char buf[bufSize];
   Error error;

   printf("Opening ROM ...\n");

   if ((cartridge->fd = open(ROM,O_RDONLY)) == 0)
   {
      error.code = 2;
      exiterror(&error);
   }

   while((bufSizeRead=read(cartridge->fd,buf,bufSize))>0)
   {
      /* Where to load to? */
      /* for(k=0;k<bufSizeRead;k++)
      {
         memory[512 + i] = buf[i];
         i++;
      } */
   }

   if (bufSizeRead == -1)
   {
      error.code = 3;
      exiterror(&error);
   }

   return 0;
}
