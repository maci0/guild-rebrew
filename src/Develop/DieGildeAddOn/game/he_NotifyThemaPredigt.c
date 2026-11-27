


extern char g_7f4ca0[];
extern char g_774a80[];
extern char g_6b5c60[];

void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, char*);

void __cdecl he_NotifyThemaPredigt(char* preacher, char* target, int topicBuilding)
{
	int i;

	if (target[2] == 6 || target[2] == 7) {
		io_FormatTextBuffer(g_774a80, 0x20c1, *(unsigned short*) preacher, topicBuilding);
		he_PostEntityMessage(*(int*) (target + 4), -1, g_774a80, 0, 0x5fb, g_6b5c60);
	}
	io_FormatTextBuffer(g_774a80, 0x20c2, topicBuilding, *(unsigned short*) preacher, (preacher[9] != 0) + 0x20c3,
	    *(unsigned short*) target);
	for (i = 0; i < 768; i++) {
		if (g_7f4ca0 + i * 540 != preacher && g_7f4ca0 + i * 540 != target &&
		    (g_7f4ca0[i * 540 + 2] == 6 || g_7f4ca0[i * 540 + 2] == 7)) {
			he_PostEntityMessage(*(int*) (g_7f4ca0 + i * 540 + 4), -1, g_774a80, 0, 0x5ec, g_6b5c60);
		}
	}
}
