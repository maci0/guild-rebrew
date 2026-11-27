int __cdecl gm_CalculateGebaeudeValue(int, int);


/* ADDRESS: GOLDTL 0x004a48a0 */
int __cdecl gm_CalcBuildingRepairCost(int building, int kind)
{
	int n;

	building = gm_CalculateGebaeudeValue(building, 100);
	n = (int) (building * 0.005f);
	if (kind == 50)
		n *= 4;
	else if (kind == 30)
		n *= 2;
	else if (kind != 10)
		n = 0;
	return n;
}
