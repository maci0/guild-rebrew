
/* Calls gm_RandomMod(7), masks to 16 bits. */
int __cdecl gm_RandomMod(int n);

/* ADDRESS: GOLDDE 0x00482640 */
int __cdecl ai_SelectRandomTorture(void)
{
    return gm_RandomMod(7) & 0xffff;
}
