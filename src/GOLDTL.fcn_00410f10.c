// FUNCTION: GOLDTL 0x00410f10
// SIZE: 64

extern char* g_6b7e98;
extern int g_6791c8;
int __cdecl fcn_00422460(int a, int b);
int __cdecl fcn_00423670(int o, int a, int b);

int __cdecl fcn_00410f10(int* a, int* b)
{
	int o;

	if (*(int*) (g_6b7e98 + 0x104) != g_6791c8) {
		return 0;
	}
	o = fcn_00422460(*a, *b);
	if (o == 0) {
		return o;
	}
	return fcn_00423670(o, 0, 0);
}
