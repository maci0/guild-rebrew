

extern char* gm_RichterKatholisch;
extern char* gm_RichterEvangelisch;
#include "client_packet_builder.h"

void __cdecl cm_BeginCommandSync(void);
int __cdecl fcn_004c4fc0(int a, int b, int c, int d, int e, int f, int g, int h);
void __cdecl cm_EndCommandSync(void);
int __cdecl fcn_004c44c0(void);
void __cdecl fcn_004c3ff0(void);
void __cdecl fcn_004c4940(void);
void __cdecl ls_ID2Ptr(void);
int* __cdecl fcn_004c4480(int h);

void __cdecl cm_AppendPacketFieldDelta(int a, int b, int off, int* v);
void __cdecl fcn_004c5360(void);

void __cdecl gm_CreateReligiousJudges(void)
{
	int a;
	int b;
	int v;

	cm_BeginCommandSync();
	a = fcn_004c4fc0(0xc, -1, -1, 0x12, -1, 0, 0, 0);
	b = fcn_004c4fc0(0xc, -1, -1, 0x12, -1, 0, 0, 0);
	cm_EndCommandSync();
	while (!fcn_004c44c0()) {
		fcn_004c3ff0();
		fcn_004c4940();
		ls_ID2Ptr();
	}
	gm_RichterKatholisch = (char*) fcn_004c4480(a);
	gm_RichterEvangelisch = (char*) fcn_004c4480(b);
	cm_BeginCommandSync();
	v = 0;
	cm_BeginPacketFieldDelta(gm_RichterKatholisch, *(int*) (gm_RichterKatholisch + 4));
	cm_AppendPacketFieldDelta(1, 1, gm_RichterKatholisch - g_aed32c + 0xc, &v);
	fcn_004c5360();
	v = 1;
	cm_BeginPacketFieldDelta(gm_RichterEvangelisch, *(int*) (gm_RichterEvangelisch + 4));
	cm_AppendPacketFieldDelta(1, 1, gm_RichterEvangelisch - g_aed32c + 0xc, &v);
	fcn_004c5360();
	cm_EndCommandSync();
	while (!fcn_004c44c0()) {
		fcn_004c3ff0();
		fcn_004c4940();
		ls_ID2Ptr();
	}
}
