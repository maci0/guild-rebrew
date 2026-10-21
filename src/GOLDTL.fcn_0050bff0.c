extern int __cdecl fcn_00502cd0(int handle, ...);
extern int __cdecl fcn_005013c0(void* link);
extern void* __cdecl gm_NextEntityQueryMatch(void);
extern float g_662cf8;

/* Scores an entity's slot chain: matching slot types 2 and 6, plus links of the
 * queried chain that repeat with the same type, scaled by g_662cf8. */
/* ADDRESS: GOLDTL 0x0050bff0 */
int __cdecl fcn_0050bff0(unsigned char* a0)
{
	unsigned char* base;
	unsigned short* slot;
	unsigned short* s;
	unsigned short* p;
	int chain_count;
	int match_count;
	int seen;
	int i;
	int repeats;
	int k;
	int want;
	int handle;
	unsigned int id;
	unsigned int id2;

	chain_count = 0;
	match_count = 0;
	seen = 0;
	i = 0;
	base = (unsigned char*) (*(int*) 0x868050 + *a0 * 0x24d);
	slot = (unsigned short*) (base + 0x23);
	while (i < 0x40) {
		if (*slot == 0)
			break;
		id = *slot & 0x7fff;
		if (seen != 0)
			chain_count += 1;
		if (((unsigned char*) *(int*) 0x99ec10)[id * 0x41] == 2
			|| ((unsigned char*) *(int*) 0x99ec10)[id * 0x41] == 6) {
			seen = 1;
			handle = fcn_00502cd0(*(int*) (a0 + 0x5d), 1, 0, id);
			if (handle != 0) {
				match_count += 1;
				p = (unsigned short*) fcn_00502cd0(*(int*) (handle + 0x14), 1, 5);
				while (p != 0) {
					want = fcn_005013c0(p);
					repeats = 1;
					for (k = i + 1; k < 0x40; k++) {
						s = (unsigned short*) (base + 0x23 + k * 2);
						if (*s == 0)
							break;
						id2 = *s & 0x7fff;
						if (((unsigned char*) *(int*) 0x99ec10)[id2 * 0x41] == 2
							|| ((unsigned char*) *(int*) 0x99ec10)[id2 * 0x41] == 6)
							break;
						if (id2 == *p) {
							chain_count += repeats;
							break;
						}
						if (want != 0 && ((unsigned char*) *(int*) 0x99ec10)[id2 * 0x41] == want)
							repeats += 1;
					}
					p = (unsigned short*) gm_NextEntityQueryMatch();
				}
			}
		}
		i += 1;
		slot += 1;
	}
	return (int) ((double) match_count / (double) chain_count * g_662cf8);
}
