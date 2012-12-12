TESTS = check_gb
check_PROGRAMS = check_gb
check_gb_SOURCES = check_gb.c $(top_srcdir)/src/cartridge.h  $(top_srcdir)/src/debug.h  $(top_srcdir)/src/display.h  $(top_srcdir)/src/error.h  $(top_srcdir)/src/memory.h  $(top_srcdir)/src/rom.h  $(top_srcdir)/src/timer.h  $(top_srcdir)/src/z80.h $(top_srcdir)/src/cartridge.c  $(top_srcdir)/src/debug.c  $(top_srcdir)/src/display.c  $(top_srcdir)/src/error.c  $(top_srcdir)/src/memory.c  $(top_srcdir)/src/rom.c  $(top_srcdir)/src/timer.c  $(top_srcdir)/src/z80.c
#check_gb_SOURCES = check_gb.c $(top_srcdir)/src/z80.h $(top_srcdir)/src/z80.c $(top_srcdir)/src/memory.h $(top_srcdir)/src/memory.c
#check_gb_SOURCES = check_gb.c
check_gb_CFLAGS = @CHECK_CFLAGS@
#check_add_LDADD = $(top_builddir)/src/add.h @CHECK_LIBS@
check_gb_LDADD = @CHECK_LIBS@
