int __cdecl fcn_00464ad0(char* file, void* info, void* internal, char* name, unsigned long nsize, void* extra, unsigned long esize, char* comment, unsigned long csize);

// FUNCTION: GOLD 0x00468700
// SIZE: 82
// FUNCTION: GOLDTL 0x465790
// SIZE: 82
int __cdecl fcn_00465790(char* s, unsigned long pos, unsigned long num)
{
	int err;

	if (s == 0 || pos == 0 || *(int*) (s + 0x7c) != 0) {
		return -102;
	}
	*(unsigned long*) (s + 0x14) = pos;
	*(unsigned long*) (s + 0x10) = num;
	err = fcn_00464ad0(s, s + 0x28, s + 0x78, 0, 0, 0, 0, 0, 0);
	*(unsigned long*) (s + 0x18) = (err == 0);
	return err;
}
