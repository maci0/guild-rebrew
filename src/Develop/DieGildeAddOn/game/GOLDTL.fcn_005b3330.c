extern char g_774a80[];
extern char g_6ab558[];



void __cdecl io_FormatTextBuffer(void*, int, void*, void*, void*, int);
void __cdecl he_MessageBoxQuickjump(int, int, void*, int, int, int, int, int, void*);

void __cdecl fcn_005b3330(void* entity, void* actor, void* building, void* record)
{
	char kind;

	kind = *(char*) ((char*) entity + 2);
	if (kind == 6 || kind == 7) {
		io_FormatTextBuffer(g_774a80, 0x407c, (char*) actor + 0x30, (char*) actor + 0x40, building,
		    2 * *(unsigned short*) record + 0x9a8);
		he_MessageBoxQuickjump(*(int*) ((char*) entity + 4), -1, g_774a80, 1, 0x5ec,
		    *(int*) ((char*) building + 1), *(int*) ((char*) record + 2), 0, g_6ab558);
	}
}
