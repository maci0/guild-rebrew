


extern unsigned char* g_868050;

int __cdecl fcn_0057ee60(int* msg)
{
	unsigned char* e;

	if (*msg == 0x19) {
		e = (unsigned char*) msg[1];
		if (e != 0 && ((char*)g_868050)[*e * 0x24d] != 0xf) {
			return 0;
		}
	}
	return 1;
}
