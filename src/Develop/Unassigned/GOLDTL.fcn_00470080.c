
/* ADDRESS: GOLDTL 0x00470080 */
void __stdcall d2_FrameTimerCallback(int timerId, int msg, int userData, int reserved1, int reserved2)
{
	int previous;

	previous = *(int*) 0x77251c;
	*(int*) 0x77251c = 0;
	*(int*) 0x772520 = previous;
}
