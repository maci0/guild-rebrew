unsigned short __cdecl fcn_0042e410(int);

// SIZE 0x24
struct info_577940 {
	char b0;
	char type;
	char pad[10];
	int owner;
	char pad2[8];
	int kind;
	char pad3[8];
};

// FUNCTION: GOLDTL 0x577940
// SIZE: 124

void __cdecl fcn_004f4830(int, struct info_577940*);

int __cdecl fcn_00577940(int x)
{
	struct info_577940 info;
	int y;
	int j;
	int n;
	int s;

	y = x + 3;
	j = 2;
	do {
		j--;
		s = fcn_0042e410(0x1d);
		n = 0x1d;
		do {
			fcn_004f4830(s, &info);
			if (info.kind == 1 && info.type == 2 && info.owner == y) {
				return s;
			}
			n--;
			s = (s + 1) % 0x1d;
		} while (n != 0);
		y++;
	} while (j != 0);
	return -1;
}
