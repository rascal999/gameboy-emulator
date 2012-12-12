#ifndef _INCL_STDINT
   #define _INCL_STDINT
   #include <stdint.h>
#endif

typedef struct
{
   int fd;
} Cartridge;


typedef struct
{
   int instructionSize;
   char stringInstruction[16];
} Debug;

typedef struct
{
   int tmp;
} Display;

typedef struct
{
   int code;
   char str[512];
} Error;


typedef struct Z80 Z80;

typedef struct
{
   uint8_t addr[0xFFFF]; /* 16 bit address buffer. Mem size of 65 536 */

   /*
      0000-3FFF   16KB ROM Bank 00     (in cartridge, fixed at bank 00)
      4000-7FFF   16KB ROM Bank 01..NN (in cartridge, switchable bank number)
      8000-9FFF   8KB Video RAM (VRAM) (switchable bank 0-1 in CGB Mode)
      A000-BFFF   8KB External RAM     (in cartridge, switchable bank, if any)
      C000-CFFF   4KB Work RAM Bank 0 (WRAM)
      D000-DFFF   4KB Work RAM Bank 1 (WRAM)  (switchable bank 1-7 in CGB Mode)
      E000-FDFF   Same as C000-DDFF (ECHO)    (typically not used)
      FE00-FE9F   Sprite Attribute Table (OAM)
      FEA0-FEFF   Not Usable
      FF00-FF7F   I/O Ports
      FF80-FFFE   High RAM (HRAM)
      FFFF        Interrupt Enable Register
   */

   uint8_t bios_rom[0xFF];
   uint8_t bank0[0x3FFF];
   uint8_t bankNNN[0x3FFF];
   uint8_t vram[0x1FFF];
   uint8_t eram[0x1FFF];
   uint8_t wram0[0xFFF];
   uint8_t wram1[0xFFF];
   uint8_t wram_shadow[0x1DFF];
   uint8_t io_ports[0x7F];

   uint8_t div; /* Divider */
   uint8_t tima; /* Timer Counter */
   uint8_t tma; /* Timer Modulo */
   uint8_t tac; /* Control */

   int bios_rom_loaded;
   int tmp;
} Memory;

/* MMU */
/* Read byte */
uint8_t rb(Memory * mem, uint16_t addr);

/* Write byte */

/* Read word */
uint16_t rw(Memory * mem, uint16_t addr);

/* Write word */
/* END MMU */


typedef struct
{
   /*
      FF04 - DIV - Divider Register (R/W)
      FF05 - TIMA - Timer counter (R/W)
      FF06 - TMA - Timer Modulo (R/W)
      FF07 - TAC - Timer Control (R/W)
      INT 50 - Timer Interrupt
   */

   unsigned short div;
   unsigned short tima;
   unsigned short tma;
   unsigned short tac;
} Timers;

/* Timers */
/* Read byte */
unsigned short rb_timer(Timers * timer, unsigned short addr);

/* Write byte */

/* Read word */
unsigned short rw_timer(Timers * timer, unsigned short addr);

/* Write word */
/* END Timers */


typedef struct
{
   uint8_t A;
   uint8_t B;
   uint8_t C;
   uint8_t D;
   uint8_t E;
   uint8_t H;
   uint8_t L;
   uint8_t F; /* Flag */
   uint16_t PC;
   uint16_t SP;
} Registers;

struct Z80
{
   Registers * r;

   /* CPU ticks of last instruction */
   uint16_t ticks;
};

int mock_LoadCartridge(char * ROM, Cartridge * cartridge);
int mock_DebugAll(Z80 * z80, Memory * memory, Debug * debug);
int mock_DebugNextInstructionSize(uint8_t opcode);
int mock_InitDisplay(Display * display);
int mock_exiterror(Error * error);
uint8_t mock_rb(Memory * mem, uint16_t addr);
int mock_wb(Memory * mem, uint16_t addr, uint8_t value);
uint16_t mock_rw(Memory * mem, uint16_t addr);
int mock_ww(Memory * mem, Z80 * z80, uint16_t addr, uint16_t value);
int mock_InitMemory(Memory * memory);
int mock_LoadGBROM(Memory * memory, char * GBROM);
unsigned short mock_rb_timer(Timers * timer, unsigned short addr);
int mock_wb_timer(Timers * timer, unsigned short addr, unsigned char value);
unsigned short mock_rw_timer(Timers * timer, unsigned short addr);
int mock_ww_timer(Timers * timer, unsigned short addr, unsigned short value);
int mock_InitTimers(Timers * timer);
int mock_InitZ80(Z80 * z80, Registers * registers);
int mock_ResetZ80(Z80 * z80, Registers * registers);
int mock_Dispatch(Memory * memory, Z80 * z80);
int mock_Fetch(Memory * memory, Z80 * z80);
int mock_Execute(Memory * memory, Z80 * z80);
int mock_HertzToMilliseconds(int Hertz);
int mock_decrementHL(Z80 * z80);
int mock_OP_00h_NOP(Memory * memory, Z80 * z80);
int mock_OP_21h_LDHLnn(Memory * memory, Z80 * z80);
int mock_OP_31h_JRNCn(Memory * memory, Z80 * z80);
int mock_OP_32h_LDDHLA(Memory * memory, Z80 * z80);
int mock_OP_AFh_XORA(Memory * memory, Z80 * z80);
int mock_OP_FFh_RST38h(Memory * memory, Z80 * z80);
