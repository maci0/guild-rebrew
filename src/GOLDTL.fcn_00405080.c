// FUNCTION: GOLDTL 0x405080
// SIZE: 64

// SIZE 0x194
typedef struct {
	int used;
	char pad[0x190];
} T405080;

extern T405080* g_6b5c20;

T405080* __cdecl fcn_00405080(void)
{
	int i;

	for (i = 0; i < 2000;) {
		if (g_6b5c20[i++].used == 0) {
			break;
		}
	}
	if (i >= 2000) {
		return 0;
	}
	return &g_6b5c20[i - 1];
}
