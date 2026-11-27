/* Pick three free building sites around the selected plot and place the
 * scene objects there. */

#include "Develop/DieGildeAddOn/game/entity_record.h"
extern __int64 g_666018;
extern int g_66601c;
char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl fcn_005cd440(int*, char*, int, int);
int __cdecl gm_HasActiveSpecialObject(void*, int);
unsigned int __cdecl gm_RandomMod(int);
void __cdecl cm_RequestCopyEntityData(int, int, int, int);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, char*);
int __cdecl gm_LookupSpecialObjectRecord(int, char*);
void __cdecl fcn_005dbe90(char*);

/* ADDRESS: GOLDTL 0x005dd5a0 */
unsigned int __cdecl gm_LowerTargetStandingWithPeers(ENTITY_RECORD_VIEW* actor, unsigned int* request)
{
	char pickerTitle[256];
	char messageText[2048];
	unsigned int query[20];
	ENTITY_RECORD_VIEW* peers[3];
	char itemSlot[4];
	int remaining;
	ENTITY_RECORD_VIEW* target;
	int slotIdx;
	int idxOrDelta;
	unsigned char entityType;

	request[4] = 1;
	entityType = actor->entity_type;
	if (entityType == 6) {
		for (idxOrDelta = 0; idxOrDelta < 0x14; idxOrDelta++) {
			query[idxOrDelta] = 0;
		}
		for (idxOrDelta = 0; idxOrDelta < 8; idxOrDelta++) {
			query[idxOrDelta + 7] = 0xffffffff;
		}
		io_FormatTextBuffer(pickerTitle, 0x9c);
		query[2] = *(unsigned int*) &g_666018;
		query[0] = 0;
		query[1] = 0x400;
		query[4] = 6;
		query[3] = g_66601c;
		target = (ENTITY_RECORD_VIEW*) fcn_005cd440((int*) query, pickerTitle, 0, 0);
	} else {
		target = (ENTITY_RECORD_VIEW*) gm_LookupEntityRecordById(request[1]);
	}
	if (!target) {
		return 0;
	}
	idxOrDelta = (gm_HasActiveSpecialObject((void*) actor, 0x2c5) != 0) + 1;
	slotIdx = gm_RandomMod(0x300) & 0xffff;
	remaining = 0x300;
	do {
		if (slotIdx != target->entity_index && slotIdx != actor->entity_index) {
			if (((ENTITY_RECORD_VIEW*) g_7f4ca0)[slotIdx].entity_index != 0xffff &&
			    ((ENTITY_RECORD_VIEW*) g_7f4ca0)[slotIdx].entity_type < 10 &&
			    ((ENTITY_RECORD_VIEW*) g_7f4ca0)[slotIdx].class_166 != 0) {
				peers[0] = &((ENTITY_RECORD_VIEW*) g_7f4ca0)[slotIdx];
				break;
			}
		}
		remaining -= 1;
		slotIdx = (slotIdx + 1) % 0x300;
	} while (remaining);
	slotIdx = gm_RandomMod(0x300) & 0xffff;
	remaining = 0x300;
	do {
		if (slotIdx != target->entity_index && slotIdx != actor->entity_index &&
		    slotIdx != peers[0]->entity_index) {
			if (((ENTITY_RECORD_VIEW*) g_7f4ca0)[slotIdx].entity_index != 0xffff &&
			    ((ENTITY_RECORD_VIEW*) g_7f4ca0)[slotIdx].entity_type < 10 &&
			    ((ENTITY_RECORD_VIEW*) g_7f4ca0)[slotIdx].class_166 != 0) {
				peers[1] = &((ENTITY_RECORD_VIEW*) g_7f4ca0)[slotIdx];
				break;
			}
		}
		slotIdx = (slotIdx + 7) % 0x300;
		remaining -= 1;
	} while (remaining);
	slotIdx = gm_RandomMod(0x300) & 0xffff;
	for (remaining = 0x300; remaining != 0; remaining--) {
		if (slotIdx != target->entity_index && slotIdx != actor->entity_index &&
		    slotIdx != peers[0]->entity_index && slotIdx != peers[1]->entity_index) {
			if (((ENTITY_RECORD_VIEW*) g_7f4ca0)[slotIdx].entity_index != 0xffff &&
			    ((ENTITY_RECORD_VIEW*) g_7f4ca0)[slotIdx].entity_type < 10 &&
			    ((ENTITY_RECORD_VIEW*) g_7f4ca0)[slotIdx].class_166 != 0) {
				peers[2] = &((ENTITY_RECORD_VIEW*) g_7f4ca0)[slotIdx];
				break;
			}
		}
		slotIdx = (slotIdx + 0xd) % 0x300;
	}
	idxOrDelta *= -0x14;
	cm_RequestCopyEntityData(target->entity_id, peers[0]->entity_id, idxOrDelta, 1);
	cm_RequestCopyEntityData(target->entity_id, peers[1]->entity_id, idxOrDelta, 1);
	cm_RequestCopyEntityData(target->entity_id, peers[2]->entity_id, idxOrDelta, 1);
	if (target->entity_type == 6 || target->entity_type == 7) {
		io_FormatTextBuffer(messageText, 0xfec, peers[0]->entity_index,
		                    peers[1]->entity_index, peers[2]->entity_index);
		he_PostEntityMessage(target->entity_id, 0xffffffff, messageText, 1, 0x5fb, 0);
	}
	io_FormatTextBuffer(messageText, 0xfed, target->entity_index);
	for (idxOrDelta = 0; idxOrDelta < 3; idxOrDelta++) {
		entityType = peers[idxOrDelta]->entity_type;
		if (entityType == 6 || entityType == 7) {
			he_PostEntityMessage(peers[idxOrDelta]->entity_id, 0xffffffff, messageText, 0,
			             0x5fb, 0);
		}
	}
	if (actor->entity_type != 6) {
		return 1;
	}
	idxOrDelta = gm_LookupSpecialObjectRecord((int) *(unsigned short*) *request, itemSlot);
	io_FormatTextBuffer(messageText, 0xfe8, *(unsigned short*) (idxOrDelta + 0x18) + 1,
	                    peers[0]->entity_index, peers[1]->entity_index,
	                    peers[2]->entity_index);
	fcn_005dbe90(messageText);
	return 1;
}
