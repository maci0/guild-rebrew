extern char g_69039c[];


void __cdecl io_FormatTextBuffer(int, int, int);

/* ADDRESS: GOLDDE 0x00594ad0 */
void __cdecl d2_FormatPriceText(int a1, int output)
{
	io_FormatTextBuffer(output, (int) &g_69039c, a1);
}
