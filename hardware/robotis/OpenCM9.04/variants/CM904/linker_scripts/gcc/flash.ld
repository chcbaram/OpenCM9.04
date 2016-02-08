/*
 * Maple (STM32F103RBT6, medium density) linker script for Flash builds.
 */

/*
 * Define memory spaces.
 */
MEMORY
{
  /*ram (rwx) : ORIGIN = 0x20000000, LENGTH = 20K
  rom (rx)  : ORIGIN = 0x08003000, LENGTH = 56K 
  
  RAM (xrw) : ORIGIN = 0x20000000, LENGTH = 20K  
  FLASH (rx) : ORIGIN = 0x8003000, LENGTH = 64K
  FLASHB1 (rx) : ORIGIN = 0x00000000, LENGTH = 0*/

  ram (rwx) : ORIGIN = 0x20000000, LENGTH = 20K
  rom (rx)  : ORIGIN = 0x08003000, LENGTH = 56K 
}

/*
 * Use medium density device vector table
 */
GROUP(libcs3_stm32_med_density.a)

REGION_ALIAS("REGION_TEXT", rom);
REGION_ALIAS("REGION_DATA", ram);
REGION_ALIAS("REGION_BSS", ram);
REGION_ALIAS("REGION_RODATA", rom);

/*
 * Define the rest of the sections
 */
_FLASH_BUILD = 1;

/*
 * Linker script for libmaple.
 *
 * Original author "lanchon" from ST forums, with modifications by LeafLabs.
 */

OUTPUT_FORMAT ("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
ENTRY(_start)
SEARCH_DIR(.)

/*
 * Link against libgcc, libc, and libm
 */
GROUP(libgcc.a libc.a libm.a)

/* These force the linker to search for particular symbols from
 * the start of the link process and thus ensure the user's
 * overrides are picked up
 */
EXTERN(__cs3_stack)
EXTERN(__cs3_reset)
EXTERN(__exc_nmi)
EXTERN(__exc_hardfault)
EXTERN(__exc_memmanage)
EXTERN(__exc_busfault)
EXTERN(__exc_usagefault)
EXTERN(__stm32reservedexception7)
EXTERN(__stm32reservedexception8)
EXTERN(__stm32reservedexception9)
EXTERN(__stm32reservedexception10)
EXTERN(__exc_svc)
EXTERN(__exc_debug_monitor)
EXTERN(__stm32reservedexception13)
EXTERN(__exc_pendsv)
EXTERN(__exc_systick)

EXTERN(__irq_wwdg)
EXTERN(__irq_pvd)
EXTERN(__irq_tamper)
EXTERN(__irq_rtc)
EXTERN(__irq_flash)
EXTERN(__irq_rcc)
EXTERN(__irq_exti0)
EXTERN(__irq_exti1)
EXTERN(__irq_exti2)
EXTERN(__irq_exti3)
EXTERN(__irq_exti4)
EXTERN(__irq_dma1_channel1)
EXTERN(__irq_dma1_channel2)
EXTERN(__irq_dma1_channel3)
EXTERN(__irq_dma1_channel4)
EXTERN(__irq_dma1_channel5)
EXTERN(__irq_dma1_channel6)
EXTERN(__irq_dma1_channel7)
EXTERN(__irq_adc)
EXTERN(__irq_usb_hp_can_tx)
EXTERN(__irq_usb_lp_can_rx0)
EXTERN(__irq_can_rx1)
EXTERN(__irq_can_sce)
EXTERN(__irq_exti9_5)
EXTERN(__irq_tim1_brk)
EXTERN(__irq_tim1_up)
EXTERN(__irq_tim1_trg_com)
EXTERN(__irq_tim1_cc)
EXTERN(__irq_tim2)
EXTERN(__irq_tim3)
EXTERN(__irq_tim4)
EXTERN(__irq_i2c1_ev)
EXTERN(__irq_i2c1_er)
EXTERN(__irq_i2c2_ev)
EXTERN(__irq_i2c2_er)
EXTERN(__irq_spi1)
EXTERN(__irq_spi2)
EXTERN(__irq_usart1)
EXTERN(__irq_usart2)
EXTERN(__irq_usart3)
EXTERN(__irq_exti15_10)
EXTERN(__irq_rtcalarm)
EXTERN(__irq_usbwakeup)

EXTERN(__irq_tim8_brk)
EXTERN(__irq_tim8_up)
EXTERN(__irq_tim8_trg_com)
EXTERN(__irq_tim8_cc)
EXTERN(__irq_adc3)
EXTERN(__irq_fsmc)
EXTERN(__irq_sdio)
EXTERN(__irq_tim5)
EXTERN(__irq_spi3)
EXTERN(__irq_uart4)
EXTERN(__irq_uart5)
EXTERN(__irq_tim6)
EXTERN(__irq_tim7)
EXTERN(__irq_dma2_channel1)
EXTERN(__irq_dma2_channel2)
EXTERN(__irq_dma2_channel3)
EXTERN(__irq_dma2_channel4_5)


/* STM32 vector table. See stm32_vector_table.S  */
EXTERN(__cs3_stm32_vector_table)

/* libcs3 C start function. See cs3.h */
EXTERN(__cs3_start_c)

/* main entry point */
EXTERN(main)

/* Initial stack pointer value. */
EXTERN(__cs3_stack)
PROVIDE(__cs3_stack = __cs3_region_start_ram + LENGTH(ram));

/* Reset vector and chip reset entry point. See start.S */
EXTERN(_start)
PROVIDE(__cs3_reset = _start);

/* Heap boundaries, for libmaple */
EXTERN(_lm_heap_start);
EXTERN(_lm_heap_end);

SECTIONS
{
    /* TODO pull out rodata and stick into separate sections  */
    .text :
      {
        __text_start = .;
        /*
         * STM32 vector table.  Leave this here.  Yes, really.
         */
        *(.stm32.interrupt_vector)

        /*
         * Program code and vague linking
         */
        *(.text .text.* .gnu.linkonce.t.*)
        *(.plt)
        *(.gnu.warning)
        *(.glue_7t) *(.glue_7) *(.vfp11_veneer)

        *(.ARM.extab* .gnu.linkonce.armextab.*)
        *(.gcc_except_table)
        *(.eh_frame_hdr)
        *(.eh_frame)

        . = ALIGN(4);
        KEEP(*(.init))

        . = ALIGN(4);
        __preinit_array_start = .;
        KEEP (*(.preinit_array))
        __preinit_array_end = .;

        . = ALIGN(4);
        __init_array_start = .;
        KEEP (*(SORT(.init_array.*)))
        KEEP (*(.init_array))
        __init_array_end = .;

        . = ALIGN(0x4);
        KEEP (*crtbegin.o(.ctors))
        KEEP (*(EXCLUDE_FILE (*crtend.o) .ctors))
        KEEP (*(SORT(.ctors.*)))
        KEEP (*crtend.o(.ctors))

        . = ALIGN(4);
        KEEP(*(.fini))

        . = ALIGN(4);
        __fini_array_start = .;
        KEEP (*(.fini_array))
        KEEP (*(SORT(.fini_array.*)))
        __fini_array_end = .;

        KEEP (*crtbegin.o(.dtors))
        KEEP (*(EXCLUDE_FILE (*crtend.o) .dtors))
        KEEP (*(SORT(.dtors.*)))
        KEEP (*crtend.o(.dtors))

        /*
         * struct __cs3_region used during __cs3_start_c
         */
        . = ALIGN(4);
        __cs3_regions = .;
        LONG (0)                          /* flags */
        LONG (__cs3_region_init_ram)      /* initial contents */
        LONG (__cs3_region_start_ram)     /* start address */
        LONG (__cs3_region_init_size_ram) /* size of initial data */
        LONG (__cs3_region_zero_size_ram) /* additional size to be zeroed */
      } > REGION_TEXT

    /*
     * Read-only data
     */
    .rodata :
      {
        *(.rodata .rodata.* .gnu.linkonce.r.*)
      } > REGION_RODATA

    /*
     * .ARM.exidx exception unwinding; mandated by ARM's C++ ABI
     */
    __exidx_start = .;
    .ARM.exidx :
      {
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
      } > REGION_RODATA
    __exidx_end = .;

    /*
     * End of text
     */
    .text.align :
      {
        . = ALIGN(8);
        _etext = .;
      } > REGION_TEXT

    /*
     * .USER_FLASH: We allow users to allocate into Flash here
     */
    .USER_FLASH :
      {
        *(.USER_FLASH)
      } > REGION_RODATA

    /*
     * .data
     */
    .data :
      {
        __cs3_region_start_ram = DEFINED(_FLASH_BUILD) ? . : __text_start;

        *(.got.plt) *(.got)
        *(.data .data.* .gnu.linkonce.d.*)

        /*
         * Heap: Linker scripts may choose a custom heap by overriding
         * _lm_heap_start and _lm_heap_end. Otherwise, the heap is in
         * internal SRAM, beginning after .bss, and growing towards
         * the stack.
         *
         * I'm shoving these here naively; there's probably a cleaner way
         * to go about this. [mbolivar]
         */
        _lm_heap_start = DEFINED(_lm_heap_start) ? _lm_heap_start : _end;
        _lm_heap_end   = DEFINED(_lm_heap_end) ? _lm_heap_end : __cs3_stack;
        . = ALIGN (8);
        _edata = .;
      } > REGION_DATA AT> REGION_TEXT

    /*
     * .bss
     */
    .bss :
      {
        *(.bss .bss.* .gnu.linkonce.b.*)
        *(COMMON)
        . = ALIGN (8);
        _end = .;
      } > REGION_BSS AT> REGION_TEXT

    /*
     * Constants needed for the pieces of CS3 we use during
     * board startup; see libcs3_stm32_src/.
     */
    __cs3_region_init_ram = (DEFINED(_FLASH_BUILD) ?
                             LOADADDR(.data) :
                             LOADADDR(.text));
    __cs3_region_init_size_ram = (DEFINED(_FLASH_BUILD) ?
                                  _edata - ADDR(.data) :
                                  _edata - ADDR(.text));
    __cs3_region_zero_size_ram = _end - _edata;
    __cs3_region_num = 1;

    /*
     * Debugging sections
     */
    .stab 0 (NOLOAD) : { *(.stab) }
    .stabstr 0 (NOLOAD) : { *(.stabstr) }
    /* DWARF debug sections.
     * Symbols in the DWARF debugging sections are relative to the beginning
     * of the section so we begin them at 0.  */
    /* DWARF 1 */
    .debug          0 : { *(.debug) }
    .line           0 : { *(.line) }
    /* GNU DWARF 1 extensions */
    .debug_srcinfo  0 : { *(.debug_srcinfo) }
    .debug_sfnames  0 : { *(.debug_sfnames) }
    /* DWARF 1.1 and DWARF 2 */
    .debug_aranges  0 : { *(.debug_aranges) }
    .debug_pubnames 0 : { *(.debug_pubnames) }
    /* DWARF 2 */
    .debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
    .debug_abbrev   0 : { *(.debug_abbrev) }
    .debug_line     0 : { *(.debug_line) }
    .debug_frame    0 : { *(.debug_frame) }
    .debug_str      0 : { *(.debug_str) }
    .debug_loc      0 : { *(.debug_loc) }
    .debug_macinfo  0 : { *(.debug_macinfo) }
    /* SGI/MIPS DWARF 2 extensions */
    .debug_weaknames 0 : { *(.debug_weaknames) }
    .debug_funcnames 0 : { *(.debug_funcnames) }
    .debug_typenames 0 : { *(.debug_typenames) }
    .debug_varnames  0 : { *(.debug_varnames) }

    .note.gnu.arm.ident 0 : { KEEP (*(.note.gnu.arm.ident)) }
    .ARM.attributes 0 : { KEEP (*(.ARM.attributes)) }
    /DISCARD/ : { *(.note.GNU-stack) }
}

