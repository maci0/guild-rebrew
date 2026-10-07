// FUNCTION: GOLD 0x004ef170
// FUNCTION: GOLDTL 0x004f10d0

int __cdecl fcn_00502cd0(int a, int b, int c, int d, int e);

void __cdecl fcn_004f10d0(char* p, int* a, int* b)
{
	*b = 0;
	*a = 0;
	if (fcn_00502cd0(*(int*) (p + 0x5d), 2, 6, 0, 0x265)) {
		*a = 2;
	} else {
		*a = fcn_00502cd0(*(int*) (p + 0x5d), 2, 6, 0, 0x263) != 0;
	}
	if (fcn_00502cd0(*(int*) (p + 0x5d), 2, 6, 0, 0x264)) {
		*b = 4;
	} else if (fcn_00502cd0(*(int*) (p + 0x5d), 2, 6, 0, 0x262)) {
		*b = 3;
	} else if (fcn_00502cd0(*(int*) (p + 0x5d), 2, 6, 0, 0x25e)) {
		*b = 2;
	} else {
		*b = fcn_00502cd0(*(int*) (p + 0x5d), 2, 6, 0, 0x25a) != 0;
	}
}
