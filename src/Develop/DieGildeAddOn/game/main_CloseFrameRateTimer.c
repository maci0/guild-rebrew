void __cdecl main_SampleFrameCounter();
void __cdecl fcn_0042e9d0(void* p);

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x00520f40 */
void __cdecl main_CloseFrameRateTimer(void)
{
    fcn_0042e9d0((void*) 0x00520ef0);
}
#else
/* ADDRESS: GOLDTL 0x00525ee0 */
/* ADDRESS: GOLDDE 0x0050f1a0 */
void __cdecl main_CloseFrameRateTimer(void)
{
    fcn_0042e9d0((void*) main_SampleFrameCounter);
}
#endif
