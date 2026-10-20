#pragma optimize("s", on)

#include <string.h>

typedef struct Obj61772e {
	char pad0[0x74];
	char f74[0x2c];
	int f0a0;
	char pad0a4[0xc];
	int f0b0;
	char pad0b4[4];
	char* f0b8;
	char pad0bc[8];
	char* f0c4;
} Obj61772e;

void __fastcall fcn_0062b663(void* self, int ignored, int value);

#pragma optimize("y", off)

/* ADDRESS: GOLDTL 0x0061772e */
void __fastcall fcn_0061772e(Obj61772e* self)
{
	char* p;
	int n;
	int m;
	int i;
	int v;

	if (self->f0b0 == 0) {
		return;
	}
	p = self->f0b8;
	n = (int) self->f0c4 - (int) self->f0b8;
	m = ((n + 3) << 14 & 0xffff0000) + 0x10000;
	m &= 0x7fff0000;
	m |= 0xfffe;
	fcn_0062b663(self->f74, 0, m);
	fcn_0062b663(self->f74, 0, 0x54584554);
	self->f0a0 += 8;
	if (n >= 4) {
		i = n >> 2;
		do {
			fcn_0062b663(self->f74, 0, *(int*) p);
			self->f0a0 += 4;
			p += 4;
			n -= 4;
			i--;
		} while (i != 0);
	}
	m = n;
	if (n != 0) {
		v = 0;
		memcpy(&v, p, n);
		fcn_0062b663(self->f74, 0, v);
		self->f0a0 += 4;
	}
	if (m == 4) {
		fcn_0062b663(self->f74, 0, 0);
		self->f0a0 += 4;
	}
}
