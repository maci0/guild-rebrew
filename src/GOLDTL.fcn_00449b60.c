extern char* g_1042c38;
extern char g_1042d00[];

int __cdecl fcn_0065f2f0(const char* a, const char* b, int n);

// FUNCTION: GOLDTL 0x449b60
// SIZE: 60
char* __cdecl fcn_00449b60(const char* name)
{
	char* p;

	for (p = g_1042c38; p != g_1042d00; p = *(char**) (p + 0x1f8)) {
		if (fcn_0065f2f0(name, p, 0x3f) == 0) {
			return p;
		}
	}
	return 0;
}
