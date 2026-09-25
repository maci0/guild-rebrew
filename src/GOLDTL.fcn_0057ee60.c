// FUNCTION: GOLD 0x5768c0
// SIZE: 64
// FUNCTION: GOLDTL 0x57ee60
// SIZE: 54

extern char* g_868050;

int __cdecl fcn_0057ee60(int* msg)
{
	unsigned char* e;

	if (*msg == 0x19) {
		e = (unsigned char*) msg[1];
		if (e != 0 && g_868050[*e * 0x24d] != 0xf) {
			return 0;
		}
	}
	return 1;
}
