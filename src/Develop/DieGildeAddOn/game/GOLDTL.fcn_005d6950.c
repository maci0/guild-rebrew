


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

// SIZE 0x18
typedef struct {
	int f0;
	int f4;
	char pad8[8];
	char b10;
	char pad11[7];
} Info;

extern __int64 g_666018;
extern char s_6accdc[];

int __cdecl amt_GetRoleTemplate(int, Info*);
unsigned char* __cdecl gm_LookupEntityRecordById(int);
#include "Develop/DieGildeAddOn/game/aemter.h"
void __cdecl cm_SendLogAction(char*);
int __cdecl cm_RequestChangeBits(int, int, int, int, int);
void __cdecl cm_RequestCopyEntityData(int, int, int, int);
int __cdecl cm_SendTraceEnd(char*);
void __cdecl io_FormatTextBuffer(char*, int, ...);
unsigned short* __cdecl fcn_005cadc0(int, Req*, char*, char*, int);
int __cdecl cm_GetCommandStatus(int);
void __cdecl cm_StepCommandQueue(void);
void __cdecl fcn_00526120(char*, int);

int __cdecl d2_ShowAbsetzenDialog(unsigned char* e, int* o)
{
	Info x;
	Req req;
	Info info;
	Info y;
	char text3[0x100];
	char text2[0x100];
	char text1[0x100];
	unsigned char* t;
	int v;
	unsigned char* q;
	unsigned short* g;
	int h1;
	int h;

	if (o[0] == 3) {
		t = e;
		v = e[0x166];
	} else if (o[0] == 4 && (t = (unsigned char*) o[0x87]) != 0) {
		v = t[0x166];
	} else {
		return 0x60;
	}
	if (!amt_GetRoleTemplate(v, &info)) {
		return 0x60;
	}
	if (e[2] != 6) {
		q = gm_LookupEntityRecordById(o[0x85]);
		if (q == 0) {
			return 0x60;
		}
		if (!srv_GetEntityOfficeSlot(q, &x, &y)) {
			return 0x60;
		}
		if (info.f4 != x.f4) {
			return 0x60;
		}
		cm_SendLogAction(s_6accdc);
		amt_AssignEntityOfficeDefault(q, t);
		cm_RequestChangeBits(*(int*) (t + 4), 0x1c8, 4, 0x200000, 0);
		cm_RequestCopyEntityData(*(int*) (e + 4), *(int*) (q + 4), -0x28, 1);
		cm_SendTraceEnd(s_6accdc);
		return 0x10;
	}
	memset(&req, 0, sizeof(req));
	memset(req.ids, 0xff, sizeof(req.ids));
	req.ids[0] = *(unsigned short*) e;
	if ((unsigned char*) o[0x87] == t) {
		req.ids[1] = *(unsigned short*) t;
	}
	req.kind = 6;
	req.f14 = 3;
	req.size = 0x400;
	req.cd = g_666018;
	io_FormatTextBuffer(text1, 0x1d98);
	io_FormatTextBuffer(text2, 0x1d99);
	g = fcn_005cadc0(info.f4, &req, text1, text2, 0);
	if (g != 0) {
		if (!srv_GetEntityOfficeSlot((unsigned char*) g, &y, &x)) {
			return 0x60;
		}
		if (x.b10 != 1) {
			goto refused;
		}
		cm_SendLogAction(s_6accdc);
		amt_AssignEntityOfficeDefault((unsigned char*) g, t);
		h1 = cm_RequestChangeBits(*(int*) (t + 4), 0x1c8, 4, 0x200000, 0);
		cm_RequestCopyEntityData(*(int*) (e + 4), *(int*) (g + 2), -0x14, 1);
		h = cm_SendTraceEnd(s_6accdc);
		while (cm_GetCommandStatus(h) == 0) {
			cm_StepCommandQueue();
		}
		if (cm_GetCommandStatus(h) == 2) {
		refused:
			io_FormatTextBuffer(text3, 0x1d9a, *g);
			fcn_00526120(text3, 0);
			return 0x20;
		}
		while (cm_GetCommandStatus(h1) == 0) {
			cm_StepCommandQueue();
		}
		io_FormatTextBuffer(text3, 0x1d9b, *g, *g);
		fcn_00526120(text3, 0);
		return 0x90;
	}
	return 0x20;
}
