int __cdecl FindStraftatIndexById(int key);

/* ADDRESS: GOLDTL 0x004f61c0 */
int __cdecl fcn_004f61c0(int* groupIds, int* flagCounts, int* totals, unsigned int entityIndex)
{
	int found[0x200];
	int* vp;
	int i;
	int idx;
	int n;
	int total;
	int cnt;
	int flagcnt;
	int group_id;
	int slot_id;
	int pos;
	int tmp;
	unsigned char* rec;
	unsigned char* p;

	for (i = 0; i < 0x20; i++) {
		groupIds[i] = -1;
	}
	total = 0;
	for (i = 0; i < 0x20; i++) {
		flagCounts[i] = 0;
	}
	for (i = 0; i < 0x20; i++) {
		totals[i] = 0;
	}
	for (i = 0; i < 0x200; i++) {
		found[i] = 0;
	}
	slot_id = *(int*) (0x7f4ca0 + (entityIndex & 0xffff) * 0x21c + 4);
	n = 0;
	for (p = (unsigned char*) 0x99f804; (int) p < 0x9a3804; p += 8) {
		if (*(int*) (p - 4) != slot_id) {
			continue;
		}
		pos = FindStraftatIndexById(*(int*) p);
		if (pos == -1) {
			continue;
		}
		rec = (unsigned char*) (0x9a3800 + pos * 0x2d);
		if (*(unsigned int*) (rec + 0x25) <= 0) {
			continue;
		}
		found[n] = (int) rec;
		n++;
	}
	if (n < 1) {
		return total;
	}
	idx = 1;
	vp = found;
	while (idx - 1 < n) {
		rec = (unsigned char*) *vp;
		flagcnt = 0;
		if (rec != 0) {
			group_id = *(int*) (rec + 0x16);
			total++;
			cnt = 1;
			if (*(int*) (rec + 0x25) == 1) {
				flagcnt = 1;
			}
			for (i = idx; i < 0x200; i++) {
				p = (unsigned char*) found[i];
				if (p == 0) {
					continue;
				}
				if (*(int*) (p + 0x16) != *(int*) (rec + 0x16)) {
					continue;
				}
				cnt++;
				if (*(int*) (p + 0x25) == 1) {
					flagcnt++;
				}
				found[i] = 0;
			}
			*vp = 0;
			if (cnt > flagCounts[0x1f]) {
				flagCounts[0x1f] = flagcnt;
				totals[0x1f] = cnt;
				groupIds[0x1f] = group_id;
			}
			for (i = 0x1e; i >= 0; i--) {
				if (totals[i] < totals[i + 1]) {
					tmp = totals[i];
					totals[i] = totals[i + 1];
					totals[i + 1] = tmp;
					tmp = flagCounts[i];
					flagCounts[i] = flagCounts[i + 1];
					flagCounts[i + 1] = tmp;
					tmp = groupIds[i];
					groupIds[i] = groupIds[i + 1];
					groupIds[i + 1] = tmp;
				}
			}
		}
		idx++;
		vp++;
	}
	if (total > 0x20) {
		return 0x20;
	}
	return total;
}
