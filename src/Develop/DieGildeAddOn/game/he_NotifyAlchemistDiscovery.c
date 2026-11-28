extern char io_MessageFormatBuf[];
extern char he_DomizilNotifyKey[];



void __cdecl io_FormatTextBuffer(void*, int, void*, void*, void*, int);
void __cdecl he_MessageBoxQuickjump(int, int, void*, int, int, int, int, int, void*);

/* ADDRESS: GOLDDE 0x00597d30 */
void __cdecl he_NotifyAlchemistDiscovery(void* entity, void* actor, void* building, void* record)
{
	char kind;

	kind = *(char*) ((char*) entity + 2);
	if (kind == 6 || kind == 7) {
		io_FormatTextBuffer(io_MessageFormatBuf, 0x407c, (char*) actor + 0x30, (char*) actor + 0x40, building,
		    2 * *(unsigned short*) record + 0x9a8);
		he_MessageBoxQuickjump(*(int*) ((char*) entity + 4), -1, io_MessageFormatBuf, 1, 0x5ec,
		    *(int*) ((char*) building + 1), *(int*) ((char*) record + 2), 0, he_DomizilNotifyKey);
	}
}
