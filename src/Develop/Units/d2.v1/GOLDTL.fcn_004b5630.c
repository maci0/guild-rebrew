#include <stdio.h>
#include "Develop/DieGildeAddOn/game/game_data.h"
extern volatile int g_6b7fac;

extern void __cdecl d3snd_StopTrackedVoices(void);
extern void *__cdecl fcn_00470820(int a, int b, const char *name);
extern void __cdecl d2_CenterDialogWindows(void *obj);
extern void __cdecl d2_SetForm(void *obj, int a);
extern int __cdecl io_AppendText(int id);
extern int __cdecl d2_GetWindowListItem(void *obj, int a, int b);
extern int __cdecl sbs_IsReady(void);
extern void *__cdecl d3snd_PlaySoundEffect(int a, int b, const char *name, int c);
extern int __cdecl sb_CheckVoicePlaying(void *node);
extern void __cdecl sb_StopVoice(void *node, int a);
extern void __cdecl main_RunFrameLoop(int a, int b);
extern void __cdecl fcn_00471e30(void *obj);

/* ADDRESS: GOLDTL 0x004b5630 */
void __cdecl fcn_004b5630(int a0, unsigned loopFlags)
{
	char buf[256];
	void *obj;
	int tab;
	void *node;
	unsigned b;
	unsigned i;

	d3snd_StopTrackedVoices();
	obj = fcn_00470820(0, 0, (const char *) 0x681130);
	d2_CenterDialogWindows(obj);
	d2_SetForm(obj, 1);
	io_AppendText(0x1b9b);
	d2_SetForm(obj, 2);
	io_AppendText(0x6811b0);
	tab = d2_GetWindowListItem(obj, 2, io_AppendText(0x7d));
	b = loopFlags | 0x80;
	if (sbs_IsReady()) {
		node = d3snd_PlaySoundEffect(-8, 0, (const char *) 0x68119c, 0);
		if (sb_CheckVoicePlaying(node)) {
			do {
				main_RunFrameLoop(0, b);
				if (g_100f1dc != -1 && d2_CurrentElementId == tab) {
					if (sb_CheckVoicePlaying(node)) {
						sb_StopVoice(node, 1);
					}
					break;
				}
			} while (sb_CheckVoicePlaying(node));
		}
	} else {
		i = g_6b7fac + 0xfa;
		if (i > g_6b7fac) {
			do {
				main_RunFrameLoop(0, b);
				if (g_100f1dc != -1 && d2_CurrentElementId == tab) {
					break;
				}
			} while (i > g_6b7fac);
		}
	}
	d2_SetForm(obj, 1);
	io_AppendText(0x1b9c);
	b = loopFlags | 0x80;
	if (sbs_IsReady()) {
		node = d3snd_PlaySoundEffect(-8, 0, (const char *) 0x68119c, 1);
		if (sb_CheckVoicePlaying(node)) {
			do {
				main_RunFrameLoop(0, b);
				if (g_100f1dc != -1 && d2_CurrentElementId == tab) {
					if (sb_CheckVoicePlaying(node)) {
						sb_StopVoice(node, 1);
					}
					break;
				}
			} while (sb_CheckVoicePlaying(node));
		}
	} else {
		i = g_6b7fac + 0xfa;
		if (i > g_6b7fac) {
			do {
				main_RunFrameLoop(0, b);
				if (g_100f1dc != -1 && d2_CurrentElementId == tab) {
					break;
				}
			} while (i > g_6b7fac);
		}
	}
	d2_SetForm(obj, 1);
	io_AppendText(0x1b9d);
	b = loopFlags | 0x80;
	if (sbs_IsReady()) {
		node = d3snd_PlaySoundEffect(-8, 0, (const char *) 0x68119c, 2);
		if (sb_CheckVoicePlaying(node)) {
			do {
				main_RunFrameLoop(0, b);
				if (g_100f1dc != -1 && d2_CurrentElementId == tab) {
					if (sb_CheckVoicePlaying(node)) {
						sb_StopVoice(node, 1);
					}
					break;
				}
			} while (sb_CheckVoicePlaying(node));
		}
	} else {
		i = g_6b7fac + 0xfa;
		if (i > g_6b7fac) {
			do {
				main_RunFrameLoop(0, b);
				if (g_100f1dc != -1 && d2_CurrentElementId == tab) {
					break;
				}
			} while (i > g_6b7fac);
		}
	}
	d2_SetForm(obj, 1);
	io_AppendText(0x6811b0);
	io_AppendText(0x1b9e);
	io_AppendText(*(int *) (a0 + 8) + 2);
	b = loopFlags | 0x80;
	if (sbs_IsReady()) {
		sprintf(buf, (const char *) 0x681180, *(unsigned *) (a0 + 0x10));
		node = d3snd_PlaySoundEffect(-7, 0, buf, -1);
		if (sb_CheckVoicePlaying(node)) {
			while (main_RunFrameLoop(0, b), g_100f1dc == -1 || d2_CurrentElementId != tab) {
				if (!sb_CheckVoicePlaying(node)) {
					fcn_00471e30(obj);
					return;
				}
			}
			if (sb_CheckVoicePlaying(node)) {
				sb_StopVoice(node, 1);
			}
		}
	} else {
		i = g_6b7fac + 0xfa;
		if (i > g_6b7fac) {
			do {
				main_RunFrameLoop(0, b);
				if (g_100f1dc != -1 && d2_CurrentElementId == tab) {
					break;
				}
			} while (i > g_6b7fac);
		}
	}
	fcn_00471e30(obj);
}
