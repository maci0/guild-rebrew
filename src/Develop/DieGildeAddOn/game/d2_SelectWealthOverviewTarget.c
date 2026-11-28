


#include <string.h>

typedef struct
{
	int x0;
	int x4;
	__int64 mask;
	int x10;
	char pad14[0x3c];
} Query;
// SIZE 0x50

extern __int64 gm_TargetPersonTypeMask;

void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl d2_OpenTargetPicker(Query*, char*, int, void*);
void __cdecl d2_ShowWealthOverviewDialog(void);
void __cdecl d3_EndCameraAndUiMode(void);

void __cdecl d2_SelectWealthOverviewTarget(void)
{
	Query q;
	char buf[0x40];

	memset(&q, 0, sizeof(q));
	q.x4 = 0x400;
	q.x10 = 6;
	q.mask = gm_TargetPersonTypeMask;
	io_FormatTextBuffer(buf, 0x18ec);
	d2_OpenTargetPicker(&q, buf, 0, (void*) d2_ShowWealthOverviewDialog);
	d3_EndCameraAndUiMode();
}
