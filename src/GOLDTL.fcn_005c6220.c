// GLOBAL: GOLDTL 0x6abb08
extern char g_6abb08[];
// GLOBAL: GOLD 0x62c420
extern char g_6abb08[];
// FUNCTION: GOLD 0x005ba7b0
// SIZE: 80
// FUNCTION: GOLDTL 0x5c6220
// SIZE: 73

char* __cdecl fcn_005c6220(int key, int* out)
{
	int n;
	int v;

	v = *(int*) g_6abb08;
	n = 0;
	while (v != 0) {
		if (v == key) {
			if (out != 0) {
				*out = n;
			}
			return (char*) (g_6abb08 + n * 0x1c);
		}
		n++;
		v = *(int*) (g_6abb08 + n * 0x1c);
	}
	return 0;
}
