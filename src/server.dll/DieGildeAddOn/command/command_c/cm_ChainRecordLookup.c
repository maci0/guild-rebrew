
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#pragma clang diagnostic ignored "-Wpointer-to-int-cast"
#pragma clang diagnostic ignored "-Wvoid-pointer-to-int-cast"
#endif

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 327B
 *    CFlags: 
 *    Symbol: _chain_handler_record_lookup
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl cm_ChainRecordLookup(int param_1,char *param_2)
 * 
 * {
 *   bool bVar1;
 *   ushort *puVar2;
 *   char *pcVar3;
 *   int iVar4;
 *   char *pcVar5;
 *   char local_1;
 *   
 *                     / * Entity chain handler that performs a record search using
 *                        FindRecord/lb_SearchRecordTable based on entity IDs passed in the payload.
 *                        Conditionally calls FUN_100150a0 depending on flags. Used for syncing
 *                        database/stat lookups within batched updates. * /
 *   local_1 = '\x02';
 *   pcVar5 = (char *)0x0;
 *   bVar1 = false;
 *   *(undefined4 *)(param_1 + 0x10) = g_plant_count;
 *   puVar2 = gm_StartFilteredEntitySearch(1,1,*(undefined4 *)(param_1 + 0x14));
 *   if (puVar2 != (ushort *)0x0) {
 *     pcVar3 = lb_SearchRecordTable((uint)*(ushort *)(param_1 + 0x1a));
 *     if (((pcVar3 == (char *)0x0) || (*(char *)(param_1 + 0x1c) != '\0')) ||
 *        (iVar4 = CheckZoneAvailability
 *                           (*(int *)((int)puVar2 + 0x71),(uint)*(byte *)(param_1 + 0x18),
 *                            (uint)*(byte *)(param_1 + 0x19),(uint)(byte)pcVar3[0x42]), iVar4 != 0)) {
 *       bVar1 = true;
 *     }
 *     if (*(char *)(param_1 + 0x1c) == '\0') {
 *       if (*(int *)(param_1 + 0x1d) != -1) {
 *         pcVar5 = FindRecord(*(char **)((int)puVar2 + 0x71),(uint)*(byte *)(param_1 + 0x18),
 *                             (uint)*(byte *)(param_1 + 0x19));
 *         if (param_2 == (char *)0x0) {
 *           return 0;
 *         }
 *         *(char **)(param_2 + 6) = pcVar5;
 *         *param_2 = '\x01';
 *         param_2[1] = '\x05';
 *         return 0;
 *       }
 *     }
 *     else {
 *       pcVar5 = FindRecord(*(char **)((int)puVar2 + 0x71),(uint)*(byte *)(param_1 + 0x18),
 */

char* __cdecl lb_SearchRecordTable(unsigned int);
int __cdecl CheckZoneAvailability(void*, unsigned int, unsigned int, unsigned int);
char* __cdecl FindRecord(void*, unsigned int, unsigned int);
char* __cdecl plt_SetPlantMap(void*, unsigned int, unsigned int, unsigned int, unsigned int);

extern int g_plant_count;
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);

/* Chain handler: performs a record/zone lookup for a filtered entity.
 * Searches the plant record table, checks zone availability, and
 * optionally creates new plant map entries via plt_SetPlantMap.
 * Writes the found record pointer and status byte into *param_2. */

// FUNCTION: SERVER 0x1000f1a0
int __cdecl cm_ChainRecordLookup(int param_1, char* param_2)
{
	char status;
	void* entity;
	char* rec;
	char* found;
	int needs_create;

	status = '\x02';
	found = (char*) 0x0;
	needs_create = 0;

	*(int*) (param_1 + 0x10) = g_plant_count;
	entity = gm_StartFilteredEntitySearch(1, 1, *(int*) (param_1 + 0x14));
	if (entity != (void*) 0x0) {
		rec = lb_SearchRecordTable(*(unsigned short*) (param_1 + 0x1a));

		if ((rec == (char*) 0x0) || (*(unsigned char*) (param_1 + 0x1c) != 0) ||
			(CheckZoneAvailability(
				 *(void**) ((char*) entity + 0x71),
				 *(unsigned char*) (param_1 + 0x18),
				 *(unsigned char*) (param_1 + 0x19),
				 (unsigned char) rec[0x42]
			 ) != 0)) {
			needs_create = 1;
		}

		if (*(unsigned char*) (param_1 + 0x1c) != 0) {
			found = FindRecord(
				*(void**) ((char*) entity + 0x71),
				*(unsigned char*) (param_1 + 0x18),
				*(unsigned char*) (param_1 + 0x19)
			);
			if ((found != (char*) 0x0) && (*(int*) (found + 0x10) != -1)) {
				return 1;
			}
		}
		else if (*(int*) (param_1 + 0x1d) != -1) {
			found = FindRecord(
				*(void**) ((char*) entity + 0x71),
				*(unsigned char*) (param_1 + 0x18),
				*(unsigned char*) (param_1 + 0x19)
			);
			if (param_2 == (char*) 0x0) {
				return 0;
			}
			*(char**) (param_2 + 6) = found;
			*param_2 = '\x01';
			param_2[1] = '\x05';
			return 0;
		}

		if (needs_create != 0) {
			found = plt_SetPlantMap(
				*(void**) ((char*) entity + 0x71),
				*(unsigned char*) (param_1 + 0x18),
				*(unsigned char*) (param_1 + 0x19),
				*(unsigned short*) (param_1 + 0x1a),
				*(unsigned char*) (param_1 + 0x1c)
			);
		}

		if (found != (char*) 0x0) {
			status = '\x01';
			*(int*) (found + 4) = *(int*) ((char*) entity + 1);
			if (*(unsigned char*) (param_1 + 0x1c) != 0) {
				*(int*) (found + 0x10) = *(int*) (param_1 + 0x1d);
			}
		}
	}

	if (param_2 != (char*) 0x0) {
		param_2[1] = '\x05';
		*param_2 = status;
		*(char**) (param_2 + 6) = found;
	}

	return 0;
}
