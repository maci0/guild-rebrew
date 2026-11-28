


extern float g_6652d8[];

int __cdecl gv_CalcGravePrice(int, int, int, int, int*);

/* ADDRESS: GOLDDE 0x004e0610 */
int __cdecl gv_CalcGraveUpgradePrice(int entity, int currentTier, int targetTier, int* ownerShareOut)
{
	int first;
	int result;

	first = gv_CalcGravePrice(entity, 100, currentTier, 1, &currentTier);
	result = gv_CalcGravePrice(entity, 100, targetTier, 1, &currentTier) - first / 2;
	*ownerShareOut = (int) (result * g_6652d8[targetTier]);
	return result;
}
