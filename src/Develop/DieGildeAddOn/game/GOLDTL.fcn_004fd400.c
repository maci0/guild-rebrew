int __cdecl gm_WalkEntityChain(int idx);

/* ADDRESS: GOLDTL 0x004fd400 */
int __cdecl fcn_004fd400(short* out, int* value)
{
	int* rec;
	int now;
	int limit;
	int best;
	int i;
	int v;
	unsigned char* p;

	rec = *(int**) 0x773d5c;
	now = *(int*) 0x7f4c00;
	best = -100000;
	limit = 0xffff;
	if (rec == 0 || *(int*) 0x69643c < now || *(short*) rec == -1 || ((unsigned char*) rec)[8] == 0) {
		*(int*) 0x69643c = now;
		p = (unsigned char*) 0x7f4ca2;
		i = 0;
		while ((int) p < 0x85a0a2) {
			if (*(short*) (p - 2) != -1 && *p < 0xa && p[6] > 0) {
				v = gm_WalkEntityChain(i);
				if (v > best) {
					best = v;
					limit = i;
				}
			}
			p += 0x21c;
			i++;
		}
		if (limit == 0xffff) {
			*(int**) 0x773d5c = 0;
			*(int*) 0x696440 = 0xc80;
		} else {
			rec = (int*) (0x7f4ca0 + limit * 0x21c);
			*(int*) 0x696440 = best;
			*(int**) 0x773d5c = rec;
		}
	}
	if (rec != 0) {
		*out = *(short*) rec;
		*value = *(int*) 0x696440;
		return 1;
	}
	*out = -1;
	*value = *(int*) 0x696440;
	return 0;
}
