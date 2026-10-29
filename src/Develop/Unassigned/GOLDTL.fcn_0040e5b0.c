extern char g_676694[];



int __cdecl fcn_00445600(int, int, int, int);
int __cdecl fcn_0064d41a(char*, char*, ...);
extern char* g_6b7e98;
void __cdecl fcn_00425bf0(void*, int, char*);

int __cdecl fcn_0040e5b0(int* a1)
{
	char buf[0x200];
	int r;

	r = fcn_00445600(0, 0x140, 0, *a1);
	if (r == 0) {
		fcn_0064d41a(buf, g_676694, *a1);
		fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), buf);
		return 0;
	}
	return r;
}
