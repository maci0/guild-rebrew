// FUNCTION: GOLD 0x004e3640
// FUNCTION: GOLDTL 0x4e4eb0

/* Guarded tail-call: if g_006f0d8c is 0, jump to fcn_004c2480, else return. */
extern int g_006f0d8c; /* 0x006f0d8c */
void __cdecl fcn_004c2480(void);

void __cdecl fcn_004e3640(void)
{
    if (g_006f0d8c == 0) {
        fcn_004c2480();
    }
}

