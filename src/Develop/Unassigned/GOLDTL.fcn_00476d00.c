void __cdecl d2_WriteSurfacePixel(int, int, unsigned char, unsigned char, unsigned char, int);


/* ADDRESS: GOLDTL 0x00476d00 */
void __cdecl d2_DrawVerticalLine(int x, int y, int height, unsigned char r, unsigned char g, unsigned char b, int surf)
{
	int i;

	for (i = 0; i < height; i++)
		d2_WriteSurfacePixel(x, i + y, r, g, b, surf);
}
