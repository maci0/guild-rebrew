#include <string.h>

#pragma pack(push, 1)
typedef struct Rec {
	char type;
	char pad1[0x40];
} Rec;
// SIZE 0x41
#pragma pack(pop)

extern char* g_99ec10;
extern unsigned char g_773d75;

unsigned short __cdecl gm_RandomMod(int);
unsigned char* __cdecl fcn_00508e40(int);
int __cdecl fcn_005c6270(void*, int);
unsigned short* __cdecl fcn_00502cd0(int, int, int);
unsigned short* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl fcn_004c51f0(int, int, int, int, unsigned char, int);
void __cdecl fcn_0051af00(char*, int, int);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);

// FUNCTION: GOLDTL 0x4bb0b0

int __cdecl fcn_004bb0b0(int* a1)
{
	unsigned short* found[6];
	char buf[0x100];
	unsigned char* p;
	unsigned short* e;
	int n;

	n = 0;
	p = fcn_00508e40(*a1);
	if (p == 0) {
		return 1;
	}
	if (gm_RandomMod(0x100) < p[0x82]) {
		return 0x400;
	}
	if (fcn_005c6270(p, 0x290) != 0) {
		return 0x400;
	}
	e = fcn_00502cd0(*(int*) (p + 0x178), 1, 5);
	while (e != 0 && n < 6) {
		if (((Rec*)g_99ec10)[*e].type != 9) {
			found[n] = e;
			n++;
		}
		e = gm_NextEntityQueryMatch();
	}
	if (n == 0) {
		return 0x400;
	}
	e = found[gm_RandomMod(n)];
	fcn_004c51f0(-1, *(int*) (p + 4), *e, 1, g_773d75, 0);
	fcn_0051af00(buf, *(unsigned short*) ((char*) a1 + 4) + 0x12e7, *e * 2 + 0x9a8);
	fcn_00545d40(*(int*) (p + 4), *(int*) (p + 4), buf, 0x100 < strlen(buf), 0x603, 0);
	return 0;
}
