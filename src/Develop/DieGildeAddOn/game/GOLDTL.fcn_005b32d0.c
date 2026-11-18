extern char g_774a80[];
extern char g_6ab558[];



void __cdecl io_FormatTextBuffer(void*, int, void*, void*);
void __cdecl he_MessageBoxQuickjump(int, int, void*, int, int, int, int, int, void*);

void __cdecl fcn_005b32d0(void* recipient, int subject, void* a3)
{
	char t;

	t = *(char*) ((char*) recipient + 2);
	if (t == 6 || t == 7) {
		io_FormatTextBuffer(g_774a80, 0x407b, (char*) subject + 0x30, (char*) subject + 0x40);
		he_MessageBoxQuickjump(*(int*) ((char*) recipient + 4), -1, g_774a80, 1, 0x5ec,
		    *(int*) ((char*) a3 + 1), -1, 0, g_6ab558);
	}
}
