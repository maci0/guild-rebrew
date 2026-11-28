extern char io_MessageFormatBuf[];
char he_DomizilNotifyKey[] = "_NACHRICHTEN_DOMIZIL_04";



void __cdecl io_FormatTextBuffer(void*, int, void*, void*, void*);
void __cdecl he_MessageBoxQuickjump(int, int, void*, int, int, int, int, int, void*);

/* ADDRESS: GOLDDE 0x00597c70 */
void __cdecl he_NotifyDomizilAccident(void* entity, int actor, void* building)
{
	char kind;

	kind = *(char*) ((char*) entity + 2);
	if (kind == 6 || kind == 7) {
		io_FormatTextBuffer(io_MessageFormatBuf, 0x407a, (char*) actor + 0x30, (char*) actor + 0x40, building);
		he_MessageBoxQuickjump(*(int*) ((char*) entity + 4), -1, io_MessageFormatBuf, 1, 0x5ec,
		    *(int*) ((char*) building + 1), -1, 0, he_DomizilNotifyKey);
	}
}
