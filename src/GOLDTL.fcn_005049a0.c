extern unsigned char* g_868050;
extern char* g_99ec10;

int __cdecl fcn_00504bd0(int);
int __cdecl fcn_00505370(unsigned char*);
int __cdecl fcn_00502cd0(int, int, int, int);

/* ADDRESS: GOLDTL 0x005049a0 */

int __cdecl fcn_005049a0(unsigned char* building)
{
	unsigned char* type;
	unsigned short* slot;
	volatile int found;
	int category;
	int item;
	int i;

	found = 0;
	category = fcn_00504bd0(building[0]);
	type = g_868050 + building[0] * 0x24d;
	if (category == 1 || category == 7 || category == 8) {
		if (type[0] == 0x1d) {
			found = fcn_00502cd0(*(int*) (building + 0x5d), 1, 0, 0x205);
		} else if (type[0] == 0x16) {
			found = fcn_00502cd0(*(int*) (building + 0x5d), 1, 0, 0x12e);
		} else if (type[0] == 4) {
			found = fcn_00502cd0(*(int*) (building + 0x5d), 1, 0, 0x54);
		} else if (type[0] == 0x1f) {
			found = fcn_00502cd0(*(int*) (building + 0x5d), 1, 0, 0xfd);
		}
		if (found != 0) {
			return found;
		}
		slot = (unsigned short*) (type + 0x23);
		for (i = 0; i < 0x40; i++, slot++) {
			if (*slot != 0xffff) {
				item = *slot & 0x7fff;
				if ((g_99ec10 + item * 64)[item] == 2 && item != 0xfd) {
					return fcn_00502cd0(*(int*) (building + 0x5d), 1, 0, item);
				}
			}
		}
		return found;
	}
	if (category == 4) {
		return fcn_00502cd0(*(int*) (building + 0x5d), 1, 0, 0xf7);
	}
	if (fcn_00505370(building) != 0) {
		return fcn_00502cd0(*(int*) (building + 0x5d), 1, 0, 0xfd);
	}
	slot = (unsigned short*) (type + 0x23);
	for (i = 0; i < 0x40; i++, slot++) {
		if (*slot != 0xffff) {
			item = *slot & 0x7fff;
			if ((g_99ec10 + item * 64)[item] == 2 && item != 0xfd) {
				return fcn_00502cd0(*(int*) (building + 0x5d), 1, 0, item);
			}
		}
	}
	return found;
}
