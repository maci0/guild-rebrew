extern char g_774a80[];



unsigned short __cdecl gm_RandomMod(int);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl fcn_00545d40(int, int, void*, int, int, int);

void __cdecl fcn_005b2560(void* a1, void* a2)
{
	char buf[0x200];
	char t;

	t = *(char*) ((char*) a2 + 2);
	if (t == 6 || t == 7) {
		io_FormatTextBuffer(buf, gm_RandomMod(3) + 0x1340, *(unsigned short*) a1);
		io_FormatTextBuffer(g_774a80, 0x1339, *(unsigned short*) a1,
		    gm_RandomMod(3) +
		        (*(char*) ((char*) a2 + 9) != 0 ? 0x133d : 0x133a),
		    *(unsigned short*) a2, buf);
		fcn_00545d40(*(int*) ((char*) a2 + 4), -1, g_774a80, 1, 0x5ec, 0);
	}
}
