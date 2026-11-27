


extern float g_6652d8[];

int __cdecl gm_CalcBribeOrPriceScore(int, int, int, int, int*);

int __cdecl gv_CalcGraveUpgradePrice(int entity, int currentTier, int targetTier, int* ownerShareOut)
{
	int first;
	int result;

	first = gm_CalcBribeOrPriceScore(entity, 100, currentTier, 1, &currentTier);
	result = gm_CalcBribeOrPriceScore(entity, 100, targetTier, 1, &currentTier) - first / 2;
	*ownerShareOut = (int) (result * g_6652d8[targetTier]);
	return result;
}
