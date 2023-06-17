#include "gdt.h"
#include "vga.h"

// Defined in asm
extern void gdtFlush(u32);
extern void idtFlush(u32);

static void initGdt();
static void gdtSetGate(i32, u32, u32, u8, u8);

static void initIdt();
static void idtSetGate(u8, u32, u16, u8);

GdtEntry   gdtEntries[5];
GdtPointer gdtPtr;
IdtEntry   idtEntries[256];
IdtPointer idtPtr;

void initDescriptorTables() {
	initGdt();
	initIdt();
}

static void initGdt() {
	gdtPtr.limit = (sizeof(GdtEntry) * 5) - 1;
	gdtPtr.base  = (u32)&gdtEntries;

	gdtSetGate(0, 0, 0, 0, 0);                // Null segment
	gdtSetGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
	gdtSetGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
	gdtSetGate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
	gdtSetGate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

	gdtFlush((u32)&gdtPtr);
}
 
static void gdtSetGate(i32 num, u32 base, u32 limit, u8 access, u8 gran) {
   gdtEntries[num].base_low    = (base & 0xFFFF);
   gdtEntries[num].base_middle = (base >> 16) & 0xFF;
   gdtEntries[num].base_high   = (base >> 24) & 0xFF;

   gdtEntries[num].limit_low   = (limit & 0xFFFF);
   gdtEntries[num].granularity = (limit >> 16) & 0x0F;

   gdtEntries[num].granularity |= gran & 0xF0;
   gdtEntries[num].access      = access;
}

static void initIdt() {
	idtPtr.limit = sizeof(IdtEntry) * 256 -1;
	idtPtr.base  = (u32)&idtEntries;

	memset(&idtEntries, 0, sizeof(IdtEntry)*256);

	idtSetGate(0,  (u32)isr0  , 0x08, 0x8E);
	idtSetGate(1,  (u32)isr1  , 0x08, 0x8E);
	idtSetGate(2,  (u32)isr2  , 0x08, 0x8E);
	idtSetGate(3,  (u32)isr3  , 0x08, 0x8E);
	idtSetGate(4,  (u32)isr4  , 0x08, 0x8E);
	idtSetGate(5,  (u32)isr5  , 0x08, 0x8E);
	idtSetGate(6,  (u32)isr6  , 0x08, 0x8E);
	idtSetGate(7,  (u32)isr7  , 0x08, 0x8E);
	idtSetGate(8,  (u32)isr8  , 0x08, 0x8E);
	idtSetGate(9,  (u32)isr9  , 0x08, 0x8E);
	idtSetGate(10, (u32)isr10 , 0x08, 0x8E);
	idtSetGate(11, (u32)isr11 , 0x08, 0x8E);
	idtSetGate(12, (u32)isr12 , 0x08, 0x8E);
	idtSetGate(13, (u32)isr13 , 0x08, 0x8E);
	idtSetGate(14, (u32)isr14 , 0x08, 0x8E);
	idtSetGate(15, (u32)isr15 , 0x08, 0x8E);
	idtSetGate(16, (u32)isr16 , 0x08, 0x8E);
	idtSetGate(17, (u32)isr17 , 0x08, 0x8E);
	idtSetGate(18, (u32)isr18 , 0x08, 0x8E);
	idtSetGate(19, (u32)isr19 , 0x08, 0x8E);
	idtSetGate(20, (u32)isr20 , 0x08, 0x8E);
	idtSetGate(21, (u32)isr21 , 0x08, 0x8E);
	idtSetGate(22, (u32)isr22 , 0x08, 0x8E);
	idtSetGate(23, (u32)isr23 , 0x08, 0x8E);
	idtSetGate(24, (u32)isr24 , 0x08, 0x8E);
	idtSetGate(25, (u32)isr25 , 0x08, 0x8E);
	idtSetGate(26, (u32)isr26 , 0x08, 0x8E);
	idtSetGate(27, (u32)isr27 , 0x08, 0x8E);
	idtSetGate(28, (u32)isr28 , 0x08, 0x8E);
	idtSetGate(29, (u32)isr29 , 0x08, 0x8E);
	idtSetGate(30, (u32)isr30 , 0x08, 0x8E);
	idtSetGate(31, (u32)isr31 , 0x08, 0x8E);

	idtFlush((u32)&idtPtr);
}

static void idtSetGate(u8 num, u32 base, u16 sel, u8 flags) {
   idtEntries[num].base_lo = base & 0xFFFF;
   idtEntries[num].base_hi = (base >> 16) & 0xFFFF;

   idtEntries[num].sel     = sel;
   idtEntries[num].always0 = 0;
   // We must uncomment the OR below when we get to using user-mode.
   // It sets the interrupt gate's privilege level to 3.
   idtEntries[num].flags   = flags /* | 0x60 */;
}

void isrHandler(Registers regs) {
	VgaContext vga;
	initVga(&vga.vgaBuffer, VGA_RED, VGA_BLACK);
	print(&vga, "Received interrupt: ");
	printNum(&vga, regs.intNo);
	print(&vga, "\n");
} 

