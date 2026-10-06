// FUNCTION: GOLD 0x004bd6a0
// FUNCTION: GOLDTL 0x4bdf40

extern int g_10058e0;
extern char* g_10058e4;
extern char g_6816ac[];

int __cdecl fcn_0065f220(char*, char*);
int __cdecl fcn_0064d41a(char*, char*, ...);

char* __cdecl fcn_004bdf40(char* name)
{
	char buf[0x40];
	int i;

	for (i = 0; i < g_10058e0; i++) {
		if (fcn_0065f220(name, g_10058e4 + i * 0x60) == 0)
			return g_10058e4 + i * 0x60;
	}
	fcn_0064d41a(buf, g_6816ac, name);
	return 0;
}
