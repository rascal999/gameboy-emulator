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
int wb_timer(Timers * timer, unsigned short addr, unsigned char value);

/* Read word */
unsigned short rw_timer(Timers * timer, unsigned short addr);

/* Write word */
int ww_timer(Timers * timer, unsigned short addr, unsigned short value);
/* END Timers */

int InitTimers(Timers * timer);
