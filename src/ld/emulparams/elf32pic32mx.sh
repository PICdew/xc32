# The master script template file is found in
# ${srcdir}/scripttempl/${SCRIPT_NAME}.sh
SCRIPT_NAME=pic32mx
TEMPLATE_NAME=elf32pic32mx
EMULATION_NAME=elf32pic32mx

# Whether this is an embedded system
EMBEDDED=yes

# Specify the particular output machine architecture for the output file.
# Must be the name of a BFD architecture
OUTPUT_ARCH=pic32mx

# Names the BFD format to use for the output file.
# Will be used for both the big endian and little endian formats.
OUTPUT_FORMAT=elf32-tradlittlemips

# Provides the symbol name that will be the application's entry point.
ENTRY=_reset

# These symbols will be defined for an executable
EXECUTABLE_SYMBOLS="
/*
 * Provide for a minimum stack and heap size
 * - _min_stack_size - represents the minimum space that must be made
 *                     available for the stack.  Can be overridden from
 *                     the command line using the linker's --defsym option.
 * - _min_heap_size  - represents the minimum space that must be made
 *                     available for the heap.  Can be overridden from
 *                     the command line using the linker's --defsym option.
 */
EXTERN (_min_stack_size _min_heap_size)
PROVIDE(_min_stack_size = 0x400) ;
PROVIDE(_min_heap_size = 0) ;
"

# These files will always be included in the link
INPUT_FILES="
INCLUDE procdefs.ld
"
# Initial section should go before .text
unset INIT_AFTER_TEXT

# Before outputting .init section
INIT_START="
    _init_begin = . ;
"

# After outputting .init section
INIT_END="
    _init_end = . ;
"

# Before outputting .fini section
FINI_START="
    _fini_begin = . ;
"

# After outputting .fini section
FINI_END="
    _fini_end = . ;
"

# The memory region to place all code sections
CODE_MEMORY_REGION="kseg0_program_mem"

# The memory region to place all data sections
DATA_MEMORY_REGION="kseg1_data_mem"

# The boot section
BOOT_SECTION="
  .reset _RESET_ADDR :
  {
    KEEP(*(.reset))
  } > kseg1_boot_mem

  .bev_excpt _BEV_EXCPT_ADDR :
  {
    KEEP(*(.bev_handler))
  } > kseg1_boot_mem

  .dbg_excpt _DBG_EXCPT_ADDR (NOLOAD) :
  {
    . += (DEFINED (_DEBUGGER) ? 0x8 : 0x0);
  } > kseg1_boot_mem

  .dbg_code _DBG_CODE_ADDR (NOLOAD) :
  {
    . += (DEFINED (_DEBUGGER) ? 0xFF0 : 0x0);
  } > debug_exec_mem

  .app_excpt _GEN_EXCPT_ADDR :
  {
    KEEP(*(.gen_handler))
  } > exception_mem

  .vector_0 _ebase_address + 0x200 :
  {
    KEEP(*(.vector_0))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_0) <= (_vector_spacing << 5), \"function at exception vector 0 too large\")

  .vector_1 _ebase_address + 0x200 + (_vector_spacing << 5) * 1 :
  {
    KEEP(*(.vector_1))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_1) <= (_vector_spacing << 5), \"function at exception vector 1 too large\")

  .vector_2 _ebase_address + 0x200 + (_vector_spacing << 5) * 2 :
  {
    KEEP(*(.vector_2))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_2) <= (_vector_spacing << 5), \"function at exception vector 2 too large\")

  .vector_3 _ebase_address + 0x200 + (_vector_spacing << 5) * 3 :
  {
    KEEP(*(.vector_3))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_3) <= (_vector_spacing << 5), \"function at exception vector 3 too large\")

  .vector_4 _ebase_address + 0x200 + (_vector_spacing << 5) * 4 :
  {
    KEEP(*(.vector_4))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_4) <= (_vector_spacing << 5), \"function at exception vector 4 too large\")

  .vector_5 _ebase_address + 0x200 + (_vector_spacing << 5) * 5 :
  {
    KEEP(*(.vector_5))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_5) <= (_vector_spacing << 5), \"function at exception vector 5 too large\")

  .vector_6 _ebase_address + 0x200 + (_vector_spacing << 5) * 6 :
  {
    KEEP(*(.vector_6))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_6) <= (_vector_spacing << 5), \"function at exception vector 6 too large\")

  .vector_7 _ebase_address + 0x200 + (_vector_spacing << 5) * 7 :
  {
    KEEP(*(.vector_7))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_7) <= (_vector_spacing << 5), \"function at exception vector 7 too large\")

  .vector_8 _ebase_address + 0x200 + (_vector_spacing << 5) * 8 :
  {
    KEEP(*(.vector_8))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_8) <= (_vector_spacing << 5), \"function at exception vector 8 too large\")

  .vector_9 _ebase_address + 0x200 + (_vector_spacing << 5) * 9 :
  {
    KEEP(*(.vector_9))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_9) <= (_vector_spacing << 5), \"function at exception vector 9 too large\")

  .vector_10 _ebase_address + 0x200 + (_vector_spacing << 5) * 10 :
  {
    KEEP(*(.vector_10))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_10) <= (_vector_spacing << 5), \"function at exception vector 10 too large\")

  .vector_11 _ebase_address + 0x200 + (_vector_spacing << 5) * 11 :
  {
    KEEP(*(.vector_11))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_11) <= (_vector_spacing << 5), \"function at exception vector 11 too large\")

  .vector_12 _ebase_address + 0x200 + (_vector_spacing << 5) * 12 :
  {
    KEEP(*(.vector_12))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_12) <= (_vector_spacing << 5), \"function at exception vector 12 too large\")

  .vector_13 _ebase_address + 0x200 + (_vector_spacing << 5) * 13 :
  {
    KEEP(*(.vector_13))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_13) <= (_vector_spacing << 5), \"function at exception vector 13 too large\")

  .vector_14 _ebase_address + 0x200 + (_vector_spacing << 5) * 14 :
  {
    KEEP(*(.vector_14))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_14) <= (_vector_spacing << 5), \"function at exception vector 14 too large\")

  .vector_15 _ebase_address + 0x200 + (_vector_spacing << 5) * 15 :
  {
    KEEP(*(.vector_15))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_15) <= (_vector_spacing << 5), \"function at exception vector 15 too large\")

  .vector_16 _ebase_address + 0x200 + (_vector_spacing << 5) * 16 :
  {
    KEEP(*(.vector_16))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_16) <= (_vector_spacing << 5), \"function at exception vector 16 too large\")

  .vector_17 _ebase_address + 0x200 + (_vector_spacing << 5) * 17 :
  {
    KEEP(*(.vector_17))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_17) <= (_vector_spacing << 5), \"function at exception vector 17 too large\")

  .vector_18 _ebase_address + 0x200 + (_vector_spacing << 5) * 18 :
  {
    KEEP(*(.vector_18))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_18) <= (_vector_spacing << 5), \"function at exception vector 18 too large\")

  .vector_19 _ebase_address + 0x200 + (_vector_spacing << 5) * 19 :
  {
    KEEP(*(.vector_19))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_19) <= (_vector_spacing << 5), \"function at exception vector 19 too large\")

  .vector_20 _ebase_address + 0x200 + (_vector_spacing << 5) * 20 :
  {
    KEEP(*(.vector_20))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_20) <= (_vector_spacing << 5), \"function at exception vector 20 too large\")

  .vector_21 _ebase_address + 0x200 + (_vector_spacing << 5) * 21 :
  {
    KEEP(*(.vector_21))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_21) <= (_vector_spacing << 5), \"function at exception vector 21 too large\")

  .vector_22 _ebase_address + 0x200 + (_vector_spacing << 5) * 22 :
  {
    KEEP(*(.vector_22))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_22) <= (_vector_spacing << 5), \"function at exception vector 22 too large\")

  .vector_23 _ebase_address + 0x200 + (_vector_spacing << 5) * 23 :
  {
    KEEP(*(.vector_23))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_23) <= (_vector_spacing << 5), \"function at exception vector 23 too large\")

  .vector_24 _ebase_address + 0x200 + (_vector_spacing << 5) * 24 :
  {
    KEEP(*(.vector_24))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_24) <= (_vector_spacing << 5), \"function at exception vector 24 too large\")

  .vector_25 _ebase_address + 0x200 + (_vector_spacing << 5) * 25 :
  {
    KEEP(*(.vector_25))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_25) <= (_vector_spacing << 5), \"function at exception vector 25 too large\")

  .vector_26 _ebase_address + 0x200 + (_vector_spacing << 5) * 26 :
  {
    KEEP(*(.vector_26))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_26) <= (_vector_spacing << 5), \"function at exception vector 26 too large\")

  .vector_27 _ebase_address + 0x200 + (_vector_spacing << 5) * 27 :
  {
    KEEP(*(.vector_27))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_27) <= (_vector_spacing << 5), \"function at exception vector 27 too large\")

  .vector_28 _ebase_address + 0x200 + (_vector_spacing << 5) * 28 :
  {
    KEEP(*(.vector_28))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_28) <= (_vector_spacing << 5), \"function at exception vector 28 too large\")

  .vector_29 _ebase_address + 0x200 + (_vector_spacing << 5) * 29 :
  {
    KEEP(*(.vector_29))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_29) <= (_vector_spacing << 5), \"function at exception vector 29 too large\")

  .vector_30 _ebase_address + 0x200 + (_vector_spacing << 5) * 30 :
  {
    KEEP(*(.vector_30))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_30) <= (_vector_spacing << 5), \"function at exception vector 30 too large\")

  .vector_31 _ebase_address + 0x200 + (_vector_spacing << 5) * 31 :
  {
    KEEP(*(.vector_31))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_31) <= (_vector_spacing << 5), \"function at exception vector 31 too large\")

  .vector_32 _ebase_address + 0x200 + (_vector_spacing << 5) * 32 :
  {
    KEEP(*(.vector_32))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_32) <= (_vector_spacing << 5), \"function at exception vector 32 too large\")

  .vector_33 _ebase_address + 0x200 + (_vector_spacing << 5) * 33 :
  {
    KEEP(*(.vector_33))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_33) <= (_vector_spacing << 5), \"function at exception vector 33 too large\")

  .vector_34 _ebase_address + 0x200 + (_vector_spacing << 5) * 34 :
  {
    KEEP(*(.vector_34))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_34) <= (_vector_spacing << 5), \"function at exception vector 34 too large\")

  .vector_35 _ebase_address + 0x200 + (_vector_spacing << 5) * 35 :
  {
    KEEP(*(.vector_35))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_35) <= (_vector_spacing << 5), \"function at exception vector 35 too large\")

  .vector_36 _ebase_address + 0x200 + (_vector_spacing << 5) * 36 :
  {
    KEEP(*(.vector_36))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_36) <= (_vector_spacing << 5), \"function at exception vector 36 too large\")

  .vector_37 _ebase_address + 0x200 + (_vector_spacing << 5) * 37 :
  {
    KEEP(*(.vector_37))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_37) <= (_vector_spacing << 5), \"function at exception vector 37 too large\")

  .vector_38 _ebase_address + 0x200 + (_vector_spacing << 5) * 38 :
  {
    KEEP(*(.vector_38))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_38) <= (_vector_spacing << 5), \"function at exception vector 38 too large\")

  .vector_39 _ebase_address + 0x200 + (_vector_spacing << 5) * 39 :
  {
    KEEP(*(.vector_39))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_39) <= (_vector_spacing << 5), \"function at exception vector 39 too large\")

  .vector_40 _ebase_address + 0x200 + (_vector_spacing << 5) * 40 :
  {
    KEEP(*(.vector_40))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_40) <= (_vector_spacing << 5), \"function at exception vector 40 too large\")

  .vector_41 _ebase_address + 0x200 + (_vector_spacing << 5) * 41 :
  {
    KEEP(*(.vector_41))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_41) <= (_vector_spacing << 5), \"function at exception vector 41 too large\")

  .vector_42 _ebase_address + 0x200 + (_vector_spacing << 5) * 42 :
  {
    KEEP(*(.vector_42))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_42) <= (_vector_spacing << 5), \"function at exception vector 42 too large\")

  .vector_43 _ebase_address + 0x200 + (_vector_spacing << 5) * 43 :
  {
    KEEP(*(.vector_43))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_43) <= (_vector_spacing << 5), \"function at exception vector 43 too large\")

  .vector_44 _ebase_address + 0x200 + (_vector_spacing << 5) * 44 :
  {
    KEEP(*(.vector_44))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_44) <= (_vector_spacing << 5), \"function at exception vector 44 too large\")

  .vector_45 _ebase_address + 0x200 + (_vector_spacing << 5) * 45 :
  {
    KEEP(*(.vector_45))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_45) <= (_vector_spacing << 5), \"function at exception vector 45 too large\")

  .vector_46 _ebase_address + 0x200 + (_vector_spacing << 5) * 46 :
  {
    KEEP(*(.vector_46))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_46) <= (_vector_spacing << 5), \"function at exception vector 46 too large\")

  .vector_47 _ebase_address + 0x200 + (_vector_spacing << 5) * 47 :
  {
    KEEP(*(.vector_47))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_47) <= (_vector_spacing << 5), \"function at exception vector 47 too large\")

  .vector_48 _ebase_address + 0x200 + (_vector_spacing << 5) * 48 :
  {
    KEEP(*(.vector_48))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_48) <= (_vector_spacing << 5), \"function at exception vector 48 too large\")

  .vector_49 _ebase_address + 0x200 + (_vector_spacing << 5) * 49 :
  {
    KEEP(*(.vector_49))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_49) <= (_vector_spacing << 5), \"function at exception vector 49 too large\")

  .vector_50 _ebase_address + 0x200 + (_vector_spacing << 5) * 50 :
  {
    KEEP(*(.vector_50))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_50) <= (_vector_spacing << 5), \"function at exception vector 50 too large\")

  .vector_51 _ebase_address + 0x200 + (_vector_spacing << 5) * 51 :
  {
    KEEP(*(.vector_51))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_51) <= (_vector_spacing << 5), \"function at exception vector 51 too large\")

  .vector_52 _ebase_address + 0x200 + (_vector_spacing << 5) * 52 :
  {
    KEEP(*(.vector_52))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_52) <= (_vector_spacing << 5), \"function at exception vector 52 too large\")

  .vector_53 _ebase_address + 0x200 + (_vector_spacing << 5) * 53 :
  {
    KEEP(*(.vector_53))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_53) <= (_vector_spacing << 5), \"function at exception vector 53 too large\")

  .vector_54 _ebase_address + 0x200 + (_vector_spacing << 5) * 54 :
  {
    KEEP(*(.vector_54))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_54) <= (_vector_spacing << 5), \"function at exception vector 54 too large\")

  .vector_55 _ebase_address + 0x200 + (_vector_spacing << 5) * 55 :
  {
    KEEP(*(.vector_55))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_55) <= (_vector_spacing << 5), \"function at exception vector 55 too large\")

  .vector_56 _ebase_address + 0x200 + (_vector_spacing << 5) * 56 :
  {
    KEEP(*(.vector_56))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_56) <= (_vector_spacing << 5), \"function at exception vector 56 too large\")

  .vector_57 _ebase_address + 0x200 + (_vector_spacing << 5) * 57 :
  {
    KEEP(*(.vector_57))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_57) <= (_vector_spacing << 5), \"function at exception vector 57 too large\")

  .vector_58 _ebase_address + 0x200 + (_vector_spacing << 5) * 58 :
  {
    KEEP(*(.vector_58))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_58) <= (_vector_spacing << 5), \"function at exception vector 58 too large\")

  .vector_59 _ebase_address + 0x200 + (_vector_spacing << 5) * 59 :
  {
    KEEP(*(.vector_59))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_59) <= (_vector_spacing << 5), \"function at exception vector 59 too large\")

  .vector_60 _ebase_address + 0x200 + (_vector_spacing << 5) * 60 :
  {
    KEEP(*(.vector_60))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_60) <= (_vector_spacing << 5), \"function at exception vector 60 too large\")

  .vector_61 _ebase_address + 0x200 + (_vector_spacing << 5) * 61 :
  {
    KEEP(*(.vector_61))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_61) <= (_vector_spacing << 5), \"function at exception vector 61 too large\")

  .vector_62 _ebase_address + 0x200 + (_vector_spacing << 5) * 62 :
  {
    KEEP(*(.vector_62))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_62) <= (_vector_spacing << 5), \"function at exception vector 62 too large\")

  .vector_63 _ebase_address + 0x200 + (_vector_spacing << 5) * 63 :
  {
    KEEP(*(.vector_63))
  } > exception_mem
  ASSERT (_vector_spacing == 0 || SIZEOF(.vector_63) <= (_vector_spacing << 5), \"function at exception vector 63 too large\")

  .startup ORIGIN(kseg0_boot_mem) :
  {
    KEEP(*(.startup))
  } > kseg0_boot_mem
"

# The first byte of the .text section should be located after the last vector
TEXT_START_ADDR="ORIGIN(${CODE_MEMORY_REGION})"

# Symbols to represent the beginning of the .text section
TEXT_START_SYMBOLS="
    _text_begin = . ;
"

# Other sections that should be included in the .text section
OTHER_TEXT_SECTIONS="
    *(.mips16.fn.*)
    *(.mips16.call.*)
"

# Symbols that represent the end of the .text section
TEXT_END_SYMBOLS="
    _text_end = . ;
"

# .rodata section should be located in the program flash, not in data memory
unset WRITABLE_RODATA

# Symbols to represent the beginning of the data sections
DATA_START_SYMBOLS="
    _data_begin = . ;
"

# Symbols defined just before .got output section
OTHER_GOT_SYMBOLS="
  _gp = ALIGN(16) + 0x7FF0 ;
"

# Symbols to represent the beginning of the .sdata section
SDATA_START_SYMBOLS="
    _sdata_begin = . ;
"

# Symbols to represent the end of the .sdata section
SDATA_END_SYMBOLS="
    _sdata_end = . ;
"

# Symbols to represent the beginning of the .sbss section
SBSS_START_SYMBOLS="
    _sbss_begin = . ;
"

# Symbols to represent the end of the .sbss section
SBSS_END_SYMBOLS="
    _sbss_end = . ;
"

# Other output sections to include in the linker script after the .sdata output
# section
OTHER_SDATA_SECTIONS="
  .lit8         ${RELOCATING-0} :
  {
    *(.lit8)
  } >${DATA_MEMORY_REGION} AT>${CODE_MEMORY_REGION}
  .lit4         ${RELOCATING-0} :
  {
    *(.lit4)
  } >${DATA_MEMORY_REGION} AT>${CODE_MEMORY_REGION}
  . = ALIGN (4) ;
  _data_end = . ;
"

# Symbols that specify the beginning of the .bss section
BSS_START_SYMBOLS="
  _bss_begin = . ;
"

# Symbols that specify the end of the .bss section
BSS_END_SYMBOLS="
  _bss_end = . ;
"

# Other output sections to include in the linker script before the DEBUG
# sections
OTHER_SECTIONS="
  /* Persistent data */
  .persist ALIGN(4) :
  {
    *(.persist)
    . = ALIGN(32 / 8) ;
  } >${DATA_MEMORY_REGION}

  /* Heap allocating takes a chunk of memory following BSS */
  .heap ALIGN(4) :
  {
    _heap = . ;
    . += _min_heap_size ;
  } >${DATA_MEMORY_REGION}

  /* Stack allocation follows the heap */
  .stack ALIGN(8) :
  {
    _splim = . ;
    _SPLIM = . ;
    . += _min_stack_size ;
  } >${DATA_MEMORY_REGION}

  /*
   * RAM functions go at the end of our stack and heap allocation.
   * Alignment of 2K required by the boundary register (BMXDKPBA).
   */
  .ramfunc ALIGN(2K) :
  {
    _ramfunc_begin = . ;
    *(.ramfunc ${RELOCATING+ .ramfunc.*})
    . = ALIGN(4) ;
    _ramfunc_end = . ;
  } >${DATA_MEMORY_REGION} AT>${CODE_MEMORY_REGION}
  _ramfunc_image_begin = LOADADDR(.ramfunc) ;
  _ramfunc_length = SIZEOF(.ramfunc) ;
  _bmxdkpba_address = _ramfunc_begin - ORIGIN(${DATA_MEMORY_REGION}) ;
  _bmxdudba_address = LENGTH(${DATA_MEMORY_REGION}) ;
  _bmxdupba_address = LENGTH(${DATA_MEMORY_REGION}) ;

  /*
   * The actual top of stack should include the gap between the stack
   * section and the beginning of the .ramfunc section caused by the
   * alignment of the .ramfunc section minus 1 word.  If RAM functions
   * do not exist, then the top of the stack should point to the end of
   * the data memory.
   */
  _stack = (_ramfunc_length > 0)
         ? _ramfunc_begin - 4
         : ORIGIN(${DATA_MEMORY_REGION}) + LENGTH(${DATA_MEMORY_REGION}) ;
  ASSERT((_min_stack_size + _min_heap_size) <= (_stack - _heap),
    \"Not enough space to allocate both stack and heap.  Reduce heap and/or stack size.\")

    /* The .pdf section belongs in the absolute section */
    .pdr 0 : { *(.pdr) }
    /* We don't load .reginfo onto the target, so don't locate it
     * in real memory 
     */
    .reginfo 0 : { *(.reginfo) }
"
