[GLOBAL gdtFlush]    ; Allows the C code to call gdt_flush().

gdtFlush:
	mov eax, [esp+4]  ; Get the pointer to the GDT, passed as a parameter.
	lgdt [eax]        ; Load the new GDT pointer

	mov ax, 0x10      ; 0x10 is the offset in the GDT to our data segment
	mov ds, ax        ; Load all data segment selectors
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:.flush   ; 0x08 is the offset to our code segment: Far jump!
.flush:
	ret

[GLOBAL idtFlush]    ; Allows the C code to call idt_flush().

idtFlush:
   mov eax, [esp+4]  ; Get the pointer to the IDT, passed as a parameter.
   lidt [eax]        ; Load the IDT pointer.
   ret

[EXTERN isrHandler]

; This is our common ISR stub. It saves the processor state, sets
; up for kernel mode segments, calls the C-level fault handler,
; and finally restores the stack frame.
isrCommonStub:
   pusha                    ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax

   mov ax, ds               ; Lower 16-bits of eax = ds.
   push eax                 ; save the data segment descriptor

   mov ax, 0x10  ; load the kernel data segment descriptor
   mov ds, ax
   mov es, ax
   mov fs, ax
   mov gs, ax

   call isrHandler

   pop eax        ; reload the original data segment descriptor
   mov ds, ax
   mov es, ax
   mov fs, ax
   mov gs, ax

   popa                     ; Pops edi,esi,ebp...
   add esp, 8     ; Cleans up the pushed error code and pushed ISR number
   sti
   iret           ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP

 %macro ISR_NOERRCODE 1  ; define a macro, taking one parameter
  [GLOBAL isr%1]        ; %1 accesses the first parameter.
  isr%1:
    cli
    push byte 0
    push byte %1
    jmp isrCommonStub
%endmacro

%macro ISR_ERRCODE 1
  [GLOBAL isr%1]
  isr%1:
    cli
    push byte %1
    jmp isrCommonStub
%endmacro

ISR_NOERRCODE 0 
ISR_NOERRCODE 1 
ISR_NOERRCODE 2 
ISR_NOERRCODE 3 
ISR_NOERRCODE 4 
ISR_NOERRCODE 5 
ISR_NOERRCODE 6 
ISR_NOERRCODE 7 
ISR_NOERRCODE 8 
ISR_NOERRCODE 9 
ISR_NOERRCODE 10
ISR_NOERRCODE 11
ISR_NOERRCODE 12
ISR_NOERRCODE 13
ISR_NOERRCODE 14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31

