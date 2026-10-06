extern char g_774a80[];
extern char g_6ab430[];
// FUNCTION: GOLD 0x005a9390
// FUNCTION: GOLDTL 0x5b2810

unsigned short __cdecl fcn_0042e410(int);
int  __cdecl fcn_0064d41a(char*, char*, int);
void __cdecl fcn_0051af00(void*, int);
void __cdecl fcn_00545d40(int, int, void*, int, int, void*);

void __cdecl fcn_005b2810(void* a1)
{
	char buf[0x40];
	int id;
	char t;

	id = fcn_0042e410(2);
	t = *(char*) ((char*) a1 + 2);
	if (t == 6 || t == 7) {
		fcn_0064d41a(buf, g_6ab430, id + 3);
		fcn_0051af00(g_774a80, id + 0x20ca);
		fcn_00545d40(*(int*) ((char*) a1 + 4), -1, g_774a80, 0, 0x600, buf);
	}
}
