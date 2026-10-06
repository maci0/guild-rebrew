
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
void __cdecl fcn_00429ed0(const char*, void*, ...);

// FUNCTION: GOLDTL 0x40c7c0

/* Registers the core script commands. */
void __cdecl fcn_0040c7c0(void)
{
	fcn_00429ed0("ecmd_Dummy", fcn_0040c3f0, 5, 0);
	fcn_00429ed0("Print", fcn_0040c400, 5, 1, 6);
	fcn_00429ed0("PrintInt", fcn_0040c410, 5, 1, 1);
	fcn_00429ed0("PrintFloat", fcn_0040c420, 5, 1, 7);
	fcn_00429ed0("rnd", fcn_0040c430, 1, 1, 1);
	fcn_00429ed0("GetTime", fcn_0040c450, 1, 0);
	fcn_00429ed0("RunScript", fcn_0040c460, 1, 1, 6);
	fcn_00429ed0("RunScriptInt", fcn_0040c4c0, 1, 2, 6, 1);
	fcn_00429ed0("RunScriptInt2", fcn_0040c530, 1, 3, 6, 1, 1);
	fcn_00429ed0("RunScriptString", fcn_0040c5a0, 1, 2, 6, 6);
	fcn_00429ed0("StopScript", fcn_0040c610, 5, 1, 1);
	fcn_00429ed0("Sleep", fcn_0040c630, 5, 1, 1);
	fcn_00429ed0("FindScript", fcn_0040c6c0, 1, 1, 6);
	fcn_00429ed0("KillLocalScripts", fcn_0040c6d0, 1, 0);
	fcn_00429ed0("CallUserFunction", fcn_0040c740, 1, 2, 1, 1);
	fcn_00429ed0("CallUserFunctionExtended", fcn_0040c780, 1, 3, 1, 1, 1);
}
