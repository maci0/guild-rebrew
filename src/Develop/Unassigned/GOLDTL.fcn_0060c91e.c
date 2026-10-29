/* Native ABI is __thiscall: the object arrives in ECX and the one stack
   argument is popped by the callee (ret 4). C89 cannot declare __thiscall, so
   the object is taken as the first __fastcall register argument and the unused
   second register argument keeps the stack argument in its native slot.
   Fills one vertex-buffer record: two index slots from the tables at 0x6664a8
   and 0x6664b4, and the position sum of records at self->0x128 (stride 0x14). */
typedef struct E0060c91e {
	int f0;
	int f4;
	char pad8[8];
	int f10;
	int f14;
	char pad18[0x7c];
	unsigned short f94;
	unsigned short f96;
} E0060c91e;

typedef struct S0060c91e {
	char pad[0x10c];
	int* f10c;
	int* f110;
	char pad114[0x14];
	char* f128;
} S0060c91e;

/* ADDRESS: GOLDTL 0x0060c91e */
int __fastcall fcn_0060c91e(S0060c91e* self, int unused, E0060c91e* e)
{
	char* rec;

	if (e->f10 == -1) {
		rec = self->f128 + (unsigned short)e->f94 * 0x14;
		self->f10c[e->f0] = *(int*)(rec + 8) + *(int*)(rec + 4);
		self->f110[e->f0] = *(int*)(0x6664a8 + e->f4 * 4);
		return 0;
	}
	self->f110[e->f0] = *(int*)(0x6664a8 + e->f4 * 4);
	self->f110[e->f10] = *(int*)(0x6664b4 + e->f14 * 4);
	rec = self->f128 + (unsigned short)e->f94 * 0x14;
	self->f10c[e->f0] = *(int*)(rec + 8) + *(int*)(rec + 4);
	if (e->f94 == e->f96) {
		self->f10c[e->f10] = self->f10c[e->f0] + 1;
	}
	else {
		rec = self->f128 + e->f96 * 0x14;
		self->f10c[e->f10] = *(int*)(rec + 8) + *(int*)(rec + 4);
	}
	return 0;
}
