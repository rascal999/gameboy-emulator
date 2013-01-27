#include <stdlib.h>
#include <check.h>
#include <stdio.h>

#ifndef _INCL_DEBUG
   #define _INCL_DEBUG
   #include "../src/debug.h"
#endif
#ifndef _INCL_Z80
   #define _INCL_Z80
   #include "../src/z80.h"
#endif
#include "../src/error.h"
#ifdef UNITTEST
   #undef wb
   #undef rb
#endif

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

/*
   uint8_t bios_rom[0xFF];
   uint8_t bank0[0x3FFF];
   uint8_t bankNNN[0x3FFF];
   uint8_t vram[0x1FFF];
   uint8_t eram[0x1FFF];
   uint8_t wram0[0xFFF];
   uint8_t wram1[0xFFF];
   uint8_t wram_shadow[0x1DFF];
   uint8_t io_ports[0x7F];
*/
                                   //     B     Ticks
START_TEST (test_check_rb) //0x00 1     4
{
   Memory memory;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers);
   InitMemory(&memory);

   //memset(memory.bios_rom,0x1,0xFF);
   memset(memory.bios_rom,0x1,sizeof(memory.bios_rom));
   memset(memory.bank0,0x2,sizeof(memory.bank0));
   memset(memory.bankNNN,0x3,sizeof(memory.bankNNN));
   memset(memory.vram,0x4,sizeof(memory.vram));
   memset(memory.eram,0x5,sizeof(memory.eram));
   memset(memory.wram0,0x6,sizeof(memory.wram0));
   memset(memory.wram1,0x7,sizeof(memory.wram1));
   memset(memory.wram_shadow,0x8,sizeof(memory.wram_shadow));
   memset(memory.sat,0x9,sizeof(memory.sat));
   memset(memory.io_ports,0xA,sizeof(memory.io_ports));
   memset(memory.hram,0xB,sizeof(memory.hram));

   memory.bios_rom_loaded = 1;

   int result = 0;
   int tmp_z80_PC = z80.regPC;

   // Bios ROM
   result = rb(&memory,0x00);
   fail_unless(result == 0x1 && memory.bios_rom_loaded == 1,"MMU failure. Result of read from 0x00 was %x",result);
   result = rb(&memory,0xFF);
   fail_unless(result == 0x1 && memory.bios_rom_loaded == 1,"MMU failure. Result of read from 0xFF was %x",result);

   memory.bios_rom_loaded = 0;

   // bank0
   result = rb(&memory,0x00);
   fail_unless(result == 0x2,"MMU failure. Result of read from 0x00 was %x, should have been 0x2",result);
   result = rb(&memory,0xFF);
   fail_unless(result == 0x2,"MMU failure. Result of read from 0xFF was %x, should have been 0x2",result);
   result = rb(&memory,0x3FFF);
   fail_unless(result == 0x2,"MMU failure. Result of read from 0x3FFF was %x, should have been 0x2",result);

   // bankNNN 
   result = rb(&memory,0x4000);
   fail_unless(result == 0x3,"MMU failure. Result of read from 0x4000 was %x, should have been 0x3",result);
   result = rb(&memory,0x5000);
   fail_unless(result == 0x3,"MMU failure. Result of read from 0x5000 was %x, should have been 0x3",result);
   result = rb(&memory,0x6000);
   fail_unless(result == 0x3,"MMU failure. Result of read from 0x6000 was %x, should have been 0x3",result);
   result = rb(&memory,0x7000);
   fail_unless(result == 0x3,"MMU failure. Result of read from 0x7000 was %x, should have been 0x3",result);
   result = rb(&memory,0x7FFF);
   fail_unless(result == 0x3,"MMU failure. Result of read from 0x7FFF was %x, should have been 0x3",result);

   // vram (GPU)
   result = rb(&memory,0x8000);
   fail_unless(result == 0x4,"MMU failure. Result of read from 0x8000 was %x, should have been 0x4",result);
   result = rb(&memory,0x9000);
   fail_unless(result == 0x4,"MMU failure. Result of read from 0x9000 was %x, should have been 0x4",result);
   result = rb(&memory,0x9FFF);
   fail_unless(result == 0x4,"MMU failure. Result of read from 0x9FFF was %x, should have been 0x4",result);

   // eram (external)
   result = rb(&memory,0xA000);
   fail_unless(result == 0x5,"MMU failure. Result of read from 0xA000 was %x, should have been 0x5",result);
   result = rb(&memory,0xB000);
   fail_unless(result == 0x5,"MMU failure. Result of read from 0xB000 was %x, should have been 0x5",result);
   result = rb(&memory,0xBFFF);
   fail_unless(result == 0x5,"MMU failure. Result of read from 0xBFFF was %x, should have been 0x5",result);

   // wram (working)
   result = rb(&memory,0xC000);
   fail_unless(result == 0x6,"MMU failure. Result of read from 0xC000 was %x, should have been 0x6",result);
   result = rb(&memory,0xCFFF);
   fail_unless(result == 0x6,"MMU failure. Result of read from 0xCFFF was %x, should have been 0x6",result);
   result = rb(&memory,0xD000);
   fail_unless(result == 0x7,"MMU failure. Result of read from 0xD000 was %x, should have been 0x7",result);
   result = rb(&memory,0xDFFF);
   fail_unless(result == 0x7,"MMU failure. Result of read from 0xDFFF was %x, should have been 0x7",result);

   // wram (working, shadow)
   result = rb(&memory,0xE000);
   fail_unless(result == 0x8,"MMU failure. Result of read from 0xE000 was %x, should have been 0x8",result);
   result = rb(&memory,0xEFFF);
   fail_unless(result == 0x8,"MMU failure. Result of read from 0xEFFF was %x, should have been 0x8",result);
   result = rb(&memory,0xF000);
   fail_unless(result == 0x8,"MMU failure. Result of read from 0xF000 was %x, should have been 0x8",result);
   result = rb(&memory,0xF0FF);
   fail_unless(result == 0x8,"MMU failure. Result of read from 0xF0FF was %x, should have been 0x8",result);
   result = rb(&memory,0xF100);
   fail_unless(result == 0x8,"MMU failure. Result of read from 0xF100 was %x, should have been 0x8",result);
   result = rb(&memory,0xF1FF);
   fail_unless(result == 0x8,"MMU failure. Result of read from 0xF1FF was %x, should have been 0x8",result);
   result = rb(&memory,0xF200);
   fail_unless(result == 0x8,"MMU failure. Result of read from 0xF200 was %x, should have been 0x8",result);
   result = rb(&memory,0xF2FF);
   fail_unless(result == 0x8,"MMU failure. Result of read from 0xF2FF was %x, should have been 0x8",result);
   result = rb(&memory,0xF300);
   fail_unless(result == 0x8,"MMU failure. Result of read from 0xF300 was %x, should have been 0x8",result);
   result = rb(&memory,0xF3FF);
   fail_unless(result == 0x8,"MMU failure. Result of read from 0xF3FF was %x, should have been 0x8",result);
   result = rb(&memory,0xF400);
   fail_unless(result == 0x8,"MMU failure. Result of read from 0xF400 was %x, should have been 0x8",result);
   result = rb(&memory,0xF4FF);
   fail_unless(result == 0x8,"MMU failure. Result of read from 0xF4FF was %x, should have been 0x8",result);
   result = rb(&memory,0xF500);
   fail_unless(result == 0x8,"MMU failure. Result of read from 0xF500 was %x, should have been 0x8",result);
   result = rb(&memory,0xF5FF);
   fail_unless(result == 0x8,"MMU failure. Result of read from 0xF5FF was %x, should have been 0x8",result);
   result = rb(&memory,0xF600);
   fail_unless(result == 0x8,"MMU failure. Result of read from 0xF600 was %x, should have been 0x8",result);
   result = rb(&memory,0xF6FF);
   fail_unless(result == 0x8,"MMU failure. Result of read from 0xF6FF was %x, should have been 0x8",result);
   result = rb(&memory,0xF700);
   fail_unless(result == 0x8,"MMU failure. Result of read from 0xF700 was %x, should have been 0x8",result);
   result = rb(&memory,0xF7FF);
   fail_unless(result == 0x8,"MMU failure. Result of read from 0xF7FF was %x, should have been 0x8",result);
   result = rb(&memory,0xF800);
   fail_unless(result == 0x8,"MMU failure. Result of read from 0xF800 was %x, should have been 0x8",result);
   result = rb(&memory,0xF8FF);
   fail_unless(result == 0x8,"MMU failure. Result of read from 0xF8FF was %x, should have been 0x8",result);
   result = rb(&memory,0xF900);
   fail_unless(result == 0x8,"MMU failure. Result of read from 0xF900 was %x, should have been 0x8",result);
   result = rb(&memory,0xF9FF);
   fail_unless(result == 0x8,"MMU failure. Result of read from 0xF9FF was %x, should have been 0x8",result);
   result = rb(&memory,0xFA00);
   fail_unless(result == 0x8,"MMU failure. Result of read from 0xFA00 was %x, should have been 0x8",result);
   result = rb(&memory,0xFAFF);
   fail_unless(result == 0x8,"MMU failure. Result of read from 0xFAFF was %x, should have been 0x8",result);
   result = rb(&memory,0xFB00);
   fail_unless(result == 0x8,"MMU failure. Result of read from 0xFB00 was %x, should have been 0x8",result);
   result = rb(&memory,0xFBFF);
   fail_unless(result == 0x8,"MMU failure. Result of read from 0xFBFF was %x, should have been 0x8",result);
   result = rb(&memory,0xFC00);
   fail_unless(result == 0x8,"MMU failure. Result of read from 0xFC00 was %x, should have been 0x8",result);
   result = rb(&memory,0xFCFF);
   fail_unless(result == 0x8,"MMU failure. Result of read from 0xFCFF was %x, should have been 0x8",result);
   result = rb(&memory,0xFD00);
   fail_unless(result == 0x8,"MMU failure. Result of read from 0xFD00 was %x, should have been 0x8",result);
   result = rb(&memory,0xFDFF);
   fail_unless(result == 0x8,"MMU failure. Result of read from 0xFDFF was %x, should have been 0x8",result);

   // sat
   result = rb(&memory,0xFE00);
   fail_unless(result == 0x9,"MMU failure. Result of read from 0xFE00 was %x, should have been 0x9",result);
   result = rb(&memory,0xFE9F);
   fail_unless(result == 0x9,"MMU failure. Result of read from 0xFE9F was %x, should have been 0x9",result);

   // io_port
   result = rb(&memory,0xFF00);
   fail_unless(result == 0xA,"MMU failure. Result of read from 0xFE00 was %x, should have been 0x9",result);
   result = rb(&memory,0xFF7F);
   fail_unless(result == 0xA,"MMU failure. Result of read from 0xFE9F was %x, should have been 0x9",result);

   // hram
   result = rb(&memory,0xFF80);
   fail_unless(result == 0xB,"MMU failure. Result of read from 0xFE00 was %x, should have been 0xB",result);
   result = rb(&memory,0xFFFF);
   fail_unless(result == 0xB,"MMU failure. Result of read from 0xFE9F was %x, should have been 0xB",result);
}
END_TEST

Suite * add_suite(void)
{
   Suite * s = suite_create("Add");

   /* Core test case */
   TCase *tc_core = tcase_create("Core");
   tcase_add_test(tc_core,test_check_rb);
   suite_add_tcase(s,tc_core);

   return s;
}

int main(void)
{
   int number_failed;
   Suite *s = add_suite();
   SRunner *sr = srunner_create(s);
   srunner_run_all(sr, CK_NORMAL);
   number_failed = srunner_ntests_failed(sr);
   srunner_free(sr);
   return (number_failed == 0) ? 0 : 1;
}
