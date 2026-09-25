// GLOBAL: GOLDTL 0x7774a0
extern char g_7774a0[];
// GLOBAL: GOLD 0x6f3880
extern char g_7774a0[];
// FUNCTION: GOLD 0x005baf60
// SIZE: 60
// FUNCTION: GOLDTL 0x5c69d0
// SIZE: 60

// SIZE 0x40
typedef struct {
	int a;
	int b;
	int c;
	int d;
	struct {
		int x;
		int y;
	} s[6];
} Rec;

void __cdecl fcn_005c69d0(void)
{
	int i;
	int j;
	Rec* r;

	for (i = 0; i < 32; i++) {
		r = (Rec*) g_7774a0 + i;
		r->a = 0;
		r->b = -1;
		r->c = -1;
		r->d = -1;
		for (j = 0; j < 6; j++) {
			r->s[j].x = -1;
			r->s[j].y = 0;
		}
	}
}
