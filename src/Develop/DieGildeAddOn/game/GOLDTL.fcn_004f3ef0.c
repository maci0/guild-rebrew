#include <string.h>
#include "Develop/DieGildeAddOn/game/entity_record.h"
extern char* gm_CityEntity;
extern unsigned char g_773d75;
extern int gm_GameTime;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
 
extern float g_662c30;
extern float g_66417c;
extern float g_6652e8[];
extern int g_6652f8[];

extern unsigned short __cdecl gm_RandomMod(int a);
extern float __cdecl gm_RandomFloat01(void);
extern void* __cdecl FindSlotEntryFiltered(void* a, void* b, int c, void* d, int e);
extern int __cdecl fcn_004f1790(char* a, void* e);
extern int __cdecl fcn_004f2810(int slot, int record, int item, int value, int a, int b);
extern int __cdecl fcn_004f2a10(int a, int record, int item, int value);
extern int __cdecl fcn_004f2d30(int record, int item, int value, int delta);
extern int __cdecl gm_CalcBribeOrPriceScore(int slot, int byte, int item, int zero, int* out);
extern int __cdecl cm_CountOccupiedBuildingStats(char* record);
extern void __cdecl fcn_004f2e80(char* record, int value);
extern void* __cdecl gm_LookupEntityRecordById(int id);
extern int __cdecl fcn_0050d320(char* slot, char mode);
extern int __cdecl cm_GetCommandStatus(int handle);
extern void __cdecl cm_FlushCommandQueue(void);
extern void __cdecl cm_PollCommandQueue(void);
extern void __cdecl cm_ExecCommand(void);
extern int __cdecl cm_RequestCopyEntityData(unsigned int a, unsigned int b, int value, int d);
extern void __cdecl he_NotifyContractBatch(int slot, int record, int count, int total);
extern void __cdecl he_NotifyContractDefault(int slot, int record);

extern char g_7f4ca0[];
extern int __cdecl fcn_004f1850();
extern int __cdecl cm_SendCopyEntityData(void* msg);

/* ADDRESS: GOLDTL 0x004f3ef0 */
void __cdecl fcn_004f3ef0(char* entity)
{
	int n;
	int result;
	char* home;
	int value;
	int hits;
	int count;
	int total;
	char* list;
	int out;
	unsigned int block[0x3e];
	char* slot;
	int* entry;
	int handle;
	int k;
	int i;
	float a;

	home = 0;
	n = 0;
	hits = 0;
	count = 0;
	total = 0;
	handle = -1;
	if (*(unsigned short*) (entity + 0x27) != 0xffff
	    && *(unsigned short*) (entity + 0x27) != *(unsigned short*) gm_CityEntity) {
		home = ((char*)&((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*) (entity + 0x27)]);
	}
	entry = (int*) FindSlotEntryFiltered(0, entity, 0, (void*) fcn_004f1850, 0xff);
	if (entry != 0) {
		do {
			if (n >= 0x40 && handle != -1) {
				while (1) {
					if (cm_GetCommandStatus(handle) != 0)
						break;
					cm_FlushCommandQueue();
					cm_PollCommandQueue();
					cm_ExecCommand();
				}
				n = 0;
				handle = -1;
			}
			slot = (char*) gm_LookupEntityRecordById(entry[1]);
			if (slot == 0) {
				result = entry[0];
				k = g_6652f8[result];

				for (i = 0; i < k; i++) {
					if (((int*) entry[4])[i * 0x11] != -1) {
						a = (gm_RandomFloat01() + 1.0f) * 0.5f;
						value = (int) ((g_662c30 * *(unsigned char*) ((char*) entry + 0xc))
							* g_6652e8[entry[0]] * a);
						if (value > 0
						    && ((fcn_004f1790((char*) *(int*) (entity + 0x65), entry) ^ gm_GameTime) & 1) == 0) {
							handle = fcn_004f2d30((int) entity, entry[0],
								fcn_004f1790((char*) *(int*) (entity + 0x65), entry), -value);
							n++;
						}
						goto next_entry;
					}
				}
				handle = fcn_004f2a10(0, (int) entity, result,
					fcn_004f1790((char*) *(int*) (entity + 0x65), entry));
				n++;
				continue;
			}
			a = (gm_RandomFloat01() + 1.0f) * 0.5f;
			result = entry[0];
			value = (int) ((g_662c30 * *(unsigned char*) ((char*) entry + 0xc))
				* g_6652e8[result] * a);
			if (value > 0) {
				list = (char*) *(int*) (entity + 0x65);
				if (((fcn_004f1790(list, entry) ^ gm_GameTime) & 1) == 0) {
					handle = fcn_004f2d30((int) entity, result, fcn_004f1790(list, entry), -value);
					n++;
				}
			}
			if (home == 0)
				continue;
			if (slot != home && gm_GameTime % 4 == *(unsigned int*) (slot + 4) % 4
			    && *(unsigned char*) ((char*) entry + 0xc) * g_662c30 < 0.66f) {
				handle = cm_RequestCopyEntityData(*(unsigned int*) (home + 4), *(unsigned int*) (slot + 4),
					-5 - gm_RandomMod(0x10), 1);
				n++;
				hits++;
			}
			if (*(unsigned short*) ((char*) entry + 0xa) != gm_GameTime)
				continue;
			result = gm_CalcBribeOrPriceScore((int) slot, *(unsigned char*) ((char*) entry + 0xc), entry[0], 0, &out);
			if (slot == home) {
				handle = fcn_004f2810((int) slot, (int) entity, entry[0],
					fcn_004f1790((char*) *(int*) (entity + 0x65), entry), 10, 0);
			} else if (*(char*) (slot + 2) != 6 && *(char*) (slot + 2) != 7) {
				value = fcn_0050d320(slot, (char) g_773d75);
				if ((int) (value * g_66417c) > result) {
					handle = fcn_004f2810((int) slot, (int) entity, entry[0],
						fcn_004f1790((char*) *(int*) (entity + 0x65), entry), 10, result);
					n++;
					count++;
					total += out;
					continue;
				}
				handle = fcn_004f2a10(0, (int) entity, entry[0],
					fcn_004f1790((char*) *(int*) (entity + 0x65), entry));
			} else {
				memset(block, 0, sizeof(block));
				*(int*) ((char*) block + 8) = *(int*) (slot + 4);
				*(int*) ((char*) block + 0x28) = gm_GameTime;
				*(int*) ((char*) block + 0x30) = g_7f4c08;
				*(int*) ((char*) block + 0xc) = *(int*) (entity + 1);
				*(int*) ((char*) block + 0x2c) = g_7f4c04;
				*(int*) ((char*) block + 0x58) = *(int*) (entity + 1);
				*(unsigned char*) ((char*) block + 4) = 0x92;
				*(unsigned short*) ((char*) block + 0x34) = (unsigned short) g_7f4c0c;
				*(unsigned char*) ((char*) block + 0x36) = 9;
				*(int*) ((char*) block + 0x5c) = entry[0];
				*(char*) ((char*) block + 0x60) = (char) fcn_004f1790((char*) *(int*) (entity + 0x65), entry);
				*(int*) ((char*) block + 0x64) = result;
				*(int*) ((char*) block + 0x68) = 10;
				handle = cm_SendCopyEntityData(block);
			}
			n++;
next_entry:
			;
		} while ((entry = (int*) FindSlotEntryFiltered(0, entity, entry, (void*) fcn_004f1850, 0xff)) != 0);
	}
	if (cm_CountOccupiedBuildingStats(entity) < 4)
		fcn_004f2e80(entity, gm_RandomMod(2) + 1);
	if (home != 0 && (*(char*) (home + 2) == 6 || *(char*) (home + 2) == 7)) {
		if (count > 0)
			he_NotifyContractBatch((int) home, (int) entity, count, total);
		if (hits != 0)
			he_NotifyContractDefault((int) home, (int) entity);
	}
}
