TESTS = check_gb_opcode_attributes check_gb_opcodes check_gb_memory
check_PROGRAMS = check_gb_opcode_attributes check_gb_opcodes check_gb_memory
TESTS_ENVIRONMENT = \
CK_DEFAULT_TIMEOUT=600

check_gb_opcode_attributes_SOURCES = check_gb_opcode_attributes.c  $(top_srcdir)/src/cartridge.h  $(top_srcdir)/src/debug.h  $(top_srcdir)/src/display.h  $(top_srcdir)/src/error.h  $(top_srcdir)/src/memory.h  $(top_srcdir)/src/opcode_attributes.h  $(top_srcdir)/src/opcode_wrappers.h  $(top_srcdir)/src/rom.h  $(top_srcdir)/src/timer.h  $(top_srcdir)/src/z80.h  $(top_srcdir)/src/cartridge.c  $(top_srcdir)/src/debug.c  $(top_srcdir)/src/display.c  $(top_srcdir)/src/error.c  $(top_srcdir)/src/memory.c  $(top_srcdir)/src/opcode_attributes.c  $(top_srcdir)/src/opcode_wrappers.c  $(top_srcdir)/src/rom.c  $(top_srcdir)/src/timer.c  $(top_srcdir)/src/z80.c

check_gb_opcodes_SOURCES = check_gb_opcodes.c  $(top_srcdir)/src/cartridge.h  $(top_srcdir)/src/debug.h  $(top_srcdir)/src/display.h  $(top_srcdir)/src/error.h  $(top_srcdir)/src/memory.h  $(top_srcdir)/src/opcode_attributes.h  $(top_srcdir)/src/opcode_wrappers.h  $(top_srcdir)/src/rom.h  $(top_srcdir)/src/timer.h  $(top_srcdir)/src/z80.h  $(top_srcdir)/src/cartridge.c  $(top_srcdir)/src/debug.c  $(top_srcdir)/src/display.c  $(top_srcdir)/src/error.c  $(top_srcdir)/src/memory.c  $(top_srcdir)/src/opcode_attributes.c  $(top_srcdir)/src/opcode_wrappers.c  $(top_srcdir)/src/rom.c  $(top_srcdir)/src/timer.c  $(top_srcdir)/src/z80.c

check_gb_memory_SOURCES = check_gb_memory.c  $(top_srcdir)/src/cartridge.h  $(top_srcdir)/src/debug.h  $(top_srcdir)/src/display.h  $(top_srcdir)/src/error.h  $(top_srcdir)/src/memory.h  $(top_srcdir)/src/opcode_attributes.h  $(top_srcdir)/src/opcode_wrappers.h  $(top_srcdir)/src/rom.h  $(top_srcdir)/src/timer.h  $(top_srcdir)/src/z80.h  $(top_srcdir)/src/cartridge.c  $(top_srcdir)/src/debug.c  $(top_srcdir)/src/display.c  $(top_srcdir)/src/error.c  $(top_srcdir)/src/memory.c  $(top_srcdir)/src/opcode_attributes.c  $(top_srcdir)/src/opcode_wrappers.c  $(top_srcdir)/src/rom.c  $(top_srcdir)/src/timer.c  $(top_srcdir)/src/z80.c

check_gb_opcode_attributes_CFLAGS = @CHECK_CFLAGS@
check_gb_opcode_attributes_CPPFLAGS = -DUNITTEST_OPCODE_ATTRIBUTES
check_gb_opcode_attributes_LDADD = @CHECK_LIBS@

check_gb_opcodes_CFLAGS = @CHECK_CFLAGS@
check_gb_opcodes_CPPFLAGS = -DUNITTEST_OPCODES
check_gb_opcodes_LDADD = @CHECK_LIBS@

check_gb_memory_CFLAGS = @CHECK_CFLAGS@
check_gb_memory_CPPFLAGS = -DUNITTEST_MEMORY
check_gb_memory_LDADD = @CHECK_LIBS@
