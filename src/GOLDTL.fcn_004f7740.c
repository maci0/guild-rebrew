// FUNCTION: GOLDTL 0x4f7740
// SIZE: 107

void __cdecl fcn_005d6030(void*, void*);
void __cdecl fcn_0051af00(void*, int, int);

int __cdecl fcn_004f7740(void* a1, void* a2)
{
	int v;

	v = *(int*) a2;
	if (v == 3 || v == 1) {
		if (*(unsigned char*) ((char*) a1 + 0xd) >= 3 &&
		    (*(int*) ((char*) a1 + 0x1c8) & 0x400) == 0) {
			if (v == 3) {
				fcn_005d6030(a1, a2);
				return 2;
			}
			if (v == 1 && *(char*) ((char*) a1 + 2) == 6) {
				fcn_0051af00((char*) a2 + 0x14, 0x679060, 0x1d65);
			}
			return 2;
		}
	}
	return 1;
}
