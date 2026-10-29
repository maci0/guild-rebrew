#pragma optimize("s", on)

#include <string.h>

typedef struct Obj617804 {
	char pad0[0x74];
	char f74[0x2c];
	int f0a0;
	char pad0a4[0xc];
	int f0b0;
	char pad0b4[0x11c];
	int f1d0;
	char f1d4[0x100];
	int f2d4;
	char f2d8[0x104];
	int f3dc;
} Obj617804;

void __fastcall fcn_0062b663(void* self, int ignored, int value);

#pragma optimize("y", off)

/* ADDRESS: GOLDTL 0x00617804 */
void __fastcall fcn_00617804(Obj617804* self)
{
	char* p;
	int n;
	int m;
	int v;

	self->f3dc = self->f1d0;
	if (self->f0b0 == 0) {
		self->f2d4 = self->f1d0;
		return;
	}
	if (strcmp(self->f1d4, self->f2d8) != 0) {
		p = self->f1d4;
		n = (int) strlen(p) + 2;
		m = ((n + 3) << 14 & 0xffff0000) + 0x10000;
		m &= 0x7fff0000;
		m |= 0xfffe;
		fcn_0062b663(self->f74, 0, m);
		fcn_0062b663(self->f74, 0, 0x454c4946);
		self->f0a0 += 8;
		if (n >= 4) {
			v = n >> 2;
			do {
				fcn_0062b663(self->f74, 0, *(int*) p);
				self->f0a0 += 4;
				p += 4;
				n -= 4;
				v--;
			} while (v != 0);
		}
		if (n != 0) {
			v = 0;
			memcpy(&v, p, n);
			fcn_0062b663(self->f74, 0, v);
			self->f0a0 += 4;
		}
		strcpy(self->f2d8, self->f1d4);
	}
	if (self->f2d4 != self->f1d0) {
		fcn_0062b663(self->f74, 0, 0x2fffe);
		fcn_0062b663(self->f74, 0, 0x454e494c);
		fcn_0062b663(self->f74, 0, self->f1d0);
		self->f0a0 += 0xc;
		self->f2d4 = self->f1d0;
	}
}
