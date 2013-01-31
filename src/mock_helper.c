/*
 * =====================================================================================
 *
 *       Filename:  mock_helper.c
 *
 *    Description:  Deprecated mock file, will be removed after function pull
 *
 *        Version:  1.0
 *        Created:  31/01/13 17:24:09
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aidan Marlin (aidan.marlin+github@gmail.com) , 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef _INCL_STDINT
   #define _INCL_STDINT
   #include <stdint.h>
#endif
#ifndef _INCL_STDLIB
   #define _INCL_STDLIB
   #include <stdlib.h>
#endif
#include "mock_helper.h"

//#define rb mock_rb
//#define wb mock_wb

Error err;

Memory memory;

int mock_LoadCartridge(char * ROM, Cartridge * cartridge)
{
}

int mock_DebugAll(Z80 * z80, Memory * memory, Debug * debug)
{
}

int mock_DebugNextInstructionSize(uint8_t opcode)
{
}

int mock_InitDisplay(Display * display)
{
}

/*int mock_exiterror(Error * err)
{
   exit(err->code);
}*/

/* MMU */
/* Read byte */
uint8_t mock_rb(Memory * mem, uint16_t addr)
{
   return mem->addr[addr];
}

int mock_wb(Memory * mem, uint16_t addr, uint8_t value)
{
   mem->addr[addr] = value;

   return 0;
}

/*uint8_t mock_rb1(Memory * mem, uint16_t addr)
{
   switch(addr & 0xF000)
   {
      case 0x0000:
         if (mem->bios_rom_loaded == 1)
         {
            if (addr < 0x100)
            {
               return mem->bios_rom[addr];
            }
         }
         return mem->bank0[addr];
      break;

      // bank0
      case 0x1000:
      case 0x2000:
      case 0x3000:
         return mem->bank0[addr];
      break;

      // bankNNN
      case 0x4000:
      case 0x5000:
      case 0x6000:
      case 0x7000:
         return mem->bank0[addr & 0x6FFF];
      break;

      // vram
      case 0x8000:
      case 0x9000:
         return mem->vram[addr & 0x1FFF];
      break;

      // eram
      case 0xA000:
      case 0xB000:
         return mem->eram[addr & 0x1FFF];
      break;

      // wram0
      case 0xC000:
         return mem->wram0[addr & 0x1FFF];
      break;

      // wram1 (switchable bank in CGB)
      case 0xD000:
         return mem->wram1[addr & 0x2FFF];
      break;

      // wram (shadow)
      case 0xE000:
         return mem->wram_shadow[addr & 0x1FFF];
      break;

      default:
      break;

      return 0;
   }

   // Working RAM shadow and sat
   switch(addr & 0xFF00)
   {
      case 0xF000: case 0xF100: case 0xF200: case 0xF300:
      case 0xF400: case 0xF500: case 0xF600: case 0xF700:
      case 0xF800: case 0xF900: case 0xFA00: case 0xFB00:
      case 0xFC00: case 0xFD00:
         return mem->wram_shadow[addr & 0x1FFF];
      break;

      case 0xFE00:
         if (addr < 0xFFA0)
         {
            return mem->sat[addr & 0xFF];
         } else {
            // Unaddressable memory region
            err.code = 30;
            exiterror(&err);
         }
      break;

      case 0xFF00:
         if (addr < 0xFF80)
         {
            return mem->io_ports[addr & 0xFF];
         } else {
            return mem->hram[addr & 0x7F];
         }
      break;
   }

   // Timer registers
   switch(addr & 0xFFFF)
   {
      case 0xFF04:
         return mem->div;
      break;

      case 0xFF05:
         return mem->tima;
      break;

      case 0xFF06:
         return mem->tma;
      break;

      case 0xFF07:
         return mem->tac;
      break;

      default:
      break;

      return 0;
   }

   return 0;
}*/

/* Write byte */
/*int mock_wb1(Memory * mem, uint16_t addr, uint8_t value)
{
   // Timer registers
   switch(addr & 0xFFFF)
   {
      case 0xFF04:
         mem->div = value;
      break;

      case 0xFF05:
         mem->tima = value;
      break;

      case 0xFF06:
         mem->tma = value;
      break;

      case 0xFF07:
         mem->tac = value;
      break;
   }

   // Working RAM shadow and sat
   switch(addr & 0xFF00)
   {
      case 0xF000: case 0xF100: case 0xF200: case 0xF300:
      case 0xF400: case 0xF500: case 0xF600: case 0xF700:
      case 0xF800: case 0xF900: case 0xFA00: case 0xFB00:
      case 0xFC00: case 0xFD00:
         mem->wram_shadow[addr & 0x1FFF] = value;
      break;

      case 0xFE00:
         if (addr < 0xFFA0)
         {
            mem->sat[addr & 0xFF] = value;
         } else {
            // Unaddressable memory region
            err.code = 30;
            exiterror(&err);
         }
      break;

      case 0xFF00:
         if (addr < 0xFF80)
         {
            mem->io_ports[addr & 0xFF] = value;
         } else {
            mem->hram[addr & 0x7F] = value;
         }
      break;
   }

   return 0;
}*/

/* Read word */
uint16_t mock_rw(Memory * mem, uint16_t addr)
{
}

/* Write word */
int mock_ww(Memory * mem, Z80 * z80, uint16_t addr, uint16_t value)
{
}
/* END MMU */

int mockInitMemory(Memory * memory)
{
   int i;
 
   for ( i = 0; i < 0x1000 ; i++ )
   {
      memory->addr[i] = 0x0;
   }
}

int mock_LoadGBROM(Memory * memory, char * GBROM)
{
}

/* Timers */
/* Read byte */
unsigned short mock_rb_timer(Timers * timer, unsigned short addr)
{
}

/* Write byte */
int mock_wb_timer(Timers * timer, unsigned short addr, unsigned char value)
{
}

/* Read word */
unsigned short mock_rw_timer(Timers * timer, unsigned short addr)
{
}

/* Write word */
int mock_ww_timer(Timers * timer, unsigned short addr, unsigned short value)
{
}
/* END Timers */

int mock_InitTimers(Timers * timer)
{
}

int mock_InitZ80(Z80 * z80, Registers * registers)
{
}

int mock_ResetZ80(Z80 * z80, Registers * registers)
{
}

int mock_Dispatch(Memory * memory, Z80 * z80)
{
}

int mock_Fetch(Memory * memory, Z80 * z80)
{
}

int mock_Execute(Memory * memory, Z80 * z80)
{
}

int mock_HertzToMilliseconds(int Hertz)
{
}

int mock_decrementHL(Z80 * z80)
{
}

/* Opcodes */
int mock_OP_00h_NOP(Memory * memory, Z80 * z80)
{
}

int mock_OP_21h_LDHLnn(Memory * memory, Z80 * z80)
{
}

int mock_OP_31h_JRNCn(Memory * memory, Z80 * z80)
{
}

int mock_OP_32h_LDDHLA(Memory * memory, Z80 * z80)
{
}

int mock_OP_AFh_XORA(Memory * memory, Z80 * z80)
{
}

int mock_OP_FFh_RST38h(Memory * memory, Z80 * z80)
{
}
