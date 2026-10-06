// GLOBAL: GOLDTL 0x10161d0
extern char g_10161d0[];
// GLOBAL: GOLDTL 0x10161bc
extern char g_10161bc[];
// FUNCTION: GOLDTL 0x46f280

void __cdecl fcn_0046b2b0(int);

int __cdecl fcn_0046f280(int a1)
{
	char* p;

	p = g_10161d0 + a1 * 0x3cc;
	if (*(int*) p != 0) {
		fcn_0046b2b0(*(int*) (g_10161bc + a1 * 0x3cc));
		return 1;
	}
	return 0;
}
