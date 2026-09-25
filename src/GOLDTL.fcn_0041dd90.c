// FUNCTION: GOLDTL 0x41dd90
// SIZE: 60

// SIZE 0x10
typedef struct {
	int a;
	int b;
	int id;
	int c;
} T41dd90;

extern int g_6b6f64;
extern T41dd90* g_6b6f80;

int __cdecl fcn_0041dd90(int id)
{
	int i;
	T41dd90* t;

	if (id != 0) {
		t = g_6b6f80;
		for (i = 0; i < g_6b6f64; i++) {
			if (t->id == id) {
				break;
			}
			t++;
		}
		return i != g_6b6f64;
	}
	return 1;
}
