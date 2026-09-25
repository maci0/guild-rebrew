// FUNCTION: GOLDTL 0x005e4c50
// SIZE: 117

extern int g_7e46ac;
extern int g_6b7fc0;
extern unsigned char g_774964;
extern char g_14cf950;
extern char g_6a2e68[];
extern char g_6b5c60[];

void __cdecl fcn_00533a40(char*);
int __cdecl fcn_005373e0(void*, int);

void __cdecl fcn_005e4c50(void)
{
	int flags;

	flags = (g_7e46ac & ~0x2000) | 0x100000;
	g_6b7fc0 = 1;
	fcn_00533a40(g_6a2e68);
	g_774964 = 0;
	while (fcn_005373e0(0, flags) != 0) {
		if (g_14cf950 == 0x39) {
			break;
		}
	}
	fcn_00533a40(g_6b5c60);
	g_6b7fc0 = 0;
	g_774964 = 1;
}
