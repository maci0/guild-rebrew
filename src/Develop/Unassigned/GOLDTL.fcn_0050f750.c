/* d2_DrawDependencyLine — draw dependency diagram line with fixed style. */

void __cdecl d2_DrawLine(int, int, int, int, int, int, int);

/* ADDRESS: GOLDTL 0x0050f750 */
void __cdecl d2_DrawDependencyLine(int x0, int y0, int x1, int y1)
{
	d2_DrawLine(x0, y0, x1, y1, 0x58, 0x1f, 0x14);
}
