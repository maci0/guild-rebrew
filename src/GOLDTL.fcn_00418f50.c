// FUNCTION: GOLDTL 0x418f50
// SIZE: 54

void __cdecl fcn_00418d70(char*);

void __cdecl fcn_00418f50(void)
{
	int i;
	char* p;

	for (i = 0; i < *(int*) 0x677680; i++) {
		p = *(char**) 0x6b5d08 + i * 0x54;
		if (*(int*) (p + 0x38) != 0) {
			fcn_00418d70(p);
		}
	}
}
