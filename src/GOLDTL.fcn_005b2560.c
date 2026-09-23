extern char g_774a80[];
// FUNCTION: GOLDTL 0x5b2560
// SIZE: 180

unsigned short __cdecl fcn_0042e410(int);
void __cdecl fcn_0051af00(void*, int, ...);
void __cdecl fcn_00545d40(int, int, void*, int, int, int);

void __cdecl fcn_005b2560(void* a1, void* a2)
{
	char buf[0x200];
	char t;

	t = *(char*) ((char*) a2 + 2);
	if (t == 6 || t == 7) {
		fcn_0051af00(buf, fcn_0042e410(3) + 0x1340, *(unsigned short*) a1);
		fcn_0051af00(g_774a80, 0x1339, *(unsigned short*) a1,
		    fcn_0042e410(3) +
		        (*(char*) ((char*) a2 + 9) != 0 ? 0x133d : 0x133a),
		    *(unsigned short*) a2, buf);
		fcn_00545d40(*(int*) ((char*) a2 + 4), -1, g_774a80, 1, 0x5ec, 0);
	}
}
