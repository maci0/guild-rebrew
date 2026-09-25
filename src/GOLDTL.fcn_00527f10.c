extern int g_7746f8;
// FUNCTION: GOLDTL 0x00527f10
// SIZE: 73

int __cdecl fcn_00504bd0(int);
int __cdecl fcn_0050e520(int, int*);

void __cdecl fcn_00527f10(unsigned char* e)
{
	int t;
	int v;

	t = fcn_00504bd0(*e);
	if (t == 3) {
		g_7746f8 = 1;
		return;
	}
	if (t == 5 && fcn_0050e520(*e, &v)) {
		g_7746f8 = v;
	}
}
