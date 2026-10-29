int __cdecl fcn_0041dd90(int);

/* ADDRESS: GOLDTL 0x004e7340 */
void __cdecl fcn_004e7340(void)
{
	int off;
	char* base;
	int* p;

	for (off = 0; off < 0xc5440; off += 0x194) {
		base = *(char**) 0x6b5c20;
		if (base[off + 9] == 0) {
			continue;
		}
		p = *(int**) (base + off + 0x14);
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
