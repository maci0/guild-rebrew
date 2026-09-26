// FUNCTION: GOLD 0x578110
// SIZE: 656
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

extern int* g_665f08;

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

	if (((struct tutor*)g_665f08)->lesson == 0) {
		return -4;
	}
	if (((struct tutor*)g_665f08)->lesson->count != 0) {
		if (((struct tutor*)g_665f08)->index >= ((struct tutor*)g_665f08)->lesson->count) {
			if (((struct tutor*)g_665f08)->lesson->done != 0) {
				((struct tutor*)g_665f08)->lesson->done();
			}
			if (((struct tutor*)g_665f08)->dlg != -1) {
				fcn_00471e30(((struct tutor*)g_665f08)->dlg);
				((struct tutor*)g_665f08)->dlg = -1;
				((struct tutor*)g_665f08)->button = -1;
				((struct tutor*)g_665f08)->state = 4;
				return 0;
			}
		}
		if (((struct tutor*)g_665f08)->state == ((struct tutor*)g_665f08)->lesson->steps[((struct tutor*)g_665f08)->index].kind) {
			fcn_004727a0(((struct tutor*)g_665f08)->dlg, 1);
			fcn_00519190("$C");
			fcn_004727a0(((struct tutor*)g_665f08)->dlg, 2);
			fcn_00519190("$C");
		} else {
			if (((struct tutor*)g_665f08)->dlg != -1) {
				fcn_00471e30(((struct tutor*)g_665f08)->dlg);
				((struct tutor*)g_665f08)->dlg = -1;
				((struct tutor*)g_665f08)->button = -1;
				((struct tutor*)g_665f08)->state = 4;
			}
			k = ((struct tutor*)g_665f08)->lesson->steps[((struct tutor*)g_665f08)->index].kind;
			if (k >= 4) {
				return -4;
			}
			switch (k) {
			case 0:
				((struct tutor*)g_665f08)->dlg = fcn_00470820(0, 0, "tutorial\\left_form");
				break;
			case 1:
				((struct tutor*)g_665f08)->dlg = fcn_00470820(0, 0, "tutorial\\right_form");
				break;
			case 2:
				((struct tutor*)g_665f08)->dlg = fcn_00470820(0, 0, "tutorial\\top_form");
				break;
			case 3:
				((struct tutor*)g_665f08)->dlg = fcn_00470820(0, 0, "tutorial\\bottom_form");
				break;
			}
			fcn_00471d80(((struct tutor*)g_665f08)->dlg, 3);
			((struct tutor*)g_665f08)->state = ((struct tutor*)g_665f08)->lesson->steps[((struct tutor*)g_665f08)->index].kind;
		}
		fcn_004727a0(((struct tutor*)g_665f08)->dlg, 1);
		fcn_00519190(((struct tutor*)g_665f08)->lesson->steps[((struct tutor*)g_665f08)->index].text);
		fcn_004727a0(((struct tutor*)g_665f08)->dlg, 2);
		((struct tutor*)g_665f08)->button = fcn_00472250(((struct tutor*)g_665f08)->dlg, 2, fcn_00519190("$Z%s", 0x7d));
		if (((struct tutor*)g_665f08)->lesson->steps[((struct tutor*)g_665f08)->index].sound != 0) {
			if (((struct tutor*)g_665f08)->sound != 0) {
				if (fcn_00423460(((struct tutor*)g_665f08)->sound) != 0) {
					fcn_004237f0(((struct tutor*)g_665f08)->sound, 0);
				}
				((struct tutor*)g_665f08)->sound = 0;
			}
			((struct tutor*)g_665f08)->sound = fcn_004c3030(-7, 0, ((struct tutor*)g_665f08)->lesson->steps[((struct tutor*)g_665f08)->index].sound, -1);
		}
		if (((struct tutor*)g_665f08)->lesson->done != 0) {
			((struct tutor*)g_665f08)->lesson->done();
		}
	}
	return 0;
}
