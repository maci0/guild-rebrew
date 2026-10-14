

typedef struct Player {
	char name[0x2f4];
} Player;
// SIZE 0x2f4

typedef struct Share {
	int amount;
	int kind;
	int goal;
} Share;

// SIZE 0x2f4
typedef struct {
	char pad0[0x5c];
	int shown;
	char pad60[0x1d0 - 0x60];
	int style;
	char pad1d4[0x2f4 - 0x1d4];
} Slot;

// SIZE 0xf8
struct msg {
	int f0;
	char b4;
	char pad5[3];
	int f8;
	int fc;
	char pad10[0x26];
	char b36;
	char pad37[0x21];
	int f58;
	char pad5c[4];
	int f60;
	char b64;
	char b65;
	char pad66[0x92];
};

// SIZE 0x21c
typedef struct {
	int f0;
	int f4;
	char pad8[0x214];
} House;

extern char g_868060[];
extern char g_7f4ca0[];
extern unsigned short g_774970;
extern char* g_1015ea0;
extern char s_6ace6c[];
extern char s_679060[];
extern char s_68be7c[];
extern int g_772514;
extern int g_7e46ac;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_774654;
extern int g_67d370;

void __cdecl fcn_004942a0(House*, Share*);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_0046f740(int, int, int, int);
void __cdecl fcn_0051af00(char*, char*, ...);
void __cdecl fcn_0046fac0(int, int, char*, int);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_00473a90(int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_004c5530(struct msg*);
void __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_005dbb60(int unused, unsigned short* p)
{
	int dlg;
	int ids[4];
	Share shares[3];
	struct msg m;
	char text[0x100];
	int result;
	int i;

	fcn_004942a0(&((House*)g_7f4ca0)[g_774970], shares);
	dlg = fcn_00470820(0, 0, s_6ace6c);
	fcn_00471b60(dlg);
	fcn_004727a0(dlg, 1);
	fcn_00519190(0x1a9d, (((unsigned char*) p)[9] != 0) + 0x1aa0, *p, 5);
	fcn_004727a0(dlg, 2);
	for (i = 0; i < 3; i++) {
		ids[i] = fcn_0046f740(0x14, i * 0x5a + 10, 0x4c6, g_772514);
		((Slot*)g_1015ea0)[ids[i]].shown = 1;
		((Slot*)g_1015ea0)[ids[i]].style = 3;
		fcn_0051af00(text, s_679060, ((Player*)g_868060)[i + 1].name);
		fcn_0046fac0(0xbe, i * 0x5a + 10, text, g_772514);
		fcn_0051af00(text, s_679060, shares[i].kind + 0x16b7);
		fcn_0046fac0(0xbe, i * 0x5a + 10 + 0x14, text, g_772514);
		fcn_0051af00(text, s_679060, shares[i].goal + 0x16b7);
		fcn_0046fac0(0xbe, i * 0x5a + 10 + 0x28, text, g_772514);
		fcn_0051af00(text, s_68be7c, shares[i].amount);
		fcn_0046fac0(0xbe, i * 0x5a + 10 + 0x3c, text, g_772514);
	}
	fcn_004727a0(dlg, 3);
	ids[3] = fcn_00472250(dlg, 3, fcn_00519190(0x1ba8));
	fcn_00473a90(0, 0);
	g_100f1dc = -1;
	result = 0;
	while (fcn_005373e0((void*) fcn_005dbb60, g_7e46ac) != 0) {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1) {
			if (g_67d370 == ids[3]) {
				g_774654 = 1;
			} else {
				for (i = 0; i < 3; i++) {
					if (g_67d370 == ids[i]) {
						m.b36 = 0x12;
						m.b4 = 0x5f;
						m.f8 = *(int*) (p + 2);
						m.fc = -1;
						m.f58 = ((House*)g_7f4ca0)[g_774970].f4;
						m.b64 = (char) shares[i].kind;
						m.b65 = (char) shares[i].goal;
						m.f60 = shares[i].amount;
						fcn_004c5530(&m);
						fcn_004c5420(*(int*) (p + 2), 0x1c8, 4, 0x10000, 0);
						result = 1;
						g_774654 = 1;
						break;
					}
				}
			}
		}
	}
	fcn_00471e30(dlg);
	return result;
}
