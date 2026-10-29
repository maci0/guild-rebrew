int __cdecl fcn_0042b120(int);
int __cdecl fcn_0042a6a0(int);

/* ADDRESS: GOLDTL 0x0042a700 */
int __cdecl fcn_0042a700(int obj)
{
	int i;
	int k;
	int v;
	int r = 0;

	if (*(int*) 0x6b7f90 != 0) {
		i = fcn_0042b120(obj);
		if (i >= 0) {
			for (k = 0; k < *(int*) (obj + 0x18); k++) {
				v = (*(int**) (0x6b7f10 + i * 4))[k];
				if (v != 0) {
					v = fcn_0042a6a0(v);
					if (v == -1) {
						r |= v;
					}
				}
			}
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
