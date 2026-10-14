/* gv_Free3Fields - proper C */




extern void __cdecl m_FreeTracked(void* ptr);

/* Frees a 3-field slot: releases the two tracked pointers at
 * +0x24 and +0x28 (if set), then the slot itself. */

void __cdecl gv_Free3Fields(int* slot)
{
	if (slot == 0)
		return;
	if (slot[9] != 0) {
		m_FreeTracked((void*) slot[9]);
		slot[9] = 0;
	}
	if (slot[0xa] != 0) {
		m_FreeTracked((void*) slot[0xa]);
		slot[0xa] = 0;
	}
	m_FreeTracked((void*) slot);
}
