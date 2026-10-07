// FUNCTION: GOLD 0x004e8730
// FUNCTION: GOLDTL 0x4ea4b0

extern char g_7f4ca4[];
extern char g_6b5c60[];

void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, char*);

void __cdecl fcn_004ea4b0(unsigned char* e, int k)
{
	char buf[0x200];
	int i;

	if (e[2] != 6 && e[2] != 7 && e[2] != 5)
		return;
	fcn_0051af00(buf, 0x1c19, *(unsigned short*) e, 0x1c1b, (e[9] != 0 ? 0x27b : 0x253) + k);
	for (i = 0; i < 0x300; i++) {
		if (g_7f4ca4[i * 0x21c - 2] == 6)
			fcn_00545d40(*(int*) (g_7f4ca4 + i * 0x21c), -1, buf, 0, 0x5fd, g_6b5c60);
		else if (g_7f4ca4[i * 0x21c - 2] == 7)
			fcn_00545d40(*(int*) (g_7f4ca4 + i * 0x21c), -1, buf, 0, 0x5fe, g_6b5c60);
	}
}
