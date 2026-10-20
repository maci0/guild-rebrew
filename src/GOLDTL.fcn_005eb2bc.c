/* ADDRESS: GOLDTL 0x005eb2bc */

/* The 40-byte inventory extent is not one function. It holds two bodies: a
 * thunk (push ebp; mov ebp,esp; push 1; call 0x613478; pop ebp;
 * jmp [0x6ad670]) and a 24-byte thiscall method that scales a two-float
 * vector at self+0 and self+4 by 1/arg and ends in ret 4. The metadata
 * symbol is _fcn_005eb2bc@12, which matches neither body's argument count,
 * so no body is reconstructed here. */
int __stdcall fcn_005eb2bc(int a1, int a2, int a3)
{
	return 0;
}
