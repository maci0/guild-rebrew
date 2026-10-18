


/* Guarded tail-call to the shared sound control (Gold 0x4c2480). */
extern int g_006f0d8c; /* 0x006f0d8c */
void __cdecl fcn_004c2d50(void);

void __cdecl fcn_004e3640(void)
{
    if (g_006f0d8c == 0) {
        fcn_004c2d50();
    }
}
