void* __cdecl fcn_00422460(int, int);
void __cdecl fcn_004238f0(void*, int);
void __cdecl fcn_00423670(void*, int, int);

/* ADDRESS: GOLDTL 0x00410f50 */
void* __cdecl fcn_00410f50(int* a1, int* a2)
{
	void* h;

	if (*(int*) ((char*) *(void**) 0x6b7e98 + 0x104) != *(int*) 0x6791c8)
		return 0;
	h = fcn_00422460(0, *a1);
	if (h != 0) {
		fcn_004238f0(h, *a2);
		fcn_00423670(h, 0, 0);
	} else {
		fcn_00422460(0, *a1);
	}
	return h;
}
