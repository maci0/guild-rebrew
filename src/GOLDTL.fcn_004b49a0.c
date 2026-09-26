extern unsigned char g_773d75;

char* __cdecl fcn_00509570(int);
int __cdecl fcn_0050b710(int, char);

// FUNCTION: GOLD 0x004b4830
// SIZE: 59
// FUNCTION: GOLDTL 0x4b49a0
// SIZE: 59

int __cdecl fcn_004b49a0(int id, char* thr)
{
	char* p;

	p = fcn_00509570(id);
	if (p == 0)
		return 0;
	return fcn_0050b710(*(int*) (p + 0x34) + *(int*) (p + 0x2c), (*(char*)&g_773d75)) > *(int*) (thr + 0x14);
}
