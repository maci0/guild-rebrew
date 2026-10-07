// FUNCTION: GOLD 0x4eab20
// FUNCTION: GOLDTL 0x004ec8a0

extern float g_66416c;
extern float g_662a94;

int __cdecl ahm_CheckFlag(char* p);

float __cdecl fcn_004ec8a0(char* p, int which)
{
	if (ahm_CheckFlag(p)) {
		if (which == 0) {
			return (*(unsigned char**) (*(char**) (p + 0x16c) + 0x65))[8] * g_66416c;
		}
		if (which == 1) {
			return (*(unsigned char**) (*(char**) (p + 0x16c) + 0x65))[9] * g_66416c;
		}
		if (which == 2) {
			return (*(unsigned char**) (*(char**) (p + 0x16c) + 0x65))[0xa] * g_66416c;
		}
		if (which == 3) {
			return (*(unsigned char**) (*(char**) (p + 0x16c) + 0x65))[0xb] * g_66416c;
		}
	}
	return g_662a94;
}
