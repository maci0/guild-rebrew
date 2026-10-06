// FUNCTION: GOLD 0x4c7f70
// FUNCTION: GOLDTL 0x4c8b10

int __cdecl fcn_004c4dc0(char*, int);
int __cdecl fcn_005015e0(char**, char**, char**, int);

int __cdecl fcn_004c8b10(char* x, char* out)
{
	char* e1;
	char* e2;
	char* e3;
	char* p;
	char* q;
	char* d;
	int v;
	unsigned int i;
	unsigned int j;
	int type;
	int n;

	v = fcn_004c4dc0(x, *(int*) (x + 0x10));
	*(int*) (x + 0x10) = v;
	if (fcn_005015e0(&e1, &e2, &e3, v) == 0)
		return 1;
	p = e1 != 0 ? e1 : (e2 != 0 ? e2 : e3);
	q = x + 0x15;
	for (i = 0; i < (unsigned char) x[0x14]; i++) {
		type = *q++;
		n = *q++;
		d = p + *(unsigned short*) q;
		q += 2;
		switch (type) {
		case 1:
			for (j = 0; j < n; j++) {
				*d = *q;
				d++;
				q++;
			}
			break;
		case 2:
			for (j = 0; j < n; j++) {
				*(short*) d = *(short*) q;
				d += 2;
				q += 2;
			}
			break;
		case 4:
			for (j = 0; j < n; j++) {
				*(int*) d = *(int*) q;
				d += 4;
				q += 4;
			}
			break;
		}
	}
	if (out != 0)
		*out = 1;
	return 0;
}
