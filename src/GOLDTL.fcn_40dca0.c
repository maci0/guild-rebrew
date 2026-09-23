// FUNCTION: GOLDTL 0x40dca0
// SIZE: 42

// fcn_0040cd70 — count nodes with [n+0x88]==[0x67a370].

int __cdecl fcn_0040cd70(void)
{
	int i;
	int n;
	int find;
	find = *(int*) 0x67a370;
	n = 0;
	for (i = 0x14d0020; i < 0x14d0c20; i += 4) {
		int p;
		p = *(int*) i;
		if (p != 0 && *(int*) (p + 0x88) == find) {
			n++;
		}
	}
	return n;
}
