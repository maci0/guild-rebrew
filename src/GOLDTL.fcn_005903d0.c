


extern unsigned char* g_868050;
extern int g_774800;

int __cdecl fcn_00507910(int);
int __cdecl gm_CheckStatLevel(int, int);

int __cdecl fcn_005903d0(unsigned short* who, unsigned char* p, short* cmd)
{
	unsigned char* t;
	int lvl;
	int flags;
	int i;

	t = g_868050 + *p * 589;
	lvl = gm_CheckStatLevel(*who, fcn_00507910(*t));
	flags = 0x81;
	if (*(unsigned short*) (p + 0x25) == *who) {
		flags |= 0x103c;
	}
	if (cmd != 0 && (*cmd == 0x211 || *cmd == 0x205)) {
		flags &= ~1;
	}
	if (*(unsigned short*) (p + 0x27) == *who) {
		flags |= 0x4461;
		for (i = 0; i < 6; i++) {
			if (t[0x223 + i] == 0) {
				break;
			}
			if (lvl == t[0x223 + i]) {
				flags |= 0x2200;
				break;
			}
		}
	}
	if (cmd != 0 && *cmd == 0x21b) {
		flags |= 0x5000;
	}
	if (g_774800 != 0) {
		flags = -1;
	}
	return flags;
}
