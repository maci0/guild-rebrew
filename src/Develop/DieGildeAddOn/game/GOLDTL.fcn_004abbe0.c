// SIZE 0x24c
typedef struct Kind {
	unsigned char type;
	char pad1[0x246];
	unsigned char cap;
	char pad248[0x24d - 0x248];
} Kind;

extern unsigned char* lpGebaeudePROT;
extern unsigned char* lpGebaeudeINST;

int __cdecl gm_CheckStatLevel(int, int);
char* __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl fcn_0057c9d0(unsigned char*);
unsigned short __cdecl gm_RandomMod(unsigned short);


/* ADDRESS: GOLDTL 0x004abbe0 */
int __cdecl fcn_004abbe0(int a1, unsigned short* a2, int a3, char* a4)
{
	int lvl;
	int best;
	int v;
	int r;
	int t;
	unsigned char* e;
	unsigned char* found;
	Kind* kind;

	lvl = gm_CheckStatLevel(*a2, 0xe);
	best = 0;
	if ((a1 != 0x46 && a1 != 0) || a3 != 0 || lvl == 0
	    || *((unsigned char*) a2 + 2) == 3 || *(int*) ((char*) a2 + 0x194) < 2)
		return 0;
	e = lpGebaeudeINST;
	found = 0;
	for (a1 = 0x100; a1 != 0; a1--, e += 0xa9) {
		if (e[0] == 0 || *(unsigned short*) (e + 0x27) != *a2)
			continue;
		kind = &((Kind*)lpGebaeudePROT)[e[0]];
		if (kind->type != 0x1f)
			continue;
		if (fcn_00502cd0(*(int*) (e + 0x5d), 2, 6, 0, 0x27f) == 0)
			continue;
		if (fcn_0057c9d0(e) != 0)
			continue;
		if (found == 0) {
			best = kind->cap == 2 ? 7 : 4;
			found = e;
		} else {
			v = kind->cap == 2 ? 7 : 4;
			if (v > best) {
				best = v;
				found = e;
			}
		}
	}
	if (found == 0 || best == 0)
		return 0;
	if (*(int*) ((char*) a2 + 0x194) >= 4) {
		if (best >= 10)
			best = 10;
	} else if (*(int*) ((char*) a2 + 0x194) >= 3) {
		if (best >= 7)
			best = 7;
	} else if (best >= 4) {
		best = 4;
	}
	r = gm_RandomMod(best);
	if (r < 4)
		t = 2;
	else
		t = (r >= 7) + 3;
	*(int*) (a4 + 4) = *(int*) (found + 1);
	*(int*) (a4 + 0xc) = r;
	*(int*) (a4 + 0x10) = t;
	a4[0] = 7;
	return 0x46;
}
