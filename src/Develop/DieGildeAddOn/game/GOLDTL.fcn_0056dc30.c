


// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"








#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;

char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_GetElapsedMinutes(pos14_7f4c00*, pos14_7f4c00*);
double __cdecl fcn_004ff040(char*);
float __cdecl fcn_004ff210(unsigned short, int);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
char* __cdecl gm_SearchTable67(int);
void __cdecl fcn_00529160(char*, int, int, char*);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, char*);
void __cdecl he_FreeAction(char*);

void __cdecl fcn_0056dc30(char* u)
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
		r = fcn_004ff040(h) * 100.0;
		if (*(unsigned int*) (u + 0xb0) > 0 && x + r < 100.0f) {
			fcn_004ff210(*(unsigned short*) h, (int) x);
			*(unsigned int*) (u + 0xb0) = (unsigned int) (*(unsigned int*) (u + 0xb0) - x);
			*(pos14_7f4c00*) (u + 0x52) = gm_GameTime;
			fcn_00500bb0((pos14_7f4c00*) (u + 0x52), 0, 10, 0);
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
		fcn_00529160(b, 0, *(unsigned short*) h, 0);
		io_FormatTextBuffer(text, 0x1a18, b, *(unsigned short*) h);
		he_MessageBoxQuickjump(((ENTITY_RECORD_VIEW *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[*(unsigned short*) (u + 8)])->entity_id, -1, text, 0, 0x5f2, *(int*) (u + 0x10), -1, 0,
		    "_NACHRICHTEN_HS_80");
		he_FreeAction(u);
		return;
	case -2:
	case -1:
		h = gm_LookupEntityRecordById(*(int*) (u + 0xac));
		if (h != 0) {
			fcn_00529160(0, 0, *(unsigned short*) h, 0);
		}
		break;
	default:
		return;
	}
	he_FreeAction(u);
}
