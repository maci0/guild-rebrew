// FUNCTION: GOLD 0x004686c0
// FUNCTION: GOLDTL 0x465750
int __cdecl fcn_00465750(char* s, unsigned long* pos, unsigned long* num)
{
	*num = 0;
	*pos = 0;
	if (s != 0 && *(int*) (s + 0x18) != 0 && *(int*) (s + 0x7c) == 0) {
		*pos = *(unsigned long*) (s + 0x14);
		*num = *(unsigned long*) (s + 0x10);
		return 0;
	}
	return -102;
}
