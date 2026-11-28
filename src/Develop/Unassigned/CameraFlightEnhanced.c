


extern char* evt_WaitingScriptTask;
extern char* evt_CurrentScript;
extern int d3_CameraAnimating;
extern int d3_ActiveCameraAnimation;
int __cdecl d3_StartCameraFlight(int a, int b, int c, int d, int e, int f, int g, int h);
void __cdecl evt_LogScriptError(char* g, int h, const char* msg);

/* ADDRESS: GOLDDE 0x0040e460 */
int __cdecl CameraFlightEnhanced(int* a1, int* a2, int* a3, int* a4, int* a5, int* a6, int* a7)
{
	if (evt_WaitingScriptTask != 0 && *(void**) (evt_WaitingScriptTask + 0x44) == (void*) CameraFlightEnhanced) {
		if (d3_CameraAnimating == 0 && d3_ActiveCameraAnimation == 0) {
			return 0;
		}
		*(void**) (evt_CurrentScript + 0xc60) = (void*) CameraFlightEnhanced;
		return 0;
	}
	if (*(int*) (evt_CurrentScript + 0xc84) == 1) {
		*(void**) (evt_CurrentScript + 0xc60) = (void*) CameraFlightEnhanced;
	}
	if (!d3_StartCameraFlight(*a1 / 17, 6, *a2, *a3, *a4, *a5, *a6, *a7)) {
		evt_LogScriptError(evt_CurrentScript, *(int*) (evt_CurrentScript + 0x118), "call failed");
	}
	return 1;
}
