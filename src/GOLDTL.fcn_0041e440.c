// FUNCTION: GOLDTL 0x41e440

int __cdecl fcn_0041e440(int** pp)
{
	int n;
	int* p;
	int i;
	char* q;

	n = 0;
	if (pp != 0) {
		p = *pp;
		if (p != 0) {
			do {
				n += p[0];
				p[0] = 0;
				q = (char*) (p + 4);
				for (i = 0; i < p[1]; i++) {
					*(int*) q = 0;
					q += p[2];
				}
				p = (int*) p[3];
			} while (p != 0);
		}
	}
	return n;
}
