typedef struct {
	int state;
	int flag;
	int c;
	int d;
} fcn_004a86b0_slot;
// SIZE 0x10

typedef struct {
	char pad0[0x18];
	int h;
	char pad[0x34 - 4 - 0x18];
} fcn_004a86b0_entry;

typedef struct {
	fcn_004a86b0_entry e[3];
	char pad9c[0x19];
	unsigned char count;
} fcn_004a86b0_game;

extern fcn_004a86b0_game* g_1007cd4;
extern fcn_004a86b0_slot g_1007ce8[];

int __cdecl fcn_004a7880(int);

// FUNCTION: GOLDTL 0x4a86b0
// SIZE: 76

void __cdecl fcn_004a86b0(void)
{
	int i;

	for (i = 0; i < 3; i++) {
		g_1007cd4->e[i].h = fcn_004a7880(i);
		g_1007ce8[g_1007cd4->e[i].h].flag = 1;
	}
	g_1007cd4->count++;
}
