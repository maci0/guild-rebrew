// GLOBAL: GOLD 0x5f14c4
extern char g_67553c[];
// FUNCTION: GOLD 0x00403d60
// FUNCTION: GOLDTL 0x404560

int __cdecl fcn_0064d41a(char*, char*, ...);
void __cdecl fcn_00435500(char*, char*);
int __cdecl fcn_00433ba0(char*);
void __cdecl fcn_00434760(int, int);

void __cdecl fcn_00404560(char* p)
{
	char buf[0x60];
	int x;

	if (*(int*) (p + 0x7c) != 0) {
		fcn_0064d41a(buf, g_67553c, p);
		fcn_00435500(*(char**) (*(char**) (p + 0x34) + 0x1ec) + 0xf4, buf);
		x = fcn_00433ba0(buf);
		fcn_00434760(x, 1);
		*(int*) (p + 0x7c) = 0;
	}
}
