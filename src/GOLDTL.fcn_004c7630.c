// GLOBAL: GOLDTL 0x68aec4
extern char g_68aec4[];
// GLOBAL: GOLDTL 0xaed328
extern unsigned int g_aed328;
// GLOBAL: GOLDTL 0xfb5740
extern char* g_fb5740;
// GLOBAL: GOLDTL 0x1005820
extern unsigned int g_1005820;
// FUNCTION: GOLD 0x004c6a90
// SIZE: 55
// FUNCTION: GOLDTL 0x4c7630
// SIZE: 55

int __cdecl fcn_0041db70(int, char*);

int __cdecl fcn_004c7630(void* a1, char* a2)
{
	int n;

	n = *(int*) ((char*) a1 + 0x10);
	g_aed328 = n;
	g_fb5740 = (char*) fcn_0041db70(n, g_68aec4);
	g_1005820 = 0;
	if (a2 != 0) {
		*a2 = 1;
	}
	return 0;
}
