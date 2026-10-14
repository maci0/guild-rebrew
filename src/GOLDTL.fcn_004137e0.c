


// SIZE 0x14
typedef struct {
	int w;
	int pad[3];
	unsigned char* data;
} Map;

int __cdecl fcn_004137e0(Map* m, int* lo, int* hi, int x0, int x1, int y)
{
	int t;
	int i;
	unsigned char* p;

	if (y < 0 || y >= m->w) {
		return 1;
	}
	if (x1 < x0) {
		t = x0;
		x0 = x1;
		x1 = t;
	}
	if (x0 >= m->w || x1 < 0) {
		return 1;
	}
	x0 = x0 < 0 ? 0 : x0;
	if (x1 >= m->w - 1) {
		x1 = m->w - 1;
	}
	p = m->data + m->w * y + x0;
	for (i = x0; i <= x1; i++) {
		*lo = *lo < *p ? *lo : *p;
		*hi = *hi > *p ? *hi : *p;
		p++;
	}
	return 0;
}
