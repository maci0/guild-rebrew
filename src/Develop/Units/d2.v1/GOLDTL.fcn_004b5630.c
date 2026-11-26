#include <stdio.h>
#include "Develop/DieGildeAddOn/game/game_data.h"
extern volatile int g_6b7fac;

extern void __cdecl fcn_004c09b0(void);
extern void *__cdecl fcn_00470820(int a, int b, const char *name);
extern void __cdecl d2_CenterDialogWindows(void *obj);
extern void __cdecl d2_SetForm(void *obj, int a);
extern int __cdecl io_AppendText(int id);
extern int __cdecl d2_GetWindowListItem(void *obj, int a, int b);
extern int __cdecl fcn_004273c0(void);
extern void *__cdecl d3snd_PlaySoundEffect(int a, int b, const char *name, int c);
extern int __cdecl fcn_00423460(void *node);
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

	fcn_004c09b0();
	obj = fcn_00470820(0, 0, (const char *) 0x681130);
	d2_CenterDialogWindows(obj);
	d2_SetForm(obj, 1);
	io_AppendText(0x1b9b);
	d2_SetForm(obj, 2);
	io_AppendText(0x6811b0);
	tab = d2_GetWindowListItem(obj, 2, io_AppendText(0x7d));
	b = loopFlags | 0x80;
	if (fcn_004273c0()) {
		node = d3snd_PlaySoundEffect(-8, 0, (const char *) 0x68119c, 0);
		if (fcn_00423460(node)) {
			do {
				main_RunFrameLoop(0, b);
				if (g_100f1dc != -1 && d2_CurrentElementId == tab) {
					if (fcn_00423460(node)) {
						sb_StopVoice(node, 1);
					}
					break;
				}
			} while (fcn_00423460(node));
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
	if (fcn_004273c0()) {
		node = d3snd_PlaySoundEffect(-8, 0, (const char *) 0x68119c, 1);
		if (fcn_00423460(node)) {
			do {
				main_RunFrameLoop(0, b);
				if (g_100f1dc != -1 && d2_CurrentElementId == tab) {
					if (fcn_00423460(node)) {
						sb_StopVoice(node, 1);
					}
					break;
				}
			} while (fcn_00423460(node));
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
	if (fcn_004273c0()) {
		node = d3snd_PlaySoundEffect(-8, 0, (const char *) 0x68119c, 2);
		if (fcn_00423460(node)) {
			do {
				main_RunFrameLoop(0, b);
				if (g_100f1dc != -1 && d2_CurrentElementId == tab) {
					if (fcn_00423460(node)) {
						sb_StopVoice(node, 1);
					}
					break;
				}
			} while (fcn_00423460(node));
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
	if (fcn_004273c0()) {
		sprintf(buf, (const char *) 0x681180, *(unsigned *) (a0 + 0x10));
		node = d3snd_PlaySoundEffect(-7, 0, buf, -1);
		if (fcn_00423460(node)) {
			while (main_RunFrameLoop(0, b), g_100f1dc == -1 || d2_CurrentElementId != tab) {
				if (!fcn_00423460(node)) {
					fcn_00471e30(obj);
					return;
				}
			}
			if (fcn_00423460(node)) {
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
