typedef struct {
	int key;
	int a;
	int b;
	int c;
} fcn_00493f50_entry;
// SIZE 0x10

extern fcn_00493f50_entry g_664260[7];

// FUNCTION: GOLD 0x004948b0
// SIZE: 39
// FUNCTION: GOLDTL 0x493f50
// SIZE: 39

fcn_00493f50_entry* __cdecl fcn_00493f50(int key)
{
	int i;

	for (i = 0; i < 7; i++) {
		if (g_664260[i].key == key)
			return &g_664260[i];
	}
	return 0;
}
