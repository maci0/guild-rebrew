extern int g_772d18;
extern int g_6b7fac;
extern int g_772d2c;
extern unsigned int g_772d38;

struct snd_4c0b40 {
	char** voice;
	unsigned int delay;
	int started;
	struct snd_4c0b40* next;
};
// SIZE 0x10

extern char* g_772d34;

char* __cdecl fcn_0064d470(char*, char*);
void __cdecl fcn_004c24c0(float, int);
int __cdecl fcn_00423670(char**, int, int);
int __cdecl fcn_00423460(char**);
void __cdecl fcn_00426170(char**, int);
void __cdecl m_FreeTracked(struct snd_4c0b40*);


/* ADDRESS: GOLDTL 0x004c0b40 */
void __cdecl fcn_004c0b40(void)
{
	struct snd_4c0b40* cur;
	struct snd_4c0b40* next;
	unsigned int now;
	int one;

	if (g_772d18 != 0)
		return;
	now = (*(volatile int*)&g_6b7fac) + ((*(volatile int*)&g_6b7fac) + (*(volatile int*)&g_6b7fac) * 2) * 4;
	cur = (*(struct snd_4c0b40**)&g_772d34);
	if (cur == 0)
		return;
	if (cur->started == 0) {
		if (cur->delay < now - g_772d38) {
			if (cur->voice != 0 && cur->voice[1] != 0) {
				one = 1;
				if (fcn_0064d470(cur->voice[1] + 4, "Fanfare") != 0 && g_772d2c == 0) {
					fcn_004c24c0(0.0f, 0x7d0);
					g_772d2c = one;
				}
				fcn_00423670((*(struct snd_4c0b40**)&g_772d34)->voice, 0, 0);
				(*(struct snd_4c0b40**)&g_772d34)->started = one;
				g_772d38 = now;
				return;
			}
			cur->started = 1;
			g_772d38 = now;
			return;
		}
	}
	if (cur->started == 0)
		return;
	if (fcn_00423460(cur->voice) != 0)
		return;
	next = (*(struct snd_4c0b40**)&g_772d34)->next;
	fcn_00426170((*(struct snd_4c0b40**)&g_772d34)->voice, 0);
	m_FreeTracked((*(struct snd_4c0b40**)&g_772d34));
	(*(struct snd_4c0b40**)&g_772d34) = next;
	g_772d38 = now;
	if (next != 0 && next->voice != 0 && next->voice[1] != 0 && g_772d2c != 0
	    && fcn_0064d470(next->voice[1] + 4, "MausclickLinks") != 0) {
		next = (*(struct snd_4c0b40**)&g_772d34)->next;
		fcn_00426170((*(struct snd_4c0b40**)&g_772d34)->voice, 0);
		m_FreeTracked((*(struct snd_4c0b40**)&g_772d34));
		(*(struct snd_4c0b40**)&g_772d34) = next;
		fcn_004c24c0(1.0f, 0x7d0);
		g_772d2c = 0;
	}
}
