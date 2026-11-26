


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
void __cdecl fcn_0052a0c0(char*, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl fcn_005bdc30(int, Query*, char*, void*, int);
void __cdecl d2_OpenRaubzugDialog(int, char*);
void __cdecl d2_RestoreHudAfterDialog(void);
void __cdecl sv_ClearObjectSelection(void);

void __cdecl fcn_0059dc50(char* e)
{
	Query q;
	char buf[0x400];

	if (d2_CheckOwnerBlocked(e) != 0) {
		return;
	}
	memset(&q, 0, sizeof(q));
	q.x4 = 0x400;
	if (e == 0) {
		return;
	}
	fcn_0052a0c0(e, 0);
	q.x4c = 0x727;
	q.x10 = 6;
	q.x8 = 0xa07443a0;
	q.xc = 1;
	io_FormatTextBuffer(buf, 0x1a83);
	fcn_005bdc30(1, &q, buf, (void*) d2_OpenRaubzugDialog, 0);
	d2_RestoreHudAfterDialog();
	sv_ClearObjectSelection();
}
