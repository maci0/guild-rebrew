


#include <string.h>

// SIZE 0x8c
typedef struct {
	unsigned char spouse_look;
	unsigned char child_look;
	char enabled;
	unsigned char look;
	int face;
	unsigned char hair;
	unsigned char body;
	char name[0x20];
	char family[0x22];
	int dynasty;
	char skills[5];
	char motto[0x33];
	int emblem;
} Setup;

// SIZE 0x208
typedef struct {
	unsigned short slot;
	char pad2[2];
	int id;
	char pad8[0x28];
	char name[0x10];
	char family[0x10];
	short look;
	char pad52[2];
	int home;
	char pad58[4];
	int spouse;
	int partner;
	int child;
	int parent;
	char pad6c[0x14];
	char skills[5];
	char pad85[0x107];
	int emblem;
	char pad190[0x64];
	char motto[0x14];
} Figure;

extern char g_7e23e0[];
extern char* g_14a60d0[];
extern char* g_14a5dbc[];
extern unsigned char g_773d75;
extern signed char g_6a3440;

void __cdecl fcn_004b3b40(void);
void __cdecl fcn_004c44a0(void);
int __cdecl fcn_004c5040(int, int, int, unsigned char, int, unsigned char, unsigned char, char*, char*);
void __cdecl fcn_004c44b0(void);
int __cdecl fcn_004c44c0(void);
void __cdecl fcn_00535960(void);
Figure* __cdecl fcn_004c4480(int);
int __cdecl fcn_004c4fc0(int, int, int, short, int, unsigned char, int, int);
unsigned short __cdecl gm_RandomMod(int);
void __cdecl fcn_004fda30(int);
void __cdecl fcn_004c54c0(int, int, int, int);
void __cdecl fcn_004c5150(int, int, char, int);
void __cdecl fcn_004b3e10(int, int, int);

void __cdecl fcn_005435e0(void)
{
	Figure* p;
	Figure* spouse;
	Figure* child;
	int h;
	int i;

	fcn_004b3b40();
	if ((*(Setup*)g_7e23e0).enabled == 0) {
		return;
	}
	fcn_004c44a0();
	h = fcn_004c5040(-1, -1, 0x10, (*(Setup*)g_7e23e0).look, (*(Setup*)g_7e23e0).face, (*(Setup*)g_7e23e0).hair, (*(Setup*)g_7e23e0).body,
		(*(Setup*)g_7e23e0).name, (*(Setup*)g_7e23e0).family);
	fcn_004c44b0();
	while (fcn_004c44c0() == 0) {
		fcn_00535960();
	}
	p = fcn_004c4480(h);
	fcn_004c44a0();
	h = fcn_004c4fc0(9, -1, -1, gm_RandomMod(4) + 0x20, -1, (*(Setup*)g_7e23e0).child_look, 0, 1);
	i = fcn_004c4fc0(9, -1, -1, gm_RandomMod(4) + 0x20, -1, (*(Setup*)g_7e23e0).spouse_look, 0, 0);
	fcn_004c44b0();
	while (fcn_004c44c0() == 0) {
		fcn_00535960();
	}
	child = fcn_004c4480(h);
	spouse = fcn_004c4480(i);
	strncpy(spouse->family, (*(Setup*)g_7e23e0).family, 0x10);
	child->look = p->look;
	child->home = p->home;
	child->parent = p->id;
	strcpy(child->name, g_14a60d0[gm_RandomMod(0x70)]);
	fcn_004fda30(child->slot);
	spouse->look = p->look;
	spouse->home = p->home;
	spouse->parent = p->id;
	strcpy(spouse->name, g_14a5dbc[gm_RandomMod(0xbf)]);
	fcn_004fda30(spouse->slot);
	child->spouse = spouse->id;
	spouse->spouse = child->id;
	p->partner = spouse->id;
	p->child = child->id;
	child->parent = p->id;
	spouse->parent = p->id;
	strcpy(p->motto, (*(Setup*)g_7e23e0).motto);
	p->emblem = (*(Setup*)g_7e23e0).emblem;
	fcn_004c54c0(p->id, spouse->id, 0x7f, 0);
	fcn_004c54c0(spouse->id, p->id, 0x7f, 0);
	fcn_004c54c0(p->id, child->id, 0x7f, 0);
	fcn_004c54c0(child->id, p->id, 0x7f, 0);
	fcn_004c54c0(spouse->id, child->id, 0x7f, 0);
	fcn_004c54c0(child->id, spouse->id, 0x7f, 0);
	fcn_004c5150(spouse->id, -1, (*(char*)&g_773d75), (gm_RandomMod(0x200) + 0x1f4) << 5);
	fcn_004c5150(child->id, -1, (*(char*)&g_773d75), (gm_RandomMod(0x200) + 0x1f4) << 5);
	if (g_6a3440 > -1) {
		fcn_004b3e10(p->id, (*(Setup*)g_7e23e0).dynasty, 0);
	}
	for (i = 0; i < 5; i++) {
		p->skills[i] = (*(Setup*)g_7e23e0).skills[i];
	}
}
