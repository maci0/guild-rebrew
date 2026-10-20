/* Native ABI is __thiscall: the object arrives in ECX and the format word is a
   stack argument popped by the callee (ret 4). C89 cannot declare __thiscall,
   so the object comes in as the first __fastcall register argument and the
   unused second register argument keeps the format word in its native slot.
   Builds the vertex-descriptor offsets in the object from the format bits:
   base offsets from the low nibble 2/4/6.., then one slot per 0x10/0x20/0x40/
   0x80 bit, then up to eight component offsets whose element sizes come from
   the table at 0x6664e0. Returns the object. */
typedef struct S005f0144 {
	int f0;
	int f4;
	int f8;
	int fc;
	int f10;
	int f14;
	int f18[8];
	int f38;
	int f3c;
} S005f0144;

/* ADDRESS: GOLDTL 0x005f0144 */
S005f0144* __fastcall fcn_005f0144(S005f0144* self, int unused, int fmt)
{
	int mask;
	int c;
	int* p;

	mask = fmt & 0xe;
	c = 0;
	p = self->f18;
	self->f0 = fmt;
	self->f8 = 0;
	self->fc = 0;
	self->f10 = 0;
	self->f14 = 0;
	self->f38 = 0;
	self->f3c = 0;
	p[0] = 0;
	if (mask == 2) {
		c = 0xc;
	}
	else if (mask == 4) {
		c = 0x10;
	}
	else if (mask >= 6) {
		mask >>= 1;
		c = mask - 2;
		self->f38 = c;
		c = c * 4 + 0xc;
	}
	if (fmt & 0x10) {
		self->f8 = c;
		c += 0xc;
	}
	if (fmt & 0x20) {
		self->fc = c;
		c += 4;
	}
	if (fmt & 0x40) {
		self->f10 = c;
		c += 4;
	}
	if (fmt & 0x80) {
		self->f14 = c;
		c += 4;
	}
	if ((fmt >> 8) & 0xf) {
		mask = (fmt >> 8) & 0xf;
		p[0] = c;
		self->f3c = mask;
		if (mask > 8)
			self->f3c = 8;
		fmt >>= 16;
		mask = 0;
		while (mask < self->f3c) {
			p[0] = c;
			c += *(int*)(0x6664e0 + (fmt & 3) * 4);
			fmt >>= 2;
			mask++;
			p++;
		}
	}
	self->f4 = c;
	return self;
}
