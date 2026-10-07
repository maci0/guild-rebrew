// SUPPORT: SERVER discarded copy of the clients' multimedia-timer unit; its references load the five WINMM import members (dropped by /OPT:REF) that the reference's IAT slot order needs
/* Timer unit: TL 0x42dcd0..0x42df70, GOLD 0x42e7b0..0x42ea50. Only tb_OpenFunction is named
 * by the clients (its error string); the other names are descriptive. The server calls none
 * of these functions, so /OPT:REF discards them all. Their storage (tick counters, TIMECAPS,
 * 32 callback slots) has no attested server owner: offsets into the unnamed BSS block
 * g_gap_10035a10 stand in so every operand is a DIR32, as in the clients. ReportMessage
 * stands in for the clients' one-argument error reporter. */
extern char g_gap_10035a10[];
#define TB_INT(off) (*(volatile int*) (g_gap_10035a10 + (off)))
#define TB_SLOTS ((struct tb_slot*) (g_gap_10035a10 + 0x100))
#define TB_SLOT_COUNT 32
#define TB_CAPS ((unsigned int*) (g_gap_10035a10 + 0x40))

// SIZE 0xc
struct tb_slot {
	void (__cdecl* fn)(void);
	unsigned int period;
	int paused;
};

typedef void (__stdcall* tb_timecb)(unsigned int, unsigned int, unsigned long, unsigned long, unsigned long);
__declspec(dllimport) unsigned int __stdcall timeSetEvent(unsigned int, unsigned int, tb_timecb, unsigned long, unsigned int);
__declspec(dllimport) unsigned int __stdcall timeKillEvent(unsigned int);
__declspec(dllimport) unsigned int __stdcall timeBeginPeriod(unsigned int);
__declspec(dllimport) unsigned int __stdcall timeEndPeriod(unsigned int);
__declspec(dllimport) unsigned int __stdcall timeGetDevCaps(void*, unsigned int);
__declspec(dllimport) unsigned int __stdcall timeGetTime(void);
extern void __cdecl srand(unsigned int);
extern void __cdecl ReportMessage(char* msg);

void __stdcall tb_Tick(unsigned int id, unsigned int msg, unsigned long user, unsigned long dw1, unsigned long dw2)
{
	struct tb_slot* s;

	if (TB_INT(0x14) != 0) {
		return;
	}
	TB_INT(0x14) = 1;
	TB_INT(0x10)++;
	if (TB_INT(0x18) == 0) {
		for (s = TB_SLOTS; s < TB_SLOTS + TB_SLOT_COUNT; s++) {
			if (s->fn != 0 && (unsigned int) TB_INT(4) % s->period == 0 && s->paused == 0) {
				s->fn();
			}
		}
		if ((unsigned int) TB_INT(4) % 3 == 0) {
			TB_INT(8)++;
		}
		if (TB_INT(4) & 1) {
			TB_INT(0xc)++;
		}
		if (*(volatile char*) (g_gap_10035a10 + 0x20) != 0) {
			if (++TB_INT(0x24) % 20 == 0) {
				TB_INT(4)++;
			}
		} else {
			TB_INT(4)++;
		}
	}
	if (TB_INT(0x1c) != 0) {
		TB_INT(0) = timeSetEvent(TB_CAPS[2], TB_CAPS[0] + 5, tb_Tick, 0, 0);
	}
	TB_INT(0x14) = 0;
}

int __cdecl tb_Init(unsigned int delay, int oneshot)
{
	timeGetDevCaps(TB_CAPS, 8);
	timeBeginPeriod(TB_CAPS[0] + 5);
	if (delay < TB_CAPS[0]) {
		return 0;
	}
	TB_CAPS[2] = delay;
	TB_INT(0x1c) = oneshot;
	TB_INT(0) = timeSetEvent(delay, TB_CAPS[0] + 5, tb_Tick, 0, oneshot ? 0 : 1);
	if (TB_INT(0) == 0) {
		return 0;
	}
	srand(timeGetTime());
	return 1;
}

void __cdecl tb_Exit(void)
{
	if (TB_INT(0) != 0 && timeKillEvent(TB_INT(0)) == 0) {
		TB_INT(0) = 0;
	}
	timeEndPeriod(TB_CAPS[0] + 5);
}

int __cdecl tb_OpenFunction(void (__cdecl* fn)(void), unsigned int period)
{
	int i;

	i = 0;
	while (TB_SLOTS[i++].fn != 0 && i < TB_SLOT_COUNT) {
	}
	if (i > TB_SLOT_COUNT) {
		ReportMessage("tb_OpenFunction: Too many TimeBaseProcs!");
		return 0;
	}
	i--;
	TB_SLOTS[i].fn = fn;
	TB_SLOTS[i].period = period;
	TB_SLOTS[i].paused = 0;
	return 1;
}

int __cdecl tb_CloseFunction(void (__cdecl* fn)(void))
{
	int i;

	for (i = 0; i < TB_SLOT_COUNT; i++) {
		if (TB_SLOTS[i].fn == fn) {
			TB_SLOTS[i].fn = 0;
			return 1;
		}
	}
	return 0;
}

int __cdecl tb_PauseFunction(void (__cdecl* fn)(void), int paused)
{
	int i;

	for (i = 0; i < TB_SLOT_COUNT; i++) {
		if (TB_SLOTS[i].fn == fn) {
			TB_SLOTS[i].paused = paused;
			return 1;
		}
	}
	return 0;
}

int __cdecl tb_IsPaused(void (__cdecl* fn)(void))
{
	int i;

	for (i = 0; i < TB_SLOT_COUNT; i++) {
		if (TB_SLOTS[i].fn == fn) {
			return TB_SLOTS[i].paused != 0;
		}
	}
	return 0;
}
