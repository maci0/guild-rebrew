// FUNCTION: GOLDTL 0x526070
// SIZE: 161

int __cdecl gm_QueryEntitySum(int, int);
void __cdecl fcn_0051af00(char*, int, int);
void __cdecl fcn_00526120(char*, int);

int __cdecl fcn_00526070(short* p, int a, int lim, int b)
{
	char buf[0x200];

	if (gm_QueryEntitySum(a, b) < lim && lim != 0) {
		if (p != 0 && *p == 0x142) {
			fcn_0051af00(buf, 0x76, (unsigned char) b);
		} else if (p != 0 && *p == 0x115) {
			fcn_0051af00(buf, 0x77, (unsigned char) b);
		} else {
			fcn_0051af00(buf, 0x75, (unsigned char) b);
		}
		fcn_00526120(buf, 4);
		return 0;
	}
	return 1;
}
