// FUNCTION: GOLD 0x00426540
// SIZE: 240
// FUNCTION: GOLDTL 0x004229b0
// SIZE: 240

// SIZE 0x30
typedef struct {
	int h;
	char* sample;
	int prio;
	int loop;
	int time;
	int flags;
	int f18;
	int f1c;
	int f20;
	int vol;
	int pan;
	int f2c;
} Voice;

extern int g_6b7d7c;
extern Voice g_14cbbe0;
extern Voice* g_6b7e88;
extern int g_6b7e8c;
int __cdecl fcn_0042aaa0(int h);
void __cdecl fcn_0042a7c0(int h);

Voice* __cdecl fcn_004229b0(void)
{
	Voice* best;
	int i;

	best = 0;
	if (g_6b7d7c == 0) {
		return &g_14cbbe0;
	}
	if (g_6b7e88 != 0) {
		for (i = 0; i < g_6b7e8c; i++) {
			if (fcn_0042aaa0(g_6b7e88[i].h) != 4 && (g_6b7e88[i].flags & 0x10) == 0) {
				best = &g_6b7e88[i++];
				break;
			}
		}
		if (best != 0) {
			for (; i < g_6b7e8c; i++) {
				if (g_6b7e88[i].prio < best->prio && fcn_0042aaa0(g_6b7e88[i].h) != 4 &&
				    (g_6b7e88[i].flags & 0x10) == 0) {
					best = &g_6b7e88[i];
				}
			}
			fcn_0042a7c0(best->h);
			best->flags = 0;
			best->f18 = 0;
			best->loop = 1;
		}
	}
	return best;
}
