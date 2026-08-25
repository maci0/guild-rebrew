/* amt_fio_LoadAemter - loads the office slot table from a save stream. */

// FUNCTION: SERVER 0x1000baf0
// SYMBOL: _amt_fio_LoadAemter
// SIZE: 606

/* Office slot table entry - 0x18 bytes per slot. */
typedef struct {
	unsigned char id;        /* +0x00 */
	unsigned char pad1[3];
	int mplayerid;           /* +0x04 */
	unsigned char mamt;      /* +0x08 */
	unsigned char pad2[3];
	int pcount;              /* +0x0c */
	unsigned char status;    /* +0x10 */
	unsigned char pad3[3];
	int msetter;             /* +0x14 */
} OFFICE_SLOT;

extern OFFICE_SLOT g_office_slots[];
extern int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize,
                                         int elementCount, int streamCtx);
extern void __cdecl InitBuildingTypeTable(void);
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

	InitBuildingTypeTable();

	if (streamCtx == 0)
		return 0;

	if (!ls_ReadVfsDataChecked(&value, 4, 1, streamCtx)) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\aemter.c", 0xe73,
		                   "amt_fio_LoadAemter(): Can't load count", 1);
		return 0;
	}
	if (value != (int) count) {
		sprintf(msg, "amt_fio_LoadAemter(): count read is %i, expected %i",
		        value, 0x2a);
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\aemter.c", 0xe7c,
		                   msg, 1);
		return 0;
	}
	for (i = 0; i < count; i++) {
		if (!ls_ReadVfsDataChecked(&g_office_slots[i].id, 1, 1, streamCtx)) {
			LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\aemter.c", 0xe82,
			                   "amt_fio_LoadAemter(): Can't load id", 1);
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&g_office_slots[i].mplayerid, 4, 1, streamCtx)) {
			LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\aemter.c", 0xe83,
			                   "amt_fio_LoadAemter(): Can't load mplayerid", 1);
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&g_office_slots[i].mamt, 1, 1, streamCtx)) {
			LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\aemter.c", 0xe84,
			                   "amt_fio_LoadAemter(): Can't load mamt", 1);
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&g_office_slots[i].pcount, 4, 1, streamCtx)) {
			LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\aemter.c", 0xe85,
			                   "amt_fio_LoadAemter(): Can't load pcount", 1);
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&g_office_slots[i].status, 1, 1, streamCtx)) {
			LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\aemter.c", 0xe86,
			                   "amt_fio_LoadAemter(): Can't load status", 1);
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&g_office_slots[i].msetter, 4, 1, streamCtx)) {
			LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\aemter.c", 0xe87,
			                   "amt_fio_LoadAemter(): Can't load msetter", 1);
			return 0;
		}
	}
	return 1;
}
