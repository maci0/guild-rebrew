// FUNCTION: GOLDTL 0x005d7640
// SIZE: 663

typedef struct Ent {
	unsigned short id;
	unsigned char kind;
	char pad3[0x166 - 3];
	unsigned char rank;
	char pad167[0x194 - 0x167];
	int level;
	char pad198[0x21c - 0x198];
} Ent;
// SIZE 0x21c

typedef struct Cmd {
	int type;
	char pad4[0x21c - 4];
	Ent* target;
} Cmd;

extern Ent g_7f4ca0[768];
extern char s_6a2f5c[];
extern char s_6acd38[];
extern int g_100f1dc;
extern int g_67d370;
extern int g_774654;
extern int g_14ce8e0;

int __cdecl fcn_005d75d0(Ent*, Ent*, Ent*);
void __cdecl fcn_0051af00(char*, ...);
int __cdecl fcn_00526120(char*, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_00525f60(Ent*, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);
int __cdecl fcn_005d71f0();

int __cdecl fcn_005d7640(Ent* ent, Cmd* cmd)
{
	Ent* pa;
	char text[0x200];
	Ent* pb;
	int i;
	int left;
	int rank;
	int want_a;
	int want_b;
	int h;
	int s;
	int yes;
	int no;

	pb = 0;
	left = 2;
	pa = 0;
	if (cmd->type == 3) {
		rank = ent->rank;
	} else if (cmd->type == 4 && cmd->target != 0) {
		rank = cmd->target->rank;
	} else {
		return 0x60;
	}
	if (rank == 15) {
		want_b = 14;
		want_a = 13;
	} else if (rank == 21) {
		want_b = 20;
		want_a = 19;
	} else if (rank == 27) {
		want_b = 26;
		want_a = 25;
	} else {
		return 0x20;
	}
	for (i = 0; i < 768; i++) {
		if (left == 0) {
			break;
		}
		if (g_7f4ca0[i].rank == want_a) {
			pa = &g_7f4ca0[i];
			left--;
		} else if (g_7f4ca0[i].rank == want_b) {
			pb = &g_7f4ca0[i];
			left--;
		}
	}
	if (ent->kind != 6 && ent->kind != 7) {
		if (ent->level < 6 || left > 0) {
			return 0x20;
		}
		return fcn_005d75d0(ent, pb, pa) ? 0x10 : 0x20;
	}
	if (left > 0) {
		fcn_0051af00(text, s_6a2f5c, 0x1dcb);
		fcn_00526120(text, 0);
		return 0;
	}
	h = fcn_00470820(0, 0, s_6acd38);
	fcn_00473a90(0, 0);
	fcn_00471b60(h);
	fcn_004727a0(h, 1);
	s = fcn_00519190(0x1dc9, 6, pb->id, pa->id);
	yes = fcn_00472250(h, 1, s);
	no = fcn_00472250(h, 1, s + 1);
	g_100f1dc = -1;
	do {
		if (g_100f1dc != -1) {
			if (g_67d370 == yes) {
				if (fcn_00525f60(ent, 6)) {
					if (fcn_005d75d0(ent, pb, pa)) {
						fcn_0051af00(text, 0x1dca);
					} else {
						fcn_0051af00(text, s_6a2f5c, 0x1dcb);
					}
					fcn_00526120(text, 0);
					g_774654 = 1;
				}
			} else if (g_67d370 == no) {
				g_774654 = 1;
			}
		}
		if (g_14ce8e0) {
			g_774654 = 1;
		}
	} while (fcn_005373e0(fcn_005d71f0, 0x657c7));
	fcn_00471e30(h);
	return 1;
}
