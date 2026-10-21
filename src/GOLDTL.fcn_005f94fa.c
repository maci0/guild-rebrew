/* Cleanup-shaped method: releases the owned interface pointers and clears
   the object's state. Native ABI is fastcall with the object in ECX and no
   stack argument (decoration @fcn_005f94fa@4). */

typedef struct Obj5f94fa {
	char pad0[0x54];
	int flags54;
	char pad58[0x20];
	int field78;
	char pad7c[0x24];
	int fielda0;
	char pada4[0x18];
	int fieldbc;
	char padc0[4];
	int fieldc4;
	int fieldc8;
	int fieldcc;
	int fieldd0;
	int fieldd4;
	char padd8[0x24];
	int fieldfc;
	char pad100[0xc];
	int field10c;
	int field110;
	int field114;
	int field118;
	char pad11c[8];
	int field124;
	int field128;
	int field12c;
	char pad130[8];
	int field138;
	char pad13c[0x68];
	int field1a4;
	char pad1a8[8];
	int field1b0;
	int field1b8;
	int field1bc;
} Obj5f94fa;

extern void __cdecl atoi(void* p);
extern void __fastcall fcn_005f243f(void* p, int ignored, int flag);

/* ADDRESS: GOLDTL 0x005f94fa */
int __fastcall fcn_005f94fa(Obj5f94fa* self)
{
	int* p;

	p = &self->fieldbc;
	atoi((void*) *p);
	*p = 0;
	p = &self->fieldc4;
	atoi((void*) *p);
	*p = 0;
	p = &self->fieldc8;
	if (*p) {
		fcn_005f243f((void*) *p, 0, 3);
	}
	*p = 0;
	p = &self->fieldcc;
	if (*p) {
		fcn_005f243f((void*) *p, 0, 3);
	}
	*p = 0;
	p = &self->fieldd0;
	atoi((void*) *p);
	*p = 0;
	p = &self->fieldfc;
	atoi((void*) *p);
	*p = 0;
	p = &self->field114;
	atoi((void*) *p);
	*p = 0;
	p = &self->field118;
	atoi((void*) *p);
	*p = 0;
	p = &self->field12c;
	atoi((void*) *p);
	*p = 0;
	p = &self->field124;
	atoi((void*) *p);
	*p = 0;
	p = &self->field128;
	atoi((void*) *p);
	*p = 0;
	p = &self->field138;
	atoi((void*) *p);
	*p = 0;
	p = &self->field10c;
	atoi((void*) *p);
	*p = 0;
	p = &self->field110;
	atoi((void*) *p);
	*p = 0;
	p = &self->fieldd4;
	atoi((void*) *p);
	*p = 0;
	p = &self->field1a4;
	atoi((void*) *p);
	*p = 0;
	p = &self->field1b0;
	atoi((void*) *p);
	*p = 0;
	p = &self->field1b8;
	atoi((void*) *p);
	*p = 0;
	p = &self->field1bc;
	atoi((void*) *p);
	*p = 0;
	self->flags54 &= ~0x10;
	self->field78 = 0;
	self->fielda0 = 0;
	return 0;
}
