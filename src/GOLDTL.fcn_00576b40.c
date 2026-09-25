// FUNCTION: GOLDTL 0x576b40
// SIZE: 321

#pragma pack(2)
// SIZE 0xe
struct pos14 {
	int a;
	int b;
	int c;
	short d;
};
#pragma pack()

// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int owner;
	char pad8[0x214];
};

extern struct pos14 g_7f4c00;
extern struct house g_7f4ca0[];
extern char g_6a7e18[];

char* __cdecl fcn_005463a0(int, ...);
char* __cdecl fcn_005462a0(void);
void __cdecl fcn_0051af00(char*, int, ...);
int __cdecl fcn_00545d40(int, int, char*, unsigned char, int, char*);
int __cdecl fcn_004c5620(int, char*);
void __cdecl fcn_00546190(char*);
void __cdecl fcn_00500bb0(struct pos14*, int, int, int);
int __cdecl fcn_004c64b0(int, int, int, int, int, int, char*);

void __cdecl fcn_00576b40(char* u)
{
	char text[0x400];
	char* o;

	if (u[0x78] & 4) {
		return;
	}
	for (o = fcn_005463a0(1, 0, 0x99); o != 0; o = fcn_005462a0()) {
		if (o != u && *(unsigned short*) (o + 8) == *(unsigned short*) (u + 8)) {
			fcn_0051af00(text, 0x3ff7, *(unsigned short*) (u + 8));
			fcn_00545d40(g_7f4ca0[*(unsigned short*) (u + 8)].owner, -1, text, 0, 0x5fa, 0);
			*(int*) (u + 0x84) = fcn_004c5620(-1, u);
			fcn_00546190(u);
			return;
		}
	}
	*(struct pos14*) (u + 0x44) = g_7f4c00;
	*(struct pos14*) (u + 0x52) = g_7f4c00;
	fcn_00500bb0((struct pos14*) (u + 0x52), 0, 1, 0);
	*(int*) (u + 0xcc) = fcn_004c64b0(0xd, *(int*) (u + 0xb0), -1, 0x2d, 0, 0, g_6a7e18);
	*(int*) (u + 0x84) = fcn_004c5620(0, u);
}
