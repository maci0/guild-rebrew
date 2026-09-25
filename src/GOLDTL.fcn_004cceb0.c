// FUNCTION: GOLD 0x004cc330
// SIZE: 83
// FUNCTION: GOLDTL 0x4cceb0
// SIZE: 83

char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl fcn_004cfc40(char*, int, int);

int __cdecl fcn_004cceb0(char* a1, char* a2)
{
	char* r;

	r = gm_LookupEntityRecordById(*(int*) (a1 + 0x10));
	if (r != 0) {
		fcn_004cfc40(r, *(int*) (a1 + 0x14), 0);
		*(int*) (r + 0x24) -= *(int*) (a1 + 0x14);
		r[8] = a1[0x18];
	}
	if (a2 != 0) {
		a2[0] = 1;
		a2[1] = 8;
		*(int*) (a2 + 6) = 0;
	}
	return 0;
}
