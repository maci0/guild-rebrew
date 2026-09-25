typedef struct Range14 {
	int base;
	int id;
	int lo;
	int hi;
	unsigned char tag;
	char pad11[3];
} Range14;
// SIZE 0x14

// FUNCTION: GOLDTL 0x43c070
// SIZE: 90
int __cdecl fcn_0043c070(char* a, int x, int id, unsigned char tag)
{
	Range14* e;
	int k;
	int r;

	r = -1;
	if (a != 0) {
		e = *(Range14**) (a + 0x1b8);
		if (e != 0) {
			k = e->id;
			while (k >= 0) {
				if (id == k && x >= e->lo && x <= e->hi) {
					if (e->tag == 0xff) {
						e->tag = tag;
					}
					r = e->base - e->lo + x;
					break;
				}
				k = e[1].id;
				e++;
			}
		}
	}
	return r;
}
