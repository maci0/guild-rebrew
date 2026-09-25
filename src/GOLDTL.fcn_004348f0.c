// FUNCTION: GOLDTL 0x4348f0
// SIZE: 115

extern char* g_1042320;
extern char g_1052a40[];
extern unsigned int g_6b8008;

int __cdecl fcn_004346f0(char*);
void __cdecl fcn_00434760(char*, int);

char __cdecl fcn_004348f0(int need, int have)
{
	char* p;
	char* best;
	unsigned int bestv;

	if (need < 0) {
		return 0;
	}
	while (have > need) {
		best = 0;
		bestv = g_6b8008;
		for (p = g_1042320; p != g_1052a40; p = *(char**) (p + 0x160)) {
			if (*(int*) (p + 0x14c) == 0 && *(unsigned int*) (p + 0x158) <= bestv) {
				bestv = *(unsigned int*) (p + 0x158);
				best = p;
			}
		}
		if (best == 0) {
			return 0;
		}
		have -= fcn_004346f0(best);
		fcn_00434760(best, 1);
	}
	return 1;
}
