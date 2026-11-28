
// fcn_00508620 — (param1) * table[param2].

/* ADDRESS: GOLDTL 0x0050b780 */
/* ADDRESS: GOLDDE 0x004f67f0 */
int __cdecl gm_TradeUnitsToAmount(int a, int b)
{
	return a * *(int*) ((char*) 0x6995bc + b * 4);
}
