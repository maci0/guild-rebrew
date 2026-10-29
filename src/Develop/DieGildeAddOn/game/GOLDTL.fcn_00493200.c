unsigned short __cdecl gm_RandomMod(int n);
char* __cdecl fcn_00508e40(int id);
int __cdecl fcn_004e8b40(int kind, int* out);
int __cdecl fcn_004e8b80(int kind, int max, void* out);
float __cdecl fcn_0050f980(int a, int b, int c);
int __cdecl fcn_004a55c0(char* obj, int flag, float* value, int extra);
void __cdecl fcn_004c4510(char* obj, int id);
void __cdecl fcn_004c4570(int a, int b, int offset, void* value);
void __cdecl fcn_004c5360(void);

/* ADDRESS: GOLDTL 0x00493200 */
int __cdecl fcn_00493200(char* a1, char* a2)
{
	char slots[0x90];
	char* pick;
	int rec[2];
	int count;
	int left;
	int index;
	int roll;
	unsigned char kind;
	unsigned char flag;
	unsigned char value;

	pick = 0;
	roll = gm_RandomMod(3) & 0xffff;
	if (a1 == 0 || a2 == 0) {
		return 0;
	}
	kind = *(unsigned char*) (a1 + 0x130);
	if (kind == 0 || *(int*) (a1 + 0x194) < 2) {
		return 0;
	}
	if (kind == 7) {
		kind = *(unsigned char*) (a1 + 0x166);
		if (kind == 0) {
			goto other;
		}
		if (fcn_004e8b40((int) kind, rec) == 0) {
			return 0;
		}
		count = fcn_004e8b80(rec[1], 6, slots);
		if (count == 0) {
			return 0;
		}
		index = gm_RandomMod(count) & 0xffff;
		for (left = count; left != 0; left--) {
			roll = *(int*) (slots + index * 24);
			if (*(int*) (a1 + 4) != roll) {
				pick = fcn_00508e40(roll);
				if (pick != 0) {
					value = (unsigned char) fcn_0050f980(*(unsigned short*) a1,
														 *(unsigned short*) pick, 1);
					roll = gm_RandomMod(0x1e) & 0xffff;
					if ((float) roll + *(float*) 0x662c98 != *(float*) &value) {
						pick = 0;
					} else {
						goto found;
					}
				}
			}
			index = (index + 1) % count;
		}
	} else if (kind == 0xa) {
		rec[0] = 0xc00;
		roll = gm_RandomMod(0x1e) & 0xffff;
		rec[1] = roll;
		value = 0;
		if (fcn_004a55c0(a1, 1, (float*) &value, 0) == 0) {
			goto other;
		}
		pick = (char*) (0x7f4ca0 + (rec[1] & 0xffff) * 0x21c);
		goto found;
	}

other:
	kind = *(unsigned char*) (a1 + 0x130);
	if (kind != 3 && kind != 4 && roll == 0) {
		return 0;
	}
	flag = 1;
	value = 0xff;
	fcn_004c4510(a2, *(int*) (a2 + 2));
	fcn_004c4570(4, 1, 0x1e, &value);
	fcn_004c4570(1, 1, 0x22, &flag);
	fcn_004c4570(1, 1, 0x1c, &value);
	fcn_004c4570(1, 1, 0x1d, &value);
	fcn_004c5360();
	return 1;

found:
	if (pick == 0) {
		goto other;
	}
	flag = 1;
	fcn_004c4510(a2, *(int*) (a2 + 2));
	pick += 4;
	fcn_004c4570(4, 1, 0x1e, pick);
	fcn_004c4570(1, 1, 0x22, &flag);
	value = (unsigned char) gm_RandomMod(8);
	fcn_004c4570(1, 1, 0x1c, &value);
	value = (unsigned char) gm_RandomMod(8);
	fcn_004c4570(1, 1, 0x1d, &value);
	fcn_004c5360();
	return 1;
}
