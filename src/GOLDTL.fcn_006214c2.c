extern int __cdecl fcn_0061324e(void);

/* ADDRESS: GOLDTL 0x006214c2 */

void __cdecl fcn_006214c2(void)
{
	void* p;

	if (fcn_0061324e() != 0) {
		p = (void*)0x62131c;
		*(void**)0x6af208 = p;
	} else {
		*(void**)0x6af208 = (void*)0x6210dd;
		p = (void*)0x621234;
	}
	*(void**)0x6af20c = p;
	((void (__cdecl*)(void))p)();
}
