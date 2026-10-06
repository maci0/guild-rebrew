// FUNCTION: GOLDTL 0x4c9fa0

int __cdecl fcn_004e6a30(int);
int __cdecl fcn_004e6bd0(int, int);

int __cdecl fcn_004c9fa0(char* a1, char* a2)
{
	if (fcn_004e6a30(*(int*) (a1 + 0x10)) == 0) {
		return 1;
	}
	if (fcn_004e6bd0(*(int*) (a1 + 0x10), *(int*) (a1 + 0x14)) == 0) {
		return 1;
	}
	if (a2 != 0) {
		*a2 = 1;
	}
	return 0;
}
