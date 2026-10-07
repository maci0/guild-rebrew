// FUNCTION: GOLD 0x46ca50
// FUNCTION: GOLDTL 0x469900
// The volatile read of g_6b7fac orders it after the reload of g_772500, as
// in the reference.

typedef struct S00469900 {
	char pad0[0x30];
	int f30;
	char pad34[8];
	int f3c;
	int f40;
	int pad44;
	int f48;
	int f4c;
	int pad50;
} S00469900;
// SIZE 0x54

extern char* g_772500;
extern int g_6b7fac;

void __cdecl fcn_00469900(int i)
{
	S00469900* e;
	int kind;

	kind = ((S00469900*)g_772500)[i].f3c;
	e = &((S00469900*)g_772500)[i];
	if ((kind == 5 || kind == 8) && e->f30 == 0) {
		i = e->f4c;
	}
	((S00469900*)g_772500)[i].f40++;
	((S00469900*)g_772500)[i].f48 = *(volatile int*)&g_6b7fac;
}
