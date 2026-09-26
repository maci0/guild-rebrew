// FUNCTION: GOLD 0x00576900
// SIZE: 61
// FUNCTION: GOLDTL 0x57eea0
// SIZE: 61

extern unsigned char* g_868050;

int __cdecl fcn_0057eea0(int* msg)
{
	unsigned char* e;
	char* t;

	if (*msg == 0x19) {
		e = (unsigned char*) msg[1];
		if (e != 0) {
			t = ((char*)g_868050) + *e * 0x24d;
			if (*t != 0xf && *t != 2) {
				return 0;
			}
		}
	}
	return 1;
}
