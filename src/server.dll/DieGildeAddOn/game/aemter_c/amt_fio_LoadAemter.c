/* amt_fio_LoadAemter - loads the office slot table from a save stream. */

// FUNCTION: SERVER 0x1000baf0
// SYMBOL: _amt_fio_LoadAemter
// SIZE: 606

/* Office slot table entry - 0x18 bytes per slot. */
// SIZE 0x18
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

extern char s_amt_fio_LoadAemter____Can_t_load_1002a0c8[];
extern char s_D__Develop_DieGildeAddOn_game_ae_1002a0a0[];
extern char s_amt_fio_LoadAemter____count_read_1002a06c[];
extern char s_amt_fio_LoadAemter____Can_t_load_1002a048[];
extern char s_amt_fio_LoadAemter____Can_t_load_1002a01c[];
extern char s_amt_fio_LoadAemter____Can_t_load_10029ff4[];
extern char s_amt_fio_LoadAemter____Can_t_load_10029fcc[];
extern char s_amt_fio_LoadAemter____Can_t_load_10029fa4[];
extern char s_amt_fio_LoadAemter____Can_t_load_10029f78[];
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
		LogMessageInternal(s_D__Develop_DieGildeAddOn_game_ae_1002a0a0, 0xe73,
		                   s_amt_fio_LoadAemter____Can_t_load_1002a0c8, 1);
		return 0;
	}
	if (value != (int) count) {
		sprintf(msg, s_amt_fio_LoadAemter____count_read_1002a06c,
		        value, 0x2a);
		LogMessageInternal(s_D__Develop_DieGildeAddOn_game_ae_1002a0a0, 0xe7c,
		                   msg, 1);
		return 0;
	}
	for (i = 0; i < count; i++) {
		if (!ls_ReadVfsDataChecked(&g_office_slots[i].id, 1, 1, streamCtx)) {
			LogMessageInternal(s_D__Develop_DieGildeAddOn_game_ae_1002a0a0, 0xe82,
			                   s_amt_fio_LoadAemter____Can_t_load_1002a048, 1);
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&g_office_slots[i].mplayerid, 4, 1, streamCtx)) {
			LogMessageInternal(s_D__Develop_DieGildeAddOn_game_ae_1002a0a0, 0xe83,
			                   s_amt_fio_LoadAemter____Can_t_load_1002a01c, 1);
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&g_office_slots[i].mamt, 1, 1, streamCtx)) {
			LogMessageInternal(s_D__Develop_DieGildeAddOn_game_ae_1002a0a0, 0xe84,
			                   s_amt_fio_LoadAemter____Can_t_load_10029ff4, 1);
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&g_office_slots[i].pcount, 4, 1, streamCtx)) {
			LogMessageInternal(s_D__Develop_DieGildeAddOn_game_ae_1002a0a0, 0xe85,
			                   s_amt_fio_LoadAemter____Can_t_load_10029fcc, 1);
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&g_office_slots[i].status, 1, 1, streamCtx)) {
			LogMessageInternal(s_D__Develop_DieGildeAddOn_game_ae_1002a0a0, 0xe86,
			                   s_amt_fio_LoadAemter____Can_t_load_10029fa4, 1);
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&g_office_slots[i].msetter, 4, 1, streamCtx)) {
			LogMessageInternal(s_D__Develop_DieGildeAddOn_game_ae_1002a0a0, 0xe87,
			                   s_amt_fio_LoadAemter____Can_t_load_10029f78, 1);
			return 0;
		}
	}
	return 1;
}
