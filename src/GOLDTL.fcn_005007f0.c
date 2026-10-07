// FUNCTION: GOLDTL 0x5007f0

extern int g_773d40;
extern char g_67bd30[];
extern char g_67a930[];

char* __cdecl fcn_0064d470(char*, char*);

void __cdecl fcn_005007f0(char* s)
{
	if (fcn_0064d470(s, g_67bd30) != 0 || fcn_0064d470(s, g_67a930) != 0) {
		g_773d40++;
	}
}
