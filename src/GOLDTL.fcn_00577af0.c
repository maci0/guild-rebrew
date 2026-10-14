


#include <string.h>

// SIZE 0xf8
struct msg {
	char pad0[4];
	unsigned char kind;
	char pad5[3];
	int owner;
	int target;
	char pad10[0x26];
	unsigned char code;
	char pad37[0x21];
	int who;
	int other;
	char pad60[0x98];
};

// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int owner;
	char pad8[0x214];
};

extern char g_7f4ca0[];

int __cdecl fcn_00577ab0(struct house*);
char* __cdecl gm_StartFilteredEntitySearch(int, ...);
float __cdecl fcn_00507f10(struct house*, int);
float __cdecl gm_RandomFloat01(void);
void __cdecl fcn_0051af00(char*, int, ...);
int __cdecl fcn_00545d40(int, int, char*, unsigned char, int, char*);
void __cdecl fcn_004c5530(struct msg*);

int __cdecl fcn_00577af0(int id, struct house* me)
{
	float a;
	float b;
	struct msg m;
	char text[0x400];
	char* e;
	struct house* h;

	if (fcn_00577ab0(me) != 0) {
		e = gm_StartFilteredEntitySearch(1, 1, id);
		if (e != 0) {
			h = &((struct house*)g_7f4ca0)[*(unsigned short*) (e + 0x27)];
			a = fcn_00507f10(h, 2);
			b = fcn_00507f10(me, 2);
			if (a - b * 0.5f + gm_RandomFloat01() * 0.5 < 0.8) {
				goto refuse;
			}
			a = fcn_00507f10(h, 3);
			b = fcn_00507f10(me, 3);
			if (a - b * 0.5f + gm_RandomFloat01() * 0.5 < 0.7) {
refuse:
				fcn_0051af00(text, 0x4032, me->id, me->id);
				fcn_00545d40(h->owner, -1, text, 1, 0x5fa, "_NACHRICHTEN_DOMIZIL_07");
				fcn_0051af00(text, 0x4034);
				fcn_00545d40(me->owner, -1, text, 1, 0x5fb, "_NACHRICHTEN_DOMIZIL_09");
			} else {
				fcn_0051af00(text, 0x4031, me->id);
				fcn_00545d40(h->owner, -1, text, 1, 0x5fa, "_NACHRICHTEN_DOMIZIL_06");
				fcn_0051af00(text, 0x4033);
				fcn_00545d40(me->owner, -1, text, 1, 0x5fb, "_NACHRICHTEN_DOMIZIL_09");
				memset(&m, 0, sizeof(m));
				m.kind = 0x9b;
				m.owner = h->owner;
				m.target = id;
				m.who = me->owner;
				m.other = h->owner;
				m.code = 2;
				fcn_004c5530(&m);
				return 1;
			}
		}
	}
	return 0;
}
