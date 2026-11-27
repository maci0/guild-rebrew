/* ADDRESS: GOLD 0x0041e740 */
int __cdecl d3_UnlockSurface(void* surface)
{
	int result;

	result = (int) surface;
	if (surface != 0) {
		result = ((int (__stdcall*)(void*, int)) (*(int**) surface)[32])(surface, 0);
	}
	return result;
}
