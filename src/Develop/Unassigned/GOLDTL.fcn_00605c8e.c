typedef struct {
	int idx;
	int val;
} SLOT;

typedef struct {
	char pad0[0xfc];
	SLOT* slots;
	char* flags;
	unsigned end;
	unsigned start;
} LIST;

/* Native ABI is thiscall: self in ecx, one stack argument, ret 4. MSVC 6
 * rejects __thiscall in C mode, so the second declared parameter absorbs
 * edx and the real argument arrives on the stack. */
/* ADDRESS: GOLDTL 0x00605c8e */
int __fastcall fcn_00605c8e(LIST* self, int unused, int* table)
{
	unsigned i;
	SLOT* s;

	i = self->start + 1;
	if (self->end <= i)
		return 0;
	do {
		s = &self->slots[i];
		if (self->flags[i] == 0)
			s->idx = table[s->idx];
		i++;
	} while (i < self->end);
	return 0;
}
