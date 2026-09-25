// FUNCTION: GOLD 0x004f7e40
// SIZE: 165
// FUNCTION: GOLDTL 0x004fa230
// SIZE: 165

extern char g_679060[];

int __cdecl fcn_005db460(void*, void*);
void __cdecl fcn_0051af00(void*, int, ...);

int __cdecl fcn_004fa230(void* a1, void* a2)
{
	int r;

	r = 0;
	*(char*) ((char*) a2 + 0x14) = 0;
	if (*(int*) a2 != 3 && *(int*) a2 != 1) {
		return 1;
	}
	if ((*(unsigned int*) ((char*) a1 + 0x1c8) & 0x100) != 0) {
		return 1;
	}
	if ((*(unsigned int*) ((char*) a1 + 0x1cc) & 0x200) == 0) {
		return 1;
	}
	if (*(char*) ((char*) a1 + 2) == 6) {
		fcn_0051af00((char*) a2 + 0x14, (int) g_679060, 0x1e15);
	}
	if ((*(unsigned int*) ((char*) a1 + 0x1c8) & 0x200) != 0) {
		return 9;
	}
	if ((*(unsigned int*) ((char*) a1 + 0x1c8) & 0x40000) != 0) {
		return 1;
	}
	if (*(int*) a2 == 3) {
		r = fcn_005db460(a1, a2);
	}
	return r | 2;
}
