char* __cdecl fcn_004ec7d0(char*);
float __cdecl fcn_004ec8a0(char*, int);
char* __cdecl fcn_004ecbe0(int);

/* ADDRESS: GOLDTL 0x004ee160 */
int __cdecl fcn_004ee160(char* a0)
{
	char* p;
	char* e;
	char* q;
	char* p2;
	float total;
	float sum;
	float r;
	int n;

	sum = 0;
	p = fcn_004ec7d0(a0);
	if (p == 0) {
		return -1;
	}
	e = *(char**) (a0 + 0x65);
	r = fcn_004ec8a0(p, 0);
	total = r * r;
	r = fcn_004ec8a0(p, 1);
	total = r * r + total;
	r = fcn_004ec8a0(p, 2);
	total = r * r + total;
	r = fcn_004ec8a0(p, 3);
	total = r * r + total;
	for (n = 6, p2 = e + 0x10; n != 0; n--, p2 += 8) {
		q = fcn_004ecbe0(*(int*) (p2 - 4));
		if (q != 0) {
			sum += *(float*) (q + 4) + *(float*) p2;
		}
	}
	return (int) (sum * *(float*) 0x664330 + total * *(float*) 0x664330) << 5;
}
