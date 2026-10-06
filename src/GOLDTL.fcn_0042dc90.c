extern char g_1053000[][0x50];

int __cdecl fcn_0065f220(const char* a, const char* b);

// FUNCTION: GOLD 0x0042e770
// FUNCTION: GOLDTL 0x42dc90
int __cdecl fcn_0042dc90(const char* name)
{
	int i;

	for (i = 0; i < 0x4800; i++) {
		if (fcn_0065f220(name, g_1053000[i]) == 0) {
			return i;
		}
	}
	return -1;
}
