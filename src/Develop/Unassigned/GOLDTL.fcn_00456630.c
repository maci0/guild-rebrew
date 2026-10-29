typedef struct
{
	int f00;
	int f04;
	unsigned int stamp;
	unsigned int key;
	char b;
	char pad11[0x14 - 0x11];
} fcn_00456630_Slot;
// SIZE 0x14

extern fcn_00456630_Slot* g_6b89b4;
extern unsigned int g_6b89a8;
extern unsigned int g_6b89ac;

int __cdecl fcn_00456590(fcn_00456630_Slot* s, int a, char b, unsigned int key, unsigned int stamp);

/* ADDRESS: GOLDTL 0x00456630 */
int __cdecl fcn_00456630(int a, char b, unsigned int key, unsigned int stamp, int unused)
{
	fcn_00456630_Slot* s;
	fcn_00456630_Slot* best;
	unsigned int i;
	unsigned int bs;

	best = 0;
	bs = stamp;
	s = g_6b89b4;
	for (i = 0; i < g_6b89a8; i++, s++) {
		if (s->key == key && s->b == b && s->stamp < bs) {
			bs = s->stamp;
			best = s;
		}
		if (s->key == 0) {
			return fcn_00456590(s, a, b, key, stamp);
		}
	}
	if (best != 0 && stamp - bs > g_6b89ac) {
		return fcn_00456590(best, a, b, key, stamp);
	}
	best = 0;
	bs = stamp;
	s = g_6b89b4;
	for (i = g_6b89a8; i > 0; i--, s++) {
		if (s->key > 0 && s->b == b && s->stamp < bs) {
			bs = s->stamp;
			best = s;
		}
	}
	if (best != 0 && stamp - bs > 1) {
		return fcn_00456590(best, a, b, key, stamp);
	}
	return 0;
}
