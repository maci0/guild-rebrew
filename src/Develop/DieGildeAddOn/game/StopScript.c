

int __cdecl evt_RequestScriptExit(int);

/* ADDRESS: GOLDDE 0x0040b420 */
int __cdecl StopScript(int* p)
{
	evt_RequestScriptExit(*p);
	return 0;
}
