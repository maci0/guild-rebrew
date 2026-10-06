// FUNCTION: GOLDTL 0x465920

int __cdecl fcn_00465920(void)
{
	int i;
	char* p;

	for (i = 0, p = (char*) (*(int*) 0x1015ea0 + 4); i < 0x3ff; i++, p += 0x2f4) {
		if (*(int*) p == 0) {
			return i;
		}
	}
	return -1;
}
