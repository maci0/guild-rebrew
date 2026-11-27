typedef struct {
	int kind;
	char pad[16];
} SLOT_ENTRY;
// SIZE 0x14

/* ADDRESS: GOLDTL 0x004f1790 */
int __cdecl gm_GetEntitySlotIndex(char* a, SLOT_ENTRY* e)
{
	if (e->kind == 0) {
		return e - *(SLOT_ENTRY**) (a + 8);
	}
	if (e->kind == 1) {
		return e - *(SLOT_ENTRY**) (a + 0xc);
	}
	if (e->kind == 2) {
		return e - *(SLOT_ENTRY**) (a + 0x10);
	}
	if (e->kind == 3) {
		return e - *(SLOT_ENTRY**) (a + 0x14);
	}
	return -1;
}
