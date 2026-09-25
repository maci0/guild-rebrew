#include <string.h>

// SIZE 0x10
typedef struct {
	short x0;
	unsigned char b2;
	char pad3;
	int f4;
	int f8;
	int fc;
} Info;

extern char g_690560[];
extern char g_679060[];

void __cdecl fcn_004fcda0(short, int, Info*);
void __cdecl fcn_0051af00(void*, int, ...);
int __cdecl fcn_004fa5f0(void*, int, int);

// FUNCTION: GOLDTL 0x004f7e70
// SIZE: 421

int __cdecl fcn_004f7e70(unsigned char* a1, int* a2)
{
	Info info;
	char buf[0x400];
	int base;

	if (*a2 != 3 && *a2 != 1)
		return 1;
	if (a1[0x166] == 0 && a1[0x169] == 0 && (*(int*) (a1 + 0x1cc) & 0xe00) == 0)
		return 1;
	if (*a2 == 3 && a1[2] == 6) {
		fcn_004fcda0(*(short*) a1, 0, &info);
		memset(buf, 0, sizeof(buf));
		base = (a1[9] != 0 ? 0x28 : 0) + 0x253;
		fcn_0051af00(buf, (int) g_690560, 0x1d96);
		if (a1[0x166] != 0)
			fcn_0051af00(buf + strlen(buf), 0x1d97, a1[0x166] + base, info.f4);
		if (a1[0x169] != 0)
			fcn_0051af00(buf + strlen(buf), 0x1d97, a1[0x169] + base, info.f8);
		if (info.b2 != 0)
			fcn_0051af00(buf + strlen(buf), 0x1d97, info.b2 + base, info.fc);
		fcn_004fa5f0(buf, 1, 0x657c7);
	} else if (*a2 == 1 && a1[2] == 6) {
		fcn_0051af00((char*) a2 + 0x14, (int) g_679060, 0x1d96);
	}
	return 2;
}
