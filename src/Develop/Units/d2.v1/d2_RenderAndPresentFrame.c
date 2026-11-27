void __cdecl d2_RenderAllElements(int a);
void __cdecl d3_PresentFrame(void);

/* ADDRESS: GOLDTL 0x0046ac30 */
void __cdecl d2_RenderAndPresentFrame(void)
{
	d2_RenderAllElements(1);
	d3_PresentFrame();
}
