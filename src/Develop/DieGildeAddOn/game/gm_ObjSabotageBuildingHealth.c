#include "Develop/DieGildeAddOn/game/spiel.h"



#include <string.h>

// SIZE 0x50
typedef struct {
	int a;
	int size;
	__int64 cd;
	int kind;
	int f14;
	int pad18;
	unsigned short ids[16];
	int pad3c[5];
} Req;

#pragma pack(1)
// SIZE 0x29
typedef struct {
	char pad0[0x27];
	unsigned short w27;
} Unit;
#pragma pack()

// SIZE 0x21c
typedef struct {
	unsigned short id;
	unsigned char b2;
	char pad3;
	int f4;
	char pad8[0x14];
	float f1c;
	char pad20[0x14c];
	Unit* f16c;
	char pad170[0xac];
} House;

extern char gm_EntitySlotTable[];
extern __int64 gm_TargetPersonTypeMask;
extern char* txt_TargetBuildingPrompt;
extern char* g_14a5590;

Unit* __cdecl d2_RunCityScrollMapDialog(int, Req*, char*, int, int);
unsigned char* __cdecl d2_OpenTargetPicker(Req*, char*, int, int);
unsigned char* __cdecl gm_LookupEntityRecordById(int);

unsigned short __cdecl gm_RandomMod(int);
void __cdecl cm_RequestCopyEntityData(int, int, int, int);
float __cdecl gm_RandomFloat01(void);
float __cdecl gm_ApplyEntityHealthDelta(int, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, int);
void __cdecl d2_ShowUseObjDialog(char*);

/* ADDRESS: GOLDDE 0x005bf750 */
int __cdecl gm_ObjSabotageBuildingHealth(unsigned char* obj, int* arg)
{
	Unit* q;
	Req req;
	char text2[0x200];
	char text[0x800];
	unsigned char* e;
	int i;

	if (obj[2] == 6) {
		memset(&req, 0, sizeof(req));
		memset(req.ids, 0xff, sizeof(req.ids));
		req.a = 1;
		req.size = -1;
		req.kind = 6;
		req.cd = 0x1a0744300;
		q = d2_RunCityScrollMapDialog(1, &req, txt_TargetBuildingPrompt, 0, 0);
		if (q == 0) {
			return 0;
		}
		req.f14 = 3;
		req.ids[0] = q->w27;
		req.size = 0x400;
		req.kind = 6;
		req.cd = gm_TargetPersonTypeMask;
		e = d2_OpenTargetPicker(&req, g_14a5590, 0, 0);
		if (e == 0) {
			return 0;
		}
	} else {
		e = gm_LookupEntityRecordById(arg[1]);
		if (e == 0) {
			return 0;
		}
		gm_ResolveEntityById((void**) (&q), 0, 0, arg[2]);
		if (q == 0) {
			return 0;
		}
	}
	cm_RequestCopyEntityData(*(unsigned short*) e, ((House*)gm_EntitySlotTable)[q->w27].f4, -20 - gm_RandomMod(0x20), 1);
	for (i = 0; i < 768; i++) {
		if (((House*)gm_EntitySlotTable)[i].b2 == 0 && ((House*)gm_EntitySlotTable)[i].f16c == q) {
			gm_ApplyEntityHealthDelta(i, (int) -((gm_RandomFloat01() * 0.2f + 0.1f) * ((House*)gm_EntitySlotTable)[i].f1c));
		}
	}
	if (e[2] == 6 || e[2] == 7) {
		io_FormatTextBuffer(text, 0x100b, q->w27, q->w27, q);
		he_PostEntityMessage(*(int*) (e + 4), -1, text, 0, 0x5fb, 0);
	}
	if (obj[2] == 6) {
		io_FormatTextBuffer(text2, 0x109b, *(unsigned short*) e, q->w27, q);
		io_FormatTextBuffer(text, 0xfe8, text2);
		d2_ShowUseObjDialog(text);
	}
	arg[4] = 1;
	return 1;
}
unsigned char _dpad_14a558c[488];
