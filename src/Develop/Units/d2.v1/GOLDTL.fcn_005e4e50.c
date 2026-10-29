


typedef struct Ent {
	unsigned short id;
	unsigned char kind;
	char pad3;
	int handle;
	char pad8[0x21c - 8];
} Ent;
// SIZE 0x21c

extern char g_7f4ca0[];
extern unsigned short g_774970;
extern char s_6ad3c4[];
extern char s_681140[];
extern char s_6ad3bc[];
extern char s_6ad3a8[];
extern char* g_7746c4;
extern int g_14ce8e0;
extern int g_100f1dc;
extern int g_67d370;
extern int g_774654;

int __cdecl fcn_00470820(int, int, char*);
int __cdecl fcn_004f65a0(Ent*, int, int*, int*);
int __cdecl fcn_0050c710(int, int, int);
int __cdecl fcn_00472830(int, int);
void __cdecl fcn_005340f0(int);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_005338a0(void);
void __cdecl d2_SetForm(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_00472640(int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_004c58b0(int, int);
void __cdecl fcn_004c6ae0(int, int);
void __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, char*);
void __cdecl fcn_00471e30(int);

void __cdecl fcn_005e4e50(Ent* other)
{
	int count;
	int yes;
	int found;
	int list[4];
	char text[0x400];
	Ent* me;
	int h;
	int max;
	int i;

	me = &((Ent*)g_7f4ca0)[g_774970];
	h = fcn_00470820(0, 0, s_6ad3c4);
	found = fcn_004f65a0(&((Ent*)g_7f4ca0)[g_774970], 4, list, &count);
	if ((*(int*)&g_7746c4)) {
		max = fcn_0050c710((*(int*)&g_7746c4), 0x24, 1);
	} else {
		max = 1;
	}
	if (count >= max + 1) {
		count = max + 1;
	}
	fcn_005340f0(fcn_00472830(h, 0));
	fcn_00471b60(h);
	fcn_005338a0();
	d2_SetForm(h, 1);
	fcn_00519190(0x4227);
	fcn_00519190(0x422b, other->id, count, 0x422c, other->id, 1);
	d2_SetForm(h, 2);
	yes = fcn_00472250(h, 2, fcn_00519190((int) s_681140, 0x422d));
	fcn_00519190((int) s_6ad3bc, 0x422e);
	if (found == 0 || count == 0) {
		fcn_00472640(yes, 0);
	}
	while (fcn_005373e0(fcn_005e4e50, 0x67fff)) {
		if (g_14ce8e0 || g_100f1dc == 1) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1 && g_67d370 == yes) {
			if (found) {
				for (i = 0; i < count; i++) {
					fcn_004c58b0(list[i], ((Ent*)g_7f4ca0)[g_774970].handle);
				}
				fcn_004c6ae0(((Ent*)g_7f4ca0)[g_774970].handle, -1);
				fcn_004c6ae0(other->handle, -1);
				fcn_004c5420(me->handle, 0x1cc, 4, 0x20000, 0);
				fcn_0051af00(text, 0x422f, other->id);
				fcn_00545d40(((Ent*)g_7f4ca0)[g_774970].handle, -1, text, 0, 0x5ec, 0);
				if (other->kind == 6 || other->kind == 7) {
					fcn_0051af00(text, 0x4230, g_774970, 1);
					fcn_00545d40(other->handle, -1, text, 0, 0x5ec, s_6ad3a8);
				}
				g_774654 = 3;
			} else {
				fcn_004c6ae0(other->handle, -1);
				g_774654 = 3;
			}
		}
	}
	fcn_00471e30(h);
}
