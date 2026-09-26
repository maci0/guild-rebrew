extern unsigned char g_773d75;

char* __cdecl fcn_00509570(int);
int __cdecl fcn_0050b710(int, char);

// FUNCTION: GOLD 0x004b48b0
// SIZE: 56
// FUNCTION: GOLDTL 0x4b4a20
// SIZE: 56

int __cdecl fcn_004b4a20(int id, char* thr)
{
	char* p;

	p = fcn_00509570(id);
	if (p == 0)
		return 0;
	return fcn_0050b710(*(int*) (p + 0x3c), (*(char*)&g_773d75)) > *(int*) (thr + 0x14);
}
