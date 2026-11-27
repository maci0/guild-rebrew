#include "Develop/DieGildeAddOn/game/building_prototype.h"


void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)

// SIZE 0x50
typedef struct {
	int a;
	int size;
	int c;
	int d;
	int kind;
	int pad[14];
	int id;
} Req;

extern unsigned char* lpGebaeudePROT;

int __cdecl d2_CheckOwnerBlocked(unsigned char*);
void __cdecl d2_InitPlayerBar(unsigned char*, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl d2_ShowThievesGuildSpyDialog(void);
void __cdecl fcn_005bdc30(int, Req*, char*, void*, int);
void __cdecl d2_RestoreHudAfterDialog(void);
void __cdecl sv_ClearObjectSelection(void);

void __cdecl d2_StartThievesGuildSpyPicker(unsigned char* building)
{
	Req req;
	char text[0x400];

	if (d2_CheckOwnerBlocked(building) == 0) {
		memset(&req, 0, sizeof(req));
		req.size = 0x400;
		if (building != 0) {
			d2_InitPlayerBar(building, 0);
			req.id = 0x727;
			req.kind = 7;
			if (*(char *)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*building].category == 0x13) {
				req.c = 0x90010;
				req.d = 0;
			}
			else {
				req.c = 0xa7fd43b4;
				req.d = 1;
			}
			io_FormatTextBuffer(text, 0x19f6);
			fcn_005bdc30(1, &req, text, d2_ShowThievesGuildSpyDialog, 0);
			d2_RestoreHudAfterDialog();
			sv_ClearObjectSelection();
		}
	}
}
