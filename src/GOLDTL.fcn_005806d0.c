// FUNCTION: GOLDTL 0x5806d0
// SIZE: 648

// SIZE 0x10
struct step {
	int f0;
	int kind;
	int text;
	int sound;
};

// SIZE 0x5c
struct lesson {
	char pad0[0x50];
	unsigned int count;
	void (__cdecl* done)(void);
	struct step* steps;
};

// SIZE 0x50
struct tutor {
	char pad0[0x14];
	int sound;
	struct lesson* lesson;
	char pad1c[0x24];
	unsigned int index;
	int state;
	int dlg;
	int button;
};

extern struct tutor* g_665f08;

void __cdecl fcn_00471e30(int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190();
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471d80(int, int);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_00423460(int);
void __cdecl fcn_004237f0(int, int);
int __cdecl fcn_004c3030(int, int, int, int);

int __cdecl fcn_005806d0(void)
{
	int k;

	if (g_665f08->lesson == 0) {
		return -4;
	}
	if (g_665f08->lesson->count != 0) {
		if (g_665f08->index >= g_665f08->lesson->count) {
			if (g_665f08->lesson->done != 0) {
				g_665f08->lesson->done();
			}
			if (g_665f08->dlg != -1) {
				fcn_00471e30(g_665f08->dlg);
				g_665f08->dlg = -1;
				g_665f08->button = -1;
				g_665f08->state = 4;
				return 0;
			}
		}
		if (g_665f08->state == g_665f08->lesson->steps[g_665f08->index].kind) {
			fcn_004727a0(g_665f08->dlg, 1);
			fcn_00519190("$C");
			fcn_004727a0(g_665f08->dlg, 2);
			fcn_00519190("$C");
		} else {
			if (g_665f08->dlg != -1) {
				fcn_00471e30(g_665f08->dlg);
				g_665f08->dlg = -1;
				g_665f08->button = -1;
				g_665f08->state = 4;
			}
			k = g_665f08->lesson->steps[g_665f08->index].kind;
			if (k >= 4) {
				return -4;
			}
			switch (k) {
			case 0:
				g_665f08->dlg = fcn_00470820(0, 0, "tutorial\\left_form");
				break;
			case 1:
				g_665f08->dlg = fcn_00470820(0, 0, "tutorial\\right_form");
				break;
			case 2:
				g_665f08->dlg = fcn_00470820(0, 0, "tutorial\\top_form");
				break;
			case 3:
				g_665f08->dlg = fcn_00470820(0, 0, "tutorial\\bottom_form");
				break;
			}
			fcn_00471d80(g_665f08->dlg, 3);
			g_665f08->state = g_665f08->lesson->steps[g_665f08->index].kind;
		}
		fcn_004727a0(g_665f08->dlg, 1);
		fcn_00519190(g_665f08->lesson->steps[g_665f08->index].text);
		fcn_004727a0(g_665f08->dlg, 2);
		g_665f08->button = fcn_00472250(g_665f08->dlg, 2, fcn_00519190("$Z%s", 0x7d));
		if (g_665f08->lesson->steps[g_665f08->index].sound != 0) {
			if (g_665f08->sound != 0) {
				if (fcn_00423460(g_665f08->sound) != 0) {
					fcn_004237f0(g_665f08->sound, 0);
				}
				g_665f08->sound = 0;
			}
			g_665f08->sound = fcn_004c3030(-7, 0, g_665f08->lesson->steps[g_665f08->index].sound, -1);
		}
		if (g_665f08->lesson->done != 0) {
			g_665f08->lesson->done();
		}
	}
	return 0;
}
