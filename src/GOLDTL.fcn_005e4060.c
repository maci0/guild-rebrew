// GLOBAL: GOLDTL 0x774964
extern char g_774964;
// GLOBAL: GOLD 0x6f25ac
extern char g_774964;
// FUNCTION: GOLD 0x005d7530
// SIZE: 66
// FUNCTION: GOLDTL 0x5e4060
// SIZE: 66

extern char g_7f4ca0[];

int __cdecl fcn_005e4060(void)
{
	unsigned char* e;
	int r;

	r = 1;
	if (*(char*) ((char*)&g_774964) != 0) {
		for (e = (unsigned char*) g_7f4ca0 + 2; (int) e < (int) g_7f4ca0 + 0x65402; e += 0x21c) {
			if (e[6] > 0 && (e[0] == 6 || e[0] == 7) && *(int*) (e + 0x20a) != -1) {
				r = 0;
				break;
			}
		}
	} else {
		r = 0;
	}
	return r;
}
