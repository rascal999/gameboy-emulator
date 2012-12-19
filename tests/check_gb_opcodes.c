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

int resetCPURegisters(Memory * memory, Z80 * z80, Registers * registers)
{
   z80->r = registers;
   z80->r->A = 0xA; // 0x0
   z80->r->B = 0xB; // 0x1
   z80->r->C = 0xC; // 0x2
   z80->r->D = 0xD; // 0x3
   z80->r->E = 0xE; // 0x4
   z80->r->F = 0x6; // 0x5
   z80->r->H = 0x8; // 0x6
   z80->r->L = 0x12; // 0x7

   z80->r->PC = 0x0;
}

int LDXY(Memory * memory, Z80 * z80, uint8_t regOrder, uint16_t tmp_z80_PC)
{
   uint8_t dest;
   char destName;

   switch((regOrder >> 4) & 0xF)
   {
      case 0x0: dest = z80->r->A; destName = 'A'; break;
      case 0x1: dest = z80->r->B; destName = 'B'; break;
      case 0x2: dest = z80->r->C; destName = 'C'; break;
      case 0x3: dest = z80->r->D; destName = 'D'; break;
      case 0x4: dest = z80->r->E; destName = 'E'; break;
      case 0x5: dest = z80->r->F; destName = 'F'; break;
      case 0x6: dest = z80->r->H; destName = 'H'; break;
      case 0x7: dest = z80->r->L; destName = 'L'; break;
   }

   switch(regOrder & 0xF)
   {
      case 0x0: fail_unless(dest == z80->r->A,"Register %c does not equal register A",destName); break;
      case 0x1: fail_unless(dest == z80->r->B,"Register %c does not equal register B",destName); break;
      case 0x2: fail_unless(dest == z80->r->C,"Register %c does not equal register C",destName); break;
      case 0x3: fail_unless(dest == z80->r->D,"Register %c does not equal register D",destName); break;
      case 0x4: fail_unless(dest == z80->r->E,"Register %c does not equal register E",destName); break;
      case 0x5: fail_unless(dest == z80->r->F,"Register %c does not equal register F",destName); break;
      case 0x6: fail_unless(dest == z80->r->H,"Register %c does not equal register H",destName); break;
      case 0x7: fail_unless(dest == z80->r->L,"Register %c does not equal register L",destName); break;
   }

   fail_unless(z80->r->PC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");
   fail_unless(z80->ticks == 4,"Ticks for opcode not registered or incorrect value");

   return 0;
}

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
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_04h_LDBB(memory,z80);

   LDXY(memory,z80,0x11,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_05h_LDDB) //0x05 1     4
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_05h_LDDB(memory,z80);

   LDXY(memory,z80,0x31,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_06h_LDHB) //0x06 1     4
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_06h_LDHB(memory,z80);

   LDXY(memory,z80,0x61,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_14h_LDBC) //0x14 1     4
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_14h_LDBC(memory,z80);

   LDXY(memory,z80,0x12,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_15h_LDDC) //0x15 1     4
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_15h_LDDC(memory,z80);

   LDXY(memory,z80,0x32,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_16h_LDHC) //0x16 1     4
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_16h_LDHC(memory,z80);

   LDXY(memory,z80,0x62,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
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
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_24h_LDBD(memory,z80);

   LDXY(memory,z80,0x13,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_25h_LDDD) //0x25 1     4
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_25h_LDDD(memory,z80);

   LDXY(memory,z80,0x33,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_26h_LDHD) //0x26 1     4
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_26h_LDHD(memory,z80);

   LDXY(memory,z80,0x63,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
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
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_34h_LDBE(memory,z80);

   LDXY(memory,z80,0x14,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_35h_LDDE) //0x35 1     4
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_35h_LDDE(memory,z80);

   LDXY(memory,z80,0x34,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_36h_LDHE) //0x36 1     4
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_36h_LDHE(memory,z80);

   LDXY(memory,z80,0x64,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_44h_LDBH) //0x44 1     4
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_44h_LDBH(memory,z80);

   LDXY(memory,z80,0x16,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_45h_LDDH) //0x45 1     4
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_45h_LDDH(memory,z80);

   LDXY(memory,z80,0x36,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_46h_LDHH) //0x46 1     4
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_46h_LDHH(memory,z80);

   LDXY(memory,z80,0x66,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_54h_LDBL) //0x54 1     4
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_54h_LDBL(memory,z80);

   LDXY(memory,z80,0x17,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_55h_LDDL) //0x55 1     4
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_55h_LDDL(memory,z80);

   LDXY(memory,z80,0x37,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_56h_LDHL) //0x56 1     4
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_56h_LDHL(memory,z80);

   LDXY(memory,z80,0x67,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_84h_LDCB(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_84h_LDCB) //0x84 1     4
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_84h_LDCB(memory,z80);

   LDXY(memory,z80,0x21,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_85h_LDEB(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_85h_LDEB) //0x85 1     4
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_85h_LDEB(memory,z80);

   LDXY(memory,z80,0x41,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_86h_LDLB(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_86h_LDLB) //0x86 1     4
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_86h_LDLB(memory,z80);

   LDXY(memory,z80,0x71,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_87h_LDAB(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_87h_LDAB) //0x87 1     4
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_87h_LDAB(memory,z80);

   LDXY(memory,z80,0x01,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_94h_LDCC(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_94h_LDCC) //0x94 1     4
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_94h_LDCC(memory,z80);

   LDXY(memory,z80,0x22,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_95h_LDEC(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_95h_LDEC) //0x95 1     4
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_95h_LDEC(memory,z80);

   LDXY(memory,z80,0x42,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_96h_LDLC(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_96h_LDLC) //0x96 1     4
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_96h_LDLC(memory,z80);

   LDXY(memory,z80,0x72,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_97h_LDAC(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_97h_LDAC) //0x97 1     4
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_97h_LDAC(memory,z80);

   LDXY(memory,z80,0x02,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_A4h_LDCD(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_A4h_LDCD) //0xA4 1     4
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_A4h_LDCD(memory,z80);

   LDXY(memory,z80,0x23,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_A5h_LDED(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_A5h_LDED) //0xA5 1     4
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_A5h_LDED(memory,z80);

   LDXY(memory,z80,0x43,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_A6h_LDLD(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_A6h_LDLD) //0xA6 1     4
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_A6h_LDLD(memory,z80);

   LDXY(memory,z80,0x73,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_A7h_LDAD(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_A7h_LDAD) //0xA7 1     4
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_A7h_LDAD(memory,z80);

   LDXY(memory,z80,0x03,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_B4h_LDCE(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_B4h_LDCE) //0xB4 1     4
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_B4h_LDCE(memory,z80);

   LDXY(memory,z80,0x24,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_B5h_LDEE(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_B5h_LDEE) //0xB5 1     4
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_B5h_LDEE(memory,z80);

   LDXY(memory,z80,0x44,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_B6h_LDLE(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_B6h_LDLE) //0xB6 1     4
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_B6h_LDLE(memory,z80);

   LDXY(memory,z80,0x74,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_B7h_LDAE(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_B7h_LDAE) //0xB7 1     4
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_B7h_LDAE(memory,z80);

   LDXY(memory,z80,0x04,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_C4h_LDCH(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_C4h_LDCH) //0xC4 1     4
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_C4h_LDCH(memory,z80);

   LDXY(memory,z80,0x26,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_C5h_LDEH(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_C5h_LDEH) //0xC5 1     4
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_C5h_LDEH(memory,z80);

   LDXY(memory,z80,0x46,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_C6h_LDLH(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_C6h_LDLH) //0xC6 1     4
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_C6h_LDLH(memory,z80);

   LDXY(memory,z80,0x76,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_C7h_LDAH(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_C7h_LDAH) //0xC7 1     4
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_C7h_LDAH(memory,z80);

   LDXY(memory,z80,0x06,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_D4h_LDCL(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_D4h_LDCL) //0xD4 1     4
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_D4h_LDCL(memory,z80);

   LDXY(memory,z80,0x27,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_D5h_LDEL(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_D5h_LDEL) //0xD5 1     4
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_D5h_LDEL(memory,z80);

   LDXY(memory,z80,0x47,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_D6h_LDLL(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_D6h_LDLL) //0xD6 1     4
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_D6h_LDLL(memory,z80);

   LDXY(memory,z80,0x77,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_D7h_LDAL(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_D7h_LDAL) //0xD7 1     4
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_D7h_LDAL(memory,z80);

   LDXY(memory,z80,0x07,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_F4h_LDCA(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_F4h_LDCA) //0xF4 1     4
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_F4h_LDCA(memory,z80);

   LDXY(memory,z80,0x20,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_F5h_LDEA(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_F5h_LDEA) //0xF5 1     4
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_F5h_LDEA(memory,z80);

   LDXY(memory,z80,0x40,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_F6h_LDLA(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_F6h_LDLA) //0xF6 1     4
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_F6h_LDLA(memory,z80);

   LDXY(memory,z80,0x70,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_F7h_LDAA(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_F7h_LDAA) //0xF7 1     4
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_F7h_LDAA(memory,z80);

   LDXY(memory,z80,0x00,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
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
   tcase_add_test(tc_core,test_check_OP_05h_LDDB);
   tcase_add_test(tc_core,test_check_OP_06h_LDHB);
   tcase_add_test(tc_core,test_check_OP_14h_LDBC);
   tcase_add_test(tc_core,test_check_OP_15h_LDDC);
   tcase_add_test(tc_core,test_check_OP_16h_LDHC);
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
   tcase_add_test(tc_core,test_check_OP_35h_LDDE);
   tcase_add_test(tc_core,test_check_OP_36h_LDHE);
   tcase_add_test(tc_core,test_check_OP_44h_LDBH);
   tcase_add_test(tc_core,test_check_OP_45h_LDDH);
   tcase_add_test(tc_core,test_check_OP_46h_LDHH);
   tcase_add_test(tc_core,test_check_OP_54h_LDBL);
   tcase_add_test(tc_core,test_check_OP_55h_LDDL);
   tcase_add_test(tc_core,test_check_OP_56h_LDHL);
   tcase_add_test(tc_core,test_check_OP_84h_LDCB);
   tcase_add_test(tc_core,test_check_OP_85h_LDEB);
   tcase_add_test(tc_core,test_check_OP_86h_LDLB);
   tcase_add_test(tc_core,test_check_OP_87h_LDAB);
   tcase_add_test(tc_core,test_check_OP_94h_LDCC);
   tcase_add_test(tc_core,test_check_OP_95h_LDEC);
   tcase_add_test(tc_core,test_check_OP_96h_LDLC);
   tcase_add_test(tc_core,test_check_OP_97h_LDAC);
   tcase_add_test(tc_core,test_check_OP_A4h_LDCD);
   tcase_add_test(tc_core,test_check_OP_A5h_LDED);
   tcase_add_test(tc_core,test_check_OP_A6h_LDLD);
   tcase_add_test(tc_core,test_check_OP_A7h_LDAD);
   tcase_add_test(tc_core,test_check_OP_B4h_LDCE);
   tcase_add_test(tc_core,test_check_OP_B5h_LDEE);
   tcase_add_test(tc_core,test_check_OP_B6h_LDLE);
   tcase_add_test(tc_core,test_check_OP_B7h_LDAE);
   tcase_add_test(tc_core,test_check_OP_C4h_LDCH);
   tcase_add_test(tc_core,test_check_OP_C5h_LDEH);
   tcase_add_test(tc_core,test_check_OP_C6h_LDLH);
   tcase_add_test(tc_core,test_check_OP_C7h_LDAH);
   tcase_add_test(tc_core,test_check_OP_D4h_LDCL);
   tcase_add_test(tc_core,test_check_OP_D5h_LDEL);
   tcase_add_test(tc_core,test_check_OP_D6h_LDLL);
   tcase_add_test(tc_core,test_check_OP_D7h_LDAL);
   tcase_add_test(tc_core,test_check_OP_F4h_LDCA);
   tcase_add_test(tc_core,test_check_OP_F5h_LDEA);
   tcase_add_test(tc_core,test_check_OP_F6h_LDLA);
   tcase_add_test(tc_core,test_check_OP_F7h_LDAA);
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
