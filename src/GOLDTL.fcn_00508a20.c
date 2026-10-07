// FUNCTION: GOLD 0x005059d0
// FUNCTION: GOLDTL 0x00508a20

unsigned short __cdecl fcn_0042e410(int n);
void __cdecl fcn_004c4510(char* p, int n);
void __cdecl fcn_004c4570(int a, int b, int off, unsigned int* v);
void __cdecl fcn_004c5360(void);

int __cdecl fcn_00508a20(char* o)
{
	int has[4];
	unsigned int flags;
	unsigned int f;
	int result;
	int i;
	int k;
	int idx;

	result = 0;
	has[0] = 0;
	has[1] = 0;
	has[2] = 0;
	has[3] = 0;
	if ((*(unsigned int*) (o + 0x2c) & 0xf0) > 0) {
		has[0] = 1;
	}
	if ((*(unsigned int*) (o + 0x2c) & 0xf00) > 0) {
		has[1] = 1;
	}
	if ((*(unsigned int*) (o + 0x2c) & 0x3000) > 0) {
		has[2] = 1;
	}
	if ((*(unsigned int*) (o + 0x2c) & 0x1c000) > 0) {
		has[3] = 1;
	}
	i = fcn_0042e410(4);
	idx = -1;
	for (k = 4; k != 0;) {
		if (has[i] == 1) {
			idx = i;
			break;
		}
		k--;
		i = (i + 1) % 4;
	}
	if (idx == -1) {
		return 0;
	}
	f = *(unsigned int*) (o + 0x2c);
	if (idx == 0) {
		f &= ~0xf0;
		result = 2;
	} else if (idx == 1) {
		f &= ~0xf00;
		result = 3;
	} else if (idx == 2) {
		f &= ~0x3000;
		result = 4;
	} else if (idx == 3) {
		f &= ~0x1c000;
		result = 5;
	}
	flags = f;
	fcn_004c4510(o, *(int*) (o + 4));
	fcn_004c4570(4, 1, 0x2c, &flags);
	fcn_004c5360();
	return result;
}
