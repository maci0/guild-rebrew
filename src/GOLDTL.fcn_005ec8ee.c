/* D3DX8 external band. Native is __stdcall with five arguments (ret 0x14):
 * it enables a runtime mode through 0x00613478 and forwards to the function
 * pointer stored at 0x006ad6dc. The native call site loads the float argument
 * through the x87 stack (fld [ebp+0xc]; push ecx; fstp [esp]); this build
 * pushes the raw slot instead, so bytes 10.. diverge. The stored 80-byte
 * extent merges this 39-byte body, the 35-byte member at 0x5ec915 and the
 * 6-byte import thunk at 0x5ec938.
 * Note: the metadata row for 0x00613478 records a cdecl symbol but the callee
 * ends in ret 4, so it is declared __stdcall here. */
int __stdcall fcn_00613478(int flag);

#pragma optimize("y", off)

/* ADDRESS: GOLDTL 0x005ec8ee */
int __stdcall fcn_005ec8ee(int a1, float a2, int a3, int a4, int a5)
{
	fcn_00613478(1);
	return (*(int (__stdcall **)(int, float, int, int, int)) 0x6ad6dc)(
		a1, a2, a3, a4, a5);
}
