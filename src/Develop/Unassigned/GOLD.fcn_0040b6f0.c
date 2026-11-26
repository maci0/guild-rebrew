
// fcn_0040b6f0 — calls fcn_00429e90(*arg).

int __cdecl evt_RequestScriptExit(int);

int __cdecl ecmd_ExitScript(int* a)
{
	evt_RequestScriptExit(*a);
	return 0;
}
