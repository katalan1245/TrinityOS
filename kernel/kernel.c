#include <trinity/kernel.h>
#include <trinity/vga.h>
#include <trinity/idt.h>
#include <trinity/print.h>
#include <trinity/kheap.h>

void kernel_main(void) {
    clear_screen();
    kprint("TrinityOS\n");
    kheap_init();

    // Initialize the interrupt descriptor table
    idt_init();

    // Enable system interrupts
    enable_interrupts();
}