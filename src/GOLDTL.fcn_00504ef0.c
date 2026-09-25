extern unsigned char* g_868050;
// FUNCTION: GOLDTL 0x00504ef0
// SIZE: 59

int __cdecl fcn_00504ef0(int type, int* out)
{
	int n;
	int i;

	n = 0;
	for (i = 0; i < 0x58; i++) {
		if (g_868050[i * 0x24d] == type) {
			out[n] = i;
			n++;
		}
	}
	return n;
}
