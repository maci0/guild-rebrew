struct frame_431330 {
	char pad0[4];
	int len;
	char pad8[0x18];
	float pos[3];
	char pad2c[0x94];
};
// SIZE 0xc0

void __cdecl fcn_00438b40(char* node, float* v);

#define FRAMES_431330(an) (*(struct frame_431330**) (*(char**) ((an) + 0x68) + 0x15c))

/* ADDRESS: GOLDTL 0x00431330 */
void __cdecl fcn_00431330(char* node, char* an, int t, int key, int flags)
{
	int cur;
	int curt;
	int keylen;
	int curlen;
	int i;
	float f;
	float d[4];
	float acc[4];

	keylen = FRAMES_431330(an)[key].len;
	cur = *(int*) (an + 0xc);
	curt = *(int*) (an + 0x10);
	curlen = FRAMES_431330(an)[cur].len;
	if (t == curt && key == cur) {
		return;
	}
	if ((flags & 1) == 1) {
		if (cur < key) {
			f = 1.0f - (float) curt / curlen;
			d[0] = FRAMES_431330(an)[cur + 1].pos[0] - FRAMES_431330(an)[cur].pos[0];
			d[1] = FRAMES_431330(an)[cur + 1].pos[1] - FRAMES_431330(an)[cur].pos[1];
			d[2] = FRAMES_431330(an)[cur + 1].pos[2] - FRAMES_431330(an)[cur].pos[2];
			acc[0] = d[0] * f;
			acc[1] = d[1] * f;
			acc[2] = d[2] * f;
		} else {
			acc[0] = 0.0f;
			acc[1] = 0.0f;
			acc[2] = 0.0f;
		}
		for (i = cur + 1; i < key; i++) {
			d[0] = FRAMES_431330(an)[i + 1].pos[0] - FRAMES_431330(an)[i].pos[0];
			d[1] = FRAMES_431330(an)[i + 1].pos[1] - FRAMES_431330(an)[i].pos[1];
			d[2] = FRAMES_431330(an)[i + 1].pos[2] - FRAMES_431330(an)[i].pos[2];
			acc[0] += d[0];
			acc[1] += d[1];
			acc[2] += d[2];
		}
		f = (cur == key ? (float) (t - curt) : (float) t) / keylen;
		d[0] = FRAMES_431330(an)[key + 1].pos[0] - FRAMES_431330(an)[key].pos[0];
		d[1] = FRAMES_431330(an)[key + 1].pos[1] - FRAMES_431330(an)[key].pos[1];
		d[2] = FRAMES_431330(an)[key + 1].pos[2] - FRAMES_431330(an)[key].pos[2];
		d[0] *= f;
		d[1] *= f;
		d[2] *= f;
		acc[0] += d[0];
		acc[1] += d[1];
		acc[2] += d[2];
		d[0] = acc[2] * *(float*) (node + 0x1ac) + acc[1] * *(float*) (node + 0x19c) + acc[0] * *(float*) (node + 0x18c);
		d[1] = acc[2] * *(float*) (node + 0x1b0) + acc[1] * *(float*) (node + 0x1a0) + acc[0] * *(float*) (node + 0x190);
		d[2] = acc[2] * *(float*) (node + 0x1b4) + acc[1] * *(float*) (node + 0x1a4) + acc[0] * *(float*) (node + 0x194);
		d[0] += *(float*) (node + 0x4c);
		d[1] += *(float*) (node + 0x50);
		d[2] += *(float*) (node + 0x54);
		fcn_00438b40(node, d);
	}
	*(int*) (an + 0xc) = key;
	*(int*) (an + 0x10) = t;
}
