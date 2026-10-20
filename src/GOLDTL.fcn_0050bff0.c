extern int __cdecl fcn_00502cd0(int handle, ...);
extern int __cdecl fcn_005013c0(void* link);
extern void* __cdecl gm_NextEntityQueryMatch(void);

/* Scores an entity's 0x40 slot chain: matching slot types 2 and 6, plus links
 * of the queried chain that repeat with the same type, scaled by 0x662cf8. */
/* ADDRESS: GOLDTL 0x0050bff0 */
int __cdecl fcn_0050bff0(unsigned char* a0)
{
	unsigned short* slots;
	unsigned short* p;
	unsigned short* q;
	unsigned char* types;
	int match_count;
	int chain_count;
	int repeats;
	int i;
	int k;
	int seen;
	int handle;
	int want;
	unsigned int id;

	types = (unsigned char*) *(int*) 0x99ec10;
	slots = (unsigned short*) (*(int*) 0x868050 + *a0 * 0x24d + 0x23);
	match_count = 0;
	chain_count = 0;
	seen = 0;
	i = 0;
	do {
		if (*slots == 0)
			break;
		id = *slots & 0x7fff;
		if (seen != 0)
			chain_count += 1;
		if (types[id * 0x41] == 2 || types[id * 0x41] == 6) {
			seen = 1;
			handle = fcn_00502cd0(*(int*) (a0 + 0x5d), 1, 0, id);
			if (handle != 0) {
				match_count += 1;
				p = (unsigned short*) fcn_00502cd0(*(int*) (handle + 0x14), 1, 5);
				while (p != 0) {
					want = fcn_005013c0(p);
					repeats = 1;
					k = i + 1;
					if (k <= 0x3f) {
						q = slots + k;
						do {
							if (*q == 0)
								break;
							if (types[(*q & 0x7fff) * 0x41] == 2 ||
							    types[(*q & 0x7fff) * 0x41] == 6)
								break;
							if ((*q & 0x7fff) == *p) {
								match_count += repeats;
								break;
							}
							if (want != 0 && types[(*q & 0x7fff) * 0x41] == want)
								repeats += 1;
							k += 1;
							q += 1;
						} while (k < 0x40);
					}
					p = (unsigned short*) gm_NextEntityQueryMatch();
				}
			}
		}
		i += 1;
		slots += 1;
	} while (i < 0x40);
	return (int) ((double) match_count / (double) chain_count * *(float*) 0x662cf8);
}
