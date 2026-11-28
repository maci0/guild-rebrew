extern int evt_ReturnValue;
extern int evt_ReturnValue;



extern char* evt_CurrentScript;

int __cdecl evt_EvaluateExpression(int);
int __cdecl evt_PopCallFrame(int);
void __cdecl evt_RequestScriptExit(int);

/* ADDRESS: GOLDDE 0x00421f90 */
void __cdecl evt_ReturnFromFunction(void)
{
	int x;

	x = evt_EvaluateExpression(0);
	if (evt_PopCallFrame((*(int*)&evt_CurrentScript)) == 0) {
		evt_RequestScriptExit((*(int*)&evt_CurrentScript));
	}
	evt_ReturnValue = x;
}
