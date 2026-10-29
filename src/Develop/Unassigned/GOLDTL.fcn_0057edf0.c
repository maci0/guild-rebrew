


extern unsigned char* lpGebaeudePROT;

int __cdecl fcn_0057edf0(int* msg)
{
	unsigned char* e;

	if (*msg == 0x19) {
		e = (unsigned char*) msg[1];
		if (e != 0 && ((char*)lpGebaeudePROT)[*e * 0x24d] == 0xf && msg[3] == 0x110) {
			return 1;
		}
	}
	return 0;
}
