// FUNCTION: GOLD 0x4b44e0
// SIZE: 112
// FUNCTION: GOLDTL 0x4b4650
// SIZE: 102

typedef struct {
	int f0;
	char pad4[0x18];
	int f1c;
} rec20;
// SIZE 0x20

rec20* __cdecl fcn_004b3bc0(int);

int __cdecl fcn_004b4650(int a1, int kind)
{
	rec20* p;

	p = fcn_004b3bc0(a1);
	if (p == 0)
		return 0;
	switch (kind) {
	case 0xb:
	case 0x13:
	case 0x17:
	case 0x1c:
	case 0x28:
		if (p->f0 == kind)
			p->f1c++;
	case 0xc: case 0xd: case 0xe: case 0xf: case 0x10: case 0x11: case 0x12:
	case 0x14: case 0x15: case 0x16: case 0x18: case 0x19: case 0x1a: case 0x1b:
	case 0x1d: case 0x1e: case 0x1f: case 0x20: case 0x21: case 0x22: case 0x23:
	case 0x24: case 0x25: case 0x26: case 0x27:
		return 1;
	}
	return 0;
}
