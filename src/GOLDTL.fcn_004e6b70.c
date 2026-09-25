char* __cdecl fcn_004e6a30(int);

// FUNCTION: GOLDTL 0x004e6b70
// SIZE: 86
int __cdecl fcn_004e6b70(int id, int v)
{
	char* p;
	int i;

	p = fcn_004e6a30(id);
	if (p != 0) {
		for (i = 0; i < *(unsigned char*) (p + 0x30); i++) {
			if (*(int*) (p + 0x34 + i * 4) == v) {
				return 0;
			}
		}
		if (*(unsigned char*) (p + 0x30) < 0x10) {
			*(int*) (p + 0x34 + *(unsigned char*) (p + 0x30) * 4) = v;
			p[0x30]++;
			return 1;
		}
	}
	return 0;
}
