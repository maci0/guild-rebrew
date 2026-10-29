


extern unsigned char* lpGebaeudePROT;

int __cdecl fcn_0050c4e0(unsigned char* e);

int __cdecl fcn_0050c550(unsigned char* e, unsigned char* x)
{
	unsigned char* t;
	int n;
	int lvl;

	t = lpGebaeudePROT + e[0] * 0x24d;
	lvl = 0;
	n = fcn_0050c4e0(x);
	if (t[0x247] == 1) {
		lvl = 1;
	} else if (t[0x247] == 2) {
		lvl = 2;
	} else if (t[0x247] == 3) {
		lvl = 7;
	}
	return lvl >= n;
}
