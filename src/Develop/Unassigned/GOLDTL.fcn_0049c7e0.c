int __cdecl ai_ExecuteAmtAction(int a1, int a2, int a3);

/* ADDRESS: GOLDTL 0x0049c7e0 */
int __cdecl ai_RunUseAmt(int a1, int a2, int a3)
{
	return ai_ExecuteAmtAction(a1, a2, a3) ? 0x27 : 0;
}
