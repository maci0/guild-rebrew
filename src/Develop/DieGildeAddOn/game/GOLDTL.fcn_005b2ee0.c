extern char g_774a80[];
extern char g_6ab4b8[];



int  __cdecl main_GetLanguage(void);
unsigned short __cdecl gm_RandomMod(int);
void __cdecl io_FormatTextBuffer(void*, int, int, int, void*, int);
void __cdecl he_PostEntityMessage(int, int, void*, int, int, void*);

void __cdecl he_NotifyHeimsuchung(void* subject, void* recipient, void* target)
{
	switch (main_GetLanguage()) {
	case 0:
	case 2:
		io_FormatTextBuffer(g_774a80, 0x409b, gm_RandomMod(3) + 0x409c,
		    *(unsigned short*) subject, target, *(unsigned short*) subject);
		break;
	case 1:
		io_FormatTextBuffer(g_774a80, 0x409b, gm_RandomMod(3) + 0x409c,
		    *(unsigned short*) subject, (void*) *(unsigned short*) subject, (int) target);
		break;
	}
	he_PostEntityMessage(*(int*) ((char*) recipient + 4), -1, g_774a80, 1, 0x5fb, g_6ab4b8);
}
