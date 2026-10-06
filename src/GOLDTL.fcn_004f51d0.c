// GLOBAL: GOLDTL 0x69037c
extern char g_69037c[];
// GLOBAL: GOLD 0x61164c
extern char g_69037c[];
// FUNCTION: GOLDTL 0x4f51d0
// FUNCTION: GOLD 0x4f30a0

#include <string.h>

/* Same by-value request struct as fcn_004f5300: caller 0x4f56b0 copies 0x2d bytes. */
// SIZE 0x2d
typedef struct tag_req_2d_b {
	char raw[0x2d];
} req_2d_b;

unsigned char* __cdecl fcn_00508e40(int);
void __cdecl fcn_0051af00(void*, int, ...);

int __cdecl fcn_004f51d0(void* a1, req_2d_b s, int b)
{
	unsigned short w;
	unsigned char* p;
	int r = 1;
	int v = (b <= r);

	p = fcn_00508e40(*(int*) ((char*) &s + 0x12));
	if (p != 0) {
		w = *(unsigned short*) p;
	} else {
		w = 0xfffe;
	}
	switch (*(int*) ((char*) &s + 0x1c) & 0xff) {
	case 2:
		if (*(int*) ((char*) &s + 4) < 0x75) {
			fcn_0051af00(a1, v + 0x140a, (char*) &s + 4,
			    *(int*) ((char*) &s + 0x1d) + 0x13f9);
		} else {
			fcn_0051af00(a1, v + 0x140a, (char*) &s + 4,
			    *(int*) ((char*) &s + 0x1d) + 0x13fb);
		}
		break;
	case 3:
		fcn_0051af00(a1, v + 0x140f, (char*) &s + 4);
		break;
	case 4:
		fcn_0051af00(a1, v + 0x1414, (char*) &s + 4, w);
		break;
	case 8:
		fcn_0051af00(a1, v + 0x1428, (char*) &s + 4);
		break;
	default:
		memcpy(a1, g_69037c, 0x20);
		r = 0;
		break;
	}
	return r;
}
