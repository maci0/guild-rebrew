// FUNCTION: GOLDTL 0x4228c0
// SIZE: 76

char* __cdecl fcn_004228c0(char* key)
{
	char* p;
	int i;

	p = *(char**) 0x6b7d78;
	if (*(int*) 0x6b7d7c == 0) {
		return (char*) 0x14cb980;
	}
	for (; p != 0; p = *(char**) (p + 0x13c)) {
		for (i = 0; i < *(int*) (p + 0x134); i++) {
			if (*(char**) (p + 0x138) + i * 0x40 == key) {
				return p;
			}
		}
	}
	return p;
}
