


#include "Develop/DieGildeAddOn/game/entity_record.h"









extern char str_fmt_s[];

unsigned char* __cdecl gm_LookupEntityRecordById(int id);
int __cdecl d2_RunDivorceAction(unsigned char* entity, int* request);
void __cdecl io_FormatTextBuffer(void*, int, ...);

int __cdecl he_HandleDivorceRequest(unsigned char* entity, int* request)
{
	int i;
	int id;
	unsigned char* spouse;

	if (*request != 3 && *request != 1) {
		return 1;
	}
	if (entity[0xd] < 5) {
		return 1;
	}
	for (i = 0; i < 768; i++) {
		if (((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].entity_index != 0xffff && (((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].class_166 != 0x12 ||
			((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].class_166 <= 0x15)) {
			break;
		}
	}
	id = *(int*) (entity + 0x5c);
	if (id == -1) {
		return 1;
	}
	if (i >= 0x300) {
		return 1;
	}
	spouse = gm_LookupEntityRecordById(id);
	if (spouse == 0) {
		return 1;
	}
	if (spouse[8] == 0) {
		return 1;
	}
	if (*request == 3) {
		return d2_RunDivorceAction(entity, request);
	}
	if (*request == 1 && entity[2] == 6) {
		io_FormatTextBuffer((char*) request + 0x14, (int) "%s", 0x1d8e);
	}
	return 2;
}
