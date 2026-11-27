void __cdecl d2_SetForm(int, int);
void __cdecl io_AppendText(int);
void __cdecl d2_RenderAndPresentFrame(void);

/* ADDRESS: GOLDTL 0x00514570 */
void __cdecl fcn_00514570(unsigned int message)
{
	d2_SetForm(*(int*) 0x7e1d40, 2);
	io_AppendText(0x6811b0);
	io_AppendText(message);
	d2_RenderAndPresentFrame();
}
