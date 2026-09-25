// FUNCTION: GOLDTL 0x00598510
// SIZE: 62

int __cdecl fcn_00598150(int, int*);
void __cdecl fcn_005983d0(int);

void __cdecl fcn_00598510(void)
{
	int ids[0x100];
	int n;
	int i;

	n = fcn_00598150(0, ids);
	for (i = 0; i < n; i++) {
		if (ids[i] != 0) {
			fcn_005983d0(ids[i]);
		}
	}
}
