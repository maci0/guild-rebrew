#include "Develop/DieGildeAddOn/game/object_prototype.h"
extern int d2_InventoryPanelEntity;
#include "Develop/Units/d2.v1/d2_gui.h"
extern char* lpObjektePROT;
extern char* d2_InventoryPanelWindowId;
extern char* g_14b52c4;
extern int d2_ObjektNameTable[];
void* __cdecl gm_QueryEntities(int container_id, int arg_count, ...);
void* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl gm_LookupSpecialObject(unsigned short id);
int __cdecl d2_GetControlValue(int handle);
void __cdecl d2_SetElementValue(int handle, ...);
void __cdecl d2_SetElementEnabled(int handle, int value);
void __cdecl d2_SetDisplayCounter(int id, int value);
int __cdecl d2_AddWindowField(int x, int y, int id, int group, char* name);
void __cdecl d2_DestroyElement(int handle);
int __cdecl fcn_0064d41a(char* buf, char* fmt, ...);
/* ADDRESS: GOLDTL 0x005c5e70 */
/* ADDRESS: GOLDDE 0x005a80f0 */
unsigned int __cdecl d2_UpdateActiveItemSlots(void)
{
	int* slot;
	unsigned int result;
	int container;
	int handle;
	int used;
	unsigned short* match;
	int i;

	container = d2_InventoryPanelEntity;
	result = 0;
	if (container == 0) {
		return 0;
	}
	for (slot = (int*) 0x776c64; (int) slot < 0x776c94; slot += 2) {
		if (*slot != 0) {
			if (gm_QueryEntities(*(int*) (container + 0x178), 1, 0, *(unsigned short*) *slot) != 0) {
				handle = d2_GetControlValue(slot[-1]);
				d2_SetElementValue(slot[-1], 0, *(unsigned int*) (*slot + 0xe), handle);
				fcn_0064d41a(((char*)&((D2_CONTROL_TL*)d2_Controls)[slot[-1]] + 0xcc), "%s~ %li %s",
				    (unsigned int) d2_ObjektNameTable[*(unsigned short*) *slot * 2], *(unsigned int*) (*slot + 0xe), g_14b52c4);
				used = gm_LookupSpecialObject(*(unsigned short*) *slot);
				if (used != 0) {
					if (*(int*) (*slot + 0x21) != 0) {
						d2_SetElementEnabled(slot[-1], 0);
						*(float*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[slot[-1]].value_1f4)) = 1.0
						    - (float) *(int*) (*slot + 0x1c) / *(int*) (used + 4);
					}
					else {
						d2_SetElementEnabled(slot[-1], 1);
						*(unsigned int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[slot[-1]].value_060)) = 0;
						*(unsigned int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[slot[-1]].value_1f4)) = 0;
					}
				}
				if (handle != 0) {
					d2_SetDisplayCounter(*(unsigned short*) *slot + 0xdf, handle);
					result = 1;
				}
			}
			else {
				*slot = 0;
				d2_DestroyElement(slot[-1]);
				slot[-1] = -1;
			}
		}
	}
	match = (unsigned short*) gm_QueryEntities(*(int*) (container + 0x178), 1, 5);
	for (;;) {
		if (match == 0) {
			return result;
		}
		if ((*(char *)&((OBJECT_PROTOTYPE*)lpObjektePROT)[*match].kind) != 9) {
			for (i = 0; i < 6; i++) {
				if (*(unsigned short**) (i * 8 + 0x776c64) == match) {
					break;
				}
			}
			if (i == 6) {
				for (i = 0; i < 6; i++) {
					if (*(int*) (i * 8 + 0x776c64) == 0) {
						*(int*) (i * 8 + 0x776c64) = (int) match;
						handle = d2_AddWindowField((i % 3) * 0x38 + 0x15, (i / 3) * 0x36 + 0x4a,
						    *match + 0xdf, 10, d2_InventoryPanelWindowId);
						*(int*) (i * 8 + 0x776c60) = handle;
						*(unsigned int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[handle].flags_1d0)) = 0x23;
						*(unsigned int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[handle].value_1dc)) = 0xffffffff;
						*(unsigned int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[handle].value_1e0)) = 0;
						fcn_0064d41a(((char*)&((D2_CONTROL_TL*)d2_Controls)[handle] + 0x0cc), "%s~ %li St",
						    (unsigned int) d2_ObjektNameTable[*match * 2],
						    *(unsigned int*) ((char*) match + 0xe));
						used = gm_LookupSpecialObject(*match);
						if (used != 0) {
							if (*(int*) ((char*) match + 0x21) != 0) {
								d2_SetElementEnabled(handle, 0);
								*(float*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[handle].value_1f4)) = 1.0
								    - (float) *(int*) ((char*) match + 0x1c) / *(int*) (used + 4);
							}
							else {
								d2_SetElementEnabled(handle, 1);
							}
						}
						break;
					}
				}
			}
		}
		match = (unsigned short*) gm_NextEntityQueryMatch();
	}
}
