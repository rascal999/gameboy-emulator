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
#ifdef UNITTEST_OPCODES
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
   uint8_t tmp_z80_PC = z80.r->PC;

   result = OP_00h_NOP(&memory,&z80);

   fail_unless(z80.r->PC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");

   fail_unless(result == 0,"Result was not 0");

   fail_unless(z80.ticks == 4,"Ticks for opcode not registered or incorrect value");
}
END_TEST

START_TEST (test_check_OP_04h_LDBB) //0x04 1     4
{
   Memory memory;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers);
   InitMemory(&memory);

   int result = 0;
   uint8_t tmp_z80_PC = z80.r->PC;

   z80.r->B = 0xB;
   z80.r->B = 0xB;

   result = OP_04h_LDBB(&memory,&z80);

   fail_unless(z80.r->PC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");

   fail_unless(result == 0,"Result was not 0");
   fail_unless(z80.r->B == z80.r->B,"Register B does not equal register B");
   fail_unless(z80.ticks == 4,"Ticks for opcode not registered or incorrect value");
}
END_TEST

START_TEST (test_check_OP_14h_LDBC) //0x14 1     4
{
   Memory memory;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers);
   InitMemory(&memory);

   int result = 0;
   uint8_t tmp_z80_PC = z80.r->PC;

   z80.r->B = 0xB;
   z80.r->C = 0xC;

   result = OP_14h_LDBC(&memory,&z80);

   fail_unless(z80.r->PC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");

   fail_unless(result == 0,"Result was not 0");
   fail_unless(z80.r->B == z80.r->C,"Register B does not equal register C");
   fail_unless(z80.ticks == 4,"Ticks for opcode not registered or incorrect value");
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

   fail_unless(z80.ticks == 12,"Ticks for opcode not registered or incorrect value");
}
END_TEST

START_TEST (test_check_OP_22h_LDIHLA) //0x22 1     8
{
   Memory memory;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers);
   InitMemory(&memory);

   //LoadGBROM(&memory,"/home/user/git/gameboy-emulator/roms/DMG_ROM.bin");

   int result = 0;
   uint8_t tmp_z80_PC = z80.r->PC;
   uint8_t tmp_z80_HL = (z80.r->H << 8) + z80.r->L;

   z80.r->H = 0;
   z80.r->L = 0x11;
   z80.r->A = 0xB;

   printf("HL = %x\n",(z80.r->H << 8) + z80.r->L);

   result = OP_22h_LDIHLA(&memory,&z80);

   fail_unless(z80.r->PC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");

   fail_unless(result == 0,"Result was not 0");
   printf("HL-1 addr content = %x\nA = %x\n",rb(&memory,(z80.r->H << 8) + z80.r->L - 1),z80.r->A);
   fail_unless(rb(&memory,(z80.r->H << 8) + z80.r->L - 1) == z80.r->A,"Content at address pointed by HL (-1 at this point) does not match A register.");
   fail_unless(z80.ticks == 8,"Ticks for opcode not registered or incorrect value");
}
END_TEST

START_TEST (test_check_OP_23h_LDDHLA) //0x23 1     8
{
   Memory memory;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers);
   InitMemory(&memory);

   //LoadGBROM(&memory,"/home/user/git/gameboy-emulator/roms/DMG_ROM.bin");

   int result = 0;
   uint8_t tmp_z80_PC = z80.r->PC;
   uint8_t tmp_z80_HL = (z80.r->H << 8) + z80.r->L;

   z80.r->H = 0;
   z80.r->L = 0x11;
   z80.r->A = 0xB;

   printf("HL = %x\n",(z80.r->H << 8) + z80.r->L);

   result = OP_23h_LDDHLA(&memory,&z80);

   fail_unless(z80.r->PC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");

   fail_unless(result == 0,"Result was not 0");
   printf("HL+1 addr content = %x\nA = %x\n",rb(&memory,(z80.r->H << 8) + z80.r->L + 1),z80.r->A);
   fail_unless(rb(&memory,(z80.r->H << 8) + z80.r->L + 1) == z80.r->A,"Content at address pointed by HL (+1 at this point) does not match A register.");
   fail_unless(z80.ticks == 8,"Ticks for opcode not registered or incorrect value");
}
END_TEST

START_TEST (test_check_OP_24h_LDBD) //0x24 1     4
{
   Memory memory;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers);
   InitMemory(&memory);

   int result = 0;
   uint8_t tmp_z80_PC = z80.r->PC;
   uint8_t tmp_z80_HL = (z80.r->H << 8) + z80.r->L;

   z80.r->B = 0xB;
   z80.r->D = 0xD;

   result = OP_24h_LDBD(&memory,&z80);

   fail_unless(z80.r->PC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");

   fail_unless(result == 0,"Result was not 0");
   fail_unless(z80.r->B == z80.r->D,"Register B does not equal register D");
   fail_unless(z80.ticks == 4,"Ticks for opcode not registered or incorrect value");
}
END_TEST

START_TEST (test_check_OP_25h_LDDD) //0x25 1     4
{
   Memory memory;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers);
   InitMemory(&memory);

   int result = 0;
   uint8_t tmp_z80_PC = z80.r->PC;
   uint8_t tmp_z80_HL = (z80.r->H << 8) + z80.r->L;

   z80.r->D = 0xD;

   result = OP_25h_LDDD(&memory,&z80);

   fail_unless(z80.r->PC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");

   fail_unless(result == 0,"Result was not 0");
   fail_unless(z80.r->D == z80.r->D,"Register D does not equal register D");
   fail_unless(z80.ticks == 4,"Ticks for opcode not registered or incorrect value");
}
END_TEST

START_TEST (test_check_OP_26h_LDHD) //0x26 1     4
{
   Memory memory;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers);
   InitMemory(&memory);

   int result = 0;
   uint8_t tmp_z80_PC = z80.r->PC;
   uint8_t tmp_z80_HL = (z80.r->H << 8) + z80.r->L;

   z80.r->D = 0xD;
   z80.r->H = 0x8;

   result = OP_26h_LDHD(&memory,&z80);

   fail_unless(z80.r->PC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");

   fail_unless(result == 0,"Result was not 0");
   fail_unless(z80.r->H == z80.r->D,"Register H does not equal register D");
   fail_unless(z80.ticks == 4,"Ticks for opcode not registered or incorrect value");
}
END_TEST

START_TEST (test_check_OP_27h_LDHLD) //0x27 1     8
{
   Memory memory;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers);
   InitMemory(&memory);

   int result = 0;
   uint8_t tmp_z80_PC = z80.r->PC;
   uint8_t tmp_z80_HL = (z80.r->H << 8) + z80.r->L;

   z80.r->D = 0xD;
   z80.r->H = 0x8;
   z80.r->L = 0x8;

   result = OP_27h_LDHLD(&memory,&z80);

   fail_unless(z80.r->PC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");

   fail_unless(result == 0,"Result was not 0");
printf("HL addr = %x value = %x\n",(z80.r->H << 8) + z80.r->L,rb(&memory,(z80.r->H << 8) + z80.r->L));
   fail_unless(rb(&memory,(z80.r->H << 8) + z80.r->L) == z80.r->D,"Content of address held in HL register does not equal register D");
   fail_unless(z80.ticks == 8,"Ticks for opcode not registered or incorrect value");
}
END_TEST

START_TEST (test_check_OP_28h_ADDAD) //0x28 1     4
{
   Memory memory;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers);
   InitMemory(&memory);

   int result = 0;
   uint8_t tmp_z80_PC = z80.r->PC;

   z80.r->A = 0x8F; // 143d
   z80.r->D = 0x1F; // 31d
   z80.r->F = 0x0;

   uint8_t tmp_z80_A = z80.r->A;

   /*
      In above F register should be:

      z = 0
      n = 0
      h = 1
      c = 0

      F == 0x2
   */

   result = OP_28h_ADDAD(&memory,&z80);
printf("Register F == %x\n",z80.r->F);
printf("Register A == %x\n",z80.r->A);
printf("Register D == %x\n",z80.r->D);
printf("Register tmp_z80_A == %x\n",tmp_z80_A);
   fail_unless(z80.r->PC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");

   fail_unless(result == 0,"Result was not 0");
   fail_unless(((z80.r->F & 0x80) >> 7) == 0,"Zero flag not equal to 0");
   fail_unless(((z80.r->F & 0x40) >> 6) == 0,"Subtract flag not equal to 0");
   fail_unless(((z80.r->F & 0x20) >> 5) == 1,"Half flag not equal to 1");
   fail_unless(((z80.r->F & 0x10) >> 4) == 0,"Carry flag not equal to 0");
   fail_unless(z80.r->A == tmp_z80_A + z80.r->D,"A register does not equal tmp_z80_A + register D");
   fail_unless(z80.ticks == 4,"Ticks for opcode not registered or incorrect value");
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
   uint8_t tmp_z80_PC = z80.r->PC;

   result = OP_31h_JRNCn(&memory,&z80);

   fail_unless((z80.r->PC - 2) == tmp_z80_PC,"Program Counter should be incremented by opcode function code");

   fail_unless(result == 0,"Result was not 0");
   fail_unless(z80.r->SP == (rb(&memory,(tmp_z80_PC + 1)) << 8) + rb(&memory,(tmp_z80_PC)),"SP register incorrect value");

   fail_unless(z80.ticks == 12,"Ticks for opcode not registered or incorrect value");
}
END_TEST

START_TEST (test_check_OP_34h_LDBE) //0x34 1     4
{
   Memory memory;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers);
   InitMemory(&memory);

   int result = 0;
   uint8_t tmp_z80_PC = z80.r->PC;
   uint8_t tmp_z80_HL = (z80.r->H << 8) + z80.r->L;

   z80.r->B = 0xB;
   z80.r->E = 0xE;

   result = OP_34h_LDBE(&memory,&z80);

   fail_unless(z80.r->PC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");

   fail_unless(result == 0,"Result was not 0");
   fail_unless(z80.r->B == z80.r->E,"Register B does not equal register E");
   fail_unless(z80.ticks == 4,"Ticks for opcode not registered or incorrect value");
}
END_TEST

START_TEST (test_check_OP_44h_LDBH) //0x44 1     4
{
   Memory memory;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers);
   InitMemory(&memory);

   int result = 0;
   uint8_t tmp_z80_PC = z80.r->PC;

   z80.r->B = 0xB;
   z80.r->H = 0x8;

   result = OP_44h_LDBH(&memory,&z80);

   fail_unless(z80.r->PC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");

   fail_unless(result == 0,"Result was not 0");
   fail_unless(z80.r->B == z80.r->H,"Register B does not equal register H");
   fail_unless(z80.ticks == 4,"Ticks for opcode not registered or incorrect value");
}
END_TEST

START_TEST (test_check_OP_54h_LDBL) //0x54 1     4
{
   Memory memory;
   Registers registers;
   Z80 z80;

   InitZ80(&z80,&registers);
   InitMemory(&memory);

   int result = 0;
   uint8_t tmp_z80_PC = z80.r->PC;

   z80.r->B = 0xB;
   z80.r->L = 0x12;

   result = OP_54h_LDBL(&memory,&z80);

   fail_unless(z80.r->PC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");

   fail_unless(result == 0,"Result was not 0");
   fail_unless(z80.r->B == z80.r->L,"Register B does not equal register L");
   fail_unless(z80.ticks == 4,"Ticks for opcode not registered or incorrect value");
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
   uint8_t tmp_z80_PC = z80.r->PC;

   result = OP_AFh_XORA(&memory,&z80);

   fail_unless(z80.r->PC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");

   fail_unless(result == 0,"Result was not 0");

   fail_unless(z80.ticks == 4,"Ticks for opcode not registered or incorrect value");
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
   tcase_add_test(tc_core,test_check_OP_04h_LDBB);
   tcase_add_test(tc_core,test_check_OP_14h_LDBC);
   tcase_add_test(tc_core,test_check_OP_AFh_XORA);
   tcase_add_test(tc_core,test_check_OP_21h_LDHLnn);
   tcase_add_test(tc_core,test_check_OP_22h_LDIHLA);
   tcase_add_test(tc_core,test_check_OP_23h_LDDHLA);
   tcase_add_test(tc_core,test_check_OP_24h_LDBD);
   tcase_add_test(tc_core,test_check_OP_25h_LDDD);
   tcase_add_test(tc_core,test_check_OP_26h_LDHD);
   tcase_add_test(tc_core,test_check_OP_27h_LDHLD);
   tcase_add_test(tc_core,test_check_OP_28h_ADDAD);
   tcase_add_test(tc_core,test_check_OP_31h_JRNCn);
   tcase_add_test(tc_core,test_check_OP_34h_LDBE);
   tcase_add_test(tc_core,test_check_OP_44h_LDBH);
   tcase_add_test(tc_core,test_check_OP_54h_LDBL);
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
