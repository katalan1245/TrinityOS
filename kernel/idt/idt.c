#include <trinity/idt.h>
#include <trinity/config.h>
#include <trinity/string.h>
#include <trinity/print.h>
#include <trinity/kernel.h>
#include <trinity/io.h>

struct idt_desc idt_descriptors[TRINITYOS_NUM_INTERRUPTS];
struct idtr_desc idtr_descriptor;

extern void idt_load(struct idtr_desc *ptr);
extern void int21h(void);
extern void no_interrupt(void);

void int21h_handler(void) {
    kprint("Keyboard pressed!\n");
    outb(0x20, 0x20);
}

void no_interrupt_handler(void) {
    outb(0x20, 0x20);
}

void idt_zero(void) {
    kprint("Divide by zero error!\n");
}

void idt_set(uint8_t interrupt_no, void *address) {
    struct idt_desc *desc = &idt_descriptors[interrupt_no];
    desc->offset_1 = (uint32_t) address & 0x0000ffff;
    desc->selector = KERNEL_CODE_SELECTOR;
    desc->zero = 0x00;
    desc->type_attr = 0xee;
    desc->offset_2 = (uint32_t) address >> 16;
}

void idt_init(void) {
    memset(idt_descriptors, 0, sizeof(idt_descriptors));
    idtr_descriptor.limit = sizeof(idt_descriptors) - 1;
    idtr_descriptor.base = (uint32_t) idt_descriptors;

    // Set all IDT
    for (int i = 0; i < TRINITYOS_NUM_INTERRUPTS; ++i) {
        idt_set(i, no_interrupt);
    }

    idt_set(0, idt_zero);
    idt_set(0x21, int21h);

    // Load the interrupt descriptor table
    idt_load(&idtr_descriptor);
}