/* gv_Free3Fields - proper C */

// CFLAGS: /O2 /Gd
// FUNCTION: SERVER 0x10010f50
// SYMBOL: _gv_Free3Fields
// SIZE: 66

extern void __cdecl m_FreeTracked(void* ptr);

/* Frees a 3-field slot: releases the two tracked pointers at
 * +0x1c and +0x20 (if set), then the slot itself. */

void __cdecl gv_Free3Fields(int* slot)
{
	if (slot == 0)
		return;
	if (slot[7] != 0) {
		m_FreeTracked((void*) slot[7]);
		slot[7] = 0;
	}
	if (slot[8] != 0) {
		m_FreeTracked((void*) slot[8]);
		slot[8] = 0;
	}
	m_FreeTracked((void*) slot);
}
