// FUNCTION: GOLDTL 0x004efd70
// SIZE: 103

typedef struct
{
	int id;
	int flags;
	char pad[0x168];
} Slot170;
// SIZE 0x170

extern Slot170 g_7731b8[8];

void __cdecl fcn_004efd70(int id)
{
	int i;
	int j;

	if (id == -1) {
		return;
	}
	for (i = 0; i < 8; i++) {
		if (g_7731b8[i].id == id) {
			g_7731b8[i].flags |= 4;
			for (j = 0; j < 3; j++) {
				if (((char*) &g_7731b8[i])[0x74 + j * 0x68] & 2) {
					return;
				}
			}
			g_7731b8[i].id = -1;
			g_7731b8[i].flags = 0;
			return;
		}
	}
}
