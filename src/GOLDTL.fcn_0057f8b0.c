


extern unsigned char* g_868050;
extern unsigned short g_774970;

int __cdecl fcn_0057f8b0(int* m)
{
	if (m[0] == 0x2b && m[1] != 0 && ((char*)g_868050)[*(unsigned char*) m[1] * 589] == 2 &&
	    *(short*) (m[1] + 0x27) == (*(short*)&g_774970) &&
	    (m[3] == 5 || m[3] == 2 || m[3] == 0xd || m[3] == 8)) {
		return 1;
	}
	if (m[0] == 0x1a || m[0] == 0x19 || m[0] == 0x1c) {
		return 1;
	}
	return 0;
}
