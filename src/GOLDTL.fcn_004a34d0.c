typedef struct {
	int a;
	int b;
	int c;
} fcn_004a34d0_entry;
// SIZE 0xc

typedef struct {
	fcn_004a34d0_entry* cur;
	int step;
} fcn_004a34d0_ring;

extern unsigned int g_7728bc;
extern fcn_004a34d0_ring* g_664448;
extern fcn_004a34d0_entry g_10082a0[];

/* ADDRESS: GOLD 0x004a3a90 */
/* ADDRESS: GOLDTL 0x004a34d0 */

fcn_004a34d0_entry* __cdecl fcn_004a34d0(void)
{
	unsigned int n;
	fcn_004a34d0_ring* r;
	fcn_004a34d0_entry* cur;

	n = g_7728bc;
	r = g_664448;
	cur = r->cur;
	if (n == 0)
		return g_10082a0;
	r->cur = &g_10082a0[(cur - g_10082a0 + r->step) % n];
	return cur;
}
