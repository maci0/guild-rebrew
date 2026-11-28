#include "Develop/DieGildeAddOn/game/entity_record.h"


// SIZE 0x21c
typedef struct {
	char data[0x21c];
} Rec21c;

extern char gm_EntitySlotTable[];

int __cdecl gm_TransferDynastyEstate(int a, int b);
int __cdecl gm_LookupEntityRecordById(int h);
int __cdecl gv_FindEntityGraveyardSlot(int h, char** obj, int** val);
unsigned char __cdecl gm_GetEntitySlotIndex(int a, int* b);
void __cdecl gv_RequestAddCandidateToOfficePool(int h, char* obj, int v, int flag);

int __cdecl cm_ExChangePlayerIdentity(char* cmd, char* result)
{
	int idx;
	int h;

	idx = gm_TransferDynastyEstate(*(int*) (cmd + 0x10), *(int*) (cmd + 0x14));
	if (result != 0) {
		result[0] = 1;
		if (idx >= 0) {
			char* obj;
			int* val;

			h = gm_LookupEntityRecordById(*(int*) (cmd + 0x14));
			if (gv_FindEntityGraveyardSlot(h, &obj, &val) != 0) {
				gv_RequestAddCandidateToOfficePool(h, obj, *val, gm_GetEntitySlotIndex(*(int*) (obj + 0x65), val));
			}
			result[1] = 1;
			*(Rec21c**) (result + 6) = ((Rec21c *)&((ENTITY_RECORD_VIEW *)gm_EntitySlotTable)[idx]);
		} else {
			result[1] = 0;
			*(int*) (result + 6) = 0;
		}
	}
	return 0;
}
