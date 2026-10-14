


// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int owner;
	char pad8[0x214];
};

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern char g_7f4ca0[];
extern char g_6a7e18[];

char* __cdecl fcn_005463a0(int, ...);
char* __cdecl fcn_005462a0(void);
void __cdecl fcn_0051af00(char*, int, ...);
int __cdecl fcn_00545d40(int, int, char*, unsigned char, int, char*);
int __cdecl fcn_004c5620(int, char*);
void __cdecl fcn_00546190(char*);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
void __cdecl fcn_005100f0(int, int);

void __cdecl fcn_00578380(char* u)
{
	char text[0x400];
	char* o;

	if (u[0x78] & 4) {
		return;
	}
	for (o = fcn_005463a0(1, 0, 0x88); o != 0; o = fcn_005462a0()) {
		if (o != u && *(unsigned short*) (o + 8) == *(unsigned short*) (u + 8) && *(int*) (o + 0xb0) == *(int*) (u + 0xb0)) {
			*(int*) (u + 0x84) = fcn_004c5620(-1, u);
			fcn_0051af00(text, 0x4096, *(int*) (u + 0xb0));
			fcn_00545d40(((struct house*)g_7f4ca0)[*(unsigned short*) (u + 8)].owner, -1, text, 0, 0x5fa, 0);
			return;
		}
	}
	*(pos14_7f4c00*) (u + 0x52) = g_7f4c00;
	fcn_00500bb0((pos14_7f4c00*) (u + 0x52), 0, 1, 0);
	if (*(int*) (u + 0xb4) == -1) {
		*(int*) (u + 0x84) = fcn_004c5620(-1, u);
		return;
	}
	*(int*) (u + 0x84) = fcn_004c5620(0, u);
	fcn_005100f0(((struct house*)g_7f4ca0)[*(unsigned short*) (u + 8)].owner, -*(int*) (u + 0xb8));
}
