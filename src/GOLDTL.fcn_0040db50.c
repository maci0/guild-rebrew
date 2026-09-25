// GLOBAL: GOLD 0x5f216c
extern char g_6761ec[];
// FUNCTION: GOLD 0x0040cc20
// SIZE: 85
// FUNCTION: GOLDTL 0x40db50
// SIZE: 85

void __cdecl fcn_004050c0(int);
extern char* g_6b7e98;
void __cdecl fcn_00425bf0(void*, int, char*);

int __cdecl fcn_0040db50(char** a1)
{
	char* p;
	char* q;
	int e;

	p = *a1;
	if (p == 0) {
		fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), g_6761ec);
	} else {
		q = *(char**) (p + 0x128);
		if (q != 0) {
			q[0x190] = 1;
			while ((e = *(int*) (q + 0x28)) != 0) {
				fcn_004050c0(e);
			}
		}
	}
	return 0;
}
