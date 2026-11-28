#include "Develop/client_types.h"

int __cdecl gm_ResolveEntityById();
int __cdecl gm_GetElapsedMinutes(void*, void*);
void __cdecl gm_ChangeObjektZustand(int, int);
void __cdecl gm_AddTime(void*, int, int, int);
void* __cdecl gm_QueryEntities(int, int, int, int, int);
int __cdecl gm_SearchTable67(int);
int __cdecl gm_FindBuildingPrimarySlot(unsigned char*);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, char*);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);
void __cdecl cm_BeginPacketFieldDelta(char*, int);
void __cdecl cm_AppendPacketFieldDelta(unsigned char, unsigned char, unsigned short, char*);
void __cdecl cm_RequestChangeAttribute(void);
void __cdecl he_FreeAction(char*);
extern pos14_7f4c00 gm_GameTime;

/* One stage of the message-box tick; state lives at +0x70 of the caller's record. */
/* ADDRESS: GOLDTL 0x0055f300 */
void __cdecl he_RunObjektUpgrade(char* e)
{
	void* item;
	char ch;
	char buf[128];
	int* msg;
	int* p;
	int i;

	item = 0;
	switch (*(int*) (e + 0x70)) {
	case 0:
		msg = (int*) (e + 0x60);
		i = gm_GetElapsedMinutes(msg, (void*) 0x7f4c00);
		item = gm_QueryEntities(0, 2, 7, 1, *(int*) (e + 0xac));
		if (item == 0) {
			item = gm_QueryEntities(0, 2, 7, 1, *(int*) (e + 0xac));
			he_FreeAction(e);
			return;
		}
		if ((int) *((unsigned char*) item + 0x12) < *(int*) (e + 0xb4)) {
			gm_ChangeObjektZustand(*(int*) (e + 0xac), i / *(int*) (e + 0xb8));
			*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
			gm_AddTime((void*) (e + 0x52), 0, *(int*) (e + 0xb8) * 2, 0);
		} else {
			*(int*) (e + 0x70) = *(int*) (e + 0x70) + 1;
		}
		msg[0] = *(int*) 0x7f4c00;
		msg[1] = *(int*) 0x7f4c04;
		msg[2] = *(int*) 0x7f4c08;
		*(unsigned short*) (msg + 3) = *(unsigned short*) 0x7f4c0c;
		return;
	case 1:
		gm_ResolveEntityById(0, &item, 0, *(int*) (e + 0xac));
		if (*(int*) (e + 0xd8) != 0) {
			io_FormatTextBuffer(buf, 0x1c49, (*(unsigned short*) item) * 2 + 0x9a8);
			p = (int*) gm_FindBuildingPrimarySlot((unsigned char*) gm_SearchTable67(*(int*) (e + 0x10)));
			if (p != 0) {
				he_MessageBoxQuickjump(*(int*) ((*(unsigned short*) (e + 8)) * 0x21c + 0x7f4ca4), -1, buf, 0, 0x5ec, *(int*) (e + 0x10), *(int*) ((char*) p + 2), 0, "_NACHRICHTEN_HS_55");
			} else {
				he_MessageBoxQuickjump(*(int*) ((*(unsigned short*) (e + 8)) * 0x21c + 0x7f4ca4), -1, buf, 0, 0x5ec, *(int*) (e + 0x10), -1, 0, "_NACHRICHTEN_HS_55");
			}
		}
		cm_RequestChangeBits(*(int*) ((char*) item + 2), 0x13, 1, 0, 0x20);
		ch = *(char*) (e + 0xb4);
		cm_BeginPacketFieldDelta((char*) item, *(int*) ((char*) item + 2));
		cm_AppendPacketFieldDelta(1, 1, 0x12, &ch);
		cm_RequestChangeAttribute();
		he_FreeAction(e);
		return;
	case -2:
	case -1:
		gm_ResolveEntityById(0, &item, 0, *(int*) (e + 0xac));
		if (item != 0) {
			cm_RequestChangeBits(*(int*) ((char*) item + 2), 0x13, 1, 0, 0x20);
		}
		he_FreeAction(e);
		return;
	default:
		return;
	}
}
