/* ADDRESS: GOLDTL 0x0047cf60 */

void __cdecl fcn_0047cf60(char* p)
{
	double v;
	float best;
	int besti;
	int i;

	v = *(float*) (p + 0x124) + *(float*) (p + 0x12c) - *(float*) (p + 0x128) * *(float*) (p + 0x12c);
	if (v < 0.0 || v < 1000.0) {
		if (v < 0.0) {
			v = 0.0;
		}
	} else {
		v = 1000.0;
	}
	*(float*) (p + 0x12c) = v;
	best = 0;
	besti = 0;
	for (i = 0; i < 13; i++) {
		if (i != *(unsigned char*) (p + 0x130)) {
			if (i == 1) {
				*(int*) (p + 0x9c) = 0;
			} else if (i == 0 && *(int*) (p + 0x194) > 6) {
				*(int*) (p + 0x90) = 0;
			} else if (i == 2 && (*(int*) (p + 0x170) != 0 || *(unsigned char*) (p + 2) == 3)) {
				*(int*) (p + 0xa8) = 0;
			} else if (i == 3) {
				v = (*(float*) (p + 0x1e4) * *(float*) (p + 0xac) + *(float*) (p + 0xb4)) - *(float*) (p + 0xb0) * *(float*) (p + 0xb4);
				if (v < 0.0 || v < 1000.0) {
					if (v < 0.0) {
						v = 0.0;
					}
				} else {
					v = 1000.0;
				}
				*(float*) (p + 0xb4) = v;
			} else {
				v = (*(float*) (p + 0x88 + i * 12) + *(float*) (p + 0x90 + i * 12)) - *(float*) (p + 0x8c + i * 12) * *(float*) (p + 0x90 + i * 12);
				if (v < 0.0 || v < 1000.0) {
					if (v < 0.0) {
						v = 0.0;
					}
				} else {
					v = 1000.0;
				}
				*(float*) (p + 0x90 + i * 12) = v;
			}
		}
		if (i != *(unsigned char*) (p + 0x130)) {
			if (*(float*) (p + 0x90 + i * 12) >= best) {
				best = *(float*) (p + 0x90 + i * 12);
				besti = i;
			}
		} else {
			v = (2.0 - *(float*) (p + 0x12c) * 0.002) * *(float*) (p + 0x90 + i * 12);
			if (v >= best) {
				best = v;
				besti = i;
			}
		}
	}
	if (besti != *(unsigned char*) (p + 0x130)) {
		if (*(float*) (p + 0x90 + *(unsigned char*) (p + 0x130) * 12) >= 1000.0f) {
			*(float*) (p + 0x90 + *(unsigned char*) (p + 0x130) * 12) -= 50.0f;
		}
		*(unsigned char*) (p + 0x130) = besti;
		*(float*) (p + 0x12c) = 0;
	}
}
