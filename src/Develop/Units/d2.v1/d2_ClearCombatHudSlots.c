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

extern GUI_ENTRY d2_CombatUnitCards[6];
#ifdef REBREW_GOLD
int __cdecl d2_CloseWindow(int slot);
void __cdecl d2_DestroyGuiElement(int slot);
#else
int __cdecl d2_CloseWindow(int slot);
void __cdecl d2_DestroyElement(int slot);
#endif

/* ADDRESS: GOLDTL 0x004d0ec0 */
void __cdecl d2_ClearCombatHudSlots(void)
{
    int i;

    for (i = 0; i < 6; ++i) {
        if (d2_CombatUnitCards[i].win != -1) {
#ifdef REBREW_GOLD
            d2_CloseWindow(d2_CombatUnitCards[i].win);
#else
            d2_CloseWindow(d2_CombatUnitCards[i].win);
#endif
            d2_CombatUnitCards[i].win = -1;
#ifdef REBREW_GOLD
            d2_DestroyGuiElement(d2_CombatUnitCards[i].frame);
#else
            d2_DestroyElement(d2_CombatUnitCards[i].frame);
#endif
        }
    }
}
