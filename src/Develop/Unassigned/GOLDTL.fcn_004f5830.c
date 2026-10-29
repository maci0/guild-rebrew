int __cdecl fcn_004c5870(int id, int v);
char* __cdecl fcn_005463a0(int a1, int a2, int a3);
int __cdecl fcn_004c4450(int i);
void __cdecl fcn_00535960(void);

/* ADDRESS: GOLDTL 0x004f5830 */
void __cdecl fcn_004f5830(void)
{
	int p;
	int r;
	int n;

	r = -1;
	n = 0;
	for (p = 0x9a3825; p < 0x9a9225; p += 0x2d) {
		if (*(unsigned int*) p == 1) {
			r = fcn_004c5870(*(int*) (p - 0x25), 0);
			n++;
		} else if (*(unsigned int*) p > 1) {
			if (fcn_005463a0(1, 1, *(int*) p) == 0) {
				r = fcn_004c5870(*(int*) (p - 0x25), 1);
				n++;
			}
		}
		if (n >= 0x20) {
			if (r != -1) {
				while (1) {
					if (fcn_004c4450(r) != 0) {
						break;
					}
					fcn_00535960();
				}
			}
			r = -1;
			n = 0;
		}
	}
}
