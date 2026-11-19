extern char* evt_CurrentScript;
extern char g_676924[];



int __cdecl fcn_00414d20(int, int, int, int);
void __cdecl evt_LogScriptError(void*, int, char*);

int __cdecl CameraFlight(int* a1, int* a2, int* a3)
{
	if (fcn_00414d20(*a1 / 17, 2, *a2, *a3) == 0) {
		evt_LogScriptError(evt_CurrentScript, *(int*) ((char*) evt_CurrentScript + 0x118), g_676924);
	}
	return 1;
}
