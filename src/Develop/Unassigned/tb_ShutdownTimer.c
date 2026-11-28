__declspec(dllimport) int __stdcall timeKillEvent(int);
__declspec(dllimport) void __stdcall timeEndPeriod(int);
extern char tb_TimeCaps[]; extern char tb_TimerId[];

typedef int (__stdcall* MM_TIME_KILL_EVENT_FN)(int);
typedef void (__stdcall* MM_TIME_END_PERIOD_FN)(int);

/* ADDRESS: GOLDDE 0x00427c30 */
void __cdecl tb_ShutdownTimer(void)
{
	int r;

	if (*(int*) &tb_TimerId != 0) {
		r = timeKillEvent(*(int*) &tb_TimerId);
		if (r == 0) {
			*(int*) &tb_TimerId = r;
		}
	}
	timeEndPeriod(*(int*) &tb_TimeCaps + 5);
}
