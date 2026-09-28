/* amt_fio_LoadAemter - loads the office slot table from a save stream. */

// FUNCTION: SERVER 0x1000baf0
// SIZE: 606

/* Office slot entry lifted to game_structs.h (this TU's read-order field
 * names are the ones kept; the aemter.c twin had `a/b/c/type/d`). */
#include "game_structs.h"

extern char g_office_slots[0x3f0]; /* 0x101de5a0 */
extern int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize,
                                         int elementCount, int streamCtx);
extern void __cdecl srv_InitBuildingTypeTable(void);

extern char s_amt_cant_load_count[];
extern char s_D__Develop_DieGildeAddOn_game_ae[];
extern char s_amt_count_mismatch[];
extern char s_amt_cant_load_id[];
extern char s_amt_cant_load_mplayerid[];
extern char s_amt_cant_load_mamt[];
extern char s_amt_cant_load_pcount[];
extern char s_amt_cant_load_status[];
extern char s_amt_cant_load_msetter[];
extern void __cdecl LogMessageInternal(const char* module, int line,
                                       const char* text, int type);
extern int __cdecl sprintf(char* buffer, const char* format, ...); /* 0x1001a299 */

/* Reads the office slot table.  The entry count depends on the save
 * version (0x25 for old saves, 0x2a for 0x10051+); each slot's six
 * fields are read with size checks.  Returns 1 on success, 0 on any
 * read failure or a count mismatch. */

int __cdecl amt_fio_LoadAemter(int streamCtx, int version)
{
	int value;
	char msg[0x100];
	unsigned int count;
	unsigned int i;

	count = (version >= 0x10051) ? 0x2a : 0x25;

	srv_InitBuildingTypeTable();

	if (streamCtx == 0)
		return 0;

	if (!ls_ReadVfsDataChecked(&value, 4, 1, streamCtx)) {
		LogMessageInternal(s_D__Develop_DieGildeAddOn_game_ae, 0xe73,
		                   s_amt_cant_load_count, 1);
		return 0;
	}
	if (value != (int) count) {
		sprintf(msg, s_amt_count_mismatch,
		        value, 0x2a);
		LogMessageInternal(s_D__Develop_DieGildeAddOn_game_ae, 0xe7c,
		                   msg, 1);
		return 0;
	}
	for (i = 0; i < count; i++) {
		if (!ls_ReadVfsDataChecked(&((OFFICE_SLOT*) g_office_slots)[i].id, 1, 1, streamCtx)) {
			LogMessageInternal(s_D__Develop_DieGildeAddOn_game_ae, 0xe82,
			                   s_amt_cant_load_id, 1);
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&((OFFICE_SLOT*) g_office_slots)[i].mplayerid, 4, 1, streamCtx)) {
			LogMessageInternal(s_D__Develop_DieGildeAddOn_game_ae, 0xe83,
			                   s_amt_cant_load_mplayerid, 1);
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&((OFFICE_SLOT*) g_office_slots)[i].mamt, 1, 1, streamCtx)) {
			LogMessageInternal(s_D__Develop_DieGildeAddOn_game_ae, 0xe84,
			                   s_amt_cant_load_mamt, 1);
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&((OFFICE_SLOT*) g_office_slots)[i].pcount, 4, 1, streamCtx)) {
			LogMessageInternal(s_D__Develop_DieGildeAddOn_game_ae, 0xe85,
			                   s_amt_cant_load_pcount, 1);
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&((OFFICE_SLOT*) g_office_slots)[i].status, 1, 1, streamCtx)) {
			LogMessageInternal(s_D__Develop_DieGildeAddOn_game_ae, 0xe86,
			                   s_amt_cant_load_status, 1);
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&((OFFICE_SLOT*) g_office_slots)[i].msetter, 4, 1, streamCtx)) {
			LogMessageInternal(s_D__Develop_DieGildeAddOn_game_ae, 0xe87,
			                   s_amt_cant_load_msetter, 1);
			return 0;
		}
	}
	return 1;
}
