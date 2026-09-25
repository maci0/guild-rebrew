// FUNCTION: GOLDTL 0x4cc710
// SIZE: 60

char* __cdecl fcn_00501510(int);
void __cdecl fcn_00506300(char*);

int __cdecl fcn_004cc710(char* a1, char* a2)
{
	char* p;

	p = fcn_00501510(*(int*) (a1 + 0x10));
	if (p == 0) {
		return 1;
	}
	fcn_00506300(p);
	if (a2 != 0) {
		a2[0] = 1;
		a2[1] = 0;
		*(int*) (a2 + 6) = 0;
	}
	return 0;
}
