extern void* g_6b5c5c;

int __cdecl ch_WorldToGridCoordinates(float*, float*, int*, int*);
int __cdecl ch_ConvertGridPointToCharacterGrid(int, int, int, int, int, int);

/* ADDRESS: GOLDTL 0x00408320 */
int __cdecl ch_CollectCharacterOccupiedCells(int a0, char* a1, int* a2)
{
	int* p;
	int* q; int* start;
	char* b; char* obj;
	unsigned char* s;
	int n;
	int end;


	int flags;

	b = *(char**) (a1 + 0x128); obj = a1;
	p = start = a2;
	if (*(int**) (obj + 0x124) != 0) {
		ch_WorldToGridCoordinates((float*) g_6b5c5c,
			(float*) ((char*) (**(int**) (obj + 0x124)) + 0x4c), p, p + 1);
		p[2] = 8;
		p += 3;
	}
	ch_WorldToGridCoordinates((float*) g_6b5c5c, (float*) (*(char**) (obj + 0x34) + 0x4c), (int*) &a2, (int*) &a1);
	p[0] = (int) a2;
	p[1] = (int) a1;
	p[2] = 1;
	p += 3;
	if (b != 0 && b[9] == '-' && *(int*) (b + 0xf4) != 0
		&& *(int*) (b + 0x154) == -1) {
		n = *(int*) (b + 0xf8);
		end = n + (*(int**) (obj + 0x124) != 0 ? 2 : 1);
		while (n < end && n < *(int*) (b + 0xf0)) {
			s = (unsigned char*) (*(int*) (b + 0xf4) + n * 2);
			ch_ConvertGridPointToCharacterGrid(a0, s[0], s[1], (int) g_6b5c5c, (int) p, (int) (p + 1));
			p[2] = 2;
			p += 3;
			n++;
		}
	}
	p[2] = 0;
	if (start[2] != 0) {
		q = start + 1;
		do {
			flags = q[1];
			if (flags & 4) {
				break;
			}
			if (q[4] == 0) {
				break;
			}
			if (q[4] & 4) {
				break;
			}
			if (q[2] > q[-1] && q[3] < q[0]) {
				p[2] = q[1] | 4;
				p[0] = q[-1] + 1;
				p[1] = q[0];
				p += 3;
				p[2] = q[1] | 4;
				p[0] = q[-1];
				p[1] = q[0] - 1;
				p += 3;
			} else if (q[2] > q[-1] && q[3] > q[0]) {
				p[2] = q[1] | 4;
				p[0] = q[-1] + 1;
				p[1] = q[0];
				p += 3;
				p[2] = q[1] | 4;
				p[0] = q[-1];
				p[1] = q[0] + 1;
				p += 3;
			} else if (q[2] < q[-1] && q[3] > q[0]) {
				p[2] = q[1] | 4;
				p[0] = q[-1] - 1;
				p[1] = q[0];
				p += 3;
				p[2] = q[1] | 4;
				p[0] = q[-1];
				p[1] = q[0] + 1;
				p += 3;
			} else if (q[2] < q[-1] && q[3] < q[0]) {
				p[2] = q[1] | 4;
				p[0] = q[-1] - 1;
				p[1] = q[0];
				p += 3;
				p[2] = q[1] | 4;
				p[0] = q[-1];
				p[1] = q[0] - 1;
				p += 3;
			}
			q += 3;
		} while (q[1] != 0);
	}
	p[2] = 0;
	return 1;
}
