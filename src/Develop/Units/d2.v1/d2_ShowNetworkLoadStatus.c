extern char str_dollar_C[];
extern char g_7e1d40[];
void __cdecl d2_SetForm(int, int);
void __cdecl io_AppendText(int);
void __cdecl d2_RenderAndPresentFrame(void);

/* ADDRESS: GOLDTL 0x00514570 */
/* ADDRESS: GOLDDE 0x004ff010 */
void __cdecl d2_ShowNetworkLoadStatus(unsigned int message)
{
	d2_SetForm(*(int*) &g_7e1d40, 2);
	io_AppendText((int) &str_dollar_C);
	io_AppendText(message);
	d2_RenderAndPresentFrame();
}
