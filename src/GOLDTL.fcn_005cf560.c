// FUNCTION: GOLD 0x5c3350
// FUNCTION: GOLDTL 0x005cf560

typedef struct
{
	char pad[0x21c];
} Player;
// SIZE 0x21c

typedef struct
{
	unsigned char x0;
	char pad1[0x222];
	unsigned char lv[6];
	char pad229[0x24];
} Shop;
// SIZE 0x24d

extern char g_7f4ca0[];
extern unsigned char* g_868050;
extern unsigned short g_774970;

void* __cdecl fcn_0050dc90(unsigned char*);
int __cdecl fcn_00507b00(int);
int __cdecl gm_CheckStatLevel(int, int);
char* __cdecl fcn_005463a0(int, int, int, int, int);
char* __cdecl fcn_005462a0(void);
void __cdecl fcn_005ceb20(unsigned char*, int);
void __cdecl fcn_005ceef0(unsigned char*, void*);
void __cdecl fcn_005ceaa0(unsigned char*);
void __cdecl fcn_005cea10(unsigned char*);
void __cdecl fcn_00532ef0(void);

void __cdecl fcn_005cf560(unsigned char* obj)
{
	Player* me;
	Shop* t;
	void* x;
	int mode;
	int lvl;
	int i;
	char* p;

	if (obj == 0 || g_774970 != *(unsigned short*) (obj + 0x27)) {
		return;
	}
	me = &((Player*)g_7f4ca0)[g_774970];
	t = &((Shop*)g_868050)[obj[0]];
	x = fcn_0050dc90(obj);
	if (t->x0 == 5 || t->x0 == 9) {
		mode = 0x40;
	}
	else if (x != 0) {
		mode = 0x30;
	}
	else {
		mode = 0x20;
		lvl = gm_CheckStatLevel(g_774970, fcn_00507b00(t->lv[0]));
		if (lvl != 0) {
			for (i = 0; i < 6; i++) {
				if (lvl == t->lv[i]) {
					x = me;
					mode = 0x10;
					break;
				}
			}
		}
	}
	for (p = fcn_005463a0(2, 0, 7, 3, *(int*) (obj + 1)); p != 0; p = fcn_005462a0()) {
		if (p[0xac] == 0) {
			mode = 0x50;
			break;
		}
	}
	switch (mode) {
	case 0x10:
	case 0x20:
		fcn_005ceb20(obj, mode);
		break;
	case 0x30:
		fcn_005ceef0(obj, x);
		break;
	case 0x40:
		fcn_005ceaa0(obj);
		break;
	case 0x50:
		fcn_005cea10(obj);
		break;
	}
	fcn_00532ef0();
}
