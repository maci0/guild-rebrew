int __cdecl fcn_004b3010(int, int, int*, int);
int __cdecl fcn_004b2dd0(char*, int, int);

/* ADDRESS: GOLDTL 0x004b3720 */
int __cdecl fcn_004b3720(int a0, char* a1, int a2)
{
	int pos;
	int result;
	int slot[4];

	pos = *(int*) 0x67fca8;
	for (;;) {
		if (*(char*) 0x7728d4 == 0) {
			return 3;
		}
		if (!fcn_004b3010(pos, 3, slot, a0)) {
			*(char*) 0x7728d4 = 0;
			return 4;
		}
		if (*(int*) 0x7f4c00 - slot[0] != 1) {
			if (*(int*) 0x7f4c00 - slot[0] <= 1) {
				return 2;
			}
			result = 0;
		} else {
			pos = fcn_004b2dd0(a1, *(int*) 0x67fca8, a2);
			if (pos) {
				result = 1;
				if (*a1 == 0) {
					result = 6;
				}
			} else {
				result = 5;
			}
		}
		pos = *(int*) 0x67fca8 + 3;
		*(int*) 0x67fca8 = pos;
		if (*(int*) 0x67fca4 < pos) {
			*(char*) 0x7728d4 = 0;
		}
		if (result != 0 && result != 6 && result != 5) {
			break;
		}
	}
	return result;
}
