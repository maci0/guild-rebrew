

typedef struct Ent {
	unsigned short id;
	unsigned char kind;
} Ent;

typedef struct Party {
	char pad0[0x30];
	unsigned char count;
	char pad31[3];
	int ids[1];
} Party;

typedef struct Obj {
	char pad0[0x88];
	int owner;
} Obj;

typedef struct Unit {
	char pad0[0x184];
	Obj* obj;
} Unit;

typedef struct Slot {
	char pad0[0x35c];
} Slot;
// SIZE 0x35c

typedef struct Game {
	int pad0;
	int player;
} Game;

extern int g_6b7fb8;
#include "client_sound.h"
extern int g_772e94;
extern int g_772ea4;
extern int g_772ea8;
extern int g_774654;
extern unsigned char g_7747b0;
extern char g_14cf950;
extern char* g_7e4260[32];
extern int g_67a370;
extern char g_6b5c60[];
extern char* g_14a97d4;
extern char* g_772eb4;
extern unsigned short* g_772f24;
extern int g_68b79c;
extern char g_9b0e20[];

unsigned short __cdecl gm_RandomMod(int n);
void __cdecl fcn_004d1a80(void);
void __cdecl fcn_004d7e50(int);
#include "Develop/Units/Msx/msx.h"
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00405540(Obj*, int);
void __cdecl fcn_00533a40(char*);
void __cdecl fcn_004d7d70(int);
Ent* __cdecl fcn_00508e40(int);
void __cdecl fcn_004d3fe0(Ent*);
void __cdecl fcn_004d4f30(Party*);
void __cdecl fcn_004d8d00(Slot*);
void __cdecl fcn_004d7f70(void);

void __cdecl fcn_004d9f20(int arg)
{
	unsigned int last;
	int r;
	Ent* e;
	int id;
	int i;

	last = (*(volatile unsigned int*)&g_6b7fb8) - 0x15e;
	r = gm_RandomMod(100);
	fcn_004d1a80();
	fcn_004d7e50(arg);
	g_772efc = 0;
	if (r < 0x32) {
		g_772efc = fcn_00420780("Athmos\\Kampfathmo_1.mp3", 0xb);
	} else {
		g_772efc = fcn_00420780("Athmos\\Kampfathmo_2.mp3", 0xb);
	}
	g_772e94 = 0;
	while (fcn_005373e0(fcn_004d9f20, 0xfd6c6) != 0) {
		if (g_772ea8 != 0) {
			break;
		}
		if (((*(int*)&g_7747b0) & 4) == 0 && g_14cf950 == 0x39) {
			g_772e94 = g_772e94 == 0;
			for (i = 0; i < 0x20; i++) {
				if (((Unit**)g_7e4260)[i] != 0 && ((Unit**)g_7e4260)[i]->obj->owner == g_67a370) {
					fcn_00405540(((Unit**)g_7e4260)[i]->obj, g_772e94);
				}
			}
			fcn_00533a40(&(*(char*)g_6b5c60));
		}
		if (g_772e94 != 0) {
			fcn_00533a40(g_14a97d4);
		} else {
			fcn_004d7d70(arg);
		}
		if (g_772ea4 != 0 || g_772ea8 != 0) {
			g_774654 = 1;
		} else if (g_772e94 == 0) {
			if ((*(volatile unsigned int*)&g_6b7fb8) > last + 0x1a4) {
				for (i = 0; i < ((Party*)g_772eb4)->count; i++) {
					id = ((Party*)g_772eb4)->ids[i];
					if (id != -1) {
						e = fcn_00508e40(id);
						if (e != 0 && e->kind != 6 && e->kind != 7) {
							fcn_004d3fe0(e);
						}
					}
				}
				last = (*(volatile unsigned int*)&g_6b7fb8);
			}
			if (((Game*)g_772f24)->player == g_68b79c) {
				fcn_004d4f30(((Party*)g_772eb4));
				for (i = 0; i < ((Party*)g_772eb4)->count; i++) {
					if (((Party*)g_772eb4)->ids[i] != -1) {
						fcn_004d8d00(&((Slot*)g_9b0e20)[i]);
					}
				}
			}
			if (g_772ea4 != 0 || g_772ea8 != 0) {
				g_774654 = 1;
			}
		}
	}
	fcn_004d7f70();
}
