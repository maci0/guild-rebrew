extern char g_7766bb;
// FUNCTION: GOLD 0x0053ee00
// SIZE: 53
// FUNCTION: GOLDTL 0x00546b40
// SIZE: 53

typedef struct {
	int a;
	char* b;
	int c;
	int d;
} Rec546b40;
// SIZE 0x10

extern Rec546b40 g_7dc6e0[];

void __cdecl fcn_005467e0(Rec546b40*);

void __cdecl fcn_00546b40(void)
{
	int i;

	for (i = 0; i < 0x40; i++) {
		if (g_7dc6e0[i].b != 0 && (*(int*) (g_7dc6e0[i].b + 4) != g_7dc6e0[i].a || g_7766bb == 0)) {
			fcn_005467e0(&g_7dc6e0[i]);
		}
	}
}
