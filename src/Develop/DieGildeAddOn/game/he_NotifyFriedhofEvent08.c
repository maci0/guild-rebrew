extern char he_GraveSlotTextIds[];
extern char io_MessageFormatBuf[];
extern char g_6ab49c[];


int  __cdecl main_GetLanguage(void);
void __cdecl io_FormatTextBuffer(void*, int, int, int, int, int, int);
void __cdecl he_PostEntityMessage(int, int, void*, int, int, void*);

/* ADDRESS: GOLDDE 0x005976b0 */
void __cdecl he_NotifyFriedhofEvent08(void* entity, void* otherEntity, int targetPtr, int actionKind, int amount, int bonus)
{
	char t;

	t = *(char*) ((char*) entity + 2);
	if (t == 6 || t == 7) {
		switch (main_GetLanguage()) {
		case 0:
		case 2:
			io_FormatTextBuffer(io_MessageFormatBuf, 0x414e, *(unsigned short*) otherEntity, targetPtr,
			    *(int*) ((int) &he_GraveSlotTextIds + actionKind * 4), amount, bonus);
			break;
		case 1:
			io_FormatTextBuffer(io_MessageFormatBuf, 0x414e, *(unsigned short*) otherEntity,
			    *(int*) ((int) &he_GraveSlotTextIds + actionKind * 4), targetPtr, amount, bonus);
			break;
		}
		he_PostEntityMessage(*(int*) ((char*) entity + 4), -1, io_MessageFormatBuf, 0, 0x5fc, g_6ab49c);
	}
}
