// FUNCTION: GOLDTL 0x4f76d0
// SIZE: 102

int  __cdecl fcn_005d63e0(void*, void*);
void __cdecl fcn_0051af00(void*, int, int);

int __cdecl fcn_004f76d0(void* a1, void* a2)
{
	int v;

	v = *(int*) a2;
	if (v != 3 && v != 1) {
		return 1;
	}
	if (*(unsigned char*) ((char*) a1 + 0xd) < 3) {
		return 1;
	}
	if (v == 3) {
		fcn_005d63e0(a1, a2);
		return 2;
	}
	if (v == 1 && *(char*) ((char*) a1 + 2) == 6) {
		fcn_0051af00((char*) a2 + 0x14, 0x679060, 0x1d60);
	}
	return 2;
}
