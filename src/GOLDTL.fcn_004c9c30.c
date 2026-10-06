// FUNCTION: GOLD 0x4c9090
// FUNCTION: GOLDTL 0x4c9c30

int __cdecl fcn_004f5940(int, int);

int __cdecl fcn_004c9c30(char* a1, char* a2)
{
	switch (fcn_004f5940(*(int*) (a1 + 0x10), *(int*) (a1 + 0x14))) {
	case 1:
		return 1;
	case 2:
		return 2;
	case 3:
		return 3;
	}
	if (a2 != 0) {
		*a2 = 1;
	}
	return 0;
}
