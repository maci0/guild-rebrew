extern char io_MessageFormatBuf[];
extern char g_6ab528[];



void __cdecl io_FormatTextBuffer(void*, int, void*, void*, int);
void __cdecl he_MessageBoxQuickjump(int, int, void*, int, int, int, int, int, void*);

void __cdecl he_NotifyAlchemistEssence(void* slot, void* actor, void* building, int essenceId)
{
	char t;

	t = *(char*) ((char*) slot + 2);
	if (t == 6 || t == 7) {
		io_FormatTextBuffer(io_MessageFormatBuf, 0x4074, (char*) actor + 0x30, (char*) actor + 0x40,
		    essenceId + 0x4172);
		he_MessageBoxQuickjump(*(int*) ((char*) slot + 4), -1, io_MessageFormatBuf, 0, 0x5ec,
		    *(int*) ((char*) *(int*) ((char*) actor + 0x16c) + 1),
		    *(int*) ((char*) building + 2), 0, g_6ab528);
	}
}
