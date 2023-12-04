ENTRY(Reset_Handler)

MEMORY
{
RAM (xrw)      : ORIGIN = 0x20000000, LENGTH = 64K
FLASH (rx)      : ORIGIN = 0x8000000, LENGTH = 512K
}
_estack = ORIGIN(RAM) + LENGTH(RAM);
_Min_Heap_Size = 0x200;      /* required amount of heap  */
_Min_Stack_Size = 0x400; /* required amount of stack */

SECTIONS
{
  
  .text : {
	. = ALIGN(4);
	KEEP(*(.isr_vector))
	. = ALIGN(4);
	*(.text) 
	*(.text*)
  *(.glue_7)
  *(.glue_7t)
  *(.eh_frame)

	  KEEP (*(.init))
    KEEP (*(.fini))
  } > FLASH
  
  .rodata :{
	. = ALIGN(4);
	*(.rodata)
	*(.rodata*)
  } > FLASH
  
  .ARM :{
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
  } >FLASH
  
  .preinit_array     :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } >FLASH
  .init_array :
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
  } >FLASH
  .fini_array :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
  } >FLASH
  
  _sidata = LOADADDR(.data);
  .data :{
	. = ALIGN(4);
	_sdata = .;
	*(.data)
	*(.data*)
	. = ALIGN(4);
	_edata = .;
  }> RAM AT >FLASH

  .bss :{
	. = ALIGN(4);
	_sbss = .;
	__bss_start__ = _sbss;
	*(.bss)
	*(.bss*)
	*(COMMON)
	. = ALIGN(4);
	_ebss = .;
	__bss_end__ = _ebss;
  } > RAM
  
  ._user_heap_stack :{
	. = ALIGN(8);
	end = .;
	. += _Min_Heap_Size;
	. += _Min_Stack_Size;
	. = ALIGN(8);
  } > RAM
  
   /* Remove information from the standard libraries */
  /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  }
}