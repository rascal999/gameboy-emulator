#ifdef UNITTEST_OPCODES
   #ifndef _INCL_MEMORY
      #define _INCL_MEMORY
      #include "mock_timer.h"
   #endif
#else
   #ifndef _INCL_MEMORY
      #define _INCL_MEMORY
      #include "timer.h"
   #endif
#endif

/* Timers */
/* Read byte */
unsigned short rb_timer(Timers * timer, unsigned short addr)
{
   return 0;
}

/* Write byte */
int wb_timer(Timers * timer, unsigned short addr, unsigned char value)
{
   return 0;
}

/* Read word */
unsigned short rw_timer(Timers * timer, unsigned short addr)
{
   return 0;
}

/* Write word */
int ww_timer(Timers * timer, unsigned short addr, unsigned short value)
{
   return 0;
}
/* END Timers */

int InitTimers(Timers * timer)
{
   return 0;
}
