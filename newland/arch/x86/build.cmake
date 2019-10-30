set(ARCH_FILES "${ARCH_DIR}/src/asm/entry.s"
  "${ARCH_DIR}/src/asm/gdt.s"
  "${ARCH_DIR}/src/asm/idt.s"
  "${ARCH_DIR}/src/asm/irq.s"
  "${ARCH_DIR}/src/bootstrap.c"
  "${ARCH_DIR}/src/gdt.c"
  "${ARCH_DIR}/src/idt.c"
  "${ARCH_DIR}/src/io.c"
  "${ARCH_DIR}/src/irq.c"
  "${ARCH_DIR}/src/misc.c"
  "${ARCH_DIR}/src/texcon.c")
include_directories("${ARCH_DIR}/include")
add_link_options("-T${ARCH_DIR}/linker.ld" "-m32")
add_compile_options("-m32")