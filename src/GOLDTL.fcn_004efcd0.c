// FUNCTION: GOLD 0x004ede70
// SIZE: 91
// FUNCTION: GOLDTL 0x4efcd0
// SIZE: 91

typedef struct
{
	int id;
	char pad[0x158];
	int h[3];
	char tail[8];
} Slot170;
// SIZE 0x170

extern int g_6b8010;
extern Slot170 g_7731b8[8];

void __cdecl fcn_004432d0(int, int);
void __cdecl fcn_00442be0(int);

void __cdecl fcn_004efcd0(void)
{
	int save;
	int i;
	int j;

	save = g_6b8010;
	fcn_004432d0(0, 1);
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 3; j++) {
			if (g_7731b8[i].h[j] != 0) {
				fcn_00442be0(g_7731b8[i].h[j]);
				g_7731b8[i].h[j] = 0;
			}
		}
	}
	fcn_004432d0(save, 1);
}
