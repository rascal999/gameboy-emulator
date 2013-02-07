TESTS = check_gb_opcodes check_gb_memory
check_PROGRAMS = check_gb_opcodes check_gb_memory
TESTS_ENVIRONMENT = \
CK_DEFAULT_TIMEOUT=600

check_gb_opcodes_SOURCES = check_gb_opcodes.c  $(top_srcdir)/src/mock_cartridge.h  $(top_srcdir)/src/mock_debug.h  $(top_srcdir)/src/mock_display.h  $(top_srcdir)/src/mock_error.h  $(top_srcdir)/src/mock_memory.h  $(top_srcdir)/src/mock_opcode_attributes.h  $(top_srcdir)/src/mock_opcode_wrappers.h  $(top_srcdir)/src/mock_rom.h  $(top_srcdir)/src/mock_timer.h  $(top_srcdir)/src/mock_z80.h  $(top_srcdir)/src/mock_cartridge.c  $(top_srcdir)/src/mock_debug.c  $(top_srcdir)/src/mock_display.c  $(top_srcdir)/src/mock_error.c  $(top_srcdir)/src/mock_memory.c  $(top_srcdir)/src/mock_opcode_attributes.c  $(top_srcdir)/src/mock_opcode_wrappers.c  $(top_srcdir)/src/mock_rom.c  $(top_srcdir)/src/mock_timer.c  $(top_srcdir)/src/mock_z80.c

check_gb_memory_SOURCES = check_gb_memory.c  $(top_srcdir)/src/mock_cartridge.h  $(top_srcdir)/src/mock_debug.h  $(top_srcdir)/src/mock_display.h  $(top_srcdir)/src/mock_error.h  $(top_srcdir)/src/mock_memory.h  $(top_srcdir)/src/mock_opcode_attributes.h  $(top_srcdir)/src/mock_opcode_wrappers.h  $(top_srcdir)/src/mock_rom.h  $(top_srcdir)/src/mock_timer.h  $(top_srcdir)/src/mock_z80.h  $(top_srcdir)/src/mock_cartridge.c  $(top_srcdir)/src/mock_debug.c  $(top_srcdir)/src/mock_display.c  $(top_srcdir)/src/mock_error.c  $(top_srcdir)/src/mock_memory.c  $(top_srcdir)/src/mock_opcode_attributes.c  $(top_srcdir)/src/mock_opcode_wrappers.c  $(top_srcdir)/src/mock_rom.c  $(top_srcdir)/src/mock_timer.c  $(top_srcdir)/src/mock_z80.c

check_gb_opcodes_CFLAGS = @CHECK_CFLAGS@
check_gb_opcodes_CPPFLAGS = -DUNITTEST_OPCODES
check_gb_opcodes_LDADD = @CHECK_LIBS@

check_gb_memory_CFLAGS = @CHECK_CFLAGS@
check_gb_memory_CPPFLAGS = -DUNITTEST_MEMORY
check_gb_memory_LDADD = @CHECK_LIBS@
