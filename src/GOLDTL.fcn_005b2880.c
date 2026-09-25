extern char g_774a80[];
extern char g_6ab44c[];
extern char g_7f4ca4[];
// FUNCTION: GOLD 0x005a9400
// SIZE: 119
// FUNCTION: GOLDTL 0x5b2880
// SIZE: 119

unsigned short __cdecl fcn_0042e410(int);
int  __cdecl fcn_0064d41a(char*, char*, int);
void __cdecl fcn_0051af00(void*, int);
void __cdecl fcn_00545d40(int, int, void*, int, int, void*);

void __cdecl fcn_005b2880(void)
{
	char buf[0x40];
	int id;
	int p;

	id = fcn_0042e410(2);
	fcn_0064d41a(buf, g_6ab44c, id + 0x12);
	fcn_0051af00(g_774a80, id + 0x20cd);
	for (p = (int) g_7f4ca4; p < (int) g_7f4ca4 + 0x65400; p += 0x21c) {
		if (*(char*) (p - 2) == 6) {
			fcn_00545d40(*(int*) p, -1, g_774a80, 0, 0x600, buf);
		}
	}
}
