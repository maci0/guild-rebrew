extern float __cdecl gm_GetEntitySkill(char* e, int stat);
extern unsigned short __cdecl gm_RandomMod(int);
extern float __cdecl gm_RandomFloat01(void);

/* ADDRESS: GOLDTL 0x004929e0 */
void __cdecl fcn_004929e0(char* gameContext, char* playerEntity, int initialRoll)
{
	unsigned char* p;
	unsigned char* c;
	unsigned char ix;
	int md;
	int i;
	int n0;
	int n1;
	int n2;
	int tier;
	int sum;
	int off;
	int v;
	float f;

	if (playerEntity == *(char**) (gameContext + 0xc)) {
		p = (unsigned char*) (gameContext + 0x18);
		c = (unsigned char*) (gameContext + 0x10);
	} else if (playerEntity == *(char**) (gameContext + 0x30)) {
		p = (unsigned char*) (gameContext + 0x3c);
		c = (unsigned char*) (gameContext + 0x34);
	} else {
		p = (unsigned char*) playerEntity;
		c = (unsigned char*) playerEntity;
	}
	f = gm_GetEntitySkill(playerEntity, 2);
	ix = (unsigned char) ((int) (f * 100.0f) / 20);
	if (ix >= 4) {
		ix = 4;
	}
	if (initialRoll != 0) {
		float r1;
		float* tab;
		md = gm_RandomMod(3);
		*c = 3;
		if (f > 0.8888f) {
			tier = (gm_RandomMod(0x10) == 0) ? 3 : 2;
		} else if (f > 0.5555f) {
			tier = (gm_RandomMod(0x10) == 0) ? 2 : 1;
		} else if (f > 0.3333f) {
			tier = (gm_RandomMod(4) == 0) ? 1 : 0;
		} else {
			tier = (gm_RandomMod(8) == 0) ? 1 : 0;
		}
		r1 = gm_RandomFloat01();
		tab = ((float (*)[6]) 0x6641e8)[ix];
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
		p[0] = (unsigned char) n0;
		p[1] = (unsigned char) n1;
		p[2] = (unsigned char) n2;
		if (n0 == n1 && n0 == n2) {
			return;
		}
		if (tier == 0) {
			return;
		}
		if (md == 0) {
			for (i = 0; i < 3 && tier != 0; i++, tier--) {
				v = p[i] + 1;
				if (v > 6) {
					v = 6;
				}
				p[i] = (unsigned char) v;
			}
		} else if (md == 1) {
			int minIdx;
			v = 6;
			minIdx = -1;
			for (i = 0; i < 3; i++) {
				if (v > p[i]) {
					minIdx = i;
					v = p[i];
				}
			}
			if (minIdx <= -1) {
				return;
			}
			v = p[minIdx] + tier;
			if (v > 6) {
				v = 6;
			}
			p[minIdx] = (unsigned char) v;
		} else {
			int idx = gm_RandomMod(3);
			v = p[idx] + tier;
			if (v > 6) {
				v = 6;
			}
			p[idx] = (unsigned char) v;
		}
	} else {
		float r2;
		float* tab;
		unsigned char die;
		f = gm_GetEntitySkill(playerEntity, 0);
		r2 = gm_RandomFloat01();
		sum = 0;
		for (i = 0; i < *c; i++) {
			sum += p[i];
		}
		if (f > 0.66) {
			if (sum > 12) {
				off = -1;
			} else if (sum < 6) {
				off = 1;
			} else {
				off = gm_RandomMod(3) - 1;
			}
		} else if (f > 0.44) {
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
		tab = ((float (*)[6]) 0x6641e8)[ix];
		for (i = 0; i < 6; i++) {
			if (r2 <= tab[i]) {
				v = off + i + 1;
				if (v < 6) {
					if (v <= 1) {
						v = 1;
					}
				}
				if (v >= 6) {
					v = 6;
				}
				die = (unsigned char) v;
				break;
			}
		}
		p[*c] = die;
		*c = *c + 1;
	}
}
