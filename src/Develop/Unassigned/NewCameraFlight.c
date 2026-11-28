extern char* evt_WaitingScriptTask;
extern char* evt_CurrentScript;
extern int d3_CameraAnimating;
extern int d3_ActiveCameraAnimation;

void __cdecl d3_StartCameraFlight(int, int, int, int, int, int, int, int);


/* Script command: forwards its seven arguments to fcn_00414d20, the first
 * divided by 14; while the script is suspended it re-arms itself. */
/* ADDRESS: GOLDTL 0x0040f720 */
/* ADDRESS: GOLDDE 0x0040e520 */
int __cdecl NewCameraFlight(int* a1, int* a2, int* a3, int* a4, int* a5, int* a6, int* a7)
{
	if (evt_WaitingScriptTask != 0 && *(int (__cdecl**)()) (evt_WaitingScriptTask + 0x44) == (int (__cdecl*)()) NewCameraFlight) {
		if (d3_CameraAnimating == 0 && d3_ActiveCameraAnimation == 0) {
			return 0;
		}
		*(int (__cdecl**)()) (evt_CurrentScript + 0xc60) = (int (__cdecl*)()) NewCameraFlight;
		return 0;
	}
	if (*(int*) (evt_CurrentScript + 0xc84) == 1) {
		*(int (__cdecl**)()) (evt_CurrentScript + 0xc60) = (int (__cdecl*)()) NewCameraFlight;
	}
	d3_StartCameraFlight(*a1 / 14, 6, *a2, *a3, *a4, *a5, *a6, *a7);
	return 1;
}
