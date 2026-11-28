extern char str_GetObjectHandle_not_found[];



int __cdecl d3_FindSceneObject(int, int, int, int);
int __cdecl fcn_0064d41a(char*, char*, ...);
extern char* evt_CurrentScript;
void __cdecl evt_LogScriptError(void*, int, char*);

/* ADDRESS: GOLDDE 0x0040d3b0 */
int __cdecl GetObjectHandle(int* id)
{
	char buf[0x200];
	int r;

	r = d3_FindSceneObject(0, 0x140, 0, *id);
	if (r == 0) {
		fcn_0064d41a(buf, str_GetObjectHandle_not_found, *id);
		evt_LogScriptError(evt_CurrentScript, *(int*) (evt_CurrentScript + 0x118), buf);
		return 0;
	}
	return r;
}
