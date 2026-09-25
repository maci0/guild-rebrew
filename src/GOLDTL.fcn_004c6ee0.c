// FUNCTION: GOLD 0x004c6350
// SIZE: 138
// FUNCTION: GOLDTL 0x4c6ee0
// SIZE: 138

int __cdecl fcn_004c4dc0(char*, int);
int __cdecl fcn_005015e0(char**, char**, char**, int);
int __cdecl fcn_0050b7c0(int, char);

int __cdecl fcn_004c6ee0(char* x)
{
	char* e1;
	char* e2;
	char* e3;
	int* p;

	if (*(int*) (x + 0x14) != -1) {
		*(int*) (x + 0x14) = fcn_004c4dc0(x, *(int*) (x + 0x14));
		if (fcn_005015e0(&e1, &e2, &e3, *(int*) (x + 0x14)) == 0)
			return 1;
		if (e1 != 0)
			p = (int*) (e1 + 0x5d);
		else if (e2 != 0)
			p = (int*) (e2 + 0x14);
		else
			p = (int*) (e3 + 0x178);
		if (fcn_0050b7c0(*p, x[0x1c]) - *(int*) (x + 0x1d) < 0)
			return 1;
	}
	return 0;
}
