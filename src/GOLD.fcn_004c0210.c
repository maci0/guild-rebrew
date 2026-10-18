/* ADDRESS: GOLD 0x004c0210 */

void* __cdecl fcn_004c0210(void)
{
	void* result;

	result = *(void**) 0x6f0b84;
	if (result != 0) {
		while (*(void**) ((char*) result + 0xc) != 0) {
			result = *(void**) ((char*) result + 0xc);
		}
		return result;
	}
	return 0;
}
