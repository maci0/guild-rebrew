#ifndef D2_CAPACITY_H
#define D2_CAPACITY_H

/* Entry count shared by the d2 GUI element table (g_1015ea0, 0x2f4-byte records),
 * its z-order list (g_772540) and the dirty-rectangle list (g_772588).
 * The German v2.06 client (GOLDDE) has 768 entries: its natives compare against
 * 0x300/0x2ff, clear slot 0xbfc and bound the element table at 0x8dc00; the
 * English clients use 1024 (0x400/0x3ff, 0xffc, 0xbd000). Inferred name; the
 * original identifier is not attested. */
#if defined(REBREW_GOLDDE)
#define d2_ELEMENT_CAPACITY 0x300
#else
#define d2_ELEMENT_CAPACITY 0x400
#endif

#endif
