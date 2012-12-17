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
   #define wb mock_wb
   #define rb mock_rb
#endif

                                   //     B     Ticks
START_TEST (test_check_OP_00h_NOP) //0x00 1     4
{
   Memory memory;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers);
   InitMemory(&memory);

   int result = 0;
   int tmp_z80_PC = z80.r->PC;

   result = OP_00h_NOP(&memory,&z80);

   fail_unless(z80.r->PC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");

   fail_unless(result == 0,"Result was not 0");

   fail_unless(z80.ticks == 4,"Ticks for opcode not registered or correct value");
}
END_TEST

START_TEST (test_check_OP_21h_LDHLnn) //0x21 1     4
{
   Memory memory;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers);
   InitMemory(&memory);

   LoadGBROM(&memory,"/home/user/git/gameboy-emulator/roms/DMG_ROM.bin");

   int result = 0;
   uint16_t tmp_z80_PC = z80.r->PC;

   result = OP_21h_LDHLnn(&memory,&z80);

   fail_unless((z80.r->PC - 2) == tmp_z80_PC,"Program Counter should be incremented by opcode function code");

   fail_unless(result == 0,"Result was not 0");
   //tmp_z80_PC is 0, and this byte is treated as an address
   fail_unless(z80.r->H == rb(&memory,(tmp_z80_PC + 1)),"H register incorrect value");
   fail_unless(z80.r->L == rb(&memory,(tmp_z80_PC)),"L register incorrect value");

   fail_unless(z80.ticks == 12,"Ticks for opcode not registered or correct value");
}
END_TEST

START_TEST (test_check_OP_31h_JRNCn) //0x31 1     4
{
   Memory memory;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers);
   InitMemory(&memory);

   int result = 0;
   int tmp_z80_PC = z80.r->PC;

   result = OP_31h_JRNCn(&memory,&z80);

   fail_unless((z80.r->PC - 2) == tmp_z80_PC,"Program Counter should be incremented by opcode function code");

   fail_unless(result == 0,"Result was not 0");
   fail_unless(z80.r->SP == (rb(&memory,(tmp_z80_PC + 1)) << 8) + rb(&memory,(tmp_z80_PC)),"SP register incorrect value");

   fail_unless(z80.ticks == 12,"Ticks for opcode not registered or correct value");
}
END_TEST

START_TEST (test_check_OP_32h_LDDHLA) //0x32 1     8
{
   Memory memory;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers);
   InitMemory(&memory);

   //LoadGBROM(&memory,"/home/user/git/gameboy-emulator/roms/DMG_ROM.bin");

   int result = 0;
   int tmp_z80_PC = z80.r->PC;
   int tmp_z80_HL = (z80.r->H << 8) + z80.r->L;

   z80.r->H = 0;
   z80.r->L = 0x11;
   z80.r->A = 0xB;

   printf("HL = %x\n",(z80.r->H << 8) + z80.r->L);

   result = OP_32h_LDDHLA(&memory,&z80);

   fail_unless(z80.r->PC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");

   fail_unless(result == 0,"Result was not 0");
   printf("HL+1 addr content = %x\nA = %x\n",rb(&memory,(z80.r->H << 8) + z80.r->L + 1),z80.r->A);
   fail_unless(rb(&memory,(z80.r->H << 8) + z80.r->L + 1) == z80.r->A,"Content at address pointed by HL (+1 at this point) does not match A register.");
   fail_unless(z80.ticks == 8,"Ticks for opcode not registered or correct value");
}
END_TEST

START_TEST (test_check_OP_AFh_XORA) //0xAF 1    4
{
   Memory memory;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers);
   InitMemory(&memory);

   int result = 0;
   int tmp_z80_PC = z80.r->PC;

   result = OP_AFh_XORA(&memory,&z80);

   fail_unless(z80.r->PC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");

   fail_unless(result == 0,"Result was not 0");

   fail_unless(z80.ticks == 4,"Ticks for opcode not registered or correct value");
   fail_unless(z80.r->A == 0,"A register should be 0");
   fail_unless(z80.r->F == 0,"All flags should be reset");
}
END_TEST

Suite * add_suite(void)
{
   Suite * s = suite_create("Add");

   /* Core test case */
   TCase *tc_core = tcase_create("Core");
   tcase_add_test(tc_core,test_check_OP_00h_NOP);
   tcase_add_test(tc_core,test_check_OP_AFh_XORA);
   tcase_add_test(tc_core,test_check_OP_21h_LDHLnn);
   tcase_add_test(tc_core,test_check_OP_31h_JRNCn);
   tcase_add_test(tc_core,test_check_OP_32h_LDDHLA);
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
