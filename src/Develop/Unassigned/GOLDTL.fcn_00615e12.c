
#pragma optimize("s", on)

#include <string.h>

typedef struct SELF_615e12 SELF_615e12;
struct SELF_615e12 {
	void* vtbl;
	int ref;
	int f08;
	char pad_00c[0x14];
	int f20;
	int f24;
	int f28;
	int f2c;
	int f30;
	int f34;
	int f38;
	int f3c;
	int f40;
	int f44;
	char pad_048[8];
	char f50[0x410];
	int f460;
	int f464;
	int f468;
	int f46c;
	int f470;
	char pad_474[0x18];
	int f48c;
	int f490;
};

/* ADDRESS: GOLDTL 0x00615e12 */
SELF_615e12* __fastcall fcn_00615e12(SELF_615e12* self)
{
	int* p;
	int i;

	self->vtbl = (void*) 0x667094;
	self->ref = 1;
	self->f08 = 0;
	self->f20 = 0;
	self->f24 = 0;
	self->f28 = 0;
	self->f2c = 0;
	self->f34 = 0;
	self->f30 = 0;
	p = &self->f40;
	for (i = 2; i != 0; i--) {
		p[-2] = 0;
		p[0] = 0;
		p++;
	}
	memset(self->f50, 0, sizeof self->f50);
	self->f460 = 0;
	self->f470 = 0;
	self->f48c = 0;
	self->f490 = 0;
	self->f468 = 0;
	return self;
}
