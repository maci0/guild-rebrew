int __cdecl fcn_00464ad0(char* file, void* info, void* internal, char* name, unsigned long nsize, void* extra, unsigned long esize, char* comment, unsigned long csize);

// FUNCTION: GOLD 0x00468020
// FUNCTION: GOLDTL 0x464e60
int __cdecl fcn_00464e60(char* s)
{
	int err;

	if (s == 0) {
		return -102;
	}
	*(unsigned long*) (s + 0x14) = *(unsigned long*) (s + 0x24);
	*(unsigned long*) (s + 0x10) = 0;
	err = fcn_00464ad0(s, s + 0x28, s + 0x78, 0, 0, 0, 0, 0, 0);
	*(unsigned long*) (s + 0x18) = (err == 0);
	return err;
}
