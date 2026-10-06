// FUNCTION: GOLD 0x00578050
// FUNCTION: GOLDTL 0x00580610

extern int* g_665f08;
extern int g_6b7fac;
extern float g_665f10;

void __cdecl fcn_00580560(void);
void __cdecl fcn_005805e0(void);
void __cdecl fcn_00472380(int, int, int, int, int);

#define ELAPSED(t) ((*(volatile unsigned int*)&g_6b7fac) - (t) ? (*(volatile unsigned int*)&g_6b7fac) - (t) : 0)
#define MIN(a, b) ((a) < (b) ? (a) : (b))

void __cdecl fcn_00580610(void)
{
	unsigned int dur;
	unsigned int el;

	if (g_665f08[6] != 0 && g_665f08[0] == 0xa) {
		if (g_665f08[26] == -1) {
			fcn_00580560();
		}
		el = MIN(ELAPSED(g_665f08[3]), *(unsigned int*) (g_665f08[6] + 0x44));
		dur = *(unsigned int*) (g_665f08[6] + 0x44);
		fcn_00472380(g_665f08[27], 0, 0x190, (int) ((float) (int) (dur - el) / dur * g_665f10), 1);
	}
	else {
		fcn_005805e0();
	}
}
