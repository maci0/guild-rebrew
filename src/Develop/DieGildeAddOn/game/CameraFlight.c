extern char* evt_CurrentScript;
extern char evt_CameraFlightErrStr[];



int __cdecl d3_StartCameraFlight(int, int, int, int);
void __cdecl evt_LogScriptError(void*, int, char*);

/* ADDRESS: GOLDDE 0x0040e400 */
int __cdecl CameraFlight(int* a1, int* a2, int* a3)
{
	if (d3_StartCameraFlight(*a1 / 17, 2, *a2, *a3) == 0) {
		evt_LogScriptError(evt_CurrentScript, *(int*) ((char*) evt_CurrentScript + 0x118), evt_CameraFlightErrStr);
	}
	return 1;
}
