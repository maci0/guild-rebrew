


#include <string.h>

// SIZE 0x50
typedef struct {
	int a;
	int size;
	__int64 cd;
	int kind;
	int f14;
	int pad18;
	int ids[8];
	int pad3c[5];
} Req;

// SIZE 0x21c
typedef struct {
	char pad0[9];
	unsigned char b9;
	char pada[0x212];
} House;

extern __int64 gm_TargetPersonTypeMask;
extern char gm_EntitySlotTable[];
#include "Develop/DieGildeAddOn/game/game_player.h"

void __cdecl io_FormatTextBuffer(char*, int, ...);
unsigned char* __cdecl d2_OpenTargetPicker(Req*, char*, int, int);
unsigned char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_HasActiveSpecialObject(unsigned char*, int);
void __cdecl cm_RequestCopyEntityData(int, int, int, int);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, int);

/* ADDRESS: GOLDDE 0x005be740 */
int __cdecl gm_ObjGrantAffinity25(unsigned char* obj, int* arg)
{
	Req req;
	char text[0x100];
	char text2[0x400];
	unsigned char* e;
	int result;
	int k;

	result = 0;
	if (obj[2] == 6) {
		memset(&req, 0, sizeof(req));
		memset(req.ids, 0xff, sizeof(req.ids));
		io_FormatTextBuffer(text, 0x9c);
		result = 1;
		req.kind = 6;
		req.a = 1;
		req.size = (((House*)gm_EntitySlotTable)[gm_LocalPlayerSlot].b9 ? 1 : 2) | 0x400;
		req.cd = gm_TargetPersonTypeMask;
		e = d2_OpenTargetPicker(&req, text, 0, 0);
		if (e == 0) {
			return 0;
		}
	} else {
		e = gm_LookupEntityRecordById(arg[1]);
		if (e != 0) {
			result = 1;
		}
	}
	if (result) {
		k = (gm_HasActiveSpecialObject(obj, 0x2c5) != 0) + 1;
		cm_RequestCopyEntityData(*(int*) (obj + 4), *(int*) (e + 4), k * 25, 1);
		if (e[2] == 6 || e[2] == 7) {
			io_FormatTextBuffer(text2, 0xfe9, *(unsigned short*) obj);
			he_PostEntityMessage(*(int*) (e + 4), -1, text2, 0, 0x5ec, 0);
		}
	}
	return result;
}
