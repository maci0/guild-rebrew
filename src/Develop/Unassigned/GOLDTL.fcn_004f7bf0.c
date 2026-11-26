


#include "Develop/DieGildeAddOn/game/entity_record.h"









extern char g_679060[];

unsigned char* __cdecl gm_LookupEntityRecordById(int id);
int __cdecl d2_RunDivorceAction(unsigned char* a1, int* a2);
void __cdecl io_FormatTextBuffer(void*, int, ...);

int __cdecl fcn_004f7bf0(unsigned char* a1, int* a2)
{
	int i;
	int id;
	unsigned char* e;

	if (*a2 != 3 && *a2 != 1) {
		return 1;
	}
	if (a1[0xd] < 5) {
		return 1;
	}
	for (i = 0; i < 768; i++) {
		if (((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].entity_index != 0xffff && (((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].class_166 != 0x12 || ((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].class_166 <= 0x15)) {
			break;
		}
	}
	id = *(int*) (a1 + 0x5c);
	if (id == -1) {
		return 1;
	}
	if (i >= 0x300) {
		return 1;
	}
	e = gm_LookupEntityRecordById(id);
	if (e == 0) {
		return 1;
	}
	if (e[8] == 0) {
		return 1;
	}
	if (*a2 == 3) {
		return d2_RunDivorceAction(a1, a2);
	}
	if (*a2 == 1 && a1[2] == 6) {
		io_FormatTextBuffer((char*) a2 + 0x14, (int) "%s", 0x1d8e);
	}
	return 2;
}
