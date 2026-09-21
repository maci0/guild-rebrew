// FUNCTION: GOLD 0x00402ac0
// SIZE: 48
// fcn_00402ac0 — find node with [n+0x34]==a in 0x1468ae0 table.

int __cdecl fcn_00402ac0(int a)
{
	int i;
	for (i = 0; i < 0x300; i++) {
		int n;
		n = *(int*) (0x1468ae0 + i * 4);
		if (n != 0 && *(int*) (n + 0x34) == a) {
			return n;
		}
	}
	return 0;
}
