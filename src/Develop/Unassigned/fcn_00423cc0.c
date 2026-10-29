char* __cdecl fcn_00423a50(char* s);

/* ADDRESS: GOLDTL 0x00423cc0 */
int __cdecl fcn_00423cc0(char* s)
{
	int r = 0;
	char* p;

	p = fcn_00423a50(s);
	if (p != 0) {
		r = *(int*) (p + 0x100);
	}
	return r;
}
