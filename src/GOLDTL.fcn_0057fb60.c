// FUNCTION: GOLDTL 0x57fb60
// SIZE: 67

int __cdecl fcn_0057fb60(void)
{
	unsigned short* p;
	unsigned short k;
	int v;

	p = *(unsigned short**) 0x7746cc;
	if (p != 0) {
		k = *p;
		v = k;
		if (v >= 0x92 && (v <= 0x97 || v == 0x2db) &&
		    *(int*) (*(int*) 0x665f08 + 0x38) == 0) {
			return k != 0x92;
		}
	}
	return -1;
}
