int __cdecl fcn_004f0cc0(char*, char*);


/* ADDRESS: GOLDTL 0x004cdd60 */
int __cdecl fcn_004cdd60(char* a1, char* a2)
{
	int r;

	if (a2 != 0) {
		a2[0] = 2;
		a2[1] = 0;
		*(int*) (a2 + 6) = 0;
	}
	r = fcn_004f0cc0(a1 + 0x10, a2);
	if (a2 != 0 && r != 0)
		a2[0] = 1;
	if (r != 0)
		return 0;
	return -1;
}
