extern void* g_6b5c5c;

int __cdecl fcn_00408270(float*, float*, int*, int*);
int __cdecl fcn_004082d0(int, int, int, int, int, int);

/* ADDRESS: GOLDTL 0x00408320 */
int __cdecl fcn_00408320(int a0, char* a1, int* a2)
{
	int* p;
	int* q;
	char* b;
	unsigned char* s;
	int n;
	int end;
	int x;
	int y;
	int k1;

	b = *(char**) (a1 + 0x128);
	p = a2;
	if (*(int**) (a1 + 0x124) != 0) {
		fcn_00408270((float*) g_6b5c5c,
			(float*) ((char*) (**(int**) (a1 + 0x124)) + 0x4c), p, p + 1);
		p[2] = 8;
		p += 3;
	}
	fcn_00408270((float*) g_6b5c5c, (float*) (*(char**) (a1 + 0x34) + 0x4c), &x, &y);
	p[0] = x;
	p[1] = y;
	p[2] = 1;
	p += 3;
	if (b != 0 && b[9] == '-' && *(int*) (b + 0xf4) != 0
		&& *(int*) (b + 0x154) == -1) {
		n = *(int*) (b + 0xf8);
		end = (*(int**) (a1 + 0x124) != 0) + 1 + n;
		while (n < end && n < *(int*) (b + 0xf0)) {
			s = (unsigned char*) (*(int*) (b + 0xf4) + n * 2);
			fcn_004082d0(a0, s[0], s[1], (int) g_6b5c5c, (int) p, (int) (p + 1));
			p[2] = 2;
			p += 3;
			n++;
		}
	}
	p[2] = 0;
	if (a2[2] != 0) {
		q = a2 + 1;
		for (;;) {
			k1 = q[1];
			if (k1 & 4) {
				break;
			}
			if (q[4] == 0) {
				break;
			}
			if (q[4] & 4) {
				break;
			}
			if (q[2] > q[-1] && q[3] < q[0]) {
				p[0] = q[-1] + 1;
				p[1] = q[0];
				p[2] = q[1] | 4;
				p += 3;
				p[0] = q[-1];
				p[1] = q[0] - 1;
				p[2] = q[1] | 4;
				p += 3;
			} else if (q[2] > q[-1] && q[3] > q[0]) {
				p[0] = q[-1] + 1;
				p[1] = q[0];
				p[2] = q[1] | 4;
				p += 3;
				p[0] = q[-1];
				p[1] = q[0] + 1;
				p[2] = q[1] | 4;
				p += 3;
			} else if (q[2] < q[-1] && q[3] > q[0]) {
				p[0] = q[-1] - 1;
				p[1] = q[0];
				p[2] = q[1] | 4;
				p += 3;
				p[0] = q[-1];
				p[1] = q[0] + 1;
				p[2] = q[1] | 4;
				p += 3;
			} else if (q[2] < q[-1] && q[3] < q[0]) {
				p[0] = q[-1] - 1;
				p[1] = q[0];
				p[2] = q[1] | 4;
				p += 3;
				p[0] = q[-1];
				p[1] = q[0] - 1;
				p[2] = q[1] | 4;
				p += 3;
			}
			q += 3;
		}
	}
	p[2] = 0;
	return 1;
}
