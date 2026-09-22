// FUNCTION: GOLDTL 0x426cc0
// SIZE: 63

void* __cdecl fcn_00426cc0(int a1)
{
	int i;
	char* base;
	char* p;

	if (a1 == -1) {
		return 0;
	}
	base = *(char**) 0x6b7e94;
	for (i = 0, p = base + 0x100; i < 0x80; i++, p += 0xc98) {
		if (*(int*) p == a1) {
			return (void*) ((int) base + i * 3224);
		}
	}
	return 0;
}
