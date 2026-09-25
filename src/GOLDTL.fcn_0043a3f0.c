// FUNCTION: GOLDTL 0x0043a3f0
// SIZE: 329

// SIZE 0x4
typedef struct {
	unsigned char r;
	unsigned char g;
	unsigned char f0 : 1;
	unsigned char f1 : 7;
	unsigned char x;
} V43a3f0;

int __cdecl fcn_0045d320(int h, int flag);
int __cdecl fcn_0045d3b0(int h, V43a3f0 c, int flag);

void __cdecl fcn_0043a3f0(char* a, char* b, V43a3f0 c)
{
	int i;
	int x;
	V43a3f0* v;
	int* h;

	if (a == 0 || b == 0 || *(int*) (*(char**) (b + 0x318) + 0x1e4) < 0) {
		return;
	}
	v = (V43a3f0*) (b + 0x49c);
	if (c.r >= 0xff && !c.f0) {
		a[0x215] &= ~0x20;
		*(int*) v = 0;
		v->f0 = 0;
		v->r = 0xff;
		for (i = 0; i < *(int*) (*(char**) (b + 0x318) + 0x1e4); i++) {
			h = *(int**) (b + 0x31c);
			x = fcn_0045d320(h[i], 1);
			(*(int**) (b + 0x31c))[*(int*) (*(char**) (b + 0x318) + 0x1e4) + i] = x;
			(*(int**) (b + 0x31c))[i] = x;
		}
		return;
	}
	if (v->r == 0xff && !v->f0) {
		a[0x215] |= 0x20;
		for (i = 0; i < *(int*) (*(char**) (b + 0x318) + 0x1e4); i++) {
			x = fcn_0045d3b0((*(int**) (b + 0x31c))[i], c, 1);
			(*(int**) (b + 0x31c))[*(int*) (*(char**) (b + 0x318) + 0x1e4) + i] = x;
			(*(int**) (b + 0x31c))[i] = x;
		}
	}
	*v = c;
}
