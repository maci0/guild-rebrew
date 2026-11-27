int __cdecl d3_UnlockSurface(void* surface);

/* ADDRESS: GOLD 0x004790d0 */
int __cdecl fcn_004790d0(void* obj)
{
	if (*(int*) ((char*) obj + 0x34) == 0) {
		return 0;
	}
	if (*(void**) ((char*) obj + 0x20) != 0) {
		d3_UnlockSurface(*(void**) ((char*) obj + 0x20));
		*(int*) ((char*) obj + 0x1c) = 0;
	}
	*(int*) ((char*) obj + 0x34) = 0;
	return 1;
}
