extern char g_774a80[];
char g_6ab558[] = "_NACHRICHTEN_DOMIZIL_04";



void __cdecl io_FormatTextBuffer(void*, int, void*, void*, void*);
void __cdecl he_MessageBoxQuickjump(int, int, void*, int, int, int, int, int, void*);

void __cdecl fcn_005b3270(void* entity, int actor, void* building)
{
	char kind;

	kind = *(char*) ((char*) entity + 2);
	if (kind == 6 || kind == 7) {
		io_FormatTextBuffer(g_774a80, 0x407a, (char*) actor + 0x30, (char*) actor + 0x40, building);
		he_MessageBoxQuickjump(*(int*) ((char*) entity + 4), -1, g_774a80, 1, 0x5ec,
		    *(int*) ((char*) building + 1), -1, 0, g_6ab558);
	}
}
