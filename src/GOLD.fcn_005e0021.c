/* ADDRESS: GOLD 0x005e0021 */
// fcn_005e0021 — swap n bytes between a and b.

void __cdecl fcn_005e0021(char* a, char* b, int n)
{
	int i;
	char* p;
	char* q;
	p = a;
	q = b;
	for (i = 0; i < n; i++) {
		char t;
		t = *q;
		*q = *p;
		*p = t;
		p++;
		q++;
	}
}
