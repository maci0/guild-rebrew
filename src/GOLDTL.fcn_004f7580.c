// FUNCTION: GOLD 0x004f5190
// SIZE: 104
// FUNCTION: GOLDTL 0x4f7580
// SIZE: 104

int  __cdecl fcn_005d5930(void*, void*);
extern char g_679060[];
void __cdecl fcn_0051af00(void*, int, int);

int __cdecl fcn_004f7580(void* a1, void* a2)
{
	int v;

	v = *(int*) a2;
	if (v != 3 && v != 1) {
		return 1;
	}
	if (*(int*) ((char*) a1 + 0x1c8) & 0x100) {
		return 1;
	}
	if (v == 3) {
		fcn_005d5930(a1, a2);
		return 2;
	}
	if (v == 1 && *(char*) ((char*) a1 + 2) == 6) {
		fcn_0051af00((char*) a2 + 0x14, (int) g_679060, 0x1d54);
	}
	return 2;
}
