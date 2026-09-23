// FUNCTION: GOLDTL 0x4f7460
// SIZE: 119

int  __cdecl fcn_005d4fa0(void*, void*);
void __cdecl fcn_0051af00(void*, int, int);

int __cdecl fcn_004f7460(void* a1, void* a2)
{
	int v;

	v = *(int*) a2;
	if (v == 3 || v == 1) {
		if ((*(char*) ((char*) a1 + 0x1c8) & 0x40) == 0) {
			if ((double) *(int*) ((char*) a1 + 0x24) < *(double*) 0x6653c8 ||
			    (*(int*) ((char*) a1 + 0x2c) & 0xfffffff0) != 0) {
				if (v == 3) {
					return fcn_005d4fa0(a1, a2);
				}
				if (v == 1 && *(char*) ((char*) a1 + 2) == 6) {
					fcn_0051af00((char*) a2 + 0x14, 0x679060, 0x1d3a);
				}
				return 2;
			}
		}
	}
	return 1;
}
