extern int g_6b7f90;
extern int* g_6b7f50[16];

int __cdecl fcn_0042b120(int *);
int __cdecl fcn_0042ac40(int);

/* ADDRESS: GOLDTL 0x0042aca0 */
int __cdecl fcn_0042aca0(int *o)
{
	int r = 0;
	int idx;
	int i;
	int v;

	if (g_6b7f90 != 0 && (idx = fcn_0042b120(o)) >= 0) {
		for (i = 0; i < o[6]; i++) {
			v = ((int *) g_6b7f50[idx])[i];
			if (v != 0 && fcn_0042ac40(v) != 0) {
				r = -1;
			}
		}
	} else {
		r = -1;
	}
	return r;
}
