typedef struct
{
   unsigned short addr[0xFFFF]; /* 16 bit address buffer. Mem size of 65 536 */
   int tmp;
} Memory;

/* MMU */
/* Read byte */
unsigned short rb(Memory * mem, unsigned short addr);

/* Write byte */
int wb(Memory * mem, unsigned short addr, unsigned char value);

/* Read word */
unsigned short rw(Memory * mem, unsigned short addr);

/* Write word */
int ww(Memory * mem, unsigned short addr, unsigned short value);
/* END MMU */

int InitMemory(Memory * memory);
