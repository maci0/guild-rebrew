// FUNCTION: GOLDTL 0x005b56e0
// SIZE: 101

// SIZE 0x1c
typedef struct {
	int id;
	int f4;
	int f8;
	int fc;
	int f10;
	int f14;
	unsigned short level;
	short pad;
} Offer;

extern Offer g_6abb08[];
extern int g_6ac240;

unsigned short __cdecl fcn_0042e410(unsigned short);

unsigned short __cdecl fcn_005b56e0(int lo, int hi)
{
	int r;
	int n;
	int k;
	Offer* o;

	r = fcn_0042e410((unsigned short) g_6ac240);
	n = g_6ac240;
	k = n;
	while (k != 0) {
		o = &g_6abb08[r];
		if (o->level >= lo && o->level <= hi) {
			return (unsigned short) o->id;
		}
		k--;
		r = (r + 1) % n;
	}
	return 0;
}
