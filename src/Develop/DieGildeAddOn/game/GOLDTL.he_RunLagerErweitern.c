#include "client_types.h"

extern pos14_7f4c00 gm_GameTime;
extern char* g_aed32c;
extern char g_7f4ca4[];

int __cdecl fcn_00500cb0(void*, char*);
void __cdecl gm_AddTime(void*, int, int, int);
int __cdecl gm_ResolveEntityById(void**, void**, void**, int);
void __cdecl ReportClientMessage(const char*);
void __cdecl he_FreeAction(char*);
void __cdecl cm_BeginPacketFieldDelta(char*, int);
int __cdecl fcn_004c4670(unsigned char, unsigned char, int, void*);
void __cdecl fcn_004c5360(void);
int __cdecl gm_StartFilteredEntitySearch(int, ...);
int __cdecl fcn_0050dc90(int);
int __cdecl fcn_005049a0(void*);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, char*);

/* ADDRESS: GOLDTL 0x0055ffe0 */
void __cdecl he_RunLagerErweitern(char* action)
{
	char* q;
	char buf[1024];
	int v5[2];
	int ent;
	char* info;
	int cat;
	int msg;
	int px;
	int entityId;
	int categoryId;

	switch (*(int*) (action + 0x70)) {
	case 0:
		*(int*) (action + 0x70) = *(int*) (action + 0x70) + 1;
		return;
	case 1:
		q = action + 0x52;
		break;
	case 0xfffffffe:
	case 0xffffffff:
		he_FreeAction(action);
		return;
	default:
		return;
	}
	if (fcn_00500cb0(q, (char*) &gm_GameTime) >= 0)
		return;
	v5[1] = 1;
	gm_ResolveEntityById(0, (void**) v5, 0, *(unsigned int*) (action + 0xac));
	if (v5[0]) {
		cm_BeginPacketFieldDelta((char*) v5[0], *(int*) ((char*) v5[0] + 2));
		fcn_004c4670(4, 1, (v5[0] - (int) g_aed32c) + 0xe, &v5[1]);
		fcn_004c5360();
		if (--*(int*) (action + 0xb0) <= 0) {
		msg = 0x606;
		ent = (int) gm_StartFilteredEntitySearch(1, 1, *(unsigned int*) (action + 0x10));
		if (ent) {
			info = (char*) fcn_0050dc90(ent);
			if (info != 0 && (*(unsigned char*) (info + 0x1b4) & 1))
				msg = 0x60b;
			cat = fcn_005049a0((void*) ent);
			io_FormatTextBuffer(buf, 0x1bbb, ent);


			if (cat) {
				categoryId = *(int*) ((char*) cat + 2); entityId = *(int*) ((char*) ent + 1);
				px = *(int*) (g_7f4ca4 + (*(unsigned short*) (action + 8)) * 0x21c);
				he_MessageBoxQuickjump(px, -1, buf, 0, msg, entityId, categoryId, 0, 0);
			} else { entityId = *(int*) ((char*) ent + 1);
				px = *(int*) (g_7f4ca4 + (*(unsigned short*) (action + 8)) * 0x21c);
				he_MessageBoxQuickjump(px, -1, buf, 0, msg, entityId, -1, 0, 0);
			}
		}
		} else {
			*(pos14_7f4c00*) q = gm_GameTime;
			gm_AddTime(q, 0, 0xf, 0);
			return;
				}
	}
	else {
		ReportClientMessage("he_RunLagerErweitern():Wrong LagerID...");
	}
	he_FreeAction(action);
}
