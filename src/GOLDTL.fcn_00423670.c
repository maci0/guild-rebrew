extern int g_6b7d7c;
extern int g_6b7fac;

int __cdecl fcn_004228c0(int* a0);
int __cdecl fcn_00422ad0(int a0, int* a1);
int __cdecl fcn_0064d3f8(void);
int __cdecl fcn_0042a5d0(int a0, int a1, int a2, int a3);
void __cdecl fcn_0042a920(int a0, int a1);
void __cdecl fcn_0042a9a0(int a0, int a1);
void __cdecl fcn_0042aa20(int a0, int a1);
void __cdecl fcn_0042a7f0(int a0);

/* ADDRESS: GOLDTL 0x00423670 */
int __cdecl fcn_00423670(int* a0, int a1, int a2)
{
	int result;
	char* ent;
	int* p2;
	char* entry;
	unsigned char type;
	int v;
	int index;
	int stamp;

	result = 0;
	if (g_6b7d7c == 0) {
		return 0;
	}
	ent = (char*) a0[1];
	if (*(int*) (ent + 0x38) == 0) {
		v = fcn_004228c0((int*) ent);
		if (v == 0) {
			result = -1;
			goto done;
		}
		result = fcn_00422ad0(v, (int*) ent);
		if (result != 0) {
			goto done;
		}
	}
	ent = (char*) a0[1];
	type = *(unsigned char*) (ent + 0x36);
	if (type == 1) {
		entry = (char*) *(int*) (ent + 0x38);
	} else if (type == 2) {
		p2 = (int*) *(int*) (ent + 0x38);
		if ((*(unsigned char*) ((char*) a0 + 0x14) & 4) != 0) {
			index = a0[8];
		} else {
			index = fcn_0064d3f8() % p2[0];
		}
		entry = (char*) p2[1] + index * 0xc;
	} else {
		result = -1;
		goto done;
	}
	type = *(unsigned char*) entry;
	if (type == 1) {
		v = 0x678fb8;
	} else if (type == 2) {
		v = 0x678fb0;
	} else {
		result = -1;
		goto done;
	}
	if (fcn_0042a5d0(*a0, v, *(int*) (entry + 8), *(int*) (entry + 4)) == -1) {
		result = -1;
		goto done;
	}
	if (a1 != 0) {
		a0[4] = ((*(volatile int*) &g_6b7fac) * 2 + (*(volatile int*) &g_6b7fac)) * 4
			+ (*(volatile int*) &g_6b7fac);
		a0[5] |= 1;
		fcn_0042a920(*a0, 0);
	} else {
		fcn_0042a920(*a0, a0[9]);
	}
	fcn_0042a9a0(*a0, a0[10]);
	if ((*(unsigned char*) ((char*) a0 + 0x14) & 4) == 0 && a2 != 0) {
		fcn_0042aa20(*a0, 1);
		a0[7] = 0;
		a0[6] = a2;
	} else {
		fcn_0042aa20(*a0, a0[3]);
		a0[6] = 0;
	}
	stamp = ((*(volatile int*) &g_6b7fac) * 2 + (*(volatile int*) &g_6b7fac)) * 4
		+ (*(volatile int*) &g_6b7fac);
	((int*) a0[1])[0xf] = a0[2] = stamp;
	a0[5] &= ~8;
	fcn_0042a7f0(*a0);
done:
	return result;
}
