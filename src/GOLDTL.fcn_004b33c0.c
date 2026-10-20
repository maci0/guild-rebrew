int __cdecl fcn_004b3010(int offset, int size, int* out, void* a0);
void __cdecl fcn_004b2e20(char* a1, int offset);

/* ADDRESS: GOLDTL 0x004b33c0 */
int __cdecl fcn_004b33c0(char* a0, char* a1)
{
	int v3;
	int v4[4];
	int v5;
	int diff;

	v3 = *(int*) 0x67fca8;
	do {
		if (!*(char*) 0x7728d4)
			return 3;
		if (!fcn_004b3010(v3, 3, v4, a0)) {
			*(char*) 0x7728d4 = 0;
			return 4;
		}
		diff = *(int*) 0x7f4c00 - v4[0];
		if (diff == 1) {
			v5 = 1;
			fcn_004b2e20(a1, *(int*) 0x67fca8 + 1);
			if (!*a1)
				v5 = 6;
		} else {
			if (diff <= 1)
				return 2;
			v5 = 0;
		}
		v3 = *(int*) 0x67fca8 + 3;
		*(int*) 0x67fca8 = v3;
		if (*(int*) 0x67fca4 < v3)
			*(char*) 0x7728d4 = 0;
	} while (!v5 || v5 == 6);
	return v5;
}
