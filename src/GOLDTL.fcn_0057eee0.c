


extern unsigned char* g_868050;

int __cdecl fcn_0057eee0(int* msg)
{
	unsigned char* e;
	char* t;

	if (*msg == 0x19) {
		e = (unsigned char*) msg[1];
		if (e != 0) {
			t = ((char*)g_868050) + *e * 0x24d;
			if (*t != 0xf && *t != 2 && *t != 0x12) {
				return 0;
			}
		}
	}
	return 1;
}
