/* ADDRESS: GOLD 0x0041bdd0 */
// fcn_0041bdd0 — if(dep || obj) 1; r=vfn; return r<=0?1:0.

int __cdecl fcn_0041bdd0(void)
{
	int r;
	void* o;
	if (*(int*) 0x14635ac == 0 || *(int*) 0x631204 == 0) {
		return 1;
	}
	o = *(void**) 0x631204;
	r = (int) ((int (__stdcall*)(void*)) (*(void***) o)[0x64 / 4])(o);
	return r <= 0;
}
