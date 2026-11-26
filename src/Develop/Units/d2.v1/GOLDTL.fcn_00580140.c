


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

extern int* g_665f08;

int __cdecl fcn_005800e0(void);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl sb_CheckVoicePlaying(int);
void __cdecl sb_StopVoice(int, int);
int __cdecl d3snd_PlaySoundEffect(int, int, int, int);

int __cdecl fcn_00580140(void)
{
	int r;

	if (((struct fsm*)g_665f08)->page == 0) {
		return -4;
	}
	r = fcn_005800e0();
	if (r == -4) {
		return r;
	}
	if ((((struct fsm*)g_665f08)->page->mode == 1 || ((struct fsm*)g_665f08)->page->mode == 2) && (((struct fsm*)g_665f08)->next == 0xa || ((struct fsm*)g_665f08)->next == 0xb)) {
		d2_SetForm(*(int*) (*(char**) (((struct fsm*)g_665f08)->dlg + 0x74) + 8), 1);
		io_AppendText(0x3fd3);
		d2_SetForm(*(int*) (*(char**) (((struct fsm*)g_665f08)->dlg + 0x74) + 8), 2);
		io_AppendText(0x3fd4);
		return 0;
	}
	d2_SetForm(*(int*) (*(char**) (((struct fsm*)g_665f08)->dlg + 0x74) + 8), 1);
	io_AppendText(((struct fsm*)g_665f08)->page->text);
	d2_SetForm(*(int*) (*(char**) (((struct fsm*)g_665f08)->dlg + 0x74) + 8), 2);
	io_AppendText(((struct fsm*)g_665f08)->page->text + 1);
	if (((struct fsm*)g_665f08)->page->voice != 0) {
		if (((struct fsm*)g_665f08)->sound != 0) {
			if (sb_CheckVoicePlaying(((struct fsm*)g_665f08)->sound) != 0) {
				sb_StopVoice(((struct fsm*)g_665f08)->sound, 0);
			}
			((struct fsm*)g_665f08)->sound = 0;
		}
		((struct fsm*)g_665f08)->sound = d3snd_PlaySoundEffect(-7, 0, ((struct fsm*)g_665f08)->page->voice, -1);
	}
	return 0;
}
