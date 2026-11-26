extern char g_774a80[];



unsigned short __cdecl gm_RandomMod(int);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl he_PostEntityMessage(int, int, void*, int, int, int);

void __cdecl he_NotifyFeudDeclared(void* initiator, void* recipient)
{
	char buf[0x200];
	char t;

	t = *(char*) ((char*) recipient + 2);
	if (t == 6 || t == 7) {
		io_FormatTextBuffer(buf, gm_RandomMod(3) + 0x1340, *(unsigned short*) initiator);
		io_FormatTextBuffer(g_774a80, 0x1339, *(unsigned short*) initiator,
		    gm_RandomMod(3) +
		        (*(char*) ((char*) recipient + 9) != 0 ? 0x133d : 0x133a),
		    *(unsigned short*) recipient, buf);
		he_PostEntityMessage(*(int*) ((char*) recipient + 4), -1, g_774a80, 1, 0x5ec, 0);
	}
}
