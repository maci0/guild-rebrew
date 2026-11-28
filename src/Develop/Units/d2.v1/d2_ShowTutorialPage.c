


// SIZE 0x14
struct page {
	char pad0[8];
	int mode;
	int text;
	int voice;
};

// SIZE 0x20
struct fsm {
	int state;
	int next;
	char pad8[0xc];
	int sound;
	struct page* page;
	char* dlg;
};

extern int* d2_TutorialState;

int __cdecl d2_ClearTutorialText(void);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl sb_CheckVoicePlaying(int);
void __cdecl sb_StopVoice(int, int);
int __cdecl d3snd_PlaySoundEffect(int, int, int, int);

int __cdecl d2_ShowTutorialPage(void)
{
	int r;

	if (((struct fsm*)d2_TutorialState)->page == 0) {
		return -4;
	}
	r = d2_ClearTutorialText();
	if (r == -4) {
		return r;
	}
	if ((((struct fsm*)d2_TutorialState)->page->mode == 1 || ((struct fsm*)d2_TutorialState)->page->mode == 2) && (((struct fsm*)d2_TutorialState)->next == 0xa ||
		((struct fsm*)d2_TutorialState)->next == 0xb)) {
		d2_SetForm(*(int*) (*(char**) (((struct fsm*)d2_TutorialState)->dlg + 0x74) + 8), 1);
		io_AppendText(0x3fd3);
		d2_SetForm(*(int*) (*(char**) (((struct fsm*)d2_TutorialState)->dlg + 0x74) + 8), 2);
		io_AppendText(0x3fd4);
		return 0;
	}
	d2_SetForm(*(int*) (*(char**) (((struct fsm*)d2_TutorialState)->dlg + 0x74) + 8), 1);
	io_AppendText(((struct fsm*)d2_TutorialState)->page->text);
	d2_SetForm(*(int*) (*(char**) (((struct fsm*)d2_TutorialState)->dlg + 0x74) + 8), 2);
	io_AppendText(((struct fsm*)d2_TutorialState)->page->text + 1);
	if (((struct fsm*)d2_TutorialState)->page->voice != 0) {
		if (((struct fsm*)d2_TutorialState)->sound != 0) {
			if (sb_CheckVoicePlaying(((struct fsm*)d2_TutorialState)->sound) != 0) {
				sb_StopVoice(((struct fsm*)d2_TutorialState)->sound, 0);
			}
			((struct fsm*)d2_TutorialState)->sound = 0;
		}
		((struct fsm*)d2_TutorialState)->sound = d3snd_PlaySoundEffect(-7, 0, ((struct fsm*)d2_TutorialState)->page->voice, -1);
	}
	return 0;
}
