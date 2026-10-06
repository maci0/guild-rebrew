// FUNCTION: GOLD 0x0050e5a0
// FUNCTION: GOLDTL 0x511b70

unsigned short __cdecl fcn_0042e410(int);
void __cdecl fcn_004e8af0(char, char*);
int __cdecl fcn_004e99c0(int);

void __cdecl fcn_00511b70(int n, int* dst, int* src)
{
	char buf[0x18];
	int t[15];
	int j;
	int i;

	t[0] = 0x18;
	t[1] = 0x27;
	t[2] = 0x33;
	t[3] = 0x3f;
	t[4] = 0x45;
	t[5] = 0x12;
	t[6] = 0x39;
	t[7] = 6;
	t[8] = 0xc;
	t[9] = 0x1e;
	t[10] = 0x4b;
	t[11] = 0x5e;
	t[12] = 0x58;
	t[13] = 0x51;
	t[14] = 0x2d;
	j = fcn_0042e410(15);
	for (i = 0; i < n; i++) {
		fcn_004e8af0((char) src[i], buf);
		dst[i] = t[j] - fcn_004e99c0((unsigned char) buf[8]) / 2;
		j = (j + 1) % 15;
	}
}
