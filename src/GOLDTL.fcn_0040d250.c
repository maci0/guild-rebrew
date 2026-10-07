// GLOBAL: GOLD 0x5f1f00
extern char g_675f80[];
// FUNCTION: GOLD 0x0040c330
// FUNCTION: GOLDTL 0x40d250

int __cdecl fcn_004032b0(int);
int __cdecl fcn_0064d41a(char*, char*, ...);
extern char* g_6b7e98;
void __cdecl fcn_00425bf0(void*, int, char*);

int __cdecl fcn_0040d250(int* a1)
{
	char buf[0x80];
	int r;

	r = fcn_004032b0(*a1);
	if (r == 0) {
		fcn_0064d41a(buf, g_675f80, *a1);
		fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), buf);
	}
	return r;
}
