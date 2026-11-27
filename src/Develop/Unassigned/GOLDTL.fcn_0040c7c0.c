
int __cdecl ecmd_Dummy();
int __cdecl evt_PrintStub();
int __cdecl PrintInt();
int __cdecl ecmd_PrintFloat();
int __cdecl ecmd_Rnd();
int __cdecl GetTime();
int __cdecl RunScript();
int __cdecl ecmd_RunScriptInt();
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
	evt_ImportCommand("Print", evt_PrintStub, 5, 1, 6);
	evt_ImportCommand("PrintInt", PrintInt, 5, 1, 1);
	evt_ImportCommand("PrintFloat", ecmd_PrintFloat, 5, 1, 7);
	evt_ImportCommand("rnd", ecmd_Rnd, 1, 1, 1);
	evt_ImportCommand("GetTime", GetTime, 1, 0);
	evt_ImportCommand("RunScript", RunScript, 1, 1, 6);
	evt_ImportCommand("RunScriptInt", ecmd_RunScriptInt, 1, 2, 6, 1);
	evt_ImportCommand("RunScriptInt2", RunScriptInt2, 1, 3, 6, 1, 1);
	evt_ImportCommand("RunScriptString", RunScriptString, 1, 2, 6, 6);
	evt_ImportCommand("StopScript", StopScript, 5, 1, 1);
	evt_ImportCommand("Sleep", fcn_0040c630, 5, 1, 1);
	evt_ImportCommand("FindScript", FindScript, 1, 1, 6);
	evt_ImportCommand("KillLocalScripts", KillLocalScripts, 1, 0);
	evt_ImportCommand("CallUserFunction", CallUserFunction, 1, 2, 1, 1);
	evt_ImportCommand("CallUserFunctionExtended", CallUserFunctionExtended, 1, 3, 1, 1, 1);
}
