extern char g_149d120[][0x74];

int __cdecl fcn_0065f220(const char* a, const char* b);

// FUNCTION: GOLDTL 0x42d630
// SIZE: 58
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
