// FUNCTION: GOLDTL 0x0042b370
// SIZE: 68

extern char g_11cd000[0x47ff][0x50];
extern int g_14b7320[];
int __cdecl fcn_0065f220(const char* a, const char* b);

int __cdecl fcn_0042b370(const char* name)
{
	int i;

	for (i = 0; g_11cd000[i] != 0 && i < 0x47ff; i++) {
		if (fcn_0065f220(g_11cd000[i], name) == 0) {
			return g_14b7320[i];
		}
	}
	return -1;
}
