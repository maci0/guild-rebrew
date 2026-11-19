extern int g_6b7ec0;
extern int g_6b7ec0;



extern char* evt_CurrentScript;

int __cdecl fcn_00428800(int);
int __cdecl fcn_00427b40(int);
void __cdecl fcn_00428720(int);

void __cdecl evt_ReturnFromFunction(void)
{
	int x;

	x = fcn_00428800(0);
	if (fcn_00427b40((*(int*)&evt_CurrentScript)) == 0) {
		fcn_00428720((*(int*)&evt_CurrentScript));
	}
	g_6b7ec0 = x;
}
