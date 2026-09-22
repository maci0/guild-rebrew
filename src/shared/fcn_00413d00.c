// FUNCTION: GOLD 0x00413d00
// SIZE: 43
// fcn_00413d00 — if(a){ if(a[0x10]){ free(a[0x10]); a[0x10]=0; } free(a); }.

int __cdecl fcn_00422620(int);

void __cdecl fcn_00413d00(void* a)
{
	if (a != 0) {
		if (*(void**) ((char*) a + 0x10) != 0) {
			fcn_00422620((int) *(void**) ((char*) a + 0x10));
			*(void**) ((char*) a + 0x10) = 0;
		}
		fcn_00422620((int) a);
	}
}
