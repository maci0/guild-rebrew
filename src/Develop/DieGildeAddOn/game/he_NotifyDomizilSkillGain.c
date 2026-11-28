extern char io_MessageFormatBuf[];
extern char he_DomizilNotifyKey[];



void __cdecl io_FormatTextBuffer(void*, int, void*, void*, int);
void __cdecl he_MessageBoxQuickjump(int, int, void*, int, int, int, int, int, void*);

/* ADDRESS: GOLDDE 0x00597da0 */
void __cdecl he_NotifyDomizilSkillGain(void* entity, void* actor, void* building, int index)
{
	char t;

	t = *(char*) ((char*) entity + 2);
	if (t == 6 || t == 7) {
		io_FormatTextBuffer(io_MessageFormatBuf, 0x407f, (char*) actor + 0x30, (char*) actor + 0x40,
		    2 * index + 0x9a8);
		he_MessageBoxQuickjump(*(int*) ((char*) entity + 4), -1, io_MessageFormatBuf, 1, 0x5ec,
		    *(int*) ((char*) building + 1), -1, 0, he_DomizilNotifyKey);
	}
}
