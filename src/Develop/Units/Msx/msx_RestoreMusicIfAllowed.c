


/* Guarded tail-call to the shared sound control (Gold 0x4c2480). */
extern int g_006f0d8c; /* 0x006f0d8c */
void __cdecl msx_RestoreMusicVolume(void);

/* ADDRESS: GOLDDE 0x004d1830 */
void __cdecl msx_RestoreMusicIfAllowed(void)
{
    if (g_006f0d8c == 0) {
        msx_RestoreMusicVolume();
    }
}
