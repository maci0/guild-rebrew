extern int he_GraveSlotTextIds[];
extern int he_GraveSlotTextIds[];
extern char io_MessageFormatBuf[];
extern char str_empty[];



int  __cdecl main_GetLanguage(void);
void __cdecl io_FormatTextBuffer(void*, int, int, int, int);
void __cdecl he_PostEntityMessage(int, int, void*, int, int, void*);

/* ADDRESS: GOLDDE 0x00597850 */
void __cdecl he_NotifyStorageTransfer(void* entity, void* otherEntity, int count, int tableIndex)
{
	char t;

	t = *(char*) ((char*) entity + 2);
	if (t == 6 || t == 7) {
		switch (main_GetLanguage()) {
		case 0:
		case 2:
			io_FormatTextBuffer(io_MessageFormatBuf, 0x4150, *(unsigned short*) otherEntity, count,
			    he_GraveSlotTextIds[tableIndex]);
			break;
		case 1:
			io_FormatTextBuffer(io_MessageFormatBuf, 0x4150, *(unsigned short*) otherEntity,
			    he_GraveSlotTextIds[tableIndex], count);
			break;
		}
		he_PostEntityMessage(*(int*) ((char*) entity + 4), -1, io_MessageFormatBuf, 0, 0x5fc, str_empty);
	}
}
