


// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"








#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;

char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_GetElapsedMinutes(pos14_7f4c00*, pos14_7f4c00*);
double __cdecl gm_GetEntityHealthRatio(char*);
float __cdecl gm_ApplyEntityHealthDelta(unsigned short, int);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
char* __cdecl gm_SearchTable67(int);
void __cdecl he_AssignActionSlot(char*, int, int, char*);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, char*);
void __cdecl he_FreeAction(char*);

void __cdecl he_RunHeilen(char* u)
{
	float x;
	char text[0x200];
	char* h;
	char* b;
	float r;

	switch (*(int*) (u + 0x70)) {
	case 0:
		h = gm_LookupEntityRecordById(*(int*) (u + 0xac));
		if (h == 0) {
			break;
		}
		x = gm_GetElapsedMinutes((pos14_7f4c00*) (u + 0x60), &gm_GameTime) * 0.1f;
		x *= 5.0f;
		r = gm_GetEntityHealthRatio(h) * 100.0;
		if (*(unsigned int*) (u + 0xb0) > 0 && x + r < 100.0f) {
			gm_ApplyEntityHealthDelta(*(unsigned short*) h, (int) x);
			*(unsigned int*) (u + 0xb0) = (unsigned int) (*(unsigned int*) (u + 0xb0) - x);
			*(pos14_7f4c00*) (u + 0x52) = gm_GameTime;
			gm_AddTime((pos14_7f4c00*) (u + 0x52), 0, 10, 0);
		} else {
			(*(int*) (u + 0x70))++;
		}
		*(pos14_7f4c00*) (u + 0x60) = gm_GameTime;
		return;
	case 1:
		h = gm_LookupEntityRecordById(*(int*) (u + 0xac));
		b = gm_SearchTable67(*(int*) (u + 0x10));
		if (h == 0 || b == 0) {
			break;
		}
		he_AssignActionSlot(b, 0, *(unsigned short*) h, 0);
		io_FormatTextBuffer(text, 0x1a18, b, *(unsigned short*) h);
		he_MessageBoxQuickjump(((ENTITY_RECORD_VIEW *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[*(unsigned short*) (u + 8)])->entity_id, -1, text, 0, 0x5f2, *(int*) (u + 0x10), -1, 0,
		    "_NACHRICHTEN_HS_80");
		he_FreeAction(u);
		return;
	case -2:
	case -1:
		h = gm_LookupEntityRecordById(*(int*) (u + 0xac));
		if (h != 0) {
			he_AssignActionSlot(0, 0, *(unsigned short*) h, 0);
		}
		break;
	default:
		return;
	}
	he_FreeAction(u);
}
