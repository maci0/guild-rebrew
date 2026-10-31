unsigned char* __cdecl gm_LookupEntityRecordById(int id);

/* ADDRESS: GOLDTL 0x004f65a0 */
void* __cdecl fcn_004f65a0(unsigned char* a1, int cap, int* out, int* out_count)
{
	int counts[0x300];
	unsigned char* groups[0x300];
	unsigned char* list[0x200];
	unsigned char* best;
	int group_count;
	int n_saved;
	int best_count;
	int n;
	int group_limit;
	int off;
	int i;
	int k;
	int j;
	unsigned char* ent;
	unsigned char* rec;
	int id;

	*out_count = 0;
	for (i = 0; i < 0x300; i++) {
		groups[i] = 0;
	}
	for (i = 0; i < 0x300; i++) {
		counts[i] = 0;
	}
	n = 0;
	group_count = 0;
	best_count = 0;
	best = 0;
	group_limit = 1;
	id = *(int*) (a1 + 4);
	for (off = 0; off < 0x5a00; off += 0x2d) {
		if (*(int*) (0x9a3825 + off) == 0) {
			continue;
		}
		if (*(int*) (0x9a3816 + off) == id) {
			continue;
		}
		ent = gm_LookupEntityRecordById(*(int*) (0x9a3816 + off));
		if (ent == 0) {
			continue;
		}
		for (rec = (unsigned char*) 0x99f804; rec < (unsigned char*) 0x9a3804; rec += 8) {
			if (*(int*) (rec - 4) == id && *(int*) rec == *(int*) (0x9a3800 + off)) {
				goto next;
			}
		}
		list[n] = (unsigned char*) (0x9a3800 + off);
		n++;
		for (k = 0; k < group_limit; k++) {
			if (k >= 0x300) {
				break;
			}
			if (groups[k] == 0) {
				groups[k] = ent;
				counts[k] = counts[k] + 1;
				group_count = group_limit;
				group_limit++;
				break;
			}
			if (*(int*) (groups[k] + 4) == *(int*) (ent + 4)) {
				counts[k] = counts[k] + 1;
				break;
			}
		}
next:
		;
	}
	if (n == 0) {
		return 0;
	}
	n_saved = n;
	if (group_count == 0) {
		return 0;
	}
	for (i = 0; i < group_count; i++) {
		if (counts[i] > best_count) {
			best = groups[i];
			best_count = counts[i];
		}
	}
	k = 0;
	for (j = 0; j < n_saved; j++) {
		if (k >= cap) {
			break;
		}
		rec = list[j];
		if (*(int*) (rec + 0x16) == *(int*) (best + 4)) {
			out[k] = *(int*) rec;
			k++;
		}
	}
	*out_count = k;
	return best;
}
