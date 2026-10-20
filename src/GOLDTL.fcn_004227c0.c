extern int g_6b7d7c;
extern char* g_6b7d78;

char* __cdecl fcn_00422760(int key, int* idx);
int __cdecl fcn_0042aaa0(int a1);

/* ADDRESS: GOLDTL 0x004227c0 */
char* __cdecl fcn_004227c0(void)
{
	char* o;
	char* found;
	char* e;
	char* p;
	int i;
	int n;
	int idx;

	o = g_6b7d78;
	found = 0;
	if (g_6b7d7c == 0) {
		return (char*) 0x14cbc20;
	}
	while (o != 0) {
		i = 0;
		if (found == 0 && *(int*) (o + 0x134) > 0) {
			e = (char*) (*(int*) (o + 0x138) + 0x38);
			do {
				if (*(int*) e != 0) {
					found = (char*) (*(int*) (o + 0x138) + i * 0x40);
					break;
				}
				i++;
				e += 0x40;
			} while (i < *(int*) (o + 0x134));
		}
		n = *(int*) (o + 0x134);
		if (i < n) {
			e = (char*) (*(int*) (o + 0x138) + i * 0x40);
			n -= i;
			do {
				if (*(int*) (e + 0x3c) < *(int*) (found + 0x3c) && *(int*) (e + 0x38) != 0) {
					found = e;
				}
				e += 0x40;
				n--;
			} while (n != 0);
		}
		o = *(char**) (o + 0x13c);
	}
	if (found != 0) {
		idx = 0;
		p = fcn_00422760((int) found, &idx);
		if (p != 0) {
			while (fcn_0042aaa0(*(int*) p) != 4 && !(*(int*) (p + 0x14) | 0x10)) {
				idx++;
				*(int*) (p + 4) = 0;
				p = fcn_00422760((int) found, &idx);
				if (p == 0) {
					return found;
				}
			}
			found = 0;
		}
	}
	return found;
}
