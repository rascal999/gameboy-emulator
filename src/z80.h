typedef struct
{
   unsigned char A;
   unsigned char B;
   unsigned char C;
   unsigned char D;
   unsigned char E;
   unsigned char H;
   unsigned char L;
   unsigned char F; /* Flag */

   /* Clocks */
   unsigned char M;
   unsigned char T;

   unsigned short PC;
   unsigned short SP;
} Registers;

typedef struct
{
   Registers * r;
} Z80;

int InitZ80(Z80 * z80, Registers * registers);
int ResetZ80(Z80 * z80, Registers * registers);
int Dispatch(Z80 * z80);
