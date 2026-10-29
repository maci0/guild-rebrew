typedef int (__stdcall *FN_41f460)(int *);

int *__cdecl fcn_0041f9b0(int *);

/* ADDRESS: GOLDTL 0x0041f460 */
int __cdecl fcn_0041f460(int *a1)
{
	int *x;
	int *y;

	x = fcn_0041f9b0(a1);
	if (x != 0) {
		y = (int *) x[0x120 / 4];
		return (*(FN_41f460 *) (*y + 0x20))(y) >= 0;
	}
	return 0;
}
