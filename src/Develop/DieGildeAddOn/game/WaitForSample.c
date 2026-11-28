int __cdecl sb_CheckVoicePlaying(int);
void __cdecl WaitForSample(int* a0);

extern int* evt_WaitingScriptTask;
extern int* evt_CurrentScript;

/* ADDRESS: GOLDTL 0x004110e0 */
/* ADDRESS: GOLDDE 0x0040fee0 */
void __cdecl WaitForSample(int* sample)
{
	int handle;

	handle = *sample;
	if (evt_WaitingScriptTask != 0 && *(int*) ((char*) evt_WaitingScriptTask + 0x44) == (int) WaitForSample) {
		if (sb_CheckVoicePlaying(handle) != 0) {
			*(int*) ((char*) evt_CurrentScript + 0xc60) = (int) WaitForSample;
		}
	} else if (*(int*) ((char*) evt_CurrentScript + 0xc84) == 1) {
		*(int*) ((char*) evt_CurrentScript + 0xc60) = (int) WaitForSample;
	}
}
