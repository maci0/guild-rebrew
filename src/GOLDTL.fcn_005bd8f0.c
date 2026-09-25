// FUNCTION: GOLDTL 0x005bd8f0
// SIZE: 123

extern char g_6ac3f4[];
extern char g_6ac3e4[];

char* __cdecl fcn_0064d470(char*, char*);

int __cdecl fcn_005bd8f0(char* name, int* o)
{
	if (fcn_0064d470(name, g_6ac3f4) != 0) {
		o[o[98]] = (int) name;
		o[o[98] + 48] = 0x17;
		o[98]++;
	}
	else if (fcn_0064d470(name, g_6ac3e4) != 0) {
		o[o[98]] = (int) name;
		o[o[98] + 48] = 0x18;
		o[98]++;
	}
	return o[98] < 0x30;
}
