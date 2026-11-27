void __cdecl io_ClearInputState(void);

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x00476b60 */
void __cdecl d2_ResetSelectionAndInput(void)
{
	*(int*) 0xf8a668 = 0xffffffff;
	io_ClearInputState();
	*(char*) 0x1468410 = 0;
}
#else
/* ADDRESS: GOLDTL 0x00473660 */
void __cdecl d2_ResetSelectionAndInput(void)
{
	*(int*) 0x100f1dc = 0xffffffff;
	io_ClearInputState();
	*(char*) 0x14cf950 = 0;
}
#endif
