


extern float g_665370;

char* __cdecl gm_QueryEntities(int obj, int mode, ...);

/* ADDRESS: GOLDDE 0x004df8c0 */
float __cdecl gv_CalcDecayReduction(char* graveyard)
{
	int sum;

	sum = 0;
	if (gm_QueryEntities(*(int*) (graveyard + 0x5d), 2, 6, 0, 0x1ff) != 0) {
		sum = 10;
	}
	if (gm_QueryEntities(*(int*) (graveyard + 0x5d), 2, 6, 0, 0x202) != 0) {
		sum += 10;
	}
	if (gm_QueryEntities(*(int*) (graveyard + 0x5d), 2, 6, 0, 0x208) != 0) {
		sum += 10;
	}
	if (gm_QueryEntities(*(int*) (graveyard + 0x5d), 2, 6, 0, 0x20d) != 0) {
		sum += 15;
	}
	if (gm_QueryEntities(*(int*) (graveyard + 0x5d), 2, 6, 0, 0x214) != 0) {
		sum += 10;
	}
	if (gm_QueryEntities(*(int*) (graveyard + 0x5d), 2, 6, 0, 0x216) != 0) {
		sum += 10;
	}
	if (gm_QueryEntities(*(int*) (graveyard + 0x5d), 2, 6, 0, 0x219) != 0) {
		sum += 15;
	}
	return sum * g_665370;
}
