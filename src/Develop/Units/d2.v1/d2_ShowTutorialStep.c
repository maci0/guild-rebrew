


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

extern int* d2_TutorialState;

void __cdecl d2_DestroyForm(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText();
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterForm(int, int);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl sb_CheckVoicePlaying(int);
void __cdecl sb_StopVoice(int, int);
int __cdecl d3snd_PlaySoundEffect(int, int, int, int);

/* ADDRESS: GOLDDE 0x00566470 */
int __cdecl d2_ShowTutorialStep(void)
{
	int k;

	if (((struct tutor*)d2_TutorialState)->lesson == 0) {
		return -4;
	}
	if (((struct tutor*)d2_TutorialState)->lesson->count != 0) {
		if (((struct tutor*)d2_TutorialState)->index >= ((struct tutor*)d2_TutorialState)->lesson->count) {
			if (((struct tutor*)d2_TutorialState)->lesson->done != 0) {
				((struct tutor*)d2_TutorialState)->lesson->done();
			}
			if (((struct tutor*)d2_TutorialState)->dlg != -1) {
				d2_DestroyForm(((struct tutor*)d2_TutorialState)->dlg);
				((struct tutor*)d2_TutorialState)->dlg = -1;
				((struct tutor*)d2_TutorialState)->button = -1;
				((struct tutor*)d2_TutorialState)->state = 4;
				return 0;
			}
		}
		if (((struct tutor*)d2_TutorialState)->state == ((struct tutor*)d2_TutorialState)->lesson->steps[((struct tutor*)d2_TutorialState)->index].kind) {
			d2_SetForm(((struct tutor*)d2_TutorialState)->dlg, 1);
			io_AppendText("$C");
			d2_SetForm(((struct tutor*)d2_TutorialState)->dlg, 2);
			io_AppendText("$C");
		} else {
			if (((struct tutor*)d2_TutorialState)->dlg != -1) {
				d2_DestroyForm(((struct tutor*)d2_TutorialState)->dlg);
				((struct tutor*)d2_TutorialState)->dlg = -1;
				((struct tutor*)d2_TutorialState)->button = -1;
				((struct tutor*)d2_TutorialState)->state = 4;
			}
			k = ((struct tutor*)d2_TutorialState)->lesson->steps[((struct tutor*)d2_TutorialState)->index].kind;
			if (k >= 4) {
				return -4;
			}
			switch (k) {
			case 0:
				((struct tutor*)d2_TutorialState)->dlg = d2_LoadForm(0, 0, "tutorial\\left_form");
				break;
			case 1:
				((struct tutor*)d2_TutorialState)->dlg = d2_LoadForm(0, 0, "tutorial\\right_form");
				break;
			case 2:
				((struct tutor*)d2_TutorialState)->dlg = d2_LoadForm(0, 0, "tutorial\\top_form");
				break;
			case 3:
				((struct tutor*)d2_TutorialState)->dlg = d2_LoadForm(0, 0, "tutorial\\bottom_form");
				break;
			}
			d2_CenterForm(((struct tutor*)d2_TutorialState)->dlg, 3);
			((struct tutor*)d2_TutorialState)->state = ((struct tutor*)d2_TutorialState)->lesson->steps[((struct tutor*)d2_TutorialState)->index].kind;
		}
		d2_SetForm(((struct tutor*)d2_TutorialState)->dlg, 1);
		io_AppendText(((struct tutor*)d2_TutorialState)->lesson->steps[((struct tutor*)d2_TutorialState)->index].text);
		d2_SetForm(((struct tutor*)d2_TutorialState)->dlg, 2);
		((struct tutor*)d2_TutorialState)->button = d2_GetWindowListItem(((struct tutor*)d2_TutorialState)->dlg, 2, io_AppendText("$Z%s", 0x7d));
		if (((struct tutor*)d2_TutorialState)->lesson->steps[((struct tutor*)d2_TutorialState)->index].sound != 0) {
			if (((struct tutor*)d2_TutorialState)->sound != 0) {
				if (sb_CheckVoicePlaying(((struct tutor*)d2_TutorialState)->sound) != 0) {
					sb_StopVoice(((struct tutor*)d2_TutorialState)->sound, 0);
				}
				((struct tutor*)d2_TutorialState)->sound = 0;
			}
			((struct tutor*)d2_TutorialState)->sound = d3snd_PlaySoundEffect(-7, 0, ((struct tutor*)d2_TutorialState)->lesson->steps[((struct tutor*)d2_TutorialState)->index].sound, -1);
		}
		if (((struct tutor*)d2_TutorialState)->lesson->done != 0) {
			((struct tutor*)d2_TutorialState)->lesson->done();
		}
	}
	return 0;
}
