


extern unsigned char* lpGebaeudePROT;

void* __cdecl fcn_00502cd0(int list, int a, int b, int c, int d);
int __cdecl fcn_00508da0(unsigned char* e);

int __cdecl fcn_0050c710(unsigned char* e, int kind, int flag)
{
	unsigned char* t;
	int sum;
	int i;
	int w;

	sum = 0;
	t = lpGebaeudePROT + e[0] * 0x24d;
	for (i = 0; i < 0x40; i++) {
		w = ((unsigned short*) (t + 0x23))[i] & 0x7fff;
		if (w != 0 && t[0x1a3 + i] == kind && fcn_00502cd0(*(int*) (e + 0x5d), 2, 6, 0, w)) {
			sum += t[0x1e3 + i];
		}
	}
	if (flag) {
		return (int) (sum * (fcn_00508da0(e) * 0.01) + 0.5);
	}
	return sum;
}
