extern char g_149d120[][0x74];

int __cdecl fcn_0065f220(const char* a, const char* b);

// FUNCTION: GOLD 0x0042e2e0
// FUNCTION: GOLDTL 0x42d630
int __cdecl fcn_0042d630(const char* name)
{
	int i;

	for (i = 0; i < 128; i++) {
		if (fcn_0065f220(g_149d120[i], name) == 0 && g_149d120[i][0] != 0) {
			return i;
		}
	}
	return -1;
}
