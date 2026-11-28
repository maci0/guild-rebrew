


typedef struct
{
	int a;
	int size;
	int c;
	int d;
	int kind;
	int pad[15];
} Req;
// SIZE 0x50

#include "Develop/DieGildeAddOn/game/entity_record.h"







#include "Develop/DieGildeAddOn/game/game_player.h"

extern int g_14b5bc0;
extern char* g_14b5bc8;
extern char str_empty[];

void __cdecl d2_ShowModalMessageBox(int, int);
int __cdecl d2_CheckActionBlocker(ENTITY_RECORD*, int);
int __cdecl d2_OpenTargetPicker(Req*, char*, char*, void*);
void __cdecl d3_EndCameraAndUiMode(void);
void __cdecl d2_ShowSchneidereiPlauschDialog(void);

/* The request's zero-fill is the original's hand-written block-fill
 * prelude; recorded C memset probes did not emit it (archived docs/codegen-walls.md
 * section 6b). */
void __cdecl d2_SelectPlauschTarget(void)
{
	Req req;
	Req* p;
	int n;

	if ((*(int*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot].flags_1cc) & 0x20000) {
		d2_ShowModalMessageBox(g_14b5bc0, 4);
		return;
	}
	if (d2_CheckActionBlocker(((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot]), 1)) {
		n = 0x50;
		p = &req;
		__asm {
			mov edi, p
			mov ebx, n
			xor eax, eax
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L1
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L1:
			add ecx, ebx
			rep stosb
		}
		req.a = 1;
		req.size = 0x400;
		req.kind = 6;
		d2_OpenTargetPicker(&req, g_14b5bc8, str_empty, d2_ShowSchneidereiPlauschDialog);
	}
	d3_EndCameraAndUiMode();
}
