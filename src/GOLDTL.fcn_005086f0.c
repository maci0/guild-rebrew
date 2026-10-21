extern double g_662908;

unsigned short __cdecl gm_RandomMod(int);
int __cdecl fcn_00508220(int, int*);
void __cdecl fcn_004c4510(unsigned short*, int);
void __cdecl fcn_004c4570(int, int, int, void*);
float __cdecl fcn_004c5360(void);
void __cdecl fcn_004ff210(unsigned short, int);
int __cdecl _ftol(void);

/* ADDRESS: GOLDTL 0x005086f0 */
/* Picks the first free animation slot from a random start, updates the four
 * packed flags fields for the chosen slot and hands the record to the pool. */
unsigned int __cdecl fcn_005086f0(unsigned short* a0)
{
	unsigned int slots[8];
	int flags;
	int id;
	int i;
	int n;
	int value;

	slots[4] = 0;
	slots[5] = 0;
	slots[6] = 0;
	slots[7] = 0;
	slots[0] = 5;
	slots[1] = 6;
	slots[2] = 7;
	slots[3] = 8;
	flags = *(int*) ((char*) a0 + 0x2c);
	if ((flags & 0x1c000) == 0) {
		slots[4] = 1;
	}
	if ((flags & 0xe0000) == 0) {
		slots[5] = 1;
	}
	if ((flags & 0x700000) == 0) {
		slots[6] = 1;
	}
	if ((flags & 0x1800000) == 0) {
		slots[7] = 1;
	}
	i = gm_RandomMod(4) & 0xffff;
	n = 4;
	while (slots[i + 4] != 1) {
		n--;
		i = (i + 1) & 0x80000003;
		if (i < 0) {
			i = (i - 1 | 0xfffffffc) + 1;
		}
		if (n == 0) {
			return 0;
		}
	}
	if (i == -1) {
		return 0;
	}
	id = slots[i];
	if (fcn_00508220(id, (int*) &slots[4]) == 0) {
		return 0;
	}
	slots[1] = 0;
	slots[0] = slots[6];
	value = gm_RandomMod((int) ((double) slots[0] * g_662908)) & 0xffff;
	if (value == 0) {
		return 0;
	}
	n = (int) ((float) value * *(float*) &slots[5]);
	flags = *(int*) ((char*) a0 + 0x2c);
	if (id == 5 || id == 8) {
		value = (value << 0x17 ^ flags) & 0x1800000;
	} else if (id == 6) {
		value = (value << 0x11 ^ flags) & 0xe0000;
	} else if (id == 7) {
		value = (value << 0x14 ^ flags) & 0x700000;
	}
	flags = flags ^ value;
	slots[5] = flags;
	fcn_004c4510(a0, *(int*) ((char*) a0 + 4));
	fcn_004c4570(4, 1, 0x2c, &slots[5]);
	fcn_004c5360();
	fcn_004ff210(*a0, -n);
	return id;
}
