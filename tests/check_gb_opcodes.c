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
   z80->r->F = 0xF; // 0x5
   z80->r->H = 0x8; // 0x6
   z80->r->L = 0x12; // 0x7

/*
   z80->r->A = 0xFF; // 0x0
   z80->r->B = 0xFF; // 0x1
   z80->r->C = 0xFF; // 0x2
   z80->r->D = 0xFF; // 0x3
   z80->r->E = 0xFF; // 0x4
   z80->r->F = 0xFF; // 0x5
   z80->r->H = 0xFF; // 0x6
   z80->r->L = 0xFF; // 0x7
*/

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

int ADDXY(Memory * memory, Z80 * z80, Z80 * old_z80, uint8_t regOrder, uint16_t tmp_z80_PC)
{
   uint8_t dest, oldDest, oldSrc;
   char destName;

   switch((regOrder >> 4) & 0xF)
   {
      case 0x0: dest = z80->r->A; oldDest = old_z80->r->A; destName = 'A'; break;
      case 0x1: dest = z80->r->B; oldDest = old_z80->r->B; destName = 'B'; break;
      case 0x2: dest = z80->r->C; oldDest = old_z80->r->C ;destName = 'C'; break;
      case 0x3: dest = z80->r->D; oldDest = old_z80->r->D; destName = 'D'; break;
      case 0x4: dest = z80->r->E; oldDest = old_z80->r->E; destName = 'E'; break;
      case 0x5: dest = z80->r->F; oldDest = old_z80->r->F; destName = 'F'; break;
      case 0x6: dest = z80->r->H; oldDest = old_z80->r->H; destName = 'H'; break;
      case 0x7: dest = z80->r->L; oldDest = old_z80->r->L; destName = 'L'; break;
   }

   switch(regOrder & 0xF)
   {
      case 0x0: oldSrc = old_z80->r->A; fail_unless(dest == ((oldDest + oldSrc) & 0xFF),"Register %c does not equal register %c + register A",destName,destName); break;
      case 0x1: oldSrc = old_z80->r->B; fail_unless(dest == ((oldDest + oldSrc) & 0xFF),"Register %c does not equal register %c + register B",destName,destName); break;
      case 0x2: oldSrc = old_z80->r->C; fail_unless(dest == ((oldDest + oldSrc) & 0xFF),"Register %c does not equal register %c + register C",destName,destName); break;
      case 0x3: oldSrc = old_z80->r->D; fail_unless(dest == ((oldDest + oldSrc) & 0xFF),"Register %c does not equal register %c + register D",destName,destName); break;
      case 0x4: oldSrc = old_z80->r->E; fail_unless(dest == ((oldDest + oldSrc) & 0xFF),"Register %c does not equal register %c + register E",destName,destName); break;
      case 0x5: oldSrc = old_z80->r->F; fail_unless(dest == ((oldDest + oldSrc) & 0xFF),"Register %c does not equal register %c + register F",destName,destName); break;
      case 0x6: oldSrc = old_z80->r->H; fail_unless(dest == ((oldDest + oldSrc) & 0xFF),"Register %c does not equal register %c + register H",destName,destName); break;
      case 0x7: oldSrc = old_z80->r->L; fail_unless(dest == ((oldDest + oldSrc) & 0xFF),"Register %c does not equal register %c + register L",destName,destName); break;
   }

   dest = (oldDest + oldSrc) & 0xFF;

   // Flags
   if ((dest < oldDest) | (dest < oldSrc))
   {
      // Carry
      fail_unless((z80->r->F & 0x10) == 0x10,"Carry flag should be set %x",z80->r->F & 0x10);
   }

   if ((dest & 0xFF) == 0x00)
   {
      // Zero flag
      fail_unless(z80->r->F & 0x80,"Zero flag should be set");
   }

   if (((oldSrc & 0xF) + (oldDest & 0xF)) & 0x10)
   {
      // Half-carry
      fail_unless(z80->r->F == z80->r->F | 0x20,"Half-carry flag should be set");
   }

   fail_unless(z80->r->PC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");
   fail_unless(z80->ticks == 4,"Ticks for opcode not registered or incorrect value");

   return 0;
}

int ADCXY(Memory * memory, Z80 * z80, Z80 * old_z80, uint8_t regOrder, uint16_t tmp_z80_PC)
{
   uint8_t dest, oldDest, oldSrc;
   char destName;

   switch((regOrder >> 4) & 0xF)
   {
      case 0x0: dest = z80->r->A; oldDest = old_z80->r->A; destName = 'A'; break;
      case 0x1: dest = z80->r->B; oldDest = old_z80->r->B; destName = 'B'; break;
      case 0x2: dest = z80->r->C; oldDest = old_z80->r->C ;destName = 'C'; break;
      case 0x3: dest = z80->r->D; oldDest = old_z80->r->D; destName = 'D'; break;
      case 0x4: dest = z80->r->E; oldDest = old_z80->r->E; destName = 'E'; break;
      case 0x5: dest = z80->r->F; oldDest = old_z80->r->F; destName = 'F'; break;
      case 0x6: dest = z80->r->H; oldDest = old_z80->r->H; destName = 'H'; break;
      case 0x7: dest = z80->r->L; oldDest = old_z80->r->L; destName = 'L'; break;
   }

   switch(regOrder & 0xF)
   {
      case 0x0: oldSrc = old_z80->r->A; fail_unless(dest == ((oldDest + oldSrc + ((z80->r->F & 0x10) >> 4)) & 0xFF),"Register %c does not equal register %c + register A + carry flag",destName,destName); break;
      case 0x1: oldSrc = old_z80->r->B; fail_unless(dest == ((oldDest + oldSrc + ((z80->r->F & 0x10) >> 4)) & 0xFF),"Register %c does not equal register %c + register B + carry flag",destName,destName); break;
      case 0x2: oldSrc = old_z80->r->C; fail_unless(dest == ((oldDest + oldSrc + ((z80->r->F & 0x10) >> 4)) & 0xFF),"Register %c does not equal register %c + register C + carry flag",destName,destName); break;
      case 0x3: oldSrc = old_z80->r->D; fail_unless(dest == ((oldDest + oldSrc + ((z80->r->F & 0x10) >> 4)) & 0xFF),"Register %c does not equal register %c + register D + carry flag",destName,destName); break;
      case 0x4: oldSrc = old_z80->r->E; fail_unless(dest == ((oldDest + oldSrc + ((z80->r->F & 0x10) >> 4)) & 0xFF),"Register %c does not equal register %c + register E + carry flag",destName,destName); break;
      case 0x5: oldSrc = old_z80->r->F; fail_unless(dest == ((oldDest + oldSrc + ((z80->r->F & 0x10) >> 4)) & 0xFF),"Register %c does not equal register %c + register F + carry flag",destName,destName); break;
      case 0x6: oldSrc = old_z80->r->H; fail_unless(dest == ((oldDest + oldSrc + ((z80->r->F & 0x10) >> 4)) & 0xFF),"Register %c does not equal register %c + register H + carry flag",destName,destName); break;
      case 0x7: oldSrc = old_z80->r->L; fail_unless(dest == ((oldDest + oldSrc + ((z80->r->F & 0x10) >> 4)) & 0xFF),"Register %c does not equal register %c + register L + carry flag",destName,destName); break;
   }
   dest = (oldDest + oldSrc) & 0xFF;

   // Flags
   if ((dest < oldDest) | (dest < oldSrc))
   {
      // Carry
      fail_unless((z80->r->F & 0x10) == 0x10,"Carry flag should be set");
   }

   if ((dest & 0xFF) == 0x00)
   {
      // Zero flag
      fail_unless(z80->r->F & 0x80,"Zero flag should be set");
   }

   if (((oldSrc & 0xF) + (oldDest & 0xF)) & 0x10)
   {
      // Half-carry
      fail_unless(z80->r->F == z80->r->F | 0x20,"Half-carry flag should be set");
   }

   fail_unless(z80->r->PC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");
   fail_unless(z80->ticks == 4,"Ticks for opcode not registered or incorrect value");

   return 0;
}

int SUBXY(Memory * memory, Z80 * z80, Z80 * old_z80, uint8_t regOrder, uint16_t tmp_z80_PC)
{
   uint8_t dest, oldDest, oldSrc;
   char destName;

   switch((regOrder >> 4) & 0xF)
   {
      case 0x0: dest = z80->r->A; oldDest = old_z80->r->A; destName = 'A'; break;
      case 0x1: dest = z80->r->B; oldDest = old_z80->r->B; destName = 'B'; break;
      case 0x2: dest = z80->r->C; oldDest = old_z80->r->C; destName = 'C'; break;
      case 0x3: dest = z80->r->D; oldDest = old_z80->r->D; destName = 'D'; break;
      case 0x4: dest = z80->r->E; oldDest = old_z80->r->E; destName = 'E'; break;
      case 0x5: dest = z80->r->F; oldDest = old_z80->r->F; destName = 'F'; break;
      case 0x6: dest = z80->r->H; oldDest = old_z80->r->H; destName = 'H'; break;
      case 0x7: dest = z80->r->L; oldDest = old_z80->r->L; destName = 'L'; break;
   }

   switch(regOrder & 0xF)
   {
      case 0x0: oldSrc = old_z80->r->A; fail_unless(dest == ((oldDest - oldSrc) & 0xFF),"Register %c does not equal register %c - register A",destName,destName); break;
      case 0x1: oldSrc = old_z80->r->B; fail_unless(dest == ((oldDest - oldSrc) & 0xFF),"Register %c does not equal register %c - register B",destName,destName); break;
      case 0x2: oldSrc = old_z80->r->C; fail_unless(dest == ((oldDest - oldSrc) & 0xFF),"Register %c does not equal register %c - register C",destName,destName); break;
      case 0x3: oldSrc = old_z80->r->D; fail_unless(dest == ((oldDest - oldSrc) & 0xFF),"Register %c does not equal register %c - register D",destName,destName); break;
      case 0x4: oldSrc = old_z80->r->E; fail_unless(dest == ((oldDest - oldSrc) & 0xFF),"Register %c does not equal register %c - register E",destName,destName); break;
      case 0x5: oldSrc = old_z80->r->F; fail_unless(dest == ((oldDest - oldSrc) & 0xFF),"Register %c does not equal register %c - register F",destName,destName); break;
      case 0x6: oldSrc = old_z80->r->H; fail_unless(dest == ((oldDest - oldSrc) & 0xFF),"Register %c does not equal register %c - register H",destName,destName); break;
      case 0x7: oldSrc = old_z80->r->L; fail_unless(dest == ((oldDest - oldSrc) & 0xFF),"Register %c does not equal register %c - register L",destName,destName); break;
   }

   dest = (oldDest - oldSrc) & 0xFF;

   // Flags
   if (dest > oldDest)
   {
      // Carry
      fail_unless((z80->r->F & 0x10) == 0x10,"Carry flag should be set %x",z80->r->F & 0x10);
   }

   if ((dest & 0xFF) == 0x00)
   {
      // Zero flag
      fail_unless(z80->r->F & 0x80,"Zero flag should be set");
   }

   if (((oldSrc & 0xF) - (oldDest & 0xF)) & 0x10)
   {
      // Half-carry
      fail_unless(z80->r->F == z80->r->F | 0x20,"Half-carry flag should be set");
   }

   fail_unless(z80->r->PC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");
   fail_unless(z80->ticks == 4,"Ticks for opcode not registered or incorrect value");

   return 0;
}

START_TEST (test_check_OP_00h_NOP)
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

START_TEST (test_check_OP_21h_LDHLnn)
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

START_TEST (test_check_OP_22h_LDIHLA)
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

START_TEST (test_check_OP_31h_JRNCn)
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

START_TEST (test_check_OP_32h_LDDHLA)
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

   result = OP_32h_LDDHLA(&memory,&z80);

   fail_unless(z80.r->PC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");

   fail_unless(result == 0,"Result was not 0");
   printf("HL+1 addr content = %x\nA = %x\n",rb(&memory,(z80.r->H << 8) + z80.r->L + 1),z80.r->A);
   fail_unless(rb(&memory,(z80.r->H << 8) + z80.r->L + 1) == z80.r->A,"Content at address pointed by HL (+1 at this point) does not match A register.");
   fail_unless(z80.ticks == 8,"Ticks for opcode not registered or incorrect value");
}
END_TEST

START_TEST (test_check_OP_40h_LDBB)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_40h_LDBB(memory,z80);

   LDXY(memory,z80,0x11,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_41h_LDBC)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_41h_LDBC(memory,z80);

   LDXY(memory,z80,0x12,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_42h_LDBD)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_42h_LDBD(memory,z80);

   LDXY(memory,z80,0x13,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_43h_LDBE)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_43h_LDBE(memory,z80);

   LDXY(memory,z80,0x14,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_44h_LDBH)
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

START_TEST (test_check_OP_45h_LDBL)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_45h_LDBL(memory,z80);

   LDXY(memory,z80,0x17,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_48h_LDCB(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_48h_LDCB)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_48h_LDCB(memory,z80);

   LDXY(memory,z80,0x21,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_49h_LDCC(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_49h_LDCC)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_49h_LDCC(memory,z80);

   LDXY(memory,z80,0x22,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_4Ah_LDCD(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_4Ah_LDCD)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_4Ah_LDCD(memory,z80);

   LDXY(memory,z80,0x23,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_4Bh_LDCE(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_4Bh_LDCE)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_4Bh_LDCE(memory,z80);

   LDXY(memory,z80,0x24,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_4Ch_LDCH(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_4Ch_LDCH)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_4Ch_LDCH(memory,z80);

   LDXY(memory,z80,0x26,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_4Dh_LDCL(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_4Dh_LDCL)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_4Dh_LDCL(memory,z80);

   LDXY(memory,z80,0x27,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_4Fh_LDCA(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_4Fh_LDCA)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_4Fh_LDCA(memory,z80);

   LDXY(memory,z80,0x20,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_50h_LDDB)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_50h_LDDB(memory,z80);

   LDXY(memory,z80,0x31,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_51h_LDDC)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_51h_LDDC(memory,z80);

   LDXY(memory,z80,0x32,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_52h_LDDD)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_52h_LDDD(memory,z80);

   LDXY(memory,z80,0x33,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_53h_LDDE)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_53h_LDDE(memory,z80);

   LDXY(memory,z80,0x34,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_54h_LDDH)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_54h_LDDH(memory,z80);

   LDXY(memory,z80,0x36,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_55h_LDDL)
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

//int OP_58h_LDEB(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_58h_LDEB)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_58h_LDEB(memory,z80);

   LDXY(memory,z80,0x41,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_59h_LDEC(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_59h_LDEC)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_59h_LDEC(memory,z80);

   LDXY(memory,z80,0x42,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_5Ah_LDED(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_5Ah_LDED)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_5Ah_LDED(memory,z80);

   LDXY(memory,z80,0x43,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_5Bh_LDEE(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_5Bh_LDEE)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_5Bh_LDEE(memory,z80);

   LDXY(memory,z80,0x44,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_5Ch_LDEH(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_5Ch_LDEH)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_5Ch_LDEH(memory,z80);

   LDXY(memory,z80,0x46,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_5Dh_LDEL(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_5Dh_LDEL)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_5Dh_LDEL(memory,z80);

   LDXY(memory,z80,0x47,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_5Fh_LDEA(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_5Fh_LDEA)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_5Fh_LDEA(memory,z80);

   LDXY(memory,z80,0x40,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_60h_LDHB)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_60h_LDHB(memory,z80);

   LDXY(memory,z80,0x61,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_61h_LDHC)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_61h_LDHC(memory,z80);

   LDXY(memory,z80,0x62,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_62h_LDHD)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_62h_LDHD(memory,z80);

   LDXY(memory,z80,0x63,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_63h_LDHE)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_63h_LDHE(memory,z80);

   LDXY(memory,z80,0x64,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_64h_LDHH)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_64h_LDHH(memory,z80);

   LDXY(memory,z80,0x66,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_65h_LDHL)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_65h_LDHL(memory,z80);

   LDXY(memory,z80,0x67,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_68h_LDLB(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_68h_LDLB)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_68h_LDLB(memory,z80);

   LDXY(memory,z80,0x71,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_69h_LDLC(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_69h_LDLC)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_69h_LDLC(memory,z80);

   LDXY(memory,z80,0x72,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_6Ah_LDLD(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_6Ah_LDLD)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_6Ah_LDLD(memory,z80);

   LDXY(memory,z80,0x73,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_6Bh_LDLE(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_6Bh_LDLE)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_6Bh_LDLE(memory,z80);

   LDXY(memory,z80,0x74,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_6Ch_LDLH(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_6Ch_LDLH)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_6Ch_LDLH(memory,z80);

   LDXY(memory,z80,0x76,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_6Dh_LDLL(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_6Dh_LDLL)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_6Dh_LDLL(memory,z80);

   LDXY(memory,z80,0x77,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_6Fh_LDLA(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_6Fh_LDLA)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_6Fh_LDLA(memory,z80);

   LDXY(memory,z80,0x70,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

START_TEST (test_check_OP_72h_LDHLD)
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

   result = OP_72h_LDHLD(&memory,&z80);

   fail_unless(z80.r->PC == tmp_z80_PC,"Program Counter should not be incremented by opcode function code");

   fail_unless(result == 0,"Result was not 0");
   fail_unless(rb(&memory,(z80.r->H << 8) + z80.r->L) == z80.r->D,"Content of address held in HL register does not equal register D");
   fail_unless(z80.ticks == 8,"Ticks for opcode not registered or incorrect value");
}
END_TEST

//int OP_78h_LDAB(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_78h_LDAB)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_78h_LDAB(memory,z80);

   LDXY(memory,z80,0x01,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_79h_LDAC(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_79h_LDAC)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_79h_LDAC(memory,z80);

   LDXY(memory,z80,0x02,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_7Ah_LDAD(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_7Ah_LDAD)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_7Ah_LDAD(memory,z80);

   LDXY(memory,z80,0x03,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_7Bh_LDAE(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_7Bh_LDAE)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_7Bh_LDAE(memory,z80);

   LDXY(memory,z80,0x04,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_7Ch_LDAH(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_7Ch_LDAH)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_7Ch_LDAH(memory,z80);

   LDXY(memory,z80,0x06,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_7Dh_LDAL(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_7Dh_LDAL)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_7Dh_LDAL(memory,z80);

   LDXY(memory,z80,0x07,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_7Fh_LDAA(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_7Fh_LDAA)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_7Fh_LDAA(memory,z80);

   LDXY(memory,z80,0x00,tmp_z80_PC);

   free(memory);
   free(registers);
   free(z80);
}
END_TEST

//int OP_80h_ADDAB(Memory * memory, Z80 * z80);
START_TEST (test_check_OP_80h_ADDAB)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_80h_ADDAB(memory,z80);
   ADDXY(memory,z80,old_z80,0x01,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_81h_ADDAC)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_81h_ADDAC(memory,z80);
   ADDXY(memory,z80,old_z80,0x02,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_82h_ADDAD)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_82h_ADDAD(memory,z80);
   ADDXY(memory,z80,old_z80,0x03,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_83h_ADDAE)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_83h_ADDAE(memory,z80);
   ADDXY(memory,z80,old_z80,0x04,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_84h_ADDAH)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_84h_ADDAH(memory,z80);
   ADDXY(memory,z80,old_z80,0x06,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_85h_ADDAL)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_85h_ADDAL(memory,z80);
   ADDXY(memory,z80,old_z80,0x07,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_87h_ADDAA)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_87h_ADDAA(memory,z80);
   ADDXY(memory,z80,old_z80,0x00,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_88h_ADCAB)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_88h_ADCAB(memory,z80);
   ADCXY(memory,z80,old_z80,0x01,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_89h_ADCAC)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_89h_ADCAC(memory,z80);
   ADCXY(memory,z80,old_z80,0x02,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_8Ah_ADCAD)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_8Ah_ADCAD(memory,z80);
   ADCXY(memory,z80,old_z80,0x03,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_8Bh_ADCAE)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_8Bh_ADCAE(memory,z80);
   ADCXY(memory,z80,old_z80,0x04,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_8Ch_ADCAH)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_8Ch_ADCAH(memory,z80);
   ADCXY(memory,z80,old_z80,0x06,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_8Dh_ADCAL)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_8Dh_ADCAL(memory,z80);
   ADCXY(memory,z80,old_z80,0x07,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_8Fh_ADCAA)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_8Fh_ADCAA(memory,z80);
   ADCXY(memory,z80,old_z80,0x00,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_90h_SUBB)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_90h_SUBB(memory,z80);
   SUBXY(memory,z80,old_z80,0x01,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_91h_SUBC)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_91h_SUBC(memory,z80);
   SUBXY(memory,z80,old_z80,0x02,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_92h_SUBD)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_92h_SUBD(memory,z80);
   SUBXY(memory,z80,old_z80,0x03,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_93h_SUBE)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_93h_SUBE(memory,z80);
   SUBXY(memory,z80,old_z80,0x04,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_94h_SUBH)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_94h_SUBH(memory,z80);
   SUBXY(memory,z80,old_z80,0x06,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_95h_SUBL)
{
   Memory * memory = malloc(sizeof(Memory));
   Registers * registers = malloc(sizeof(Registers));
   Z80 * z80 = malloc(sizeof(Z80));
   Memory * old_memory = malloc(sizeof(Memory));
   Registers * old_registers = malloc(sizeof(Registers));
   Z80 * old_z80 = malloc(sizeof(Z80));

   resetCPURegisters(memory,z80,registers);
   resetCPURegisters(memory,old_z80,old_registers);
   InitMemory(memory);

   int result = 0;
   uint16_t tmp_z80_PC = z80->r->PC;

   result = OP_95h_SUBL(memory,z80);
   SUBXY(memory,z80,old_z80,0x07,tmp_z80_PC);

   free(old_z80);
   free(old_registers);
   free(old_memory);
   free(z80);
   free(memory);
   free(registers);
}
END_TEST

START_TEST (test_check_OP_AFh_XORA)
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
   tcase_add_test(tc_core,test_check_OP_21h_LDHLnn);
   tcase_add_test(tc_core,test_check_OP_22h_LDIHLA);
   tcase_add_test(tc_core,test_check_OP_31h_JRNCn);
   tcase_add_test(tc_core,test_check_OP_32h_LDDHLA);
   tcase_add_test(tc_core,test_check_OP_40h_LDBB);
   tcase_add_test(tc_core,test_check_OP_41h_LDBC);
   tcase_add_test(tc_core,test_check_OP_42h_LDBD);
   tcase_add_test(tc_core,test_check_OP_43h_LDBE);
   tcase_add_test(tc_core,test_check_OP_44h_LDBH);
   tcase_add_test(tc_core,test_check_OP_45h_LDBL);
   tcase_add_test(tc_core,test_check_OP_48h_LDCB);
   tcase_add_test(tc_core,test_check_OP_49h_LDCC);
   tcase_add_test(tc_core,test_check_OP_4Ah_LDCD);
   tcase_add_test(tc_core,test_check_OP_4Bh_LDCE);
   tcase_add_test(tc_core,test_check_OP_4Ch_LDCH);
   tcase_add_test(tc_core,test_check_OP_4Dh_LDCL);
   tcase_add_test(tc_core,test_check_OP_4Fh_LDCA);
   tcase_add_test(tc_core,test_check_OP_50h_LDDB);
   tcase_add_test(tc_core,test_check_OP_51h_LDDC);
   tcase_add_test(tc_core,test_check_OP_52h_LDDD);
   tcase_add_test(tc_core,test_check_OP_53h_LDDE);
   tcase_add_test(tc_core,test_check_OP_54h_LDDH);
   tcase_add_test(tc_core,test_check_OP_55h_LDDL);
   tcase_add_test(tc_core,test_check_OP_58h_LDEB);
   tcase_add_test(tc_core,test_check_OP_59h_LDEC);
   tcase_add_test(tc_core,test_check_OP_5Ah_LDED);
   tcase_add_test(tc_core,test_check_OP_5Bh_LDEE);
   tcase_add_test(tc_core,test_check_OP_5Ch_LDEH);
   tcase_add_test(tc_core,test_check_OP_5Dh_LDEL);
   tcase_add_test(tc_core,test_check_OP_5Fh_LDEA);
   tcase_add_test(tc_core,test_check_OP_60h_LDHB);
   tcase_add_test(tc_core,test_check_OP_61h_LDHC);
   tcase_add_test(tc_core,test_check_OP_62h_LDHD);
   tcase_add_test(tc_core,test_check_OP_63h_LDHE);
   tcase_add_test(tc_core,test_check_OP_64h_LDHH);
   tcase_add_test(tc_core,test_check_OP_65h_LDHL);
   tcase_add_test(tc_core,test_check_OP_68h_LDLB);
   tcase_add_test(tc_core,test_check_OP_69h_LDLC);
   tcase_add_test(tc_core,test_check_OP_6Ah_LDLD);
   tcase_add_test(tc_core,test_check_OP_6Bh_LDLE);
   tcase_add_test(tc_core,test_check_OP_6Ch_LDLH);
   tcase_add_test(tc_core,test_check_OP_6Dh_LDLL);
   tcase_add_test(tc_core,test_check_OP_6Fh_LDLA);
   tcase_add_test(tc_core,test_check_OP_72h_LDHLD);
   tcase_add_test(tc_core,test_check_OP_78h_LDAB);
   tcase_add_test(tc_core,test_check_OP_79h_LDAC);
   tcase_add_test(tc_core,test_check_OP_7Ah_LDAD);
   tcase_add_test(tc_core,test_check_OP_7Bh_LDAE);
   tcase_add_test(tc_core,test_check_OP_7Ch_LDAH);
   tcase_add_test(tc_core,test_check_OP_7Dh_LDAL);
   tcase_add_test(tc_core,test_check_OP_7Fh_LDAA);
   tcase_add_test(tc_core,test_check_OP_80h_ADDAB);
   tcase_add_test(tc_core,test_check_OP_81h_ADDAC);
   tcase_add_test(tc_core,test_check_OP_82h_ADDAD);
   tcase_add_test(tc_core,test_check_OP_83h_ADDAE);
   tcase_add_test(tc_core,test_check_OP_84h_ADDAH);
   tcase_add_test(tc_core,test_check_OP_85h_ADDAL);
   tcase_add_test(tc_core,test_check_OP_87h_ADDAA);
   tcase_add_test(tc_core,test_check_OP_88h_ADCAB);
   tcase_add_test(tc_core,test_check_OP_89h_ADCAC);
   tcase_add_test(tc_core,test_check_OP_8Ah_ADCAD);
   tcase_add_test(tc_core,test_check_OP_8Bh_ADCAE);
   tcase_add_test(tc_core,test_check_OP_8Ch_ADCAH);
   tcase_add_test(tc_core,test_check_OP_8Dh_ADCAL);
   tcase_add_test(tc_core,test_check_OP_8Fh_ADCAA);
   tcase_add_test(tc_core,test_check_OP_90h_SUBB);
   tcase_add_test(tc_core,test_check_OP_91h_SUBC);
   tcase_add_test(tc_core,test_check_OP_92h_SUBD);
   tcase_add_test(tc_core,test_check_OP_93h_SUBE);
   tcase_add_test(tc_core,test_check_OP_94h_SUBH);
   tcase_add_test(tc_core,test_check_OP_95h_SUBL);
   tcase_add_test(tc_core,test_check_OP_AFh_XORA);
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
