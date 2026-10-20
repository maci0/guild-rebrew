/* Native body also loads the 6th argument into EDX before the call; that
 * register argument is not reachable from C at a cdecl call site. */
int __cdecl fcn_0060fc6e(int a1, int a2, int a3, int a4, int a5, int a6,
                         int a7, int a8);

#pragma optimize("s", on)
#pragma optimize("y", off)

/* ADDRESS: GOLDTL 0x0060ffe8 */
int __stdcall fcn_0060ffe8(int a1, int a2, int a3, int a4, int a5, int a6,
                           int a7, int a8)
{
	return fcn_0060fc6e(a1, a2, a3, a4, a5, a7, a8, 4);
}
