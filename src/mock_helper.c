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

int mock_exiterror(Error * err)
{
   exit(err->code);
}

/* MMU */
/* Read byte */
uint8_t mock_rb(Memory * mem, uint16_t addr)
{
   //printf("mock rb addr = %x\n",addr);
   return mem->bios_rom[addr];
}

/* Write byte */
int mock_wb(Memory * mem, uint16_t addr, uint8_t value)
{
   //printf("mock wb addr = %x value = %x\n",addr,value);
   mem->bios_rom[addr] = value;

   return 0;
}

/* Read word */
uint16_t mock_rw(Memory * mem, uint16_t addr)
{
}

/* Write word */
int mock_ww(Memory * mem, Z80 * z80, uint16_t addr, uint16_t value)
{
}
/* END MMU */

int mock_InitMemory(Memory * memory)
{
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
