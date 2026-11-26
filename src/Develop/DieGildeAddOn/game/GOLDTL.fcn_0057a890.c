unsigned short __cdecl gm_RandomMod(int n);
float __cdecl gm_RandomFloat01(void);
int __cdecl gm_GetKindRecord(int type, int* out);
void __cdecl cm_BeginPacketFieldDelta(char* off, int v);
void __cdecl cm_AppendPacketFieldDelta(int a, int b, int off, int* v);
void __cdecl cm_RequestChangeAttribute(void);
float __cdecl fcn_004ff210(unsigned short id, int v);

/* ADDRESS: GOLDTL 0x0057a890 */
int __cdecl he_InflictAffliction(char* off, float chance, int kind, float* out)
{
	int type;
	int other;
	int flags;
	int tmp[3];
	int roll;
	int x;
	int d;
	float f;

	type = 0;
	other = 0;
	if (!(gm_RandomFloat01() >= chance)) {
		flags = *(int*) (off + 0x2c);
		if (kind == 2) {
			if ((flags & 0xf0) == 0) {
				type = 2;
			}
			if ((flags & 0xf00) == 0) {
				other = 3;
			}
		} else if (kind == 1) {
			if ((flags & 0x3000) == 0) {
				type = 4;
			}
			if ((flags & 0x1c000) == 0) {
				other = 5;
			}
		} else {
			if ((flags & 0xe0000) == 0) {
				type = 6;
			}
			other = gm_RandomMod(2) ? 7 : 8;
			if ((flags & 0x1800000) != 0 && other == 8) {
				other = 0;
			}
			if ((flags & 0x700000) != 0 && other == 7) {
				other = 0;
			}
		}
		if (type != 0) {
			if (other != 0 && gm_RandomMod(2) == 0) {
				type = other;
			}
		} else {
			if (other == 0) {
				return 0;
			}
			type = other;
		}
		if (!gm_GetKindRecord(type, tmp)) {
			return type;
		}
		roll = gm_RandomMod(tmp[0]);
		x = roll & 0xffff;
		d = (int) ((float) x * *(float*) &tmp[1]);
		if (x == 0) {
			return type;
		}
		if (type == 2) {
			flags ^= ((x << 4) ^ flags) & 0xf0;
		} else if (type == 3) {
			flags ^= ((x << 8) ^ flags) & 0xf00;
		} else if (type == 4) {
			flags ^= ((x << 12) ^ flags) & 0x3000;
		} else if (type == 5) {
			flags ^= ((x << 14) ^ flags) & 0x1c000;
		} else if (type == 6) {
			flags ^= ((x << 17) ^ flags) & 0xe0000;
		} else if (type == 7) {
			flags ^= ((x << 20) ^ flags) & 0x700000;
		} else if (type == 8) {
			flags ^= ((x << 23) ^ flags) & 0x1800000;
		} else if (type == 9) {
			flags ^= ((x << 25) ^ flags) & 0x1e000000;
		}
		cm_BeginPacketFieldDelta(off, *(int*) (off + 4));
		cm_AppendPacketFieldDelta(4, 1, 0x2c, &flags);
		cm_RequestChangeAttribute();
		f = fcn_004ff210(*(unsigned short*) off, -d);
		if (out != 0) {
			*out = f;
		}
		return type;
	}
	return 0;
}
