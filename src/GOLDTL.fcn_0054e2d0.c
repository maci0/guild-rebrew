

#pragma pack(2)
// SIZE 0xe
struct pos14 {
	int a;
	int b;
	int c;
	short d;
};
#pragma pack()

extern struct pos14 g_7f4c00;

// SIZE 0xf8
struct msg {
	int f0;
	char b4;
	char pad[3];
	int f8;
	int fc;
	char pad2[0x18];
	struct pos14 pos;
	char b36;
	char pad3[0x21];
	char b58;
	char pad4[3];
	char b5c;
	char pad5[0x9b];
};

// FUNCTION: GOLD 0x00546350
// SIZE: 182
// FUNCTION: GOLDTL 0x54e2d0
// SIZE: 182

char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
void __cdecl fcn_00500bb0(struct pos14*, int, int, int);
int __cdecl fcn_004c5620(int, char*);

void __cdecl fcn_0054e2d0(char* o)
{
	if (o[0x78] & 2) {
		if (gm_StartFilteredEntitySearch(1, 1, *(int*) (o + 0xac)) == 0) {
			*(struct pos14*) (o + 0x52) = g_7f4c00;
			fcn_00500bb0((struct pos14*) (o + 0x52), 0, 0, 1);
			*(int*) (o + 0x84) = fcn_004c5620(-1, o);
		}
		*(struct pos14*) (o + 0x52) = g_7f4c00;
		fcn_00500bb0((struct pos14*) (o + 0x52), 0, 0, 1);
		*(int*) (o + 0x84) = fcn_004c5620(0, o);
	}
}
