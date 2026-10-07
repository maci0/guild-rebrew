// GLOBAL: GOLDTL 0x67bd90
extern char g_67bd90[];
// FUNCTION: GOLDTL 0x45f060

void __cdecl fcn_0064d41a(void*, void*, int);
int __cdecl fcn_0045ee20(void*, int, int);

int __cdecl fcn_0045f060(int a1, int a2)
{
	char buf[0x14];

	if (a1 < 0) {
		return 0;
	}
	fcn_0064d41a(buf, g_67bd90, a1);
	return fcn_0045ee20(buf, a2, a1);
}
