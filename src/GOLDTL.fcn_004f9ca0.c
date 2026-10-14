


extern char g_679060[];

int __cdecl fcn_004fa5f0(void*, int, int);
void __cdecl fcn_0051af00(void*, int, ...);

int __cdecl fcn_004f9ca0(unsigned char* a1, int* a2)
{
	char buf[0x100];

	if (*a2 != 3 && *a2 != 1) {
		return 1;
	}
	if (a1[0xd] > 8) {
		return 4;
	}
	if (a1[0xd] < 8) {
		return 1;
	}
	if (*a2 == 3 && a1[2] == 6) {
		fcn_0051af00(buf, 0x1e04, (a1[9] != 0 ? 0x11e : 0x114) + a1[0xd]);
		fcn_004fa5f0(buf, 0, 0x657c7);
		return 2;
	}
	if (*a2 == 1 && a1[2] == 6) {
		fcn_0051af00((char*) a2 + 0x14, (int) g_679060, 0x1e03);
	}
	return 2;
}
