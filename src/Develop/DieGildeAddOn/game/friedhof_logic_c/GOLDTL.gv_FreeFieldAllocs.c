// FUNCTION: GOLDTL 0x4f2290
// SIZE: 66

extern void __cdecl m_FreeTracked(void* ptr);

/* Frees a field slot's three allocations: the worker table at +0x1c, the
 * entry table at +0x20, then the slot itself.  The client's gv_UpgradeField
 * (0x4f2060) calls this; the +0x24/+0x28 variant that gv_Free3Fields
 * (0x45b790) frees belongs to a different structure. */

void __cdecl gv_FreeFieldAllocs(int* slot)
{
	if (slot == 0) {
		return;
	}
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
