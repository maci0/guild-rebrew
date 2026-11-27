
/* ADDRESS: GOLDTL 0x004a43e0 */
char* __cdecl am_GetMethodName(int index)
{
	if (index != 0 && index < 0x49) {
		return (char*) (0x1008541 + index * 148);
	}
	return (char*) 0x67ef9c;
}
