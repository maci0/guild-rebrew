// FUNCTION: GOLD 0x510ad0
// SIZE: 896
// FUNCTION: GOLDTL 0x00514120
// SIZE: 891

#include <string.h>

// SIZE 0x2f4
typedef struct {
	char name[0x54];
	short used;
	char pad56[0x2f4 - 0x56];
} Variant;

// SIZE 0x40
typedef struct {
	unsigned short slot;
	char pad2[2];
	int id;
	char pad8[0x28];
	char name[0x10];
} Figure;

// SIZE 0xb4
typedef struct {
	char pad0[0xb0];
	int view;
} Scene;

// SIZE 0x4
typedef struct {
	int kind;
} Device;

extern int g_699364;
extern int g_67a370;
extern Figure* g_773da8;
extern char g_773d75;
extern Variant g_868060[4];
extern Device* g_6b8300;

void __cdecl fcn_00517250(char*, int);
void __cdecl fcn_004432d0(int, int);
char __cdecl fcn_00510b70(char*);
void __cdecl srv_LogWinsockError(void);
void __cdecl fcn_004f6740(void);
int __cdecl fcn_0051e070(void);
void* __cdecl fcn_00445600(int, int, int, char*);
void __cdecl fcn_00442be0(void*);
void __cdecl fcn_00437ac0(int, int, int, void*);
void __cdecl fcn_005109f0(void);
void __cdecl fcn_005105a0(void);
void __cdecl fcn_00510b40(void);
void __cdecl fcn_00513d40(char*);
void __cdecl fcn_004c44a0(void);
void __cdecl fcn_004c4f30(int, int, int, int);
int __cdecl fcn_004c4fc0(int, int, int, short, int, unsigned char, int, int);
void __cdecl fcn_004c44b0(void);
int __cdecl fcn_004c44c0(void);
void __cdecl fcn_004c3ff0(void);
void __cdecl fcn_004c4940(void);
void __cdecl ls_ID2Ptr(void);
Figure* __cdecl fcn_004c4480(int);
void __cdecl fcn_004c5150(int, int, char, int);
void __cdecl fcn_00512680(void);
void __cdecl fcn_00512910(void);
void __cdecl fcn_00535960(void);
void* __cdecl gm_StartFilteredEntitySearch(int, int, int);
void __cdecl fcn_005059b0(void*, int, int);
void* __cdecl gm_AddObjekt(void);
void __cdecl fcn_005016c0(void);
void __cdecl fcn_005016f0(int);
void __cdecl fcn_005017a0(int);
int __cdecl fcn_0045b700(Device*, int, int);

int __cdecl fcn_00514120(char* map)
{
	void* folder;
	int h;
	int i;
	void* s;

	g_699364 = 1;
	fcn_00517250(map, 0);
	fcn_004432d0(0, 0);
	if (fcn_00510b70(map) == 0) {
		return 1;
	}
	srv_LogWinsockError();
	fcn_004f6740();
	if (fcn_0051e070() != 0) {
		folder = fcn_00445600(0, 0x100, 0, "ordner_CITIES_GER");
	} else {
		folder = fcn_00445600(0, 0x100, 0, "ordner_CITIES_INT");
	}
	if (folder != 0) {
		fcn_00442be0(folder);
	}
	fcn_00437ac0(g_67a370, 0, 0x140, fcn_005109f0);
	fcn_00437ac0(g_67a370, 0, 0x40, fcn_005105a0);
	fcn_00437ac0(g_67a370, 0, 0x20, fcn_00510b40);
	fcn_00513d40("bk_BRUNNEN");
	fcn_00513d40("bk_GEFAENGNIS");
	fcn_00513d40("bk_HANDWERK");
	fcn_00513d40("bk_KIRCHE_KL");
	fcn_00513d40("bk_KIRCHE_MT");
	fcn_00513d40("bk_KIRCHE_GR");
	fcn_00513d40("bk_RATHAUS");
	fcn_00513d40("bk_STADTWACHE");
	fcn_00513d40("bk_WIRTSHAUS_KL");
	fcn_00513d40("bk_WIRTSHAUS_GR");
	fcn_00513d40("bk_WOHNSITZ_KL");
	fcn_00513d40("bk_WOHNSITZ_GR");
	fcn_00513d40("bk_ZUNFTHAUS");
	fcn_00513d40("bk_RAUBRITTERFESTE");
	fcn_00513d40("bk_DOMIZIL");
	fcn_00513d40("bk_STATUEN");
	fcn_004c44a0();
	fcn_004c4f30(0x44, -1, 0, 0);
	fcn_004c4f30(0x45, -1, 0, 0);
	h = fcn_004c4fc0(0xa, -1, -1, 0x12, -1, 0, 0, 1);
	fcn_004c44b0();
	while (fcn_004c44c0() == 0) {
		fcn_004c3ff0();
		fcn_004c4940();
		ls_ID2Ptr();
	}
	fcn_004c44a0();
	g_773da8 = fcn_004c4480(h);
	strcpy(g_773da8->name, "STADT");
	fcn_004c5150(g_773da8->id, -1, g_773d75, 200000000);
	while (fcn_004c44c0() == 0) {
		fcn_004c3ff0();
		fcn_004c4940();
		ls_ID2Ptr();
	}
	fcn_004c44b0();
	for (i = 1; i < 4; i++) {
		if (g_868060[i].used != 0) {
			fcn_004c5150(g_773da8->id, -1, (char) i, 200000000);
		}
	}
	fcn_00512680();
	fcn_004c44a0();
	fcn_00512910();
	fcn_004c44b0();
	while (fcn_004c44c0() == 0) {
		fcn_00535960();
	}
	for (s = gm_StartFilteredEntitySearch(1, 5, 0x1c); s != 0; s = gm_AddObjekt()) {
		fcn_005059b0(s, g_773da8->slot, g_773da8->slot);
	}
	fcn_005016c0();
	for (i = 0; i < 4; i++) {
		if (g_868060[i].name[0] == 0) {
			break;
		}
		fcn_005016f0(i);
	}
	fcn_004c44a0();
	fcn_005017a0((unsigned char) g_773d75);
	fcn_004c44b0();
	while (fcn_004c44c0() == 0) {
		fcn_00535960();
	}
	fcn_004432d0(1, 0);
	fcn_004432d0(0, 0);
	if (g_6b8300->kind == 0x80) {
		((Scene*) g_67a370)->view = fcn_0045b700(g_6b8300, 0x100, 2);
	} else if (g_6b8300->kind == 0x40) {
		((Scene*) g_67a370)->view = fcn_0045b700(g_6b8300, 0x80, 2);
	} else {
		((Scene*) g_67a370)->view = fcn_0045b700(g_6b8300, 0x100, 2);
	}
	return 0;
}
