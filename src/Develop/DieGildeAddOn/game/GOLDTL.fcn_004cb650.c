


char* __cdecl gm_StartFilteredEntitySearch(int, ...);
unsigned short* __cdecl gm_LookupEntityRecordById(int);
void __cdecl fcn_005059b0(char*, int, int);

int __cdecl fcn_004cb650(char* x, char* out)
{
	char* e;
	unsigned short* a;
	unsigned short* b;

	e = gm_StartFilteredEntitySearch(1, 1, *(int*) (x + 0x10));
	if (e == 0)
		return 1;
	a = gm_LookupEntityRecordById(*(int*) (x + 0x18));
	if (a == 0 && *(int*) (x + 0x18) != -1)
		return 1;
	b = gm_LookupEntityRecordById(*(int*) (x + 0x14));
	if (b == 0 && *(int*) (x + 0x14) != -1)
		return 2;
	fcn_005059b0(e, *b, *a);
	if (out != 0) {
		out[0] = 2;
		out[1] = 0;
		*(int*) (out + 6) = 0;
	}
	return 0;
}
