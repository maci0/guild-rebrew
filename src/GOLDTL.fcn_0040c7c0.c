
int __cdecl fcn_0040c3f0();
int __cdecl fcn_0040c400();
int __cdecl fcn_0040c410();
int __cdecl fcn_0040c420();
int __cdecl fcn_0040c430();
int __cdecl fcn_0040c450();
int __cdecl fcn_0040c460();
int __cdecl fcn_0040c4c0();
int __cdecl fcn_0040c530();
int __cdecl fcn_0040c5a0();
int __cdecl fcn_0040c610();
int __cdecl fcn_0040c630();
int __cdecl fcn_0040c6c0();
int __cdecl fcn_0040c6d0();
int __cdecl fcn_0040c740();
int __cdecl fcn_0040c780();
void __cdecl evt_ImportCommand(const char*, void*, ...);

/* ADDRESS: GOLDTL 0x0040c7c0 */

/* Registers the core script commands. */
void __cdecl fcn_0040c7c0(void)
{
	evt_ImportCommand("ecmd_Dummy", fcn_0040c3f0, 5, 0);
	evt_ImportCommand("Print", fcn_0040c400, 5, 1, 6);
	evt_ImportCommand("PrintInt", fcn_0040c410, 5, 1, 1);
	evt_ImportCommand("PrintFloat", fcn_0040c420, 5, 1, 7);
	evt_ImportCommand("rnd", fcn_0040c430, 1, 1, 1);
	evt_ImportCommand("GetTime", fcn_0040c450, 1, 0);
	evt_ImportCommand("RunScript", fcn_0040c460, 1, 1, 6);
	evt_ImportCommand("RunScriptInt", fcn_0040c4c0, 1, 2, 6, 1);
	evt_ImportCommand("RunScriptInt2", fcn_0040c530, 1, 3, 6, 1, 1);
	evt_ImportCommand("RunScriptString", fcn_0040c5a0, 1, 2, 6, 6);
	evt_ImportCommand("StopScript", fcn_0040c610, 5, 1, 1);
	evt_ImportCommand("Sleep", fcn_0040c630, 5, 1, 1);
	evt_ImportCommand("FindScript", fcn_0040c6c0, 1, 1, 6);
	evt_ImportCommand("KillLocalScripts", fcn_0040c6d0, 1, 0);
	evt_ImportCommand("CallUserFunction", fcn_0040c740, 1, 2, 1, 1);
	evt_ImportCommand("CallUserFunctionExtended", fcn_0040c780, 1, 3, 1, 1, 1);
}
