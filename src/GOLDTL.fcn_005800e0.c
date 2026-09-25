// FUNCTION: GOLDTL 0x5800e0
// SIZE: 91

void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_00519190(void*);

int __cdecl fcn_005800e0(void)
{
	char* p;

	p = *(char**) (*(int*) 0x665f08 + 0x1c);
	if (p == 0) {
		return -4;
	}
	p = *(char**) (p + 0x74);
	if (p == 0) {
		return -4;
	}
	fcn_004727a0(*(int*) (p + 8), 1);
	fcn_00519190((void*) 0x6811b0);
	fcn_004727a0(*(int*) (*(int*) (*(int*) (*(int*) 0x665f08 + 0x1c) + 0x74) + 8), 2);
	fcn_00519190((void*) 0x6811b0);
	return 0;
}
