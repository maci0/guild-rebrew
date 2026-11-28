extern char g_68b7a4[];
extern char g_772514[];
extern char g_14a9a14[];
extern char d2_Controls[];
extern char str_dollar_C[];
/* Build the two dialog windows for the current city record and initialize
 * their screen offsets. */

int __cdecl d2_LoadForm(int, int, int);
void __cdecl d2_CenterForm(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl d2_AddWindowTextButton(int, int, int, unsigned int, unsigned int);
void __cdecl d2_CenterElement(int);
int __cdecl d2_AddWindowValueGauge(int, int, int, int, unsigned int, int, int,
                        unsigned int);
void __cdecl io_AppendText(int);
void __cdecl d2_ClearCombatHudSlots(void);
void __cdecl d2_InitCombatUnitCards(void);

/* ADDRESS: GOLDTL 0x004d7e50 */
/* ADDRESS: GOLDDE 0x004c4da0 */
void __cdecl d2_InitCombatHud(void)
{
	int dialog;

	dialog = d2_LoadForm(0, 0, ((int) &g_68b7a4 + 0x72c));
	*(unsigned int*) ((int) &g_772514 + 0xa00) = dialog;
	d2_CenterForm(dialog, 3);
	d2_SetForm(dialog, 0);
	*(unsigned int*) ((int) &g_68b7a4 + 0x4) = d2_AddWindowTextButton(0x10, 0xc, 0xbf,
	                                         *(unsigned int*) &g_14a9a14,
	                                         *(unsigned int*) &g_772514);
	*(unsigned int*) (*(unsigned int*) (int) &d2_Controls +
	                  *(unsigned int*) ((int) &g_68b7a4 + 0x4) * 0x2f4 + 0x6c) = 1;
	d2_CenterElement(*(unsigned int*) ((int) &g_68b7a4 + 0x4));
	*(unsigned int*) &g_68b7a4 = d2_AddWindowValueGauge(
	    (*(int*) (*(unsigned int*) ((int) &g_772514 + 0x48) + 0xc) - 0x190) / 2, 0x37, 0x190, 0,
	    *(unsigned int*) ((int) &g_68b7a4 + 0x818), 0x83, 0x42, *(unsigned int*) &g_772514);
	*(unsigned int*) (*(unsigned int*) (int) &d2_Controls +
	                  *(unsigned int*) &g_68b7a4 * 0x2f4 + 0x84) = 0x54;
	*(unsigned int*) (*(unsigned int*) (int) &d2_Controls +
	                  *(int*) (*(unsigned int*) &g_772514 * 0x3cc + ((int) &d2_Controls + 0x31c)) *
	                      0x2f4 +
	                  0x5c) = 1;
	d2_SetForm(*(unsigned int*) ((int) &g_68b7a4 + 0x81c), 0);
	io_AppendText((int) &str_dollar_C);
	d2_ClearCombatHudSlots();
	d2_InitCombatUnitCards();
}
