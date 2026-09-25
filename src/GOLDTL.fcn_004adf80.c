typedef struct {
	int key;
	char pad4[0x28];
} fcn_004adf80_entry;
// SIZE 0x2c

extern int g_67fbac;
extern fcn_004adf80_entry* g_67fbb4;
extern int g_7728cc;
extern int g_7728c8;

// FUNCTION: GOLDTL 0x4adf80
// SIZE: 86

void __cdecl fcn_004adf80(void)
{
	int i;

	for (i = 0; i < g_67fbac; i++) {
		if (g_67fbb4[i].key == g_7728cc) {
			g_7728c8 = g_7728cc;
			if (i < g_67fbac - 1)
				g_7728cc = g_67fbb4[i + 1].key;
			else
				g_7728cc = -1;
			return;
		}
	}
}
