void __cdecl cm_RequestModifyHealth(int, int);

/* ADDRESS: GOLDTL 0x005100f0 */
void __cdecl fcn_005100f0(int id, int amount)
{
	cm_RequestModifyHealth(id, amount);
}
