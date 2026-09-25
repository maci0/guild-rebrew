// FUNCTION: GOLD 0x4ad010
// SIZE: 133
// FUNCTION: GOLDTL 0x4ad130
// SIZE: 133

extern int g_67fba8;
extern int g_67fbac;
extern char* g_67fbb0;
extern char* g_67fbb4;

char* __cdecl fcn_004ad130(int id, int* kind)
{
	int i;

	for (i = 0; i < g_67fba8; i++) {
		if (*(int*) (g_67fbb0 + i * 0x2c) == id) {
			if (kind != 0)
				*kind = 0x27;
			return g_67fbb0 + i * 0x2c;
		}
	}
	for (i = 0; i < g_67fbac; i++) {
		if (*(int*) (g_67fbb4 + i * 0x2c) == id) {
			if (kind != 0)
				*kind = 0x26;
			return g_67fbb4 + i * 0x2c;
		}
	}
	return 0;
}
