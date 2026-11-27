/* ADDRESS: GOLD 0x0047cb30 */
void __cdecl d2_SetClipRect(int x, int y, int w, int h)
{
	*(int*) 0x6f0458 = x;
	*(int*) 0x6f045c = y;
	*(int*) 0x5fed5c = w;
	*(int*) 0x5fed60 = h;
}
