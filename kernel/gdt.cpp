#include <gdt.h>

gdt_entry_t GDT::m_gdt_entries[5];
gdt_ptr_t   GDT::m_gdt_ptr;

extern "C"
{
    extern void gdt_flush(uint32_t);
}

void GDT::Init()
{
    /* We have 5 entries */
    m_gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
    /* Setting up pointer to our entries (ignore error) */
    m_gdt_ptr.base  = (uint32_t)&m_gdt_entries;
    
    _SetGate(0, 0, 0, 0, 0);                // Null segment
    _SetGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
    _SetGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
    _SetGate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
    _SetGate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment
    
    gdt_flush((uint32_t)&m_gdt_ptr);
}

void GDT::_SetGate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
   m_gdt_entries[num].base_low    = (base & 0xFFFF);
   m_gdt_entries[num].base_middle = (base >> 16) & 0xFF;
   m_gdt_entries[num].base_high   = (base >> 24) & 0xFF;
   m_gdt_entries[num].limit_low   = (limit & 0xFFFF);
   m_gdt_entries[num].granularity = (limit >> 16) & 0x0F;
   m_gdt_entries[num].granularity |= gran & 0xF0;
   m_gdt_entries[num].access      = access;
}
