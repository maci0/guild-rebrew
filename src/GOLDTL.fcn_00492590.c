#include <string.h>

unsigned short __cdecl gm_RandomMod(int n);
float __cdecl gm_RandomFloat01(void);
char* __cdecl fcn_0064d530(char* dst, const char* src, unsigned int n);

extern char g_772628[];
extern char* g_14a5dbc[];
extern char* g_14a60d0[];

/* ADDRESS: GOLDTL 0x00492590 */
unsigned int __cdecl fcn_00492590(int a0)
{
	float tab[15];
	float r;
	int row;
	int i;
	int col;
	int res;
	int cs;
	int v2;
	int sel;
	int v;
	unsigned char bl;
	char* src;

	tab[0] = 0.2f;
	tab[1] = 0.55f;
	tab[2] = 0.85f;
	tab[3] = 0.95f;
	tab[4] = 1.0f;
	tab[5] = 0.1f;
	tab[6] = 0.4f;
	tab[7] = 0.7f;
	tab[8] = 0.9f;
	tab[9] = 1.0f;
	tab[10] = 0.05f;
	tab[11] = 0.25f;
	tab[12] = 0.55f;
	tab[13] = 0.8f;
	tab[14] = 1.0f;
	res = 0;
	r = gm_RandomFloat01();
	if (a0 == 1) {
		row = 0;
	} else {
		row = (a0 != 2) + 1;
	}
	for (i = 1; i <= 5; i++) {
		if (r <= tab[row * 5 + (i - 1)]) {
			res = i;
			break;
		}
	}
	if (row == 1) {
		cs = (unsigned short) gm_RandomMod(3);
	} else {
		v = gm_RandomMod(2);
		if (row != 0) {
			cs = row - (v & 0xffff);
		} else {
			cs = (unsigned short) v;
		}
	}
	r = gm_RandomFloat01();
	v2 = res;
	for (col = 0; col < 5; col++) {
		if (r <= tab[cs * 5 + col]) {
			v2 = (col + 1) * 0x100;
			break;
		}
	}
	memset(g_772628, 0, 0x21c);
	g_772628[9] = (char) gm_RandomMod(2);
	if (g_772628[9] != 0) {
		src = g_14a60d0[gm_RandomMod(0x70) & 0xffff];
	} else {
		src = g_14a5dbc[gm_RandomMod(0xbf) & 0xffff];
	}
	fcn_0064d530(g_772628 + 0x30, src, 0xf);
	switch (res) {
	case 1:
		bl = 0x15;
		sel = 0x2a;
		break;
	case 2:
		bl = 0x15;
		sel = 0x3f;
		break;
	case 3:
		bl = 0x3f;
		sel = 0x3f;
		break;
	case 4:
		bl = 0x69;
		sel = 0x3f;
		break;
	case 5:
		bl = 0xa8;
		sel = 0x54;
		break;
	default:
		bl = (unsigned char) res;
		sel = res;
		break;
	}
	for (i = 0; i < 5; i++) {
		g_772628[0x80 + i] = (char) (gm_RandomMod(sel) + bl + 1);
	}
	g_772628[2] = 10;
	return v2 | res;
}
