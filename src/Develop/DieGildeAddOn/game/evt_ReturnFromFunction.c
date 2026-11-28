extern int g_6b7ec0;
extern int g_6b7ec0;



extern char* evt_CurrentScript;

int __cdecl evt_EvaluateExpression(int);
int __cdecl evt_PopCallFrame(int);
void __cdecl evt_RequestScriptExit(int);

void __cdecl evt_ReturnFromFunction(void)
{
	int x;

	x = evt_EvaluateExpression(0);
	if (evt_PopCallFrame((*(int*)&evt_CurrentScript)) == 0) {
		evt_RequestScriptExit((*(int*)&evt_CurrentScript));
	}
	g_6b7ec0 = x;
}
