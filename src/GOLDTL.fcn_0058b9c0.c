// FUNCTION: GOLDTL 0x58b9c0
// SIZE: 90

void __cdecl fcn_0051af00(void*, int, ...);

void __cdecl fcn_0058b9c0(void* a1, void* a2)
{
	if (*(int*) ((char*) a1 + 0x2c) != 0) {
		if (*(int*) ((char*) a1 + 0x38) == 0) {
			fcn_0051af00(a2, 0x6a22d8,
			    *(int*) ((char*) a1 + 0x2c) + 0x253,
			    (char*) a1 + 4, (char*) a1 + 0x14);
		} else {
			fcn_0051af00(a2, 0x6a22d8,
			    *(int*) ((char*) a1 + 0x2c) + 0x27b,
			    (char*) a1 + 4, (char*) a1 + 0x14);
		}
	} else {
		fcn_0051af00(a2, 0x68b3f8, (char*) a1 + 4, (char*) a1 + 0x14);
	}
}
