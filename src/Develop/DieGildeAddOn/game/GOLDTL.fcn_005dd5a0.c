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
void __cdecl fcn_00545d40(int, int, char*, int, int, char*);
int __cdecl gm_LookupSpecialObjectRecord(int, char*);
void __cdecl fcn_005dbe90(char*);

/* ADDRESS: GOLDTL 0x005dd5a0 */
unsigned int __cdecl fcn_005dd5a0(ENTITY_RECORD_VIEW* a0, unsigned int* a1)
{
	char v10[256];
	char messageText[2048];
	unsigned int v8[20];
	ENTITY_RECORD_VIEW* v12[3];
	char v13[4];
	int v14;
	ENTITY_RECORD_VIEW* v4;
	int v5;
	int v6;
	unsigned char v2;

	a1[4] = 1;
	v2 = a0->entity_type;
	if (v2 == 6) {
		for (v6 = 0; v6 < 0x14; v6++) {
			v8[v6] = 0;
		}
		for (v6 = 0; v6 < 8; v6++) {
			v8[v6 + 7] = 0xffffffff;
		}
		io_FormatTextBuffer(v10, 0x9c);
		v8[2] = *(unsigned int*) &g_666018;
		v8[0] = 0;
		v8[1] = 0x400;
		v8[4] = 6;
		v8[3] = g_66601c;
		v4 = (ENTITY_RECORD_VIEW*) fcn_005cd440((int*) v8, v10, 0, 0);
	} else {
		v4 = (ENTITY_RECORD_VIEW*) gm_LookupEntityRecordById(a1[1]);
	}
	if (!v4) {
		return 0;
	}
	v6 = (gm_HasActiveSpecialObject((void*) a0, 0x2c5) != 0) + 1;
	v5 = gm_RandomMod(0x300) & 0xffff;
	v14 = 0x300;
	do {
		if (v5 != v4->entity_index && v5 != a0->entity_index) {
			if (((ENTITY_RECORD_VIEW*) g_7f4ca0)[v5].entity_index != 0xffff &&
			    ((ENTITY_RECORD_VIEW*) g_7f4ca0)[v5].entity_type < 10 &&
			    ((ENTITY_RECORD_VIEW*) g_7f4ca0)[v5].class_166 != 0) {
				v12[0] = &((ENTITY_RECORD_VIEW*) g_7f4ca0)[v5];
				break;
			}
		}
		v14 -= 1;
		v5 = (v5 + 1) % 0x300;
	} while (v14);
	v5 = gm_RandomMod(0x300) & 0xffff;
	v14 = 0x300;
	do {
		if (v5 != v4->entity_index && v5 != a0->entity_index &&
		    v5 != v12[0]->entity_index) {
			if (((ENTITY_RECORD_VIEW*) g_7f4ca0)[v5].entity_index != 0xffff &&
			    ((ENTITY_RECORD_VIEW*) g_7f4ca0)[v5].entity_type < 10 &&
			    ((ENTITY_RECORD_VIEW*) g_7f4ca0)[v5].class_166 != 0) {
				v12[1] = &((ENTITY_RECORD_VIEW*) g_7f4ca0)[v5];
				break;
			}
		}
		v5 = (v5 + 7) % 0x300;
		v14 -= 1;
	} while (v14);
	v5 = gm_RandomMod(0x300) & 0xffff;
	for (v14 = 0x300; v14 != 0; v14--) {
		if (v5 != v4->entity_index && v5 != a0->entity_index &&
		    v5 != v12[0]->entity_index && v5 != v12[1]->entity_index) {
			if (((ENTITY_RECORD_VIEW*) g_7f4ca0)[v5].entity_index != 0xffff &&
			    ((ENTITY_RECORD_VIEW*) g_7f4ca0)[v5].entity_type < 10 &&
			    ((ENTITY_RECORD_VIEW*) g_7f4ca0)[v5].class_166 != 0) {
				v12[2] = &((ENTITY_RECORD_VIEW*) g_7f4ca0)[v5];
				break;
			}
		}
		v5 = (v5 + 0xd) % 0x300;
	}
	v6 *= -0x14;
	cm_RequestCopyEntityData(v4->entity_id, v12[0]->entity_id, v6, 1);
	cm_RequestCopyEntityData(v4->entity_id, v12[1]->entity_id, v6, 1);
	cm_RequestCopyEntityData(v4->entity_id, v12[2]->entity_id, v6, 1);
	if (v4->entity_type == 6 || v4->entity_type == 7) {
		io_FormatTextBuffer(messageText, 0xfec, v12[0]->entity_index,
		                    v12[1]->entity_index, v12[2]->entity_index);
		fcn_00545d40(v4->entity_id, 0xffffffff, messageText, 1, 0x5fb, 0);
	}
	io_FormatTextBuffer(messageText, 0xfed, v4->entity_index);
	for (v6 = 0; v6 < 3; v6++) {
		v2 = v12[v6]->entity_type;
		if (v2 == 6 || v2 == 7) {
			fcn_00545d40(v12[v6]->entity_id, 0xffffffff, messageText, 0,
			             0x5fb, 0);
		}
	}
	if (a0->entity_type != 6) {
		return 1;
	}
	v6 = gm_LookupSpecialObjectRecord((int) *(unsigned short*) *a1, v13);
	io_FormatTextBuffer(messageText, 0xfe8, *(unsigned short*) (v6 + 0x18) + 1,
	                    v12[0]->entity_index, v12[1]->entity_index,
	                    v12[2]->entity_index);
	fcn_005dbe90(messageText);
	return 1;
}
