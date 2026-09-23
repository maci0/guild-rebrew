// FUNCTION: GOLD 0x004cb210
// SIZE: 59
// FUNCTION: GOLDTL 0x4cbda0
// SIZE: 59

int __cdecl fcn_004f5d00(int, int, int, int);

int __cdecl fcn_004cbda0(void* a1, char* a2)
{
	char b;

	b = 2;
	if (fcn_004f5d00(*(int*) ((char*) a1 + 0x10), *(int*) ((char*) a1 + 0x14),
	                 *(int*) ((char*) a1 + 0x18), *(int*) ((char*) a1 + 0x1c)) > 0) {
		b = 1;
	}
	if (a2 != 0) {
		a2[0] = b;
		a2[1] = 0;
		*(int*) (a2 + 6) = 0;
	}
	return 0;
}
