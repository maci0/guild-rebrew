


extern char* g_6b7ebc;
extern char* evt_CurrentScript;
extern int d3_CameraAnimating;
extern int d3_ActiveCameraAnimation;
int __cdecl fcn_00414d20(int a, int b, int c, int d, int e, int f, int g, int h);
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);

int __cdecl CameraFlightEnhanced(int* a1, int* a2, int* a3, int* a4, int* a5, int* a6, int* a7)
{
	if (g_6b7ebc != 0 && *(void**) (g_6b7ebc + 0x44) == (void*) CameraFlightEnhanced) {
		if (d3_CameraAnimating == 0 && d3_ActiveCameraAnimation == 0) {
			return 0;
		}
		*(void**) (evt_CurrentScript + 0xc60) = (void*) CameraFlightEnhanced;
		return 0;
	}
	if (*(int*) (evt_CurrentScript + 0xc84) == 1) {
		*(void**) (evt_CurrentScript + 0xc60) = (void*) CameraFlightEnhanced;
	}
	if (!fcn_00414d20(*a1 / 17, 6, *a2, *a3, *a4, *a5, *a6, *a7)) {
		fcn_00425bf0(evt_CurrentScript, *(int*) (evt_CurrentScript + 0x118), "call failed");
	}
	return 1;
}
