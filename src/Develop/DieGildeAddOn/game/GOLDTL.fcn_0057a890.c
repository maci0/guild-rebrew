int __cdecl gm_RandomMod(int n);
float __cdecl gm_RandomFloat01(void);
int __cdecl fcn_00508220(int type, int* out);
void __cdecl fcn_004c4510(char* off, int v);
void __cdecl fcn_004c4570(int a, int b, int off, int* v);
void __cdecl fcn_004c5360(void);
float __cdecl fcn_004ff210(unsigned short id, int v);

/* ADDRESS: GOLDTL 0x0057a890 */
int __cdecl fcn_0057a890(char* off, float chance, int kind, float* out)
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
	if (!(gm_RandomFloat01() < chance)) {
		return 0;
	}
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
	if (!fcn_00508220(type, tmp)) {
		return type;
	}
	roll = gm_RandomMod(tmp[0]);
	x = roll & 0xffff;
	d = (int) ((float) x * *(float*) &tmp[1]);
	if (x == 0) {
		return type;
	}
	switch (type) {
	case 2:
		flags ^= (x << 4) & 0xf0;
		break;
	case 3:
		flags ^= (x << 8) & 0xf00;
		break;
	case 4:
		flags ^= (x << 12) & 0x3000;
		break;
	case 5:
		flags ^= (x << 14) & 0x1c000;
		break;
	case 6:
		flags ^= (x << 17) & 0xe0000;
		break;
	case 7:
		flags ^= (x << 20) & 0x700000;
		break;
	case 8:
		flags ^= (x << 23) & 0x1800000;
		break;
	case 9:
		flags ^= (x << 25) & 0x1e000000;
		break;
	}
	fcn_004c4510(off, *(int*) (off + 4));
	fcn_004c4570(4, 1, 0x2c, &flags);
	fcn_004c5360();
	f = fcn_004ff210(*(unsigned short*) off, -d);
	if (out != 0) {
		*out = f;
	}
	return type;
}
