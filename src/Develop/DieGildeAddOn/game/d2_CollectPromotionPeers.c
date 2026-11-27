int __cdecl amt_ListPromotionOffices(unsigned char* a1, int max, int* out);
int __cdecl d2_BuildPersonStatusDesc(void* sel);
int __cdecl gm_MatchesTargetFilter(unsigned short a, unsigned short b, int c, int d);

/* ADDRESS: GOLDTL 0x005cc100 */
int __cdecl d2_CollectPromotionPeers(char* entity, unsigned int capacity, char* results, int query)
{
	int n;
	int i;
	int ids[4];
	char* ent;
	char* out;
	int count;

	count = 0;
	if (*(char*) (entity + 0x166) == 0) {
		return 0;
	}
	n = amt_ListPromotionOffices((unsigned char*) entity, 4, ids);
	if (n == 0) {
		return 0;
	}
	if (capacity == 0) {
		ent = (char*) 0x7f4e08;
		do {
			if (*ent != 0) {
				i = 0;
				if (n > 0) {
					do {
						if (ids[i] == (int) (unsigned char) *ent) {
							count++;
							break;
						}
						i++;
					} while (i < n);
				}
			}
			ent += 0x21c;
		} while ((int) ent < 0x85a208);
		return count;
	}
	i = 0;
	if (n > 0) {
		do {
			if ((unsigned int) count >= capacity) {
				break;
			}
			out = results + count * 0x38;
			ent = (char*) 0x7f4ca0;
			do {
				if (ids[i] == (int) (unsigned char) ent[0x168]) {
					*(char**) out = ent;
					*(int*) (out + 0x34) = ids[i];
					d2_BuildPersonStatusDesc(out);
					*(int*) (out + 0x30) = gm_MatchesTargetFilter(*(unsigned short*) entity,
						*(unsigned short*) *(char**) out, query, 0);
					count++;
					out += 0x38;
					if ((unsigned int) count >= capacity) {
						break;
					}
				}
				ent += 0x21c;
			} while ((int) ent < 0x85a0a0);
			i++;
		} while (i < n);
	}
	return count;
}
