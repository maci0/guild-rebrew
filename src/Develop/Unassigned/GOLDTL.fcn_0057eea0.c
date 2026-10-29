


extern unsigned char* lpGebaeudePROT;

int __cdecl fcn_0057eea0(int* msg)
{
	unsigned char* e;
	char* t;

	if (*msg == 0x19) {
		e = (unsigned char*) msg[1];
		if (e != 0) {
			t = ((char*)lpGebaeudePROT) + *e * 0x24d;
			if (*t != 0xf && *t != 2) {
				return 0;
			}
		}
	}
	return 1;
}
