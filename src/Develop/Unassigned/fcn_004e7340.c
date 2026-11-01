int __cdecl fcn_0041dd90(int);

/* ADDRESS: GOLDTL 0x004e7340 */
void __cdecl fcn_004e7340(void)
{
	int row;
	char* base;
	int* p;

	for (row = 0; row < 0x7d0; row++) {
		base = *(char**) 0x6b5c20;
		if (base[row * 0x194 + 9] == 0) {
			continue;
		}
		p = *(int**) (base + row * 0x194 + 0x14);
		if (p == 0) {
			continue;
		}
		if (!fcn_0041dd90((int) p)) {
			__asm { int 3 }
		}
		p = *(int**) ((char*) p + 0x34);
		if (p == 0) {
			continue;
		}
		if (!fcn_0041dd90((int) p)) {
			__asm { int 3 }
		}
	}
}
