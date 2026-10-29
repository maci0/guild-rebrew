extern int g_6b7f90;
extern int *g_6b7f50;

int __cdecl fcn_0042b120(int *);
int __cdecl fcn_0042ac40(int);

/* ADDRESS: GOLDTL 0x0042aca0 */
int __cdecl fcn_0042aca0(int *o)
{
	int i;
	int r;
	int idx;
	int v;

	r = 0;
	if (g_6b7f90 == 0) {
		return -1;
	}
	idx = fcn_0042b120(o);
	if (idx < 0) {
		return -1;
	}
	for (i = 0; i < o[6]; i++) {
		v = ((int *) g_6b7f50[idx])[i];
		if (v != 0 && fcn_0042ac40(v) != 0) {
			r = -1;
		}
	}
	return r;
}
