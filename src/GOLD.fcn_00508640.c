/* ADDRESS: GOLD 0x00508640 */
// fcn_00508640 — (param1) / table[param2].

int __cdecl fcn_00508640(int a, int b)
{
	return a / *(int*) ((char*) 0x61a88c + b * 4);
}
