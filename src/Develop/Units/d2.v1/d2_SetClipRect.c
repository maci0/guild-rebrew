#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x0047cb30 */
void __cdecl d2_SetClipRect(int x, int y, int w, int h)
{
	*(int*) 0x6f0458 = x;
	*(int*) 0x6f045c = y;
	*(int*) 0x5fed5c = w;
	*(int*) 0x5fed60 = h;
}
#else
/* ADDRESS: GOLDTL 0x0047a040 */
/* ADDRESS: GOLDDE 0x004692f0 */
void __cdecl d2_SetClipRect(int left, int top, int right, int bottom)
{
	*(int*) 0x7725f8 = left;
	*(int*) 0x7725fc = top;
	*(int*) 0x67d964 = right;
	*(int*) 0x67d968 = bottom;
}
#endif
