// FUNCTION: GOLD 0x0043fed0
/* Calls fcn_0043f270, then zeroes g_00633748. */
extern int g_00633748; /* 0x00633748 */
void __cdecl fcn_0043f270(void);

void __cdecl fcn_0043fed0(void)
{
    fcn_0043f270();
    g_00633748 = 0;
}
