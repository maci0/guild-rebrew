int __cdecl sb_CheckVoicePlaying(int);
void __cdecl WaitForSample(int* a0);

extern int* g_6b7ebc;
extern int* evt_CurrentScript;

/* ADDRESS: GOLDTL 0x004110e0 */
void __cdecl WaitForSample(int* sample)
{
	int handle;

	handle = *sample;
	if (g_6b7ebc != 0 && *(int*) ((char*) g_6b7ebc + 0x44) == (int) WaitForSample) {
		if (sb_CheckVoicePlaying(handle) != 0) {
			*(int*) ((char*) evt_CurrentScript + 0xc60) = (int) WaitForSample;
		}
	} else if (*(int*) ((char*) evt_CurrentScript + 0xc84) == 1) {
		*(int*) ((char*) evt_CurrentScript + 0xc60) = (int) WaitForSample;
	}
}
