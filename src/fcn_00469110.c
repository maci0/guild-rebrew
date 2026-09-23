// GLOBAL: GOLDTL 0x1015ea0
extern char* g_1015ea0;
// FUNCTION: GOLDTL 0x469110
// SIZE: 40

void __cdecl fcn_00469090(int);

void __cdecl fcn_00469110(int a1, int a2)
{
	*(int*) ((char*) g_1015ea0 + a1 * 0x2f4 + 0x18) = a2;
	fcn_00469090(a1);
}
