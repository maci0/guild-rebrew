/* ADDRESS: GOLD 0x0041bdd0 */
unsigned char __cdecl fcn_0041bdd0(void)
{
	void* o;

	if (*(int*) 0x14635ac == 0 || *(int*) 0x631204 == 0) {
		return 1;
	}
	o = *(void**) 0x631204;
	return ((int (__stdcall*)(void*)) (*(void***) o)[0x64 / 4])(o) == 0;
}
