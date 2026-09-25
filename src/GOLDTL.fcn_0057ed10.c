// FUNCTION: GOLDTL 0x57ed10
// SIZE: 65

extern char* g_868050;
extern short* g_7746cc;

int __cdecl fcn_0057ed10(int* msg)
{
	unsigned char* e;

	if (*msg == 0x1a) {
		e = (unsigned char*) msg[1];
		if (e != 0) {
			if (g_868050[*e * 0x24d] == 0x12 && *g_7746cc == 0x74) {
				return 0;
			}
		}
	}
	return 1;
}
