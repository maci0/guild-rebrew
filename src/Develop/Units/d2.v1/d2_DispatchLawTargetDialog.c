int __cdecl gm_GetBuildingCategorySlot(int k, int* out);
int __cdecl fcn_005cff10(char* s);
int __cdecl d2_RunLawTargetSelectDialog(char* s, int a2, int a3, int a4);

/* ADDRESS: GOLDTL 0x005d0460 */
int __cdecl d2_DispatchLawTargetDialog(char* s, int a2, int a3, int a4)
{
	char* p;
	int r;

	if (s == 0) {
		return 0;
	}
	r = gm_GetBuildingCategorySlot((unsigned char) *s, (int*) &p);
	if (r != 0) {
		return fcn_005cff10(p);
	}
	return d2_RunLawTargetSelectDialog(s, a2, a3, a4);
}
