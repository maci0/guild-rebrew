/* ADDRESS: GOLDTL 0x00455910 */
int __cdecl fcn_00455910(int a0, int a1, float* a2)
{
	float corners[32];
	float minx;
	float miny;
	float minz;
	float maxx;
	float maxy;
	float maxz;
	int* slot;
	int i;
	int rec;
	int base;
	float* p;

	if (*(int*) (a1 + 0x310) == 0) {
		return 0;
	}
	if (*(char*) (a1 + 0x4a0) != 0) {
		minx = 1e10f;
		miny = 1e10f;
		minz = 1e10f;
		maxx = -1e10f;
		maxy = -1e10f;
		maxz = *(float*) 0x662c6c;
		slot = (int*) (a1 + 0x390);
		i = 3;
		do {
			if (*slot != 0) {
				rec = *(int*) (*slot + 0x15c);
				base = slot[-0x1a] * 0xc0 + rec;
				if (*(float*) (base + 0x3c) <= minx) {
					minx = *(float*) (base + 0x3c);
				}
				if (*(float*) (base + 0x40) <= miny) {
					miny = *(float*) (base + 0x40);
				}
				if (*(float*) (base + 0x44) <= minz) {
					minz = *(float*) (base + 0x44);
				}
				if (maxx <= *(float*) (base + 0x48)) {
					maxx = *(float*) (base + 0x48);
				}
				if (maxy <= *(float*) (base + 0x4c)) {
					maxy = *(float*) (base + 0x4c);
				}
				if (maxz <= *(float*) (base + 0x50)) {
					maxz = *(float*) (base + 0x50);
				}
				base = slot[-0x19] * 0xc0 + rec;
				if (*(float*) (base + 0x3c) <= minx) {
					minx = *(float*) (base + 0x3c);
				}
				if (*(float*) (base + 0x40) <= miny) {
					miny = *(float*) (base + 0x40);
				}
				if (*(float*) (base + 0x44) <= minz) {
					minz = *(float*) (base + 0x44);
				}
				if (maxx <= *(float*) (base + 0x48)) {
					maxx = *(float*) (base + 0x48);
				}
				if (maxy <= *(float*) (base + 0x4c)) {
					maxy = *(float*) (base + 0x4c);
				}
				if (maxz <= *(float*) (base + 0x50)) {
					maxz = *(float*) (base + 0x50);
				}
			}
			slot += 0x1f;
			i--;
		} while (i != 0);
		corners[0] = minx;
		corners[1] = miny;
		corners[2] = minz;
		corners[4] = maxx;
		corners[5] = miny;
		corners[6] = minz;
		corners[8] = minx;
		corners[9] = maxy;
		corners[10] = minz;
		corners[12] = maxx;
		corners[13] = maxy;
		corners[14] = minz;
		corners[16] = minx;
		corners[17] = miny;
		corners[18] = maxz;
		corners[20] = maxx;
		corners[21] = miny;
		corners[22] = maxz;
		corners[24] = minx;
		corners[25] = maxy;
		corners[26] = maxz;
		corners[28] = maxx;
		corners[29] = maxy;
		corners[30] = maxz;
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
