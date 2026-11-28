

typedef struct {
	int a;
	int b;
	int c;
	int d;
} Msg;
// SIZE 0x10

typedef void (__cdecl* MsgFn)(Msg*);

typedef struct {
	char pad0[8];
	int kind;
	char padc[0x38 - 0xc];
	MsgFn cb;
	char pad3c[4];
	int key;
	int wait;
	int next;
	int alt_key;
} Cfg;
// SIZE 0x50

typedef struct {
	int state;
	int want;
	char pad8[4];
	unsigned int since;
	int ticks;
	char pad14[4];
	Cfg* cfg;
	char pad1c[0x2c - 0x1c];
	int done;
	int busy;
	char pad34[0x3c - 0x34];
	int mode;
	char pad40[0x50 - 0x40];
	int arg;
} Seq;
// SIZE 0x54

#include "Develop/DieGildeAddOn/game/game_data.h"
extern Seq* d2_TutorialState;
extern volatile unsigned int gm_GameTicks;

void __cdecl d2_HideTutorialPrompt(void);
void __cdecl d2_UpdateTutorialArrow(int);

void __cdecl d2_DispatchTutorialInput(int a, int b, int c, int d)
{
	Msg m;

	if (d2_TutorialActive == 0 || d2_TutorialState->cfg == 0) {
		return;
	}
	m.a = a;
	m.b = b;
	m.c = c;
	m.d = d;
	if (d2_TutorialState->cfg->kind != 2) {
		if (d2_TutorialState->want != 4 && d2_TutorialState->want != 0xa) {
			return;
		}
		if (d2_TutorialState->cfg->cb != 0) {
			d2_TutorialState->cfg->cb(&m);
			d2_TutorialState->ticks++;
			return;
		}
		if (d2_TutorialState->cfg->key == 3) {
			if (gm_GameTicks > d2_TutorialState->cfg->wait + d2_TutorialState->since) {
				d2_TutorialState->state = d2_TutorialState->cfg->next;
				d2_TutorialState->want = d2_TutorialState->cfg->next;
				d2_TutorialState->since = gm_GameTicks;
				d2_TutorialState->done = 1;
			}
			return;
		}
		if (d2_TutorialState->cfg->key != a) {
			goto tick;
		}
		if (c == 0) {
			d2_TutorialState->state = d2_TutorialState->cfg->next;
		} else {
			d2_TutorialState->state = 0xb;
		}
		d2_TutorialState->want = d2_TutorialState->state;
		d2_TutorialState->since = gm_GameTicks;
		goto tick;
	}
	if (d2_TutorialState->want != 4 && d2_TutorialState->want != 9 && d2_TutorialState->want != 0xa) {
		return;
	}
	if (d2_TutorialState->cfg->cb != 0) {
		d2_TutorialState->cfg->cb(&m);
		return;
	}
	if (d2_TutorialState->mode == 1) {
		if (c == 0) {
			if (d2_TutorialState->cfg->key == a) {
				d2_TutorialState->want = 5;
				d2_TutorialState->since = gm_GameTicks;
				if (b != 0) {
					d2_TutorialState->arg = b;
				}
			}
		} else if (c == 1 && d2_TutorialState->cfg->key == a) {
			d2_TutorialState->want = 4;
			d2_TutorialState->since = gm_GameTicks;
			d2_TutorialState->busy = 0;
			d2_HideTutorialPrompt();
			d2_UpdateTutorialArrow(2);
		}
		d2_TutorialState->state = d2_TutorialState->want;
		d2_TutorialState->ticks++;
		return;
	}
	if (d2_TutorialState->mode != 3) {
		goto tick;
	}
	if (d2_TutorialState->want == 9) {
		if (d2_TutorialState->cfg->alt_key != 0 && d2_TutorialState->cfg->alt_key == a) {
			d2_TutorialState->state = 0xa;
			d2_TutorialState->want = 0xa;
			d2_TutorialState->since = gm_GameTicks;
			d2_TutorialState->ticks++;
			return;
		}
		if (d2_TutorialState->cfg->key != a || c != 1) {
			goto tick;
		}
		d2_TutorialState->state = 4;
		d2_TutorialState->want = 4;
		d2_TutorialState->since = gm_GameTicks;
		d2_TutorialState->busy = 0;
		d2_HideTutorialPrompt();
		d2_UpdateTutorialArrow(2);
		d2_TutorialState->ticks++;
		return;
	}
	if (d2_TutorialState->want == 0xa) {
		if (d2_TutorialState->cfg->key != a || c != 1) {
			goto tick;
		}
		d2_TutorialState->state = 0xb;
		d2_TutorialState->want = 0xb;
		d2_TutorialState->since = gm_GameTicks;
	} else {
		if (d2_TutorialState->want != 4 || d2_TutorialState->cfg->key != a || c != 0) {
			goto tick;
		}
		d2_TutorialState->state = 9;
		d2_TutorialState->want = 9;
		d2_TutorialState->since = gm_GameTicks;
	}
tick:
	d2_TutorialState->ticks++;
}
