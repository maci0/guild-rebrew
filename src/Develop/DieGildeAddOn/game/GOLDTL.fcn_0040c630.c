extern char* evt_WaitingScriptTask;
extern char* evt_CurrentScript;
extern volatile int gm_GameTicks;

/* Sleep. While this command is the one in progress, wait until the
 * clock reaches the stored base plus the tick count divided by 14.
 * A count of -1 waits forever. The first entry records the clock. */

/* ADDRESS: GOLDTL 0x0040c630 */
/* ADDRESS: GOLDDE 0x0040b440 */
int __cdecl ecmd_Sleep(int* ticks)
{
	char* vm;
	int n;

	if (evt_WaitingScriptTask != 0 && *(void**) (evt_WaitingScriptTask + 0x44) == (void*) ecmd_Sleep) {
		vm = evt_CurrentScript;
		n = *ticks;
		if (n != -1 && (unsigned) gm_GameTicks >= (unsigned) (n / 14 + *(int*) (vm + 0xc88))) {
			return 0;
		}
		*(void**) (vm + 0xc60) = (void*) ecmd_Sleep;
		return 0;
	}
	*(void**) (evt_CurrentScript + 0xc60) = (void*) ecmd_Sleep;
	*(int*) (evt_CurrentScript + 0xc88) = gm_GameTicks;
	return 1;
}
