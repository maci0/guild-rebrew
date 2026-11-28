typedef struct {
	char pad0[0xd];
	unsigned char state;
	char padE[0x6];
	void* obj;
} SUBTREE_SLOT_ENTRY;
// SIZE 0x18

void __cdecl d3_SetSubtreeVisible(void*, int);


/* ADDRESS: GOLDTL 0x004bd1a0 */
/* ADDRESS: GOLDDE 0x004ab020 */
void __cdecl d3_HideSubtreeEntries(SUBTREE_SLOT_ENTRY* slots)
{
	int i;

	if (slots != 0) {
		for (i = 0; i < 64; i++) {
			if (slots[i].state != 0xff && slots[i].obj != 0)
				d3_SetSubtreeVisible(slots[i].obj, 0);
		}
	}
}
