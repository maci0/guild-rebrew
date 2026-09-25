// FUNCTION: GOLDTL 0x005c95d0
// SIZE: 639

typedef struct
{
	unsigned char x0;
	char pad1[0x222];
	unsigned char x223;
	char pad224[0x29];
} Shop;
// SIZE 0x24d

extern Shop* g_868050;
extern unsigned short g_774970;
extern int g_14ce8e0;
extern int g_774654;
extern char* g_77255c;
extern char s_6a4320[];
extern char s_6a4310[];
extern char s_6a4304[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
void __cdecl fcn_00504bd0(int);
void __cdecl fcn_0050c1b0(unsigned char*, int, int*);
int __cdecl fcn_0050bfe0(unsigned char*);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

void __cdecl fcn_005c95d0(unsigned char* a)
{
	int st[21];
	Shop* t;
	int dlg;

	t = &g_868050[a[0]];
	dlg = fcn_00470820(0x3c, 0, s_6a4320);
	fcn_00471b60(dlg);
	fcn_004727a0(dlg, 1);
	*(int*) (g_77255c + 0x28c) = 0x56;
	fcn_00504bd0(a[0]);
	fcn_0050c1b0(a, g_774970, st);
	if (a[5] != 0) {
		fcn_00519190((int) s_6a4310, a[0] * 14 + 0x48e, a + 5);
	}
	else {
		fcn_00519190((int) s_6a4304, a[0] * 14 + 0x48e);
	}
	fcn_00519190(0xa3, fcn_0050bfe0(a));
	if (st[0] != 0) {
		fcn_00519190(0xa4, st[0]);
	}
	if (st[2] != 0) {
		fcn_00519190(0xa5, st[2]);
	}
	if (st[6] != 0) {
		fcn_00519190(0xa6, t->x223 + 0x130, st[6]);
	}
	if (st[4] + st[5] != 0) {
		fcn_00519190(0xa7, st[4] + st[5]);
	}
	if (st[8] != 0) {
		fcn_00519190(0xa8, st[8]);
	}
	if (st[12] != 0) {
		fcn_00519190(0xa9, st[12]);
	}
	if (st[15] != 0) {
		fcn_00519190(0xaa, st[15]);
	}
	if (st[13] != 0) {
		fcn_00519190(0xab, st[13]);
	}
	if (st[14] != 0) {
		fcn_00519190(0xac, st[14]);
	}
	if (st[19] != 0) {
		fcn_00519190(0xad, st[19]);
	}
	if (st[18] != 0) {
		if (t->x0 == 4 || t->x0 == 0x10 || t->x0 == 0x13) {
			fcn_00519190(0xb3, st[18]);
		}
		else {
			fcn_00519190(0xae, st[18]);
		}
	}
	if (st[1] != 0) {
		fcn_00519190(0xaf, st[1]);
	}
	if (st[20] > 0) {
		fcn_00519190(0xb0, st[20]);
	}
	else if (st[20] < 0) {
		fcn_00519190(0xb1, st[20] + st[18]);
	}
	if (fcn_005373e0((void*) fcn_005c95d0, 0x677c7) != 0) {
		do {
			if (g_14ce8e0 != 0) {
				g_774654 = 1;
			}
		} while (fcn_005373e0((void*) fcn_005c95d0, 0x677c7) != 0);
	}
	fcn_00471e30(dlg);
}
