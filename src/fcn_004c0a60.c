// FUNCTION: GOLDTL 0x4c0a60
// SIZE: 29

void* __cdecl fcn_004c0a60(void)
{
	void* result;

	result = *(void**) 0x772d34;
	if (result != 0) {
		while (*(void**) ((char*) result + 0xc) != 0) {
			result = *(void**) ((char*) result + 0xc);
		}
		return result;
	}
	return 0;
}
