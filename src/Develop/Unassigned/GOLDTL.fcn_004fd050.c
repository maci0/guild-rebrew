


extern int g_773d48;

void __cdecl amt_ProcessPrivilegeIncome(int, int, int*);
void __cdecl cm_StepCommandQueue(void);

void __cdecl gm_CollectAllTaxes(void)
{
	int buf[4];
	int i;

	g_773d48 = 0;
	for (i = 0; i < 0x300; i++) {
		amt_ProcessPrivilegeIncome(i, 1, buf);
		if (g_773d48 > 0x40) {
			cm_StepCommandQueue();
			g_773d48 = 0;
		}
	}
	g_773d48 = 0;
}
