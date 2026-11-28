extern char d2_DialogButtonAction[];
extern char io_LastKeyScancode[];
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
/* ADDRESS: GOLDDE 0x004663c0 */
void __cdecl d2_ResetSelectionAndInput(void)
{
	*(int*) &d2_DialogButtonAction = 0xffffffff;
	io_ClearInputState();
	*(char*) &io_LastKeyScancode = 0;
}
#endif
