extern unsigned char g_slot_table[2];
extern void* gm_CityEntity;

int __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_CheckEntityAgeLimit(unsigned int);
int __cdecl gm_IsNpcEntityState(void*);
float __cdecl gm_CalcEntityFavor(unsigned int a0, unsigned int a1, unsigned int a2);

/* ADDRESS: GOLDTL 0x005cf720 */
int __cdecl gm_MatchesTargetFilter(unsigned int self, unsigned int candidate, unsigned char* p)
{
	unsigned int off;
	unsigned int idx;
	unsigned int flags;
	int i;
	short* q;
	float f;
	int b4;
	int b5;
	int b6;
	int b7;

	if ((unsigned short) self == (unsigned short) candidate)
		return 0;
	idx = candidate & 0xffff;
	off = idx * 0x21c;
	if (*(short*) (g_slot_table + off) == -1)
		return 0;
	if (g_slot_table[off + 0x1b1] > 0)
		return 0;
	if ((g_slot_table + off) == (unsigned char*) gm_CityEntity)
		return 0;
	if (!p)
		goto ret1;
	flags = *(unsigned int*) (p + 4);
	if (!flags)
		goto ret1;
	if (g_slot_table[off + 2] >= 10)
		return 0;
	if (p[0x14] & 2) {
		i = 0;
		q = (short*) (p + 0x1c);
		do {
			if ((unsigned short) candidate == (unsigned short) *q && *q != -1)
				return 0;
			i++;
			q++;
		} while (i < 4);
	}
	if (flags & 0x3ffff) {
		if ((flags & 1) && g_slot_table[off + 9] == 1)
			return 0;
		if ((flags & 2) && !g_slot_table[off + 9])
			return 0;
		if ((flags & 0x1000) && *(int*) (g_slot_table + off + 0x5c) != -1) {
			i = gm_LookupEntityRecordById(*(int*) (g_slot_table + off + 0x5c));
			if (i && *(unsigned char*) (i + 8) > 0)
				return 0;
		}
		flags = *(unsigned int*) (p + 4);
		if ((flags & 4) && *(short*) (g_slot_table + off + 0x50) != *(short*) (g_slot_table + (self & 0xffff) * 0x21c + 0x50) &&
		    *(int*) (g_slot_table + off + 0x5c) != *(int*) (g_slot_table + (self & 0xffff) * 0x21c + 4))
			return 0;
		if (flags & 8) {
			if (*(short*) (g_slot_table + off + 0x50) == *(short*) (g_slot_table + (self & 0xffff) * 0x21c + 0x50))
				return 0;
			if (*(int*) (g_slot_table + off + 0x5c) == *(int*) (g_slot_table + (self & 0xffff) * 0x21c + 4))
				return 0;
		}
		if ((flags & 0x40) && g_slot_table[off + 2] != 1)
			return 0;
		if (flags & 0x10) {
			if (!g_slot_table[off + 0x165])
				return 0;
			if (g_slot_table[off + 2])
				return 0;
		}
		if ((flags & 0x100) && g_slot_table[off + 2] != 6 && g_slot_table[off + 2] != 7 && (g_slot_table[off + 2] != 5 && !g_slot_table[off + 0x166]) && !g_slot_table[off + 0x169])
			return 0;
		if ((flags & 0x200) && !gm_CheckEntityAgeLimit(candidate))
			return 0;
		if ((*(unsigned int*) (p + 4) & 0x400) && gm_CheckEntityAgeLimit(candidate))
			return 0;
		flags = *(unsigned int*) (p + 4);
		if ((flags & 0x2000) && *(int*) (g_slot_table + off + 0x184))
			return 0;
		if (flags & 0x4000) {
			if (g_slot_table[off + 2] == 6)
				return 0;
			if (g_slot_table[off + 2] == 7)
				return 0;
			if (g_slot_table[off + 2] == 5)
				return 0;
		}
		if ((flags & 0x8000) && (g_slot_table[off + 2] != 6 && g_slot_table[off + 2] != 7) && g_slot_table[off + 2] != 5)
			return 0;
		if ((flags & 0x800) && !g_slot_table[off + 0x166] && !g_slot_table[off + 0x169])
			return 0;
		if ((flags & 0x10000) && !*(int*) (g_slot_table + off + 0x170))
			return 0;
		if ((flags & 0x20000) && (*(unsigned int*) (g_slot_table + off + 0x1c8) & 0x800000))
			return 0;
		if ((flags & 0x20) && (*(unsigned int*) (g_slot_table + off + 0x1c8) & 0x40000000))
			return 0;
		if ((flags & 0x80) && !*(int*) (g_slot_table + off + 0x1f0))
			return 0;
		if (!(flags & 0x40000) && (*(unsigned int*) (g_slot_table + off + 0x1cc) & 0x3000))
			return 0;
	}
	if (flags & 0xf00000) {
		b4 = ((flags & 0x100000) && (g_slot_table[off + 2] == 6 || g_slot_table[off + 2] == 7));
		b5 = ((flags & 0x200000) && g_slot_table[off + 2] == 5); b4 |= b5;
		b6 = ((flags & 0x400000) && g_slot_table[off + 2] != 5 && gm_IsNpcEntityState(g_slot_table + off) != 0); b4 |= b6;
		b7 = ((*(unsigned int*) (p + 4) & 0x800000) && !g_slot_table[off + 2]);
		if (!(b4 | b7))
			return 0;
	}
	if (!*(int*) (p + 0x40))
		goto ret1;
	f = gm_CalcEntityFavor((int) (self & 0xffff), (int) (candidate & 0xffff), 1);
	if (f < *(float*) (p + 0x44))
		return 0;
	if (f <= *(float*) (p + 0x48))
		goto ret1;
	return 0;

ret1:
	return 1;
}
