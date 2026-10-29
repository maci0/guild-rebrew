int __cdecl fcn_004f5dd0(int);

/* ADDRESS: GOLDTL 0x004a4680 */
int __cdecl fcn_004a4680(float* o0, float* o1, int idx, char* s, int* p4)
{
	float base;
	float v9;
	float v8;
	float v10;
	float v11;
	char* t;
	int i;
	int found;

	if (p4 != 0) {
		base = (float) *(int*) ((char*) p4 + 0xc);
	} else {
		base = 1.0f;
	}
	v9 = *(float*) (s + 0x10c) - *(float*) 0x662918;
	v9 = v9 * ((float) fcn_004f5dd0(*(int*) (s + 4)) + base);
	*o0 = 0.0f;
	*o1 = 0.0f;
	found = (*(unsigned char*) (idx * 0x94 + 0x10085d0) & *(unsigned char*) (s + 0x218)) == 0;
	if (found) {
		v10 = *(float*) 0x662914;
		v8 = *(float*) 0x662cf8;
	} else {
		v10 = *(float*) 0x662c98;
		v8 = *(float*) 0x662914;
	}
	found = !found;
	if (!found) {
		t = (char*) (idx * 0x94) + 0x1008574;
		for (i = 0; i < 4; i++) {
			if (*(char*) (t - 4) == *(char*) (s + 0x130)
				&& *(float*) t > *(float*) 0x6628a8) {
				found = 1;
				break;
			}
			t += 8;
		}
	}
	if (!found) {
		t = (char*) (idx * 0x94) + 0x10085b4;
		for (i = 0; i < 4; i++) {
			if (*(char*) (t - 4) == *(char*) (s + 0x130)
				&& *(float*) t > *(float*) 0x6628a8) {
				found = 1;
				break;
			}
			t += 8;
		}
	}
	t = (char*) (idx * 0x94) + 0x1008570;
	for (i = 4; i != 0; i--) {
		if (*(float*) (t + 4) <= *(float*) 0x6628a8) {
			v11 = v8;
			if (*(unsigned char*) t == *(unsigned char*) (s + 0x130)) {
				v11 = v10;
			}
			v11 = (*(float*) (t + 4) / v11)
				* *(float*) (s + (*(unsigned char*) t + 0xc) * 0xc);
		} else if (*(unsigned char*) t != *(unsigned char*) (s + 0x130)) {
			v11 = (*(float*) (s + (*(unsigned char*) t + 0xc) * 0xc)
				* *(float*) (t + 4)) / (v8 + v9);
		} else {
			v11 = (*(float*) (s + (*(unsigned char*) t + 0xc) * 0xc)
				* *(float*) (t + 4)) / (v10 + v9);
		}
		*o0 += v11;
		if (*(float*) (t + 0x44) <= *(float*) 0x6628a8) {
			v11 = v8;
			if (*(unsigned char*) (t + 0x40) == *(unsigned char*) (s + 0x130)) {
				v11 = v10;
			}
			v11 = (*(float*) (t + 0x44) / v11)
				* *(float*) (s + (*(unsigned char*) (t + 0x40) + 0xc) * 0xc);
		} else if (*(unsigned char*) (t + 0x40) != *(unsigned char*) (s + 0x130)) {
			v11 = (*(float*) (s + (*(unsigned char*) (t + 0x40) + 0xc) * 0xc)
				* *(float*) (t + 0x44)) / (v8 + v9);
		} else {
			v11 = (*(float*) (s + (*(unsigned char*) (t + 0x40) + 0xc) * 0xc)
				* *(float*) (t + 0x44)) / (v10 + v9);
		}
		*o1 += v11;
		t += 8;
	}
	return found;
}
