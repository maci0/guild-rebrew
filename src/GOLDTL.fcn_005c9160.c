// FUNCTION: GOLDTL 0x5c9160
// SIZE: 86

// SIZE 0x2f4
typedef struct {
	char pad0[0x18];
	int f18;
	char pad1[0x54];
	int f70;
	char pad2[0x280];
} Obj;

extern char* g_1015ea0;

int __cdecl fcn_0046fac0(int, int, int, int);
void __cdecl fcn_00472900(int, int);

void __cdecl fcn_005c9160(int a, int b, int c, int d, int e)
{
	int idx;

	idx = fcn_0046fac0(b - d, c, a, *(int*) 0x772514);
	((Obj*)g_1015ea0)[idx].f70 = 1;
	((Obj*)g_1015ea0)[idx].f18 = d;
	fcn_00472900(idx, e);
}
