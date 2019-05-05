#include <kernel/page.h>
#include <compiler.h>

// --------------------------------------------------------------
//         Only used in boot when paging isn't enabled
// --------------------------------------------------------------
static page_directory_t *page_directory_ptr BOOT_BSS_SECTION;
static page_tables_t *page_tables_ptr BOOT_BSS_SECTION;

static void page__map_page_table(uint32_t page_table_index) BOOT_SECTION;
static void page__map_high_half_pages() BOOT_SECTION;
static void page__enable_paging() BOOT_SECTION;

extern void page__setup() BOOT_SECTION;

// 1) setup directory entries (each points to a page table and all present)
// 2) all pages are not present except mapped pages (16M: including frame buffer 0xb8000 )
// 3) enable paging
void
page__setup() {
    page_directory_ptr = (page_directory_t *) va_to_pa(&page_directory);
    page_tables_ptr = (page_tables_t *) va_to_pa(&page_tables);
    for(uint32_t page_table_index = 0; page_table_index < 1024; ++page_table_index) {
        for(uint32_t page_index = 0; page_index < 1024; ++page_index) {
            (*page_tables_ptr)[page_table_index][page_index] = 0x00000002; // pages not present bit
        }
        addr_t page_table_pa = &(*page_tables_ptr)[page_table_index];
        (*page_directory_ptr)[page_table_index] = page_table_pa | 0x00000003; // page table present
    }
    page__map_high_half_pages();
    page__enable_paging();
}

static void
page__map_page_table(uint32_t page_table_index) {
    uint32_t page_table_physical_start = PHYSICAL_BASE + page_table_index * SIZE_PER_PAGE_TABLE;
    for(uint32_t page_index = 0; page_index < 1024; ++page_index) {
        uint32_t page_table_entry = (page_table_physical_start + page_index * SIZE_PER_PAGE) | 0x00000003;
        (*page_tables_ptr)[page_table_index][page_index] = page_table_entry;
        (*page_tables_ptr)[page_table_index + KERNEL_PAGE_TABLE_INDEX][page_index] = page_table_entry;
    }
}

static void
page__map_high_half_pages() {
    for(uint32_t page_table_index = 0; page_table_index < KERNEL_HIGH_HALF_SIZE; ++page_table_index) {
        page__map_page_table(page_table_index);
    }
}

static void
page__enable_paging() {
    asm volatile (
    "movl %0, %%eax  \n"
    "movl %%eax, %%cr3   \n"
    "movl %%cr0, %%eax   \n"
    "orl $0x80000000, %%eax \n"
    "movl %%eax, %%cr0"
    : : "r" (page_directory_ptr)
    );
}

extern void page__after_boot() {
    // recycle identity mapping
    for(uint32_t page_table_index = 0; page_table_index < KERNEL_HIGH_HALF_SIZE; ++page_table_index) {
        for(uint32_t page_index = 0; page_index < 1024; ++page_index) {
            page_tables[page_table_index][page_index] &= ~0x00000001;
        }
    }
}

