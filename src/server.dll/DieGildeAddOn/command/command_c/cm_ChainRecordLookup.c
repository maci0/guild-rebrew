
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
 * int __cdecl cm_ChainRecordLookup(int cmd,char *result)
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
 *                        plt_FindRecord/lb_SearchRecordTable based on entity IDs passed in the payload.
 *                        Conditionally calls FUN_100150a0 depending on flags. Used for syncing
 *                        database/stat lookups within batched updates. * /
 *   local_1 = '\x02';
 *   pcVar5 = (char *)0x0;
 *   bVar1 = false;
 *   *(undefined4 *)(cmd + 0x10) = g_dynamic_count;
 *   puVar2 = gm_StartFilteredEntitySearch(1,1,*(undefined4 *)(cmd + 0x14));
 *   if (puVar2 != (ushort *)0x0) {
 *     pcVar3 = lb_SearchRecordTable((uint)*(ushort *)(cmd + 0x1a));
 *     if (((pcVar3 == (char *)0x0) || (*(char *)(cmd + 0x1c) != '\0')) ||
 *        (iVar4 = plt_CheckZoneAvailability
 *                           (*(int *)((int)puVar2 + 0x71),(uint)*(byte *)(cmd + 0x18),
 *                            (uint)*(byte *)(cmd + 0x19),(uint)(byte)pcVar3[0x42]), iVar4 != 0)) {
 *       bVar1 = true;
 *     }
 *     if (*(char *)(cmd + 0x1c) == '\0') {
 *       if (*(int *)(cmd + 0x1d) != -1) {
 *         pcVar5 = plt_FindRecord(*(char **)((int)puVar2 + 0x71),(uint)*(byte *)(cmd + 0x18),
 *                             (uint)*(byte *)(cmd + 0x19));
 *         if (result == (char *)0x0) {
 *           return 0;
 *         }
 *         *(char **)(result + 6) = pcVar5;
 *         *result = '\x01';
 *         result[1] = '\x05';
 *         return 0;
 *       }
 *     }
 *     else {
 *       pcVar5 = plt_FindRecord(*(char **)((int)puVar2 + 0x71),(uint)*(byte *)(cmd + 0x18),
 */

char* __cdecl lb_SearchRecordTable(unsigned int);
int __cdecl plt_CheckZoneAvailability(void*, unsigned int, unsigned int, unsigned int);
char* __cdecl plt_FindRecord(void*, unsigned int, unsigned int);
char* __cdecl plt_SetPlantMap(void*, unsigned int, unsigned int, unsigned int, unsigned int);

extern int g_dynamic_count;
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);

/* Chain handler: performs a record/zone lookup for a filtered entity.
 * Searches the plant record table, checks zone availability, and
 * optionally creates new plant map entries via plt_SetPlantMap.
 * Writes the found record pointer and status byte into *result. */

// FUNCTION: SERVER 0x1000f1a0
int __cdecl cm_ChainRecordLookup(int cmd, char* result)
{
	char status;
	void* entity;
	char* rec;
	char* found;
	int needs_create;

	status = '\x02';
	found = (char*) 0x0;
	needs_create = 0;

	*(int*) (cmd + 0x10) = g_dynamic_count;
	entity = gm_StartFilteredEntitySearch(1, 1, *(int*) (cmd + 0x14));
	if (entity != (void*) 0x0) {
		rec = lb_SearchRecordTable(*(unsigned short*) (cmd + 0x1a));

		if ((rec == (char*) 0x0) || (*(unsigned char*) (cmd + 0x1c) != 0) ||
			(plt_CheckZoneAvailability(
				 *(void**) ((char*) entity + 0x71),
				 *(unsigned char*) (cmd + 0x18),
				 *(unsigned char*) (cmd + 0x19),
				 (unsigned char) rec[0x42]
			 ) != 0)) {
			needs_create = 1;
		}

		if (*(unsigned char*) (cmd + 0x1c) != 0) {
			found = plt_FindRecord(
				*(void**) ((char*) entity + 0x71),
				*(unsigned char*) (cmd + 0x18),
				*(unsigned char*) (cmd + 0x19)
			);
			if ((found != (char*) 0x0) && (*(int*) (found + 0x10) != -1)) {
				return 1;
			}
		}
		else if (*(int*) (cmd + 0x1d) != -1) {
			found = plt_FindRecord(
				*(void**) ((char*) entity + 0x71),
				*(unsigned char*) (cmd + 0x18),
				*(unsigned char*) (cmd + 0x19)
			);
			if (result == (char*) 0x0) {
				return 0;
			}
			*(char**) (result + 6) = found;
			*result = '\x01';
			result[1] = '\x05';
			return 0;
		}

		if (needs_create != 0) {
			found = plt_SetPlantMap(
				*(void**) ((char*) entity + 0x71),
				*(unsigned char*) (cmd + 0x18),
				*(unsigned char*) (cmd + 0x19),
				*(unsigned short*) (cmd + 0x1a),
				*(unsigned char*) (cmd + 0x1c)
			);
		}

		if (found != (char*) 0x0) {
			status = '\x01';
			*(int*) (found + 4) = *(int*) ((char*) entity + 1);
			if (*(unsigned char*) (cmd + 0x1c) != 0) {
				*(int*) (found + 0x10) = *(int*) (cmd + 0x1d);
			}
		}
	}

	if (result != (char*) 0x0) {
		result[1] = '\x05';
		*result = status;
		*(char**) (result + 6) = found;
	}

	return 0;
}
