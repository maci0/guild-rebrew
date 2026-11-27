/* Build the two dialog windows for the current city record and initialize
 * their screen offsets. */

int __cdecl d2_LoadForm(int, int, int);
void __cdecl fcn_00471d80(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl d2_AddWindowTextButton(int, int, int, unsigned int, unsigned int);
void __cdecl d2_CenterElement(int);
int __cdecl d2_AddWindowValueGauge(int, int, int, int, unsigned int, int, int,
                        unsigned int);
void __cdecl io_AppendText(int);
void __cdecl d2_ClearCombatHudSlots(void);
void __cdecl d2_InitCombatUnitCards(void);

/* ADDRESS: GOLDTL 0x004d7e50 */
void __cdecl d2_InitCombatHud(void)
{
	int dialog;

	dialog = d2_LoadForm(0, 0, 0x68bed0);
	*(unsigned int*) 0x772f14 = dialog;
	fcn_00471d80(dialog, 3);
	d2_SetForm(dialog, 0);
	*(unsigned int*) 0x68b7a8 = d2_AddWindowTextButton(0x10, 0xc, 0xbf,
	                                         *(unsigned int*) 0x14a9a14,
	                                         *(unsigned int*) 0x772514);
	*(unsigned int*) (*(unsigned int*) 0x1015ea0 +
	                  *(unsigned int*) 0x68b7a8 * 0x2f4 + 0x6c) = 1;
	d2_CenterElement(*(unsigned int*) 0x68b7a8);
	*(unsigned int*) 0x68b7a4 = d2_AddWindowValueGauge(
	    (*(int*) (*(unsigned int*) 0x77255c + 0xc) - 0x190) / 2, 0x37, 0x190, 0,
	    *(unsigned int*) 0x68bfbc, 0x83, 0x42, *(unsigned int*) 0x772514);
	*(unsigned int*) (*(unsigned int*) 0x1015ea0 +
	                  *(unsigned int*) 0x68b7a4 * 0x2f4 + 0x84) = 0x54;
	*(unsigned int*) (*(unsigned int*) 0x1015ea0 +
	                  *(int*) (*(unsigned int*) 0x772514 * 0x3cc + 0x10161bc) *
	                      0x2f4 +
	                  0x5c) = 1;
	d2_SetForm(*(unsigned int*) 0x68bfc0, 0);
	io_AppendText(0x6811b0);
	d2_ClearCombatHudSlots();
	d2_InitCombatUnitCards();
}
