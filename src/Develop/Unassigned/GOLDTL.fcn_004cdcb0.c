


char* __cdecl cut_FindCutsceneById(int);

int __cdecl fcn_004cdcb0(char* a1, char* a2)
{
	char* p;

	if (a2 != 0) {
		a2[0] = 2;
		a2[1] = 0;
		*(int*) (a2 + 6) = 0;
	}
	p = cut_FindCutsceneById(*(int*) (a1 + 0x10));
	if (p == 0) {
		return 1;
	}
	*(int*) (p + 0xc) = *(int*) (a1 + 0x14);
	if (a2 != 0) {
		*a2 = 1;
	}
	return 0;
}
