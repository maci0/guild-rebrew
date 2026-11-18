extern char g_774a80[];
extern char g_6ab540[];


void __cdecl io_FormatTextBuffer(void*, int, void*, void*, int);
void __cdecl he_MessageBoxQuickjump(int, int, void*, int, int, int, int, int, void*);

/* ADDRESS: GOLD 0x5a9d80 */
void __cdecl fcn_005b3200(void* recipient, void* subject, void* a3, int a4)
{
	char t;

	t = *(char*) ((char*) recipient + 2);
	if (t == 6 || t == 7) {
		io_FormatTextBuffer(g_774a80, 0x4077, (char*) subject + 0x30, (char*) subject + 0x40,
		    2 * a4 + 0x9a8);
		he_MessageBoxQuickjump(*(int*) ((char*) recipient + 4), -1, g_774a80, 0, 0x5ec,
		    *(int*) ((char*) *(int*) ((char*) subject + 0x16c) + 1),
		    *(int*) ((char*) a3 + 2), 0, g_6ab540);
	}
}
