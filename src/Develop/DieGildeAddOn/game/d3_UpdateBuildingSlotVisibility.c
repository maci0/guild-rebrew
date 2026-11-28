#include <string.h>
#include "Develop/DieGildeAddOn/game/object_prototype.h"
#include "Develop/DieGildeAddOn/game/building_prototype.h"
extern char* d3_ActiveCamera;
extern char* g_7f3b24;
extern char* g_7f3ee0;
extern char* lpObjektePROT;
extern unsigned char* lpGebaeudePROT;
extern unsigned char* d2_InteriorBuilding;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern unsigned char d3_CurrentSeason;

extern void* __cdecl fcn_00502cd0(int list, int a, int b, ...);
extern void* __cdecl gm_NextEntityQueryMatch(void);
extern int __cdecl gm_IsRawItem(int handle);
extern int __cdecl gm_FindObjektPrototypeByName(char* key);
extern int __cdecl gm_GetEntityUiFlags(int a, void* table, void* record, int mode);
extern void __cdecl d3_SetSubtreeVisible(char* record, int mode);
extern char __cdecl d3_ComputeObjectBoundingSphere(char* record, char* scene, float* out, float* value);
extern double dbl_1_5;
extern void* __cdecl evt_LoadGfxScript(char* name);
extern int __cdecl evt_CallScriptFunction(char* handle, int a, ...);
extern void __cdecl SelectTextureSet(char* record, int target, char mode, int flag);

/* ADDRESS: GOLDTL 0x005156a0 */
void __cdecl d3_UpdateBuildingSlotVisibility(char* record)
{
	char* list;
	unsigned char* entry;
	unsigned char* proto;
	char* slot;
	unsigned short* item;
	char* table;
	unsigned int id;
	int k0;
	unsigned int id2;
	char k1;
	int idx;
	float buf[4];

	slot = 0;
	id = *(unsigned int*) (record + 0x48) & 0xffffff;
	k0 = record[0x4b];
	if (g_7f3b24 != 0)
		list = (char*) *(int*) (g_7f3b24 + 0x14);
	else
		list = (char*) *(int*) (g_7f3ee0 + 0x5d);
	if (k0 == 1) {
		entry = (unsigned char*) &((OBJECT_PROTOTYPE*) lpObjektePROT)[id];
		if (*entry == 2)
			goto label_59eb;
		if (*entry == 0x1d)
			goto label_5a7a;
		if (*entry == 0x21 || *entry == 6)
			goto label_59eb;
		slot = (char*) fcn_00502cd0((int) list, 1, 0, id);
		if (slot == 0)
			goto label_59eb;
		*(unsigned int*) (slot + 0x18) = 0;
		table = *(char**) (record + 0x1fc);
		if (table != 0) {
			id2 = *(unsigned int*) (table + 0x48) & 0xffffff;
			k1 = table[0x4b];
			if (k1 == 1) {
				unsigned short* other;

				other = (unsigned short*) fcn_00502cd0((int) list, 1, 0, id2);
				if (other != 0) {
					d3_SetSubtreeVisible(record, 1);
					*(char**) (record + 0x204) = slot;
					*(unsigned int*) (record + 0x224) = 0;
					*(char**) (slot + 0x18) = record;
					if (gm_IsRawItem(*(unsigned short*) slot) != 0) {
						item = (unsigned short*) fcn_00502cd0((int) list, 1, 4, *entry);
						while (item != 0) {
							unsigned short itemId;
							unsigned short slotId;

							itemId = *item;
							slotId = *(unsigned short*) slot;
							if (itemId != slotId) {
								BUILDING_PROTOTYPE* row;
								int best;
								int second;
								int count;
								int i;

								best = -1;
								second = -1;
								row = &((BUILDING_PROTOTYPE*) lpGebaeudePROT)[*(unsigned char*) g_7f3ee0];
								count = row->component_count;
								for (i = 0; i < count; i++) {
									if ((row->components[i] & 0x7fff) != 0) {
										if (itemId == (row->components[i] & 0x7fff))
											best = i;
										else if (slotId == (row->components[i] & 0x7fff))
											second = i;
									}
								}
								if (best != -1 && best > second)
									d3_SetSubtreeVisible(record, 0);
							}
							item = (unsigned short*) gm_NextEntityQueryMatch();
						}
					}
					proto = (unsigned char*) &((OBJECT_PROTOTYPE*) lpObjektePROT)[*other];
					if (gm_IsRawItem(*(unsigned short*) slot) != 0) {
						item = (unsigned short*) fcn_00502cd0((int) list, 1, 4, *proto);
						while (item != 0) {
							if (*item > *other)
								d3_SetSubtreeVisible(record, 0);
							item = (unsigned short*) gm_NextEntityQueryMatch();
						}
					}
				} else {
					d3_SetSubtreeVisible(record, 0);
					*(unsigned int*) (record + 0x204) = 0;
				}
			} else {
				d3_SetSubtreeVisible(record, 1);
				*(char**) (record + 0x204) = slot;
				*(unsigned int*) (record + 0x224) = 0;
				*(char**) (slot + 0x18) = record;
				if (gm_IsRawItem(*(unsigned short*) slot) != 0) {
					item = (unsigned short*) fcn_00502cd0((int) list, 1, 4, *entry);
					while (item != 0) {
						if (*item > *(unsigned short*) slot)
							d3_SetSubtreeVisible(record, 0);
						item = (unsigned short*) gm_NextEntityQueryMatch();
					}
				}
			}
		} else {
			proto = (unsigned char*) &((OBJECT_PROTOTYPE*) lpObjektePROT)[id];
			d3_SetSubtreeVisible(record, 1);
			*(char**) (record + 0x204) = slot;
			if (*proto != 0x1d)
				*(unsigned int*) (record + 0x224) = 0;
			*(char**) (slot + 0x18) = record;
			if (gm_IsRawItem(*(unsigned short*) slot) != 0) {
				item = (unsigned short*) fcn_00502cd0((int) list, 1, 4, *proto);
				while (item != 0) {
					if (*item > *(unsigned short*) slot)
						d3_SetSubtreeVisible(record, 0);
					item = (unsigned short*) gm_NextEntityQueryMatch();
				}
			}
		}
		goto label_5aab;
label_59eb:
		if (*entry != 0x1d) {
			slot = (char*) fcn_00502cd0((int) *(void**) (g_7f3ee0 + 0x5d), 2, 6, 0, id);
			if (slot != 0) {
				d3_SetSubtreeVisible(record, 1);
				*(char**) (record + 0x204) = slot;
				if ((*entry == 6 || *entry == 2) && d2_InteriorBuilding != 0) {
					if (gm_GetEntityUiFlags(gm_LocalPlayerSlot, g_7f3ee0, slot, 0) & 0x4000) {
						*(unsigned int*) (record + 0x224) = 1;
						*(char**) (slot + 0x18) = record;
						goto label_5aab;
					}
				} else {
					*(unsigned int*) (record + 0x224) = 0;
				}
				*(char**) (slot + 0x18) = record;
				goto label_5aab;
			}
		}
label_5a7a:
		if (((OBJECT_PROTOTYPE*) lpObjektePROT)[id].kind != 0x1d && ((OBJECT_PROTOTYPE*) lpObjektePROT)[id].kind != 0x21) {
			*(unsigned int*) (record + 0x204) = 0;
			if (*(int*) (record + 0x218) != 1)
				d3_SetSubtreeVisible(record, 0);
		}
label_5aab:
		if (slot != 0 && (*(unsigned char*) (slot + 0x13) & 0xa0) != 0) {
			if (*(int*) (record + 0x1ec) != 0) {
				float value;
				int scaled;
				char* handle;

				if (d3_ComputeObjectBoundingSphere(record, d3_ActiveCamera, buf, &value)) {
					scaled = (int) (value * dbl_1_5);
					handle = (char*) evt_LoadGfxScript((char*) 0x6a1f3c);
					if (handle != 0)
						evt_CallScriptFunction(handle, 6, (int) buf[0], (int) buf[1],
							(int) buf[2], (int) value, scaled, record);
				}
			}
			*(unsigned char*) (slot + 0x13) &= 0x5f;
		}
	}
	if (strncmp(record, (char*) 0x6a1f38, 3) == 0) {
		idx = gm_FindObjektPrototypeByName(record + 6);
		if (idx != -1) {
			if (((OBJECT_PROTOTYPE*) lpObjektePROT)[idx].kind == 2) {
				if (fcn_00502cd0(*(int*) (g_7f3ee0 + 0x5d), 1, 0, idx) != 0)
					d3_SetSubtreeVisible(record, 0);
				else
					d3_SetSubtreeVisible(record, 1);
			} else {
				if (fcn_00502cd0((int) list, 1, 0, idx) != 0)
					d3_SetSubtreeVisible(record, 0);
				else
					d3_SetSubtreeVisible(record, 1);
			}
		}
	} else if (strncmp(record, (char*) 0x68d6fc, 4) == 0
			|| strncmp(record, (char*) 0x68d6f8, 3) == 0) {
		if (*(int*) (record + 0x1cc) != 0) {
			SelectTextureSet(record, *(int*) (record + 0x1cc), (char) d3_CurrentSeason, 1);
			return;
		}
		SelectTextureSet(record, *(int*) (record + 0x1ec) + 0xf4,
			(char) d3_CurrentSeason, 1);
	}
}
