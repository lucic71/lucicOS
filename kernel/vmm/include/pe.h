#ifndef PE_H_
#define PE_H_

#include <stdint.h>

/*
 * The following routines serve as a common interface for Page Directory and
 * Page Table entries.
 *
 */

/* Page Entry Flags. */

enum PE_FLAGS {

	PE_PRESENT		=	0x01,	  
	PE_WRITABLE		=   0x02,	  
	PE_USER			=   0x04,	  
	PE_PWT			=   0x08,	  
	PE_PCD			=   0x10, 
	PE_ACCESSED		=	0x20, 
	PE_DIRTY		=	0x40, 
	PE_4MB			=	0x80, 
	PE_CPU_GLOBAL	=	0x100,
	PE_LV4_GLOBAL	=	0x200,
   	PE_FRAME		=	0xFFFFF000

};

inline void pe_set_attr(uint32_t *e, uint32_t attr) { *e |= attr; }

inline void pe_unset_attr(uint32_t *e, uint32_t attr) { *e &= ~attr; }

void pe_set_frame(uint32_t *e, uint32_t addr) {
    *e = (*e & ~PE_FRAME) | (addr << 12);
}

inline uint32_t pe_get_frame (uint32_t e) { return e & PE_FRAME; }

inline int pe_is_present (uint32_t e) { return e & PE_PRESENT; }

inline int pe_is_writable (uint32_t e) { return e & PE_WRITABLE; }

inline int pe_is_user (uint32_t e) { return e & PE_USER; }

inline int pe_is_4mb (uint32_t e) { return e & PE_4MB; }

#endif
