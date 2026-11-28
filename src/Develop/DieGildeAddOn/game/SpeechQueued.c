extern char g_6b7e98[];
extern char evt_ActiveContextId[];
int* __cdecl d3snd_QueueSound(int, int, int, int, int);

/* ADDRESS: GOLDTL 0x00411090 */
/* ADDRESS: GOLDDE 0x0040fe90 */
int* __cdecl SpeechQueued(int* a1, int* a2, int* a3, int* a4, int* a5)
{
	if (*(int*) (*(int*) &g_6b7e98 + 0x104) != *(int*) &evt_ActiveContextId) {
		return 0;
	}
	return d3snd_QueueSound(*a1, *a2, *a3, *a4, *a5);
}
