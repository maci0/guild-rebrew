

#include "Develop/Units/d2.v1/d2_window_view.h"





// SIZE 0x3cc

#include "client_types.h"

#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"
extern char s_6ab6b8[];
extern char s_6ab67c[];
extern char s_6ab63c[];
extern char s_6ab624[];
extern char s_6ab610[];

int __cdecl d2_CreateWindow(int, int, int, int, int);
void __cdecl d2_SetElementFont(int, int);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl io_AppendText(int, ...);
int __cdecl evt_CountActiveScripts(void);
int __cdecl evt_CalcScriptMemSize(char*);
int __cdecl sprintf(char*, const char*, ...);
int __cdecl d2_UpdateWindowDrag(char*);
void __cdecl d2_CloseWindow(int);

void __cdecl d2_ShowScriptMemory(void)
{
	D2_WIN* w;
	char buf[0x100];
	int h;
	int total;
	int i;
	char* e;

	h = d2_CreateWindow(0x20, 0x60, 0x280, 0x190, 0x414);
	d2_SetElementFont(((D2_WIN*)g_1015f40)[h].slot, 0x54);
	while (main_RunFrameLoop((void*) d2_ShowScriptMemory, 0x657c7) != 0) {
		w = &((D2_WIN*)g_1015f40)[h];
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		d2_CurrentWindowId = h;
		io_AppendText((int) "$C");
		io_AppendText((int) s_6ab6b8, evt_CountActiveScripts());
		io_AppendText((int) s_6ab67c);
		io_AppendText((int) s_6ab63c);
		total = 0;
		for (i = 0; i < 128; i++) {
			e = g_6b7e94 + i * 0xc98;
			if ((e[0] != 0 && *(int*) (e + 0x100) != -1) || (e[0x124] & 1)) {
				sprintf(buf, s_6ab624, *(int*) (e + 0x100), e, *(int*) (e + 0x110), *(int*) (e + 0x114), evt_CalcScriptMemSize(e));
				io_AppendText((int) buf);
				total += evt_CalcScriptMemSize(e);
			}
		}
		io_AppendText((int) s_6ab610, total);
		d2_UpdateWindowDrag((char*)w);
	}
	d2_CloseWindow(h);
}
