extern char tb_TimeCaps[]; extern char tb_TimerId[];

typedef int (__stdcall* MM_TIME_KILL_EVENT_FN)(int);
typedef void (__stdcall* MM_TIME_END_PERIOD_FN)(int);

void __cdecl tb_ShutdownTimer(void)
{
	int r;

	if (*(int*) &tb_TimerId != 0) {
		r = (*(MM_TIME_KILL_EVENT_FN*) 0x66232c)(*(int*) &tb_TimerId);
		if (r == 0) {
			*(int*) &tb_TimerId = r;
		}
	}
	(*(MM_TIME_END_PERIOD_FN*) 0x662328)(*(int*) &tb_TimeCaps + 5);
}
