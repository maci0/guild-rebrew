
/* ADDRESS: GOLDTL 0x0050dfd0 */
/* 52 native calls supply an unused second dword; int is an inferred carrier. */
/* ADDRESS: GOLDDE 0x004f8d20 */
int __cdecl gm_GetStorageSlotCapacity(char* slot, int unused)
{
	int n;

	if (*(unsigned short*) slot == 0x1dd) {
		n = *(int*) (slot + 0xe);
		return (n + 2) * 5;
	}
	n = *(int*) (slot + 0xe);
	if (n == 3) {
		return 0x50;
	}
	return n * 20;
}

typedef struct STORAGE_SLOT STORAGE_SLOT;
struct STORAGE_SLOT {
    unsigned char pad_000[0x14];
    int id;
    unsigned char pad_018[4];
    unsigned char f1c;
};

extern int __cdecl gm_GetStorageSlotCapacity(char* slot, int unused);
extern unsigned short* __cdecl gm_QueryEntities(int container_id, int arg_count, ...);
extern int __cdecl gm_NextEntityQueryMatch(void);

/* ADDRESS: GOLDTL 0x0050e170 */
/* ADDRESS: GOLDDE 0x004f8ec0 */
int __cdecl gm_GetFreeStorageSlotCapacity(STORAGE_SLOT* slot, int itemId, int maxAmount)
{
    int total;
    unsigned short* found;
    int i;

    total = gm_GetStorageSlotCapacity((char*) slot, itemId);
    found = gm_QueryEntities(slot->id, 1, 0, itemId);
    if (found != 0) {
        if (total - *(int*) ((char*) found + 0xe) > maxAmount) {
            return maxAmount;
        }
        return total - *(int*) ((char*) found + 0xe);
    }
    i = 0;
    if (gm_QueryEntities(slot->id, 1, 5) != 0) {
        do {
            i++;
        } while (gm_NextEntityQueryMatch() != 0);
    }
    if (i >= (int) slot->f1c) {
        return 0;
    }
    if (total >= maxAmount) {
        return maxAmount;
    }
    return total;
}
