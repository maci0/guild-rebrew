// FUNCTION: GOLDTL 0x00546b80
// SIZE: 39

typedef struct {
	int a;
	int b;
	int c;
	int d;
} Rec546b80;
// SIZE 0x10

extern Rec546b80 g_7dc6e0[];

void __cdecl fcn_005467e0(Rec546b80*);

void __cdecl fcn_00546b80(int k)
{
	int i;

	for (i = 0; i < 0x40; i++) {
		if (g_7dc6e0[i].c == k) {
			fcn_005467e0(&g_7dc6e0[i]);
		}
	}
}
