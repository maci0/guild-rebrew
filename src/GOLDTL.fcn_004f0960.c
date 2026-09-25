// FUNCTION: GOLDTL 0x4f0960
// SIZE: 88

typedef struct
{
	int id;
	char pad[0x158];
	int h[3];
	char tail[8];
} Slot170;
// SIZE 0x170

extern Slot170 g_7731b8[8];

int __cdecl fcn_004f0960(int id)
{
	int free;
	int i;
	int v;

	free = -1;
	if (id != -1) {
		for (i = 0; i < 8; i++) {
			v = g_7731b8[i].id;
			if (v == -1) {
				if (free == -1) {
					free = i;
				}
			} else if (v == id) {
				return 1;
			}
		}
		if (free >= -1) {
			g_7731b8[free].id = id;
			return 1;
		}
	}
	return 0;
}
