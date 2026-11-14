int __cdecl fcn_0041e740(void* surface);

/* ADDRESS: GOLD 0x004790d0 */
int __cdecl fcn_004790d0(void* a0)
{
	if (*(int*) ((char*) a0 + 0x34) == 0) {
		return 0;
	}
	if (*(void**) ((char*) a0 + 0x20) != 0) {
		fcn_0041e740(*(void**) ((char*) a0 + 0x20));
		*(int*) ((char*) a0 + 0x1c) = 0;
	}
	*(int*) ((char*) a0 + 0x34) = 0;
	return 1;
}
