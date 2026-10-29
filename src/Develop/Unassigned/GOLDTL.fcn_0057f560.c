


extern unsigned char* lpGebaeudePROT;
extern unsigned short g_774970;

int __cdecl fcn_0057f560(int* m)
{
	if (m[0] == 0x2b && m[1] != 0 && ((char*)lpGebaeudePROT)[*(unsigned char*) m[1] * 589] == 0x12 &&
	    *(short*) (m[1] + 0x27) == (*(short*)&g_774970) && (m[3] == 0xc || m[3] == 0x1df)) {
		return 1;
	}
	if (m[0] == 0x1a || m[0] == 0x19 || m[0] == 0x1c) {
		return 1;
	}
	return 0;
}
