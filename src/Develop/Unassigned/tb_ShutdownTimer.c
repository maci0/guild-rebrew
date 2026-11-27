extern char g_1052c48[]; extern char g_6b7fa8[];

typedef int (__stdcall* MM_TIME_KILL_EVENT_FN)(int);
typedef void (__stdcall* MM_TIME_END_PERIOD_FN)(int);

void __cdecl tb_ShutdownTimer(void)
{
	int r;

	if (*(int*) &g_6b7fa8 != 0) {
		r = (*(MM_TIME_KILL_EVENT_FN*) 0x66232c)(*(int*) &g_6b7fa8);
		if (r == 0) {
			*(int*) &g_6b7fa8 = r;
		}
	}
	(*(MM_TIME_END_PERIOD_FN*) 0x662328)(*(int*) &g_1052c48 + 5);
}
