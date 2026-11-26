void __cdecl d2_DestroyForm(int);
void __cdecl fcn_004d1910(void);
void __cdecl fcn_004d0ec0(void);

/* ADDRESS: GOLDTL 0x004d7f70 */
void __cdecl fcn_004d7f70(void)
{
    d2_DestroyForm(*(unsigned int*) 0x772f14);
    *(unsigned int*) 0x772f14 = 0;
    fcn_004d1910();
    fcn_004d0ec0();
}
