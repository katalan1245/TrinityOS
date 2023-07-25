#include <trinity/kheap.h>
#include <trinity/heap.h>
#include <trinity/config.h>
#include <trinity/print.h>

struct heap kernel_heap;
struct heap_table kernel_heap_table;

void kheap_init(void) {
    int total_table_entries = TRINITYOS_HEAP_SIZE_BYTES / TRINITYOS_HEAP_BLOCK_SIZE;
    kernel_heap_table.entries = (HEAP_BLOCK_TABLE_ENTRY *) TRINITYOS_HEAP_TABLE_ADDRESS;
    kernel_heap_table.total = total_table_entries;

    void *end = (void *)(TRINITYOS_HEAP_ADDRESS + TRINITYOS_HEAP_SIZE_BYTES);
    int res = heap_create(&kernel_heap, (void *) TRINITYOS_HEAP_ADDRESS, end, &kernel_heap_table);
    if (res < 0) {
        kprint("Failed to create heap\n");
    }
}

void *kmalloc(size_t size) {
    return heap_malloc(&kernel_heap, size);
}

void kfree(void *ptr) {
    return heap_free(&kernel_heap, ptr);
}