extern int g_14cbca0;
extern int g_699364;
extern char g_868060[];

int __cdecl fcn_004c4dc0(char*, int);
int __cdecl fcn_00503890(int, int, int);
int __cdecl fcn_005037c0(int, int, int);

// FUNCTION: GOLD 0x004c6f60
// SIZE: 174
// FUNCTION: GOLDTL 0x4c7b00
// SIZE: 174

int __cdecl fcn_004c7b00(unsigned char* a1, char* a2)
{
	int v;

	if (g_14cbca0 != -1)
		g_699364 = *(int*) (a1 + 0x18);
	if (*(int*) (a1 + 0x14) != -1) {
		v = fcn_004c4dc0((char*) a1, *(int*) (a1 + 0x14));
		*(int*) (a1 + 0x14) = v;
		if (fcn_00503890(v, *(unsigned short*) (g_868060 + a1[0x1c] * 756 + 0x54), *(int*) (a1 + 0x1d)) == 0)
			return 1;
	}
	if (*(int*) (a1 + 0x10) != -1) {
		v = fcn_004c4dc0((char*) a1, *(int*) (a1 + 0x10));
		*(int*) (a1 + 0x10) = v;
		if (fcn_005037c0(v, *(unsigned short*) (g_868060 + a1[0x1c] * 756 + 0x54), *(int*) (a1 + 0x1d)) == 0)
			return 1;
	}
	if (a2 != 0)
		a2[0] = 1;
	return 0;
}
