

int __cdecl evt_RequestScriptExit(int);

int __cdecl StopScript(int* p)
{
	evt_RequestScriptExit(*p);
	return 0;
}
