// GLOBAL: GOLDTL 0x67dae0
extern char g_67dae0[];
// GLOBAL: GOLDTL 0x67dad4
extern char g_67dad4[];
// GLOBAL: GOLDTL 0x67dac4
extern char g_67dac4[];
// FUNCTION: GOLDTL 0x47abd0
// SIZE: 73

void* __cdecl fcn_0041db70(int, char*);

void* __cdecl fcn_0047abd0(int a1, int a2, int a3)
{
	void* p;

	p = fcn_0041db70(0x38, g_67dae0);
	*(int*) ((char*) p + 0x24) = a1;
	*(int*) ((char*) p + 0x28) = (int) fcn_0041db70(a1 * 4, g_67dad4);
	*(int*) ((char*) p + 0x2c) = a2;
	*(int*) ((char*) p + 0x30) = (int) fcn_0041db70(a2 * 12, g_67dac4);
	return p;
}
