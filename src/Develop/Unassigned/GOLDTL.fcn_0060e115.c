/* Native ABI is __thiscall: object in ECX, one stack argument popped by the
   callee (ret 4). C89 cannot declare __thiscall, so the object arrives as the
   first __fastcall register argument and the unused second register argument
   keeps the stack argument in its native slot. Word-wide twin of the dword
   slot filler: writes the 16-bit index pair from tables 0x6664a8/0x6664b4 and
   the position sum of the records at self->0x128 (stride 0x14). */
typedef struct E0060e115 {
	unsigned short f0;
	unsigned short f2;
	char pad4[4];
	unsigned short f8;
	unsigned short fA;
	char padc[0x48];
	unsigned short f54;
	unsigned short f56;
} E0060e115;

typedef struct S0060e115 {
	char pad[0x10c];
	int* f10c;
	unsigned short* f110;
	char pad114[0x14];
	char* f128;
} S0060e115;

/* ADDRESS: GOLDTL 0x0060e115 */
int __fastcall fcn_0060e115(S0060e115* self, int unused, E0060e115* e)
{
	char* rec;

	if (e->f8 == 0xffff) {
		rec = self->f128 + e->f54 * 0x14;
		self->f10c[e->f0] = *(int*)(rec + 8) + *(int*)(rec + 4);
		self->f110[e->f0] = *(unsigned short*)(0x6664a8 + e->f2 * 4);
		return 0;
	}
	self->f110[e->f0] = *(unsigned short*)(0x6664a8 + e->f2 * 4);
	self->f110[e->f8] = *(unsigned short*)(0x6664b4 + e->fA * 4);
	rec = self->f128 + e->f54 * 0x14;
	self->f10c[e->f0] = *(int*)(rec + 8) + *(int*)(rec + 4);
	if (e->f54 == e->f56) {
		self->f10c[e->f8] = self->f10c[e->f0] + 1;
	}
	else {
		rec = self->f128 + e->f56 * 0x14;
		self->f10c[e->f8] = *(int*)(rec + 8) + *(int*)(rec + 4);
	}
	return 0;
}
