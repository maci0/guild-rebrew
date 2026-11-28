


// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"







#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;


char* __cdecl gm_LookupEntityRecordById(int);
char* __cdecl he_StartHandlungSearch(int, int, int);
char* __cdecl he_fn_Handlung(void);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, int);
int __cdecl cm_SendSetHE(int, char*);
void __cdecl he_FreeAction(char*);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
void __cdecl gm_ModifyHealth(int, int);
void __cdecl gm_TryRecordCrime(int, int, int, int, int);

void __cdecl he_StartHauchDesVerfalls(char* e)
{
	char buf[0x400];
	char* p;
	char* o;

	if ((e[0x78] & 4) != 0) {
		return;
	}
	p = gm_LookupEntityRecordById(*(int*) (e + 0xb0));
	for (o = he_StartHandlungSearch(1, 0, 0x89); o != 0; o = he_fn_Handlung()) {
		if (o != e && *(unsigned short*) (o + 8) == *(unsigned short*) (e + 8) && *(int*) (o + 0xb0) == *(int*) (e + 0xb0)) {
			if (p != 0) {
				io_FormatTextBuffer(buf, 0x40a2, *(unsigned short*) p);
				he_PostEntityMessage(((ENTITY_RECORD_VIEW *)&((ENTITY_RECORD_VIEW *)gm_EntitySlotTable)[*(unsigned short*) (e + 8)])->entity_id, -1, buf, 0, 0x5fa, 0);
			}
			*(int*) (e + 0x84) = cm_SendSetHE(-1, e);
			he_FreeAction(e);
			return;
		}
	}
	if (gm_LookupEntityRecordById(*(int*) (e + 0xb4)) == 0) {
		he_FreeAction(e);
		return;
	}
	*(int*) (e + 0xbc) = 0;
	*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
	gm_AddTime((pos14_7f4c00*) (e + 0x52), 0, 1, 0);
	gm_ModifyHealth(((ENTITY_RECORD_VIEW *)&((ENTITY_RECORD_VIEW *)gm_EntitySlotTable)[*(unsigned short*) (e + 8)])->entity_id, -*(int*) (e + 0xb8));
	*(int*) (e + 0x70) = 0;
	gm_TryRecordCrime(0x1b, 1, ((ENTITY_RECORD_VIEW *)&((ENTITY_RECORD_VIEW *)gm_EntitySlotTable)[*(unsigned short*) (e + 8)])->entity_id, p != 0 ? *(int*) (p + 4) : -1,
	    p != 0 && *(char**) (p + 0x170) != 0 ? *(int*) (*(char**) (p + 0x170) + 1) : -1);
}
