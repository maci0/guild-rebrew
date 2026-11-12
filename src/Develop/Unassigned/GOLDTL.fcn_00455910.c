/* ADDRESS: GOLDTL 0x00455910 */
int __cdecl fcn_00455910(int a0, int a1, float* a2)
{
	float corners[32];
	float mn[4];
	float mx[4];

	int* slot;
	int i;
	int rec;
	int base;
	float* p;

	if (*(int*) (a1 + 0x310) == 0) {
		return 0;
	}
	if (*(char*) (a1 + 0x4a0) != 0) {
		mn[0] = 1e10f;
		mn[1] = 1e10f;
		mn[2] = 1e10f;
		mx[0] = -1e10f;
		mx[1] = -1e10f;
		mx[2] = -1e10f;
		slot = (int*) (a1 + 0x390);
		i = 3;
		do {
			if (*slot != 0) {
				rec = *(int*) (*slot + 0x15c);
				base = slot[-0x1a] * 0xc0 + rec;
				if (!(*(float*) (base + 0x3c) > mn[0])) {
					mn[0] = *(float*) (base + 0x3c);
				}
				if (!(*(float*) (base + 0x40) > mn[1])) {
					mn[1] = *(float*) (base + 0x40);
				}
				if (!(*(float*) (base + 0x44) > mn[2])) {
					mn[2] = *(float*) (base + 0x44);
				}
				if (!(*(float*) (base + 0x48) < mx[0])) {
					mx[0] = *(float*) (base + 0x48);
				}
				if (!(*(float*) (base + 0x4c) < mx[1])) {
					mx[1] = *(float*) (base + 0x4c);
				}
				if (!(*(float*) (base + 0x50) < mx[2])) {
					mx[2] = *(float*) (base + 0x50);
				}
				base = slot[-0x19] * 0xc0 + rec;
				if (!(*(float*) (base + 0x3c) > mn[0])) {
					mn[0] = *(float*) (base + 0x3c);
				}
				if (!(*(float*) (base + 0x40) > mn[1])) {
					mn[1] = *(float*) (base + 0x40);
				}
				if (!(*(float*) (base + 0x44) > mn[2])) {
					mn[2] = *(float*) (base + 0x44);
				}
				if (!(*(float*) (base + 0x48) < mx[0])) {
					mx[0] = *(float*) (base + 0x48);
				}
				if (!(*(float*) (base + 0x4c) < mx[1])) {
					mx[1] = *(float*) (base + 0x4c);
				}
				if (!(*(float*) (base + 0x50) < mx[2])) {
					mx[2] = *(float*) (base + 0x50);
				}
			}
			slot += 0x1f;
			i--;
		} while (i != 0);
		corners[0] = mn[0];
		corners[1] = mn[1];
		corners[2] = mn[2];
		corners[4] = mx[0];
		corners[5] = mn[1];
		corners[6] = mn[2];
		corners[8] = mn[0];
		corners[9] = mx[1];
		corners[10] = mn[2];
		corners[12] = mx[0];
		corners[13] = mx[1];
		corners[14] = mn[2];
		corners[16] = mn[0];
		corners[17] = mn[1];
		corners[18] = mx[2];
		corners[20] = mx[0];
		corners[21] = mn[1];
		corners[22] = mx[2];
		corners[24] = mn[0];
		corners[25] = mx[1];
		corners[26] = mx[2];
		corners[28] = mx[0];
		corners[29] = mx[1];
		corners[30] = mx[2];
		for (i = 0; i < 8; i++) {
			p = (float*) (a1 + i * 0x50);
			p[0] = corners[i * 4] * a2[0] + corners[i * 4 + 1] * a2[4] + corners[i * 4 + 2] * a2[8] + a2[0xc];
			p[1] = corners[i * 4] * a2[1] + corners[i * 4 + 1] * a2[5] + corners[i * 4 + 2] * a2[9] + a2[0xd];
			p[2] = corners[i * 4] * a2[2] + corners[i * 4 + 1] * a2[6] + corners[i * 4 + 2] * a2[10] + a2[0xe];
		}
		return a1;
	}
	for (i = 0; i < 8; i++) {
		rec = *(int*) (a1 + 0x318);
		p = (float*) (a1 + i * 0x50);
		p[0] = *(float*) (rec + 0x1fc + i * 0xc) * a2[4] + *(float*) (rec + 0x200 + i * 0xc) * a2[8] + *(float*) (rec + 0x1f8 + i * 0xc) * a2[0] + a2[0xc];
		rec = *(int*) (a1 + 0x318);
		p[1] = *(float*) (rec + 0x1fc + i * 0xc) * a2[5] + *(float*) (rec + 0x200 + i * 0xc) * a2[9] + *(float*) (rec + 0x1f8 + i * 0xc) * a2[1] + a2[0xd];
		rec = *(int*) (a1 + 0x318);
		p[2] = *(float*) (rec + 0x1fc + i * 0xc) * a2[6] + *(float*) (rec + 0x200 + i * 0xc) * a2[10] + *(float*) (rec + 0x1f8 + i * 0xc) * a2[2] + a2[0xe];
	}
	return a1;
}
