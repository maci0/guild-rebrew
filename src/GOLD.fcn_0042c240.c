// FUNCTION: GOLD 0x0042c240
// fcn_0042c240 — i=fcn_0042c1e0(a); if(i<0) return -1; base=a[0x14]; end=a[0x18];
//   if(base>=end||end<=0) return -1; p=[0x633370+i*4]; n=0; while(n<end && *p) { n++; p++; } return n.

int __cdecl fcn_0042c1e0(void*);

int __cdecl fcn_0042c240(char* a)
{
	int i;
	int base;
	int end;
	int n;
	char* p;
	i = fcn_0042c1e0(a);
	if (i < 0) {
		return -1;
	}
	base = *(int*) (a + 0x14);
	end = *(int*) (a + 0x18);
	if (base >= end || end <= 0) {
		return -1;
	}
	p = *(char**) (0x633370 + i * 4);
	n = 0;
	while (n < end && *(int*) p != 0) {
		n++;
		p += 4;
	}
	return n;
}
