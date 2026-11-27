extern float __cdecl gm_GetEntitySkill(char* e, int stat);
extern unsigned short __cdecl gm_RandomMod(int);
extern float __cdecl gm_RandomFloat01(void);

/* ADDRESS: GOLDTL 0x004929e0 */
void __cdecl ai_RollWirtshausDice(char* gameContext, char* playerEntity, int initialRoll)
{
	unsigned char* dice;
	unsigned char* diceCount;
	unsigned char skillTier;
	int mode;
	int i;
	int n0;
	int n1;
	int n2;
	int tier;
	int sum;
	int off;
	int val;
	float skill;

	if (playerEntity == *(char**) (gameContext + 0xc)) {
		dice = (unsigned char*) (gameContext + 0x18);
		diceCount = (unsigned char*) (gameContext + 0x10);
	} else if (playerEntity == *(char**) (gameContext + 0x30)) {
		dice = (unsigned char*) (gameContext + 0x3c);
		diceCount = (unsigned char*) (gameContext + 0x34);
	} else {
		dice = (unsigned char*) playerEntity;
		diceCount = (unsigned char*) playerEntity;
	}
	skill = gm_GetEntitySkill(playerEntity, 2);
	skillTier = (unsigned char) ((int) (skill * 100.0f) / 20);
	if (skillTier >= 4) {
		skillTier = 4;
	}
	if (initialRoll != 0) {
		float r1;
		float* tab;
		mode = gm_RandomMod(3);
		*diceCount = 3;
		if (skill > 0.8888f) {
			tier = (gm_RandomMod(0x10) == 0) ? 3 : 2;
		} else if (skill > 0.5555f) {
			tier = (gm_RandomMod(0x10) == 0) ? 2 : 1;
		} else if (skill > 0.3333f) {
			tier = (gm_RandomMod(4) == 0) ? 1 : 0;
		} else {
			tier = (gm_RandomMod(8) == 0) ? 1 : 0;
		}
		r1 = gm_RandomFloat01();
		tab = ((float (*)[6]) 0x6641e8)[skillTier];
		for (i = 0; i < 6; i++) {
			if (r1 <= tab[i]) {
				n0 = i + 1;
				break;
			}
		}
		r1 = gm_RandomFloat01();
		for (i = 0; i < 6; i++) {
			if (r1 <= tab[i]) {
				n1 = i + 1;
				break;
			}
		}
		r1 = gm_RandomFloat01();
		for (i = 0; i < 6; i++) {
			if (r1 <= tab[i]) {
				n2 = i + 1;
				break;
			}
		}
		dice[0] = (unsigned char) n0;
		dice[1] = (unsigned char) n1;
		dice[2] = (unsigned char) n2;
		if (n0 == n1 && n0 == n2) {
			return;
		}
		if (tier == 0) {
			return;
		}
		if (mode == 0) {
			for (i = 0; i < 3 && tier != 0; i++, tier--) {
				val = dice[i] + 1;
				if (val > 6) {
					val = 6;
				}
				dice[i] = (unsigned char) val;
			}
		} else if (mode == 1) {
			int minIdx;
			val = 6;
			minIdx = -1;
			for (i = 0; i < 3; i++) {
				if (val > dice[i]) {
					minIdx = i;
					val = dice[i];
				}
			}
			if (minIdx <= -1) {
				return;
			}
			val = dice[minIdx] + tier;
			if (val > 6) {
				val = 6;
			}
			dice[minIdx] = (unsigned char) val;
		} else {
			int idx = gm_RandomMod(3);
			val = dice[idx] + tier;
			if (val > 6) {
				val = 6;
			}
			dice[idx] = (unsigned char) val;
		}
	} else {
		float r2;
		float* tab;
		unsigned char die;
		skill = gm_GetEntitySkill(playerEntity, 0);
		r2 = gm_RandomFloat01();
		sum = 0;
		for (i = 0; i < *diceCount; i++) {
			sum += dice[i];
		}
		if (skill > 0.66) {
			if (sum > 12) {
				off = -1;
			} else if (sum < 6) {
				off = 1;
			} else {
				off = gm_RandomMod(3) - 1;
			}
		} else if (skill > 0.44) {
			if (sum > 13) {
				off = -1;
			} else if (sum < 5) {
				off = 1;
			} else {
				off = gm_RandomMod(3) - 1;
			}
		} else {
			if (sum > 14) {
				off = -1;
			} else if (sum < 4) {
				off = 1;
			} else {
				off = gm_RandomMod(3) - 1;
			}
		}
		tab = ((float (*)[6]) 0x6641e8)[skillTier];
		for (i = 0; i < 6; i++) {
			if (r2 <= tab[i]) {
				val = off + i + 1;
				if (val < 6) {
					if (val <= 1) {
						val = 1;
					}
				}
				if (val >= 6) {
					val = 6;
				}
				die = (unsigned char) val;
				break;
			}
		}
		dice[*diceCount] = die;
		*diceCount = *diceCount + 1;
	}
}
