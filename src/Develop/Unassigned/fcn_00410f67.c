void* __cdecl fcn_00422460(int, int);
void __cdecl fcn_004238f0(void*, int);
void __cdecl fcn_00423670(void*, int, int);

/* ADDRESS: GOLDTL 0x00410f67 */
void* __cdecl fcn_00410f67(int* a, int* b)
{
	void* r;

	r = fcn_00422460(0, *a);
	if (r != 0) {
		fcn_004238f0(r, *b);
		fcn_00423670(r, 0, 0);
		return r;
	}
	fcn_00422460(0, *a);
	return r;
}
