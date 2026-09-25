// FUNCTION: GOLDTL 0x43a9c0
// SIZE: 112

extern int g_6b8058;
extern int g_6b8010;
extern int g_67a370;
extern int g_6b8008;
extern int g_6b8300;
extern char g_67a42c[];

int __cdecl fcn_0064d41a(char*, char*, ...);
void __cdecl fcn_0043f690(int);
void __cdecl fcn_0043b8f0(int);

char __cdecl fcn_0043a9c0(int flags)
{
	char buf[0x100];

	fcn_0064d41a(buf, g_67a42c, g_6b8008, g_67a370, g_6b8010, g_6b8058, flags);
	if (g_6b8300 != 0) {
		if ((flags & 2) != 0) {
			fcn_0043f690(g_6b8300);
		}
		fcn_0043b8f0(g_6b8300);
	}
	g_6b8058 = flags;
	return 1;
}
