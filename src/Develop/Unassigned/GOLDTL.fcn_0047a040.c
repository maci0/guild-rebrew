
/* ADDRESS: GOLDTL 0x0047a040 */
void __cdecl d2_SetClipRect(int left, int top, int right, int bottom)
{
	*(int*) 0x7725f8 = left;
	*(int*) 0x7725fc = top;
	*(int*) 0x67d964 = right;
	*(int*) 0x67d968 = bottom;
}
