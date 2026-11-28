


#include <string.h>

#include "Develop/DieGildeAddOn/game/entity_record.h"







#include "Develop/DieGildeAddOn/game/game_player.h"
extern __int64 gm_TargetPersonTypeMask;
#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl io_FormatTextBuffer(char*, int, ...);
char* __cdecl d2_OpenTargetPicker(int*, char*, int, int);
char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl cm_RequestCopyEntityData(int, int, int, int);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, int);
char* __cdecl gm_LookupSpecialObjectRecord(int, int*);
void __cdecl d2_ShowUseObjDialog(char*);

int __cdecl gm_ObjBefriendOppositeGender(char* ent, int* arg)
{
	int tmp;
	int desc[20];
	char name[0x100];
	char text[0x400];
	char* obj;
	char* rec;
	int ok;

	ok = 0;
	if (ent[2] == 6) {
		memset(desc, 0, sizeof(desc));
		memset(desc + 7, 0xff, 8 * sizeof(int));
		io_FormatTextBuffer(name, 0x9c);
		desc[0] = 1;
		desc[1] = ((((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot].gender != 0) + 1) | 0x400;
		desc[4] = 6;
		desc[2] = (*(int*)&gm_TargetPersonTypeMask);
		desc[3] = g_66601c;
		obj = d2_OpenTargetPicker(desc, name, 0, 0);
		if (obj == 0) {
			goto end;
		}
		ok = 1;
	} else {
		obj = gm_LookupEntityRecordById(arg[1]);
		if (obj == 0) {
			goto end;
		}
		ok = 1;
	}
	cm_RequestCopyEntityData(*(int*) (ent + 4), *(int*) (obj + 4), 0x19, ok);
	if (obj[2] == 6 || obj[2] == 7) {
		io_FormatTextBuffer(text, 0xffa, *(unsigned short*) ent);
		he_PostEntityMessage(*(int*) (obj + 4), -1, text, 0, 0x5ec, 0);
	}
	if (ent[2] == 6) {
		rec = gm_LookupSpecialObjectRecord(**(unsigned short**) arg, &tmp);
		arg[4] = ok;
		io_FormatTextBuffer(text, 0xfe8, *(unsigned short*) (rec + 0x18) + 1, *(unsigned short*) obj);
		d2_ShowUseObjDialog(text);
	}
end:
	return ok;
}
