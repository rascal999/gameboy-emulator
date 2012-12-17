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
   memset(memory.io_ports,0x9,sizeof(memory.io_ports));

   memory.bios_rom_loaded = 1;

   int result = 0;
   int tmp_z80_PC = z80.r->PC;

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
   fail_unless(result == 0x3,"MMU failure. Result of read from 0x4000 was %x",result);
   result = rb(&memory,0x5000);
   fail_unless(result == 0x3,"MMU failure. Result of read from 0x5000 was %x",result);
   result = rb(&memory,0x6000);
   fail_unless(result == 0x3,"MMU failure. Result of read from 0x6000 was %x",result);
   result = rb(&memory,0x7000);
   fail_unless(result == 0x3,"MMU failure. Result of read from 0x7000 was %x",result);
   result = rb(&memory,0x7FFF);
   fail_unless(result == 0x3,"MMU failure. Result of read from 0x7FFF was %x",result);
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
