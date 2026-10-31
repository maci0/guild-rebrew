


int __cdecl gm_QueryEntitySum(int, int);
void __cdecl io_FormatTextBuffer(char*, int, int);
void __cdecl fcn_00526120(char*, int);

int __cdecl fcn_00526070(short* p, int a, int lim, int b)
{
	char buf[0x200];

	if (gm_QueryEntitySum(a, b) < lim && lim != 0) {
		if (p != 0 && *p == 0x142) {
			io_FormatTextBuffer(buf, 0x76, (unsigned char) b);
		} else if (p != 0 && *p == 0x115) {
			io_FormatTextBuffer(buf, 0x77, (unsigned char) b);
		} else {
			io_FormatTextBuffer(buf, 0x75, (unsigned char) b);
		}
		fcn_00526120(buf, 4);
		return 0;
	}
	return 1;
}
