extern char g_774a80[];
extern char g_6ab528[];


void __cdecl io_FormatTextBuffer(void*, int, void*, void*, int);
void __cdecl he_MessageBoxQuickjump(int, int, void*, int, int, int, int, int, void*);

/* ADDRESS: GOLD 0x5a9d10 */
void __cdecl he_NotifyDomizil03(void* recipient, void* subject, void* targetObj, int recipeId)
{
	char t;

	t = *(char*) ((char*) recipient + 2);
	if (t == 6 || t == 7) {
		io_FormatTextBuffer(g_774a80, 0x4075, (char*) subject + 0x30, (char*) subject + 0x40,
		    2 * recipeId + 0x9a8);
		he_MessageBoxQuickjump(*(int*) ((char*) recipient + 4), -1, g_774a80, 0, 0x5ec,
		    *(int*) ((char*) *(int*) ((char*) subject + 0x16c) + 1),
		    *(int*) ((char*) targetObj + 2), 0, g_6ab528);
	}
}
