extern char g_774a80[];
extern char g_6ab558[];



void __cdecl io_FormatTextBuffer(void*, int, void*, void*, int);
void __cdecl he_MessageBoxQuickjump(int, int, void*, int, int, int, int, int, void*);

void __cdecl fcn_005b33a0(void* entity, void* actor, void* building, int index)
{
	char t;

	t = *(char*) ((char*) entity + 2);
	if (t == 6 || t == 7) {
		io_FormatTextBuffer(g_774a80, 0x407f, (char*) actor + 0x30, (char*) actor + 0x40,
		    2 * index + 0x9a8);
		he_MessageBoxQuickjump(*(int*) ((char*) entity + 4), -1, g_774a80, 1, 0x5ec,
		    *(int*) ((char*) building + 1), -1, 0, g_6ab558);
	}
}
