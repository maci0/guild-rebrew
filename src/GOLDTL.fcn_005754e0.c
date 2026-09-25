// FUNCTION: GOLD 0x0056d0e0
// SIZE: 524
// FUNCTION: GOLDTL 0x5754e0
// SIZE: 524

#pragma pack(2)
// SIZE 0xe
struct pos14 {
	int a;
	int b;
	int c;
	short d;
};
#pragma pack()

// SIZE 0x24
typedef struct {
	int f0;
	int f4;
	int f8;
	char pad[0x14];
	char f20;
	char pad2[3];
} rec24;

// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int owner;
	char pad8[0x214];
};

// SIZE 0x7c
struct req {
	int who;
	char pad4[0x78];
};

extern char g_6a3440;
extern rec24 g_10069a0[128];
extern struct house g_7f4ca0[];
extern struct pos14 g_7f4c00;
extern int g_6a3760;

void __cdecl fcn_00546190(char*);
void __cdecl fcn_00500bb0(struct pos14*, int, int, int);
int __cdecl fcn_004b5070(rec24*);
int __cdecl fcn_004c5790(int, struct req*);
int __cdecl fcn_004c4450(int);

void __cdecl fcn_005754e0(char* u)
{
	struct req q;
	int i;
	int r;

	if (g_6a3440 <= -1) {
		fcn_00546190(u);
		return;
	}
	for (i = 0; i < 128; i++) {
		if (g_10069a0[i].f0 != 0 && g_10069a0[i].f4 == g_7f4ca0[*(unsigned short*) (u + 8)].owner) {
			break;
		}
	}
	if (i >= 128) {
		fcn_00500bb0((struct pos14*) (u + 0x52), 0, 0x1e, 0);
		return;
	}
	switch (*(int*) (u + 0x70)) {
	case 0:
		if (g_10069a0[i].f20 == 0 && (unsigned short) g_7f4c00.b < 0x16 && fcn_004b5070(&g_10069a0[i]) != 0) {
			g_10069a0[i].f20 = 1;
			fcn_00500bb0((struct pos14*) (u + 0x52), 0, 1, 0);
			*(int*) (u + 0x70) = 1;
			return;
		}
		fcn_00500bb0((struct pos14*) (u + 0x52), 0, 10, 0);
		return;
	case 1:
		fcn_00500bb0((struct pos14*) (u + 0x52), 0, 1, 0);
		if (g_10069a0[i].f20 == 1 && (unsigned short) g_7f4c00.b < 0x16 && g_6a3760 == -1) {
			q.who = g_10069a0[i].f4;
			*(int*) (u + 0xac) = fcn_004c5790(8, &q);
			*(int*) (u + 0x70) = 2;
			return;
		}
		fcn_00500bb0((struct pos14*) (u + 0x52), 1, 0, 0);
		*(int*) (u + 0x70) = 1;
		return;
	case 2:
		r = fcn_004c4450(*(int*) (u + 0xac));
		fcn_00500bb0((struct pos14*) (u + 0x52), 0, 1, 0);
		if (r == 0) {
			return;
		}
		if (r == 1) {
			*(int*) (u + 0x70) = 0;
			fcn_00500bb0((struct pos14*) (u + 0x52), 0x18, 0, 0);
			return;
		}
		*(int*) (u + 0x70) = 1;
		fcn_00500bb0((struct pos14*) (u + 0x52), 0, 0x1e, 0);
		return;
	case -2:
	case -1:
		fcn_00546190(u);
		break;
	}
}
