#ifndef _INCL_Z80
   #define _INCL_Z80
   #include "z80.h"
#endif

typedef struct
{
   int fd;
} Cartridge;

int LoadCartridge(char * ROM, Cartridge * cartridge);
