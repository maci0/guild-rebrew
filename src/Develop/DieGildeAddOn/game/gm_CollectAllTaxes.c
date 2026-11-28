


extern int gm_QueuedCommandCount;

void __cdecl amt_ProcessPrivilegeIncome(int, int, int*);
void __cdecl cm_StepCommandQueue(void);

/* ADDRESS: GOLDDE 0x004e8b80 */
void __cdecl gm_CollectAllTaxes(void)
{
	int buf[4];
	int i;

	gm_QueuedCommandCount = 0;
	for (i = 0; i < 0x300; i++) {
		amt_ProcessPrivilegeIncome(i, 1, buf);
		if (gm_QueuedCommandCount > 0x40) {
			cm_StepCommandQueue();
			gm_QueuedCommandCount = 0;
		}
	}
	gm_QueuedCommandCount = 0;
}
