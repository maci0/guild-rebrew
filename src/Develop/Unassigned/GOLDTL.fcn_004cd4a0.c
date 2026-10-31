char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl fcn_004030e0(char*);


/* ADDRESS: GOLDTL 0x004cd4a0 */
int __cdecl fcn_004cd4a0(char* a1, char* a2)
{
	char* e;

	if (a2 != 0) {
		a2[0] = 2;
		a2[1] = 0;
		*(int*) (a2 + 6) = 0;
	}
	e = gm_LookupEntityRecordById(*(int*) (a1 + 0x10));
	if (e != 0 && *(char**) (e + 0x184) != 0) {
		fcn_004030e0(*(char**) (e + 0x184));
		*(char**) (e + 0x184) = 0;
		if (a2 != 0)
			a2[0] = 1;
		return 0;
	}
	return 1;
}
