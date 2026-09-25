struct fcn_00475290_entry {
	int a;
	int b;
	int c;
	int d;
	int e;
	int used;
};
// SIZE 0x18

extern int g_100f804;
extern int g_67d8d4;
extern struct fcn_00475290_entry g_100f200[];
// FUNCTION: GOLDTL 0x475290
// SIZE: 80

int __cdecl fcn_00475290(int a, int b, int c, int d, int e)
{
	int n;
	struct fcn_00475290_entry* p;

	n = g_100f804 + 1;
	g_100f804 = n;
	g_67d8d4 = n;
	if (n > 0x40)
		return 0;
	p = &g_100f200[n];
	p->a = a;
	p->b = b;
	p->c = c;
	p->d = d;
	p->e = e;
	p->used = 1;
	return n;
}
