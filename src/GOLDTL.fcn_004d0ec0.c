/* Inferred access view shared with the six-record initializer. */
typedef struct GUI_ENTRY {
    int icon;
    int frame;
    int win;
    int unused0c;
    int text;
    int name;
    int label;
    char* unit;
} GUI_ENTRY;

extern GUI_ENTRY g_9b4840[6];
#ifdef REBREW_GOLD
int __cdecl fcn_00472cd0(int slot);
void __cdecl fcn_0046e700(int slot);
#else
int __cdecl fcn_0046f280(int slot);
void __cdecl fcn_0046b2b0(int slot);
#endif

/* ADDRESS: GOLD 0x004cfe70 */
/* ADDRESS: GOLDTL 0x004d0ec0 */
void __cdecl fcn_004d0ec0(void)
{
    int i;

    for (i = 0; i < 6; ++i) {
        if (g_9b4840[i].win != -1) {
#ifdef REBREW_GOLD
            fcn_00472cd0(g_9b4840[i].win);
#else
            fcn_0046f280(g_9b4840[i].win);
#endif
            g_9b4840[i].win = -1;
#ifdef REBREW_GOLD
            fcn_0046e700(g_9b4840[i].frame);
#else
            fcn_0046b2b0(g_9b4840[i].frame);
#endif
        }
    }
}
