// FUNCTION: GOLD 0x00576850
// SIZE: 67
// FUNCTION: GOLDTL 0x57edf0
// SIZE: 67

extern unsigned char* g_868050;

int __cdecl fcn_0057edf0(int* msg)
{
	unsigned char* e;

	if (*msg == 0x19) {
		e = (unsigned char*) msg[1];
		if (e != 0 && ((char*)g_868050)[*e * 0x24d] == 0xf && msg[3] == 0x110) {
			return 1;
		}
	}
	return 0;
}
