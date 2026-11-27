
// fcn_00508640 — (param1) / table[param2].

/* ADDRESS: GOLDTL 0x0050b7a0 */
int __cdecl gm_AmountToTradeUnits(int a, int b)
{
	return a / *(int*) ((char*) 0x6995bc + b * 4);
}
