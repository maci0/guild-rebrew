// FUNCTION: GOLDTL 0x00541150
// SIZE: 629

#pragma pack(push, 1)
// SIZE 0x24d
typedef struct {
	unsigned char kind;
	char pad1[0x222];
	unsigned char level;
	char pad224[0x29];
} Office;

// SIZE 0x25
typedef struct {
	unsigned char office;
	char pad1[4];
	char name[0x20];
} Player;
#pragma pack(pop)

// SIZE 0x290
typedef struct {
	char pad0[0x28c];
	int style;
} Dialog;

extern unsigned char* g_868050;
extern char* g_77255c;
extern unsigned short g_774970;
extern int g_14ce8e0;
extern int g_774654;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00504bd0(int);
int __cdecl fcn_0050c1b0(Player*, int, int*);
void __cdecl fcn_00519190(char*, ...);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

void __cdecl fcn_00541150(Player* p)
{
	int st[21];
	Office* o;
	int box;

	o = (Office*)(g_868050 + p->office * sizeof(Office));
	box = fcn_00470820(0x3c, 0, "Runden\\Spielerrunde_Ende_geb");
	fcn_00471b60(box);
	fcn_004727a0(box, 1);
	((Dialog*)g_77255c)->style = 0x55;
	fcn_00504bd0(p->office);
	if (fcn_0050c1b0(p, (unsigned short) (*(int*)&g_774970), st) != 0) {
		if (p->name[0] != 0) {
			fcn_00519190("$A$Z%1s >%s<$2A", p->office * 14 + 0x48e, p->name);
		} else {
			fcn_00519190("$A$Z%1s$2A", p->office * 14 + 0x48e);
		}
		if (st[0] != 0) {
			fcn_00519190((char*) 0x2039, st[0]);
		}
		if (st[2] != 0) {
			fcn_00519190((char*) 0x203a, st[2]);
		}
		if (st[6] != 0) {
			fcn_00519190((char*) 0x203b, o->level + 0x130, st[6]);
		}
		if (st[4] + st[5] != 0) {
			fcn_00519190((char*) 0x203c, st[4] + st[5]);
		}
		if (st[8] != 0) {
			fcn_00519190((char*) 0x203d, st[8]);
		}
		if (st[12] != 0) {
			fcn_00519190((char*) 0x203e, st[12]);
		}
		if (st[15] != 0) {
			fcn_00519190((char*) 0x203f, st[15]);
		}
		if (st[13] != 0) {
			fcn_00519190((char*) 0x2040, st[13]);
		}
		if (st[14] != 0) {
			fcn_00519190((char*) 0x2041, st[14]);
		}
		if (st[19] != 0) {
			fcn_00519190((char*) 0x2042, st[19]);
		}
		if (st[18] != 0) {
			if (o->kind == 4 || o->kind == 0x10 || o->kind == 0x13) {
				fcn_00519190((char*) 0x2043, st[18]);
			} else {
				fcn_00519190((char*) 0x2044, st[18]);
			}
		}
		if (st[1] != 0) {
			fcn_00519190((char*) 0x2045, st[1]);
		}
		if (st[20] > 0) {
			fcn_00519190((char*) 0x2046, st[20]);
		} else if (st[20] < 0) {
			fcn_00519190((char*) 0x2047, st[20] + st[18]);
		}
	}
	while (fcn_005373e0(fcn_00541150, 0x24087) != 0) {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	}
	fcn_00471e30(box);
}
