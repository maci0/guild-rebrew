typedef struct {
	int kind;
	char pad[16];
} SLOT_ENTRY;
// SIZE 0x14

/* ADDRESS: GOLDTL 0x004f1790 */
int __cdecl gm_GetEntitySlotIndex(char* owner, SLOT_ENTRY* entry)
{
	if (entry->kind == 0) {
		return entry - *(SLOT_ENTRY**) (owner + 8);
	}
	if (entry->kind == 1) {
		return entry - *(SLOT_ENTRY**) (owner + 0xc);
	}
	if (entry->kind == 2) {
		return entry - *(SLOT_ENTRY**) (owner + 0x10);
	}
	if (entry->kind == 3) {
		return entry - *(SLOT_ENTRY**) (owner + 0x14);
	}
	return -1;
}
