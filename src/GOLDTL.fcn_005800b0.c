// FUNCTION: GOLD 0x00577ae0
// SIZE: 43
// FUNCTION: GOLDTL 0x5800b0
// SIZE: 43

extern int* g_665f08;

void __cdecl fcn_00545780(void*);

int __cdecl fcn_005800b0(void)
{
	char* p;

	p = *(char**) ((int) g_665f08 + 0x1c);
	if (p == 0) {
		return -4;
	}
	if (*(int*) (p + 0x74) == 0) {
		return -4;
	}
	fcn_00545780(p);
	return 0;
}
