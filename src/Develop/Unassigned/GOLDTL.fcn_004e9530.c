


typedef struct
{
	unsigned char id;
	char pad1[3];
	int x4;
	unsigned char type;
	char pad9[3];
	int xc;
	unsigned char x10;
	char pad11[7];
} Rec18;
// SIZE 0x18

int __cdecl fcn_004e8a80(int, Rec18*);

int __cdecl fcn_004e9530(int n)
{
	Rec18 r;

	if (n == 0) {
		return 0;
	}
	if (n >= 0x1b) {
		n = 0x1b;
	}
	while (n > 0) {
		if (fcn_004e8a80(n, &r) != 0 && r.x10 == 3 && r.xc <= 1) {
			break;
		}
		n--;
	}
	return n;
}
