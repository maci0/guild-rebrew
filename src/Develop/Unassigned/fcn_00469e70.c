extern int g_0067d3cc;
extern int g_007725a8;
extern void __cdecl d2_SubRefcount(int v);

/* ADDRESS: GOLDTL 0x00469e70 */
void __cdecl fcn_00469e70(void)
{
    if (g_0067d3cc != -1)
        d2_SubRefcount(g_0067d3cc);
    g_0067d3cc = -1;
    g_007725a8 = 0;
}
