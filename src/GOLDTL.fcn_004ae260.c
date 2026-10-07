// FUNCTION: GOLD 0x004ae120
// FUNCTION: GOLDTL 0x4ae260

extern char g_7f4ca0[];

int __cdecl fcn_004ae260(int a1)
{
	int o;

	o = (a1 & 0xffff) * 540;
	if (*(unsigned short*) ((int) g_7f4ca0 + o) != 0xffff
	    && *(unsigned char*) ((int) g_7f4ca0 + 8 + o) > 0
	    && *(unsigned char*) ((int) g_7f4ca0 + 2 + o) == 0) {
		return 1;
	}
	return 0;
}
