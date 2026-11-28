void __cdecl cm_RequestModifyHealth(int, int);

/* ADDRESS: GOLDTL 0x005100f0 */
/* ADDRESS: GOLDDE 0x004fadc0 */
void __cdecl gm_ModifyHealth(int id, int amount)
{
	cm_RequestModifyHealth(id, amount);
}
