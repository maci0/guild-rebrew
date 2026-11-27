


void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)

typedef struct
{
	int a;
	int size;
	int c;
	int d;
	int kind;
	int pad[14];
	int id;
} Req;
// SIZE 0x50

extern __int64 g_666018;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_14aba0c;

int __cdecl d2_CheckOwnerBlocked(char*);
char* __cdecl he_StartHandlungSearch(int, int, int);
char* __cdecl he_fn_Handlung(void);
char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl cm_SendSetHE(int, char*);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl d2_InitPlayerBar(char*, int);
int __cdecl d2_OpenTargetPicker(Req*, char*, int, void*);
void __cdecl d2_RestoreHudAfterDialog(void);
void __cdecl d3_EndCameraAndUiMode(void);
void __cdecl d2_ShowModalMessageBox(int, int);
void __cdecl d2_RunEntfuehrungDialog(void);

void __cdecl d2_StartEntfuehrungDialog(char* building)
{
	Req req;
	char text[0x40];
	char* p;
	char* q;

	if (d2_CheckOwnerBlocked(building) != 0) {
		return;
	}
	for (p = he_StartHandlungSearch(1, 0, 0x3c); p != 0; p = he_fn_Handlung()) {
		if (*(int*) (p + 0xb4) == *(int*) (building + 1)) {
			d2_ShowModalMessageBox(g_14aba0c, 0);
			return;
		}
	}
	for (p = he_StartHandlungSearch(1, 0, 0x3d); p != 0; p = he_fn_Handlung()) {
		if (*(int*) (p + 0xb0) == *(int*) (building + 1)) {
			q = gm_LookupEntityRecordById(*(int*) (p + 0xac));
			if (q != 0 && (unsigned char) q[0x1b1] > 0) {
				d2_ShowModalMessageBox(g_14aba0c, 0);
				return;
			}
			*(int*) (p + 0x84) = cm_SendSetHE(-1, p);
		}
	}
	memset(&req, 0, sizeof(req));
	memset(&req.pad[2], -1, 0x20);
	req.a = 0;
	req.size = 0x400;
	req.kind = 6;
	req.c = (*(int*)&g_666018);
	req.d = g_66601c;
	io_FormatTextBuffer(text, 0x19b8);
	d2_InitPlayerBar(building, 0);
	d2_OpenTargetPicker(&req, text, 0, (void*) d2_RunEntfuehrungDialog);
	d2_RestoreHudAfterDialog();
	d3_EndCameraAndUiMode();
}
