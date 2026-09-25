typedef struct fcn_004c09b0_node fcn_004c09b0_node;
struct fcn_004c09b0_node {
	int* f0;
	int f4;
	int f8;
	fcn_004c09b0_node* next;
};
// SIZE 0x10

extern int g_772d2c;
extern fcn_004c09b0_node* g_772d34;

void __cdecl fcn_004c2d90(float, int);
void __cdecl fcn_00426170(int*, int);
void __cdecl fcn_0041ddd0(void*);

// FUNCTION: GOLD 0x004c01b0
// SIZE: 88
// FUNCTION: GOLDTL 0x4c09b0
// SIZE: 88

void __cdecl fcn_004c09b0(void)
{
	fcn_004c09b0_node* next;

	if (g_772d2c != 0) {
		g_772d2c = 0;
		fcn_004c2d90(1.0f, 2000);
	}
	while (g_772d34 != 0) {
		next = g_772d34->next;
		fcn_00426170(g_772d34->f0, 0);
		fcn_0041ddd0(g_772d34);
		g_772d34 = next;
	}
}
