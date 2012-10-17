#include "z80.h"

int InitZ80(Z80 * z80, Registers * registers)
{
   z80->r = registers;
   z80->r->A = 0;
   z80->r->B = 0;
   z80->r->C = 0;
   z80->r->D = 0;
   z80->r->E = 0;
   z80->r->H = 0;
   z80->r->L = 0;
   z80->r->F = 0;
   z80->r->T = 0;
   z80->r->M = 0;
   z80->r->PC = 0;
   z80->r->SP = 0;

   return 0;
}

int ResetZ80(Z80 * z80, Registers * registers)
{
   InitZ80(z80,registers);

   return 0;
}

int Dispatch(Z80 * z80)
{
   /* Testing register manipulation */
   z80->r->A = 1;
}
