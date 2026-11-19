extern unsigned char* lpGebaeudePROT;

int __cdecl fcn_00502cd0(int container_id, int arg_count, ...);

/* ADDRESS: GOLDTL 0x0050be50 */
int __cdecl fcn_0050be50(unsigned char* building, void** out)
{
	int slot_offset = 0x23;
	int mask;
	unsigned short* slot;
	unsigned char* base;
	void* store;
	int n;
	int i;

	n = 0;
	base = (unsigned char*) lpGebaeudePROT + building[0] * 0x24d;

	for (i = 0; i < 0x40; i++) { slot = (unsigned short*) (base + slot_offset) + i; if (*slot == 0) break;
		mask = *slot & 0x7fff;
		store = (void*) fcn_00502cd0(*(int*) (building + 0x5d), 2, 6, 0, mask);
		if (store != 0) {
			out[n++] = store;
		}
	}
	return n;
}
