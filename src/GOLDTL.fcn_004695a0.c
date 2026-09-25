typedef struct Group {
	int count;
	int sel;
	int ids[33];
} Group;
// SIZE 0x8c

extern Group g_102cbc4[8];

void __cdecl fcn_00472380(int id, int on);

// FUNCTION: GOLDTL 0x4695a0
// SIZE: 107
void __cdecl fcn_004695a0(int g, int sel)
{
	int i;

	for (i = 0; i < g_102cbc4[g].count; i++) {
		if (i != sel) {
			fcn_00472380(g_102cbc4[g].ids[i], 0);
		} else {
			fcn_00472380(g_102cbc4[g].ids[i], 1);
		}
	}
	g_102cbc4[g].sel = sel;
}
