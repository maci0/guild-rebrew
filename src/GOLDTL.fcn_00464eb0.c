int __cdecl fcn_00464ad0(char* file, void* info, void* internal, char* name, unsigned long nsize, void* extra, unsigned long esize, char* comment, unsigned long csize);

// FUNCTION: GOLD 0x468070
// FUNCTION: GOLDTL 0x464eb0
int __cdecl fcn_00464eb0(char* s)
{
	int err;

	if (s == 0) {
		return -102;
	}
	if (*(int*) (s + 0x18) == 0) {
		return -100;
	}
	if (*(unsigned long*) (s + 0x10) + 1 == *(unsigned long*) (s + 4)) {
		return -100;
	}
	*(unsigned long*) (s + 0x14) += 0x2e + *(unsigned long*) (s + 0x48) + *(unsigned long*) (s + 0x4c) + *(unsigned long*) (s + 0x50);
	(*(unsigned long*) (s + 0x10))++;
	err = fcn_00464ad0(s, s + 0x28, s + 0x78, 0, 0, 0, 0, 0, 0);
	*(unsigned long*) (s + 0x18) = (err == 0);
	return err;
}
