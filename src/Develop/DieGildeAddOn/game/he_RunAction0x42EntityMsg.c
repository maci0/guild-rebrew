


// fcn_00545890 — if([a+0x70]!=-2) fcn_004bb6c0(a+0xac); fcn_0053e450(a).

int __cdecl fcn_004bb6c0(void*);
int __cdecl he_FreeAction(int);

void __cdecl he_RunAction0x42EntityMsg(char* action)
{
	if (*(int*) (action + 0x70) != -2) {
		fcn_004bb6c0(action + 0xac);
	}
	he_FreeAction((int) action);
}

