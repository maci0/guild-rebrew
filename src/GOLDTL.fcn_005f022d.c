typedef struct Pos5f022d {
	float x;
	float y;
	float z;
} Pos5f022d;

typedef struct Obj5f022d {
	char pad0[8];
	char* base;
} Obj5f022d;

/* ADDRESS: GOLDTL 0x005f022d */
/* Native ABI is __thiscall (self in ecx, two stack arguments, ret 8).
 * MSVC 6 C rejects __thiscall (C4234), so __fastcall carries self in ecx;
 * its unused edx slot is the dummy parameter. */
void __fastcall fcn_005f022d(Obj5f022d* self, int d1, int a1, Pos5f022d* a2)
{
	if (self->base != 0) {
		*(Pos5f022d*) (self->base + a1) = *a2;
	}
}
