void __cdecl d2_SetActiveTextColor(unsigned char r, unsigned char g, unsigned char b);

/* ADDRESS: GOLDTL 0x0046bd00 */
void __cdecl d2_SetTextColor(unsigned char r, unsigned char g, unsigned char b)
{
	d2_SetActiveTextColor(r, g, b);
}
