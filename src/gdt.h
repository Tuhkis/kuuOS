#ifndef GDT_H
#define GDT_H

#include "kernel.h"

typedef struct {
	u16 limit_low;           // The lower 16 bits of the limit.
	u16 base_low;            // The lower 16 bits of the base.
	u8  base_middle;         // The next 8 bits of the base.
	u8  access;              // Access flags, determine what ring this segment can be used in.
	u8  granularity;
	u8  base_high;           // The last 8 bits of the base.
} __attribute__((packed)) GdtEntry;

typedef struct {
	u16 limit;
	u32 base;
} __attribute__((packed)) GdtPointer;

typedef struct {
	u16 base_lo;             // The lower 16 bits of the address to jump to when this interrupt fires.
	u16 sel;                 // Kernel segment selector.
	u8  always0;             // This must always be zero.
	u8  flags;               // More flags. See documentation.
	u16 base_hi;             // The upper 16 bits of the address to jump to.
} __attribute__((packed)) IdtEntry;

typedef struct {
	u16 limit;
	u32 base; // The address of the first element in our idt_entry_t array.
} __attribute__((packed)) IdtPointer;

void initDescriptorTables(); 
extern void isr0 ();
extern void isr1 ();
extern void isr2 ();
extern void isr3 ();
extern void isr4 ();
extern void isr5 ();
extern void isr6 ();
extern void isr7 ();
extern void isr8 ();
extern void isr9 ();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

typedef struct {
   u32 ds;                  // Data segment selector
   u32 edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
   u32 intNo, errCode;    // Interrupt number and error code (if applicable)
   u32 eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
} Registers;

#endif // GDT_H
