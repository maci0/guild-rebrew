// FUNCTION: GOLD 0x0056a410
// SIZE: 496
// FUNCTION: GOLDTL 0x5727f0
// SIZE: 496

#pragma pack(1)
// SIZE 0x41
struct rec {
	char pad0[0x36];
	unsigned short level;
	char pad38[9];
};
#pragma pack()

// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int handle;
	char pad8[0x174];
	char* who;
	char pad180[0x9c];
};

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
extern struct house g_7f4ca0[];
extern struct rec* g_99ec10;
extern unsigned char g_773d75;

int __cdecl fcn_00500cb0(struct pos14*, struct pos14*);
void __cdecl fcn_005015e0(char**, int, int, int);
unsigned short __cdecl fcn_0042e410(unsigned short);
void __cdecl fcn_004c51f0(int, int, int, int, unsigned char, int);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_00545e80(int, int, char*, int, int, int, int, int, char*);
void __cdecl fcn_00529160(char*, int, int, int);
void __cdecl fcn_00546190(char*);

void __cdecl fcn_005727f0(char* e)
{
	char* r;
	char buf[0x200];
	struct rec* p;
	int amt;
	int i;
	int x; /* never assigned: the original passes an uninitialised stack slot */

	switch (*(int*) (e + 0x70)) {
	case 0:
		*(int*) (e + 0x70) = *(int*) (e + 0x70) + 1;
		return;
	case 1:
		if (*(int*) (e + 0x14) == 0 && *(int*) (e + 0x18) == 0) {
			break;
		}
		if (fcn_00500cb0((struct pos14*) (e + 0x52), &g_7f4c00) >= 0) {
			return;
		}
		fcn_005015e0(&r, 0, 0, *(int*) (e + 0xb0));
		if (r == 0) {
			*(int*) (e + 0x70) = -1;
			return;
		}
		p = &g_99ec10[*(unsigned short*) (e + 0xac)];
		amt = (fcn_0042e410((unsigned short) (p->level * 40)) + p->level * 40)
		    * (*(int*) (e + 0x18) + *(int*) (e + 0x14));
		fcn_004c51f0(*(int*) (e + 0xb4), -1, *(unsigned short*) (e + 0xac), amt, g_773d75, 0);
		fcn_0051af00(buf, 0x1bb8, *(unsigned short*) (e + 0xac) * 2 + 0x9a8, x, amt);
		fcn_00545e80(g_7f4ca0[*(unsigned short*) (r + 0x27)].handle, -1, buf, 0, 0x5f1, *(int*) (r + 1), -1, 0,
		    "_NACHRICHTEN_HS_08");
		for (i = 0; i < 768; i++) {
			if (g_7f4ca0[i].who == e) {
				fcn_00529160(r, 0, g_7f4ca0[i].id, 0);
			}
		}
		fcn_00546190(e);
		return;
	case -2:
	case -1:
		for (i = 0; i < 768; i++) {
			if (g_7f4ca0[i].who == e) {
				fcn_00529160(0, 0, g_7f4ca0[i].id, 0);
			}
		}
		break;
	default:
		return;
	}
	fcn_00546190(e);
}
