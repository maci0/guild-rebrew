// FUNCTION: GOLDTL 0x4faa90
// SIZE: 85
// FUNCTION: GOLD 0x004f86a0
// SIZE: 85

extern char g_1043370[];

unsigned short __cdecl fcn_0042e410(int);
void __cdecl fcn_0045b920(char*, int, int, int);

void __cdecl fcn_004faa90(int x, int y, int c)
{
	char* g;
	int d;
	int a;
	int b;

	g = (*(char**)g_1043370);
	d = *(int*) (g + 0x20) / 8;
	a = fcn_0042e410(d) + d * x;
	b = fcn_0042e410(d) + d * y;
	fcn_0045b920(g, a, b, c);
}
