
int __cdecl ecmd_Dummy();
int __cdecl fcn_0040c400();
int __cdecl PrintInt();
int __cdecl fcn_0040c420();
int __cdecl fcn_0040c430();
int __cdecl GetTime();
int __cdecl RunScript();
int __cdecl fcn_0040c4c0();
int __cdecl RunScriptInt2();
int __cdecl RunScriptString();
int __cdecl StopScript();
int __cdecl fcn_0040c630();
int __cdecl FindScript();
int __cdecl KillLocalScripts();
int __cdecl CallUserFunction();
int __cdecl CallUserFunctionExtended();
void __cdecl evt_ImportCommand(const char*, void*, ...);


/* Registers the core script commands. */
/* ADDRESS: GOLDTL 0x0040c7c0 */
void __cdecl evt_RegisterCoreCommands(void)
{
	evt_ImportCommand("ecmd_Dummy", ecmd_Dummy, 5, 0);
	evt_ImportCommand("Print", fcn_0040c400, 5, 1, 6);
	evt_ImportCommand("PrintInt", PrintInt, 5, 1, 1);
	evt_ImportCommand("PrintFloat", fcn_0040c420, 5, 1, 7);
	evt_ImportCommand("rnd", fcn_0040c430, 1, 1, 1);
	evt_ImportCommand("GetTime", GetTime, 1, 0);
	evt_ImportCommand("RunScript", RunScript, 1, 1, 6);
	evt_ImportCommand("RunScriptInt", fcn_0040c4c0, 1, 2, 6, 1);
	evt_ImportCommand("RunScriptInt2", RunScriptInt2, 1, 3, 6, 1, 1);
	evt_ImportCommand("RunScriptString", RunScriptString, 1, 2, 6, 6);
	evt_ImportCommand("StopScript", StopScript, 5, 1, 1);
	evt_ImportCommand("Sleep", fcn_0040c630, 5, 1, 1);
	evt_ImportCommand("FindScript", FindScript, 1, 1, 6);
	evt_ImportCommand("KillLocalScripts", KillLocalScripts, 1, 0);
	evt_ImportCommand("CallUserFunction", CallUserFunction, 1, 2, 1, 1);
	evt_ImportCommand("CallUserFunctionExtended", CallUserFunctionExtended, 1, 3, 1, 1, 1);
}
