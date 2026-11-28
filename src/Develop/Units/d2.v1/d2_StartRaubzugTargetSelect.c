


#include <string.h>

typedef struct
{
	int x0;
	int x4;
	unsigned int x8;
	int xc;
	int x10;
	char pad14[0x38];
	int x4c;
} Query;
// SIZE 0x50

int __cdecl d2_CheckOwnerBlocked(char*);
void __cdecl d2_InitPlayerBar(char*, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl d2_RunCityScrollMapDialog(int, Query*, char*, void*, int);
void __cdecl d2_OpenRaubzugDialog(int, char*);
void __cdecl d2_RestoreHudAfterDialog(void);
void __cdecl sv_ClearObjectSelection(void);

/* ADDRESS: GOLDDE 0x00582ef0 */
void __cdecl d2_StartRaubzugTargetSelect(char* building)
{
	Query q;
	char buf[0x400];

	if (d2_CheckOwnerBlocked(building) != 0) {
		return;
	}
	memset(&q, 0, sizeof(q));
	q.x4 = 0x400;
	if (building == 0) {
		return;
	}
	d2_InitPlayerBar(building, 0);
	q.x4c = 0x727;
	q.x10 = 6;
	q.x8 = 0xa07443a0;
	q.xc = 1;
	io_FormatTextBuffer(buf, 0x1a83);
	d2_RunCityScrollMapDialog(1, &q, buf, (void*) d2_OpenRaubzugDialog, 0);
	d2_RestoreHudAfterDialog();
	sv_ClearObjectSelection();
}
