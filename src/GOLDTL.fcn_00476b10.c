// FUNCTION: GOLDTL 0x476b10
// SIZE: 349

typedef struct Surf {
	char pad0[0x10];
	int pitch;
	unsigned char bpp;
	char pad15[0x1c - 0x15];
	char* bits;
	char pad20[0x2c - 0x20];
	int x0;
	int y0;
	int x1;
	int y1;
} Surf;
// SIZE 0x3c

short __cdecl fcn_0041bac0(unsigned char r, unsigned char g, unsigned char b);

int __cdecl fcn_00476b10(int x, int y, unsigned char r, unsigned char g, unsigned char b, Surf* s)
{
	short c;
	char* p;

	if (s == 0 || x < s->x0 || x >= s->x1 || y < s->y0 || y >= s->y1) {
		return 0;
	}
	c = fcn_0041bac0(r, g, b);
	switch (s->bpp) {
	case 8:
		s->bits[s->pitch * y + x] = (r + g + b) / 3;
		break;
	case 15:
	case 16:
		((short*) s->bits)[s->pitch * y + x] = c;
		break;
	case 24:
		p = s->bits + (s->pitch * y + x) * 3;
		p[0] = r;
		p[1] = g;
		p[2] = b;
		break;
	case 32:
		p = s->bits + (s->pitch * y + x) * 4;
		p[3] = (char) 0xff;
		p[2] = r;
		p[1] = g;
		p[0] = b;
		break;
	}
	return 1;
}
