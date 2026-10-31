extern float __cdecl gm_GetEntitySkill(char* e, int stat);
extern int __cdecl gm_RandomMod(int);
extern float __cdecl gm_RandomFloat01(void);

/* ADDRESS: GOLDTL 0x004929e0 */
int __cdecl fcn_004929e0(char* a0, char* a1, int a2)
{
	unsigned char* p;
	unsigned char* c;
	unsigned char* tab;
	unsigned char ix;
	unsigned char md;
	int i;
	int n;
	int n0;
	int n1;
	int n2;
	int tier;
	int sum;
	int off;
	int lim;
	int thr;
	int v;
	float f;
	float r;

	p = a1;
	c = a1;
	if (a1 == *(char**) (a0 + 0xc)) {
		p = a0 + 0x18;
		c = a0 + 0x10;
	} else if (a1 == *(char**) (a0 + 0x30)) {
		p = a0 + 0x3c;
		c = a0 + 0x34;
	}
	f = gm_GetEntitySkill(a1, 2);
	ix = (unsigned char) ((int) (f * 100.0f) / 20);
	if (ix >= 4) {
		ix = 4;
	}
	if (a2 != 0) {
		md = (unsigned char) (gm_RandomMod(3) & 0xffff);
		*c = 3;
		if (f > *(float*) 0x6642f8) {
			tier = 3 - (((unsigned short) gm_RandomMod(0x10)) != 0);
		} else if (f > *(float*) 0x6642f4) {
			tier = 2 - (((unsigned short) gm_RandomMod(0x10)) != 0);
		} else {
			tier = 1 - (((unsigned short) gm_RandomMod(f > *(float*) 0x6642f0 ? 4 : 8)) != 0);
		}
		tab = (unsigned char*) 0x6641e8 + ix * 0x18;
		n0 = ix;
		r = gm_RandomFloat01();
		for (i = 0; i < 6; i++) {
			if (r <= *(float*) (tab + i * 4)) {
				n0 = i + 1;
				break;
			}
		}
		n1 = *(int*) &r;
		r = gm_RandomFloat01();
		for (i = 0; i < 6; i++) {
			if (r <= *(float*) (tab + i * 4)) {
				n1 = i + 1;
				break;
			}
		}
		n2 = *(int*) &r;
		r = gm_RandomFloat01();
		for (i = 0; i < 6; i++) {
			if (r <= *(float*) (tab + i * 4)) {
				n2 = i + 1;
				break;
			}
		}
		p[0] = (unsigned char) n0;
		p[1] = (unsigned char) n1;
		p[2] = (unsigned char) n2;
		if (n0 == n1 && n0 == n2) {
			return 0;
		}
		if (tier == 0) {
			return 0;
		}
		if (md == 0) {
			for (i = 0; i < 3 && tier > 0; i++, tier--) {
				n = p[i] + 1;
				if (n > 6) {
					n = 6;
				}
				p[i] = (unsigned char) n;
			}
		} else if (md == 1) {
			v = 6;
			n = -1;
			for (i = 0; i < 3; i++) {
				if (v > p[i]) {
					n = i;
					v = p[i];
				}
			}
			if (n <= -1) {
				return 0;
			}
			v = p[n] + tier;
			if (v > 6) {
				v = 6;
			}
			p[n] = (unsigned char) v;
		} else {
			n = gm_RandomMod(3) & 0xffff;
			v = p[n] + tier;
			if (v > 6) {
				v = 6;
			}
			p[n] = (unsigned char) v;
		}
	} else {
		f = gm_GetEntitySkill(a1, 0);
		r = gm_RandomFloat01();
		sum = 0;
		n = *c;
		for (i = 0; i < n; i++) {
			sum += p[i];
		}
		if (f > *(double*) 0x664180) {
			lim = 12;
			thr = 6;
		} else if (f > *(double*) 0x6642e8) {
			lim = 13;
			thr = 5;
		} else {
			lim = 14;
			thr = 4;
		}
		if (sum > lim) {
			off = -1;
		} else if (sum >= thr) {
			off = (gm_RandomMod(3) & 0xffff) - 1;
		} else {
			off = 1;
		}
		tab = (unsigned char*) 0x6641e8 + ix * 0x18;
		for (i = 0; i < 6; i++) {
			if (r <= *(float*) (tab + i * 4)) {
				n = off + i + 1;
				if (n > 6) {
					n = 6;
				} else if (n < 1) {
					n = 1;
				}
				goto append;
			}
		}
		n = *(unsigned char*) &f;
	append:
		p[*c] = (unsigned char) n;
		*c = *c + 1;
	}
	return 0;
}
