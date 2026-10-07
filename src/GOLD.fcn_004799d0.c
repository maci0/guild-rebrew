// FUNCTION: GOLD 0x004799d0

typedef struct Surf004799d0 {
	char pad0[0x10];
	int pitch;
	unsigned char bpp;
	char pad15[0x1c - 0x15];
	char* bits;
	char pad20[0x24 - 0x20];
	int x0;
	int y0;
	int x1;
	int y1;
} Surf004799d0;
// SIZE 0x3c

int __cdecl fcn_0041e670(unsigned char r, unsigned char g, unsigned char b);

int __cdecl fcn_004799d0(int x, int y, unsigned char r, unsigned char g, unsigned char b, Surf004799d0* s)
{
	int c;
	unsigned char n;

	if (s == 0 || x < s->x0 || x >= s->x1 || y < s->y0 || y >= s->y1) {
		return 0;
	}
	n = s->bpp >> 3;
	c = fcn_0041e670(r, g, b);
	switch (s->bpp) {
	case 8:
		s->bits[s->pitch * y + x] = (r + g + b) / 3;
		break;
	case 15:
	case 16:
		((short*) s->bits)[s->pitch * y + x] = c;
		break;
	case 24:
		s->bits[s->pitch * y + x * n] = r;
		s->bits[s->pitch * y + x * n + 1] = g;
		s->bits[s->pitch * y + x * n + 2] = b;
		break;
	case 32:
		((int*) s->bits)[s->pitch * y + x] = c;
		break;
	}
	return 1;
}
