// FUNCTION: GOLD 0x004eae60
// SIZE: 52
// FUNCTION: GOLDTL 0x4ecbe0
// SIZE: 52

typedef struct
{
	int key;
	int a;
	int b;
} Rec0c;
// SIZE 0xc

extern int g_772fe0;
extern Rec0c* g_772fe4;

Rec0c* __cdecl fcn_004ecbe0(int key)
{
	int i;

	for (i = 0; i < g_772fe0; i++) {
		if (g_772fe4[i].key == key) {
			return &g_772fe4[i];
		}
	}
	return 0;
}
