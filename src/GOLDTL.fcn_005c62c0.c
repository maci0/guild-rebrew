// FUNCTION: GOLD 0x005ba850
// FUNCTION: GOLDTL 0x5c62c0

unsigned short* __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl fcn_005c61e0(unsigned int);

int __cdecl fcn_005c62c0(char* a, int b)
{
	unsigned short* e;

	e = fcn_00502cd0(0, 2, 7, 0, b);
	if (e != 0 && fcn_005c61e0(*e) != 0 && *(int*) ((char*) e + 0x21) != 0 &&
	    *(int*) ((char*) e + 0x25) == *(int*) (a + 1)) {
		return 1;
	}
	return 0;
}
