#include <string.h>
extern char* d3_ActiveCamera;
extern int d2_ScreenHeight;
extern int g_1040494;
extern int g_10432a4;
extern int g_10421a0;
extern int g_10529c8;
extern short g_14ce8c0;
extern short g_14ce8c2;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_14cf950;
#include "client_dialog_state.h"
extern char* g_7746a0;
extern char* g_7746a4;
extern int g_100f1dc;
extern char* txt_TextEntries[];
extern int main_LoopFlags;
extern unsigned char g_6a375c;
extern int g_6b7fdc;
extern int g_14b5e50;
extern int g_14b5e54;
extern int d2_CurrentWindowId;

void __cdecl fcn_00533880(void);
void __cdecl fcn_005338a0(void);
void __cdecl d3_SelectSceneContext(int, int);
void __cdecl d3_SetNodePosition(char*, int*);
void __cdecl d3_SetObjectRotation(char*, int*);
void __cdecl fcn_00445f50(int, int, float, int);
int __cdecl sprintf(char*, const char*, ...);
char* __cdecl strcpy(char*, const char*);
typedef struct { char unknown00[9]; char name[0x100]; char path[0x107]; } FileSlot53ed60;
int __cdecl vfs_ListFilesByExtension(char*, char*, FileSlot53ed60*);
int __cdecl vfs_Tfopen(char*, char*, int);
int __cdecl fcn_00521eb0(int, char*);
void __cdecl CloseVfsStream(int);
char* __cdecl d3_SpawnCityMapMarker(char*);
int __cdecl sprintf(char*, const char*, ...);
int __cdecl txt_FindEntryIndex(char*);
void __cdecl RegisterStatusText(char*, char*, int);
char* __cdecl fcn_00442910(int, void*, void*, char*);
void __cdecl d3_ApplyObjectAnimation(char*, char*, int);
char __cdecl d3_SetObjectVisible(char*, char);
int __cdecl fcn_004e4470(char*);
void __cdecl cut_WaitForScript(int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471d80(int, int);
void __cdecl fcn_00471db0(int, int);
int __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
void __cdecl fcn_00438da0(float, float, float, float, int, int, int, int, int);
void __cdecl d2_CreateButtonRow(int, int, int*, int, ...);
int __cdecl main_RunFrameLoop(void*, int);
char* __cdecl d3_FindSceneObjectAtScreenPoint(float, float, int, int);
int __cdecl fcn_0064f170(char*, char*, int);
void __cdecl fcn_0053eb60(int);
void __cdecl d2_SetFormVisibility(int, int);
int __cdecl d2_RunChooseIntroMenu(void);
int __cdecl fcn_0053dc20(void);
int __cdecl fcn_004130b0(char*, char*);
void __cdecl d2_DestroyForm(int);
void __cdecl d3_DestroyObject(char*);
void __cdecl d3_AnimateObjectTransform(char*, float*, float*, int, int);

/* Local frame layout; the 0x8984-byte frame is mostly the city name table. */
/* ADDRESS: GOLDTL 0x0053ed60 */
int __cdecl fcn_0053ed60(int unused, int network)
{
	struct {
		char langName[0x40];
		char hdr[0xfc];
		char keybuf[0x100];
		char* cities[0x40];
		char namebuf[0x100];
		int values[0x40];
		FileSlot53ed60 names[0x40];
	} data;
	float pos[4];
	float dir[3];
	char* obj;
	char* city;
	char* image;
	char* sel;
	int win1;
	int win2;
	int tmp_ids[2];
	int ok_id;
	int info_id;
	int count;
	int i;
	int h;
	int idx;
	int result;
	int highlight;
	int prev;

	result = 0;
	obj = 0;
	prev = 0;
	highlight = -1;
	fcn_00533880();
	fcn_005338a0();
	d3_SelectSceneContext(0, 0);
	d3_SetNodePosition(d3_ActiveCamera, (int*) (d3_ActiveCamera + 0x5c));
	d3_SetObjectRotation(d3_ActiveCamera, (int*) (d3_ActiveCamera + 0x90));
	fcn_00445f50(0, 0, 1.0f, 0);
	if (network == 0) {
		count = vfs_ListFilesByExtension((char*) 0x6a3778, (char*) 0x6a41b8, data.names);
	} else {
		count = vfs_ListFilesByExtension((char*) 0x6a3778, (char*) 0x6a41b0, data.names);
	}
	for (i = 0; i < count; i++) {
		h = vfs_Tfopen(data.names[i].path, (char*) 0x6750e8, g_6b7fdc);
		if (h == 0) {
			return 0;
		}
		if (fcn_00521eb0(h, data.hdr) == 0) {
			CloseVfsStream(h);
			return 0;
		}
		CloseVfsStream(h);
		data.values[i] = (signed char) data.hdr[0x30] - (*(int*) &g_6a375c & 0xff);
		city = d3_SpawnCityMapMarker(data.hdr + 5);
		data.cities[i] = city;
		if (city != 0) {
			sprintf(data.keybuf, (char*) 0x6a22a8, data.hdr + 5);
			_strupr(data.keybuf);
			idx = txt_FindEntryIndex(data.keybuf);
			if (idx != -1) {
				strcpy(data.langName, txt_TextEntries[idx]);
			} else {
				strcpy(data.langName, data.hdr + 5);
			}
			sprintf(data.namebuf, (char*) 0x6a41a4, data.hdr + 5);
			strcpy(city, data.namebuf);
			RegisterStatusText(data.namebuf, data.langName, 0);
		}
	}
	city = (char*) data.cities[4];
	sel = city;
	if (city != 0) {
		pos[0] = *(float*) (city + 0x4c);
		pos[1] = *(float*) (city + 0x50);
		pos[2] = *(float*) (city + 0x54);
		pos[3] = 0.0f;
		dir[0] = 0.0f;
		dir[1] = 0.0f;
		dir[2] = 0.0f;
		obj = fcn_00442910(0, pos, dir, (char*) 0x6a40a0);
		*(char*) (obj + 0x215) = *(char*) (obj + 0x215) | 1;
		*(char*) (obj + 0x216) = (*(char*) (obj + 0x216) & 0xfd) | 1;
		d3_ApplyObjectAnimation(obj, (char*) 0x6a4080, 1);
	}
	d3_SetObjectVisible(city, 0);
	main_LoopFlags = 0x12d6;
	cut_EventLoopFlags = 0x12d6;
	cut_WaitForScript(fcn_004e4470((char*) 0x6a4024));
	win1 = fcn_00470820(0, 0, (char*) 0x6a3dd4);
	fcn_00471d80(win1, 3);
	fcn_00471db0(win1, 1);
	d2_SetForm(win1, 0);
	io_AppendText(0x1abb);
	fcn_00438da0((float) g_1040494, (float) d2_ScreenHeight, 0.0f, 0.0f, g_10529c8, g_10421a0, g_10432a4, g_1040494, d2_ScreenHeight);
	win2 = fcn_00470820(0, 0, (char*) 0x6a4194);
	fcn_00471d80(win2, 3);
	fcn_00471db0(win2, 1);
	d2_SetForm(win2, 2);
	d2_CreateButtonRow(d2_CurrentWindowId, 0, tmp_ids, 2, g_14b5e50, g_14b5e54);
	ok_id = tmp_ids[0];
	info_id = tmp_ids[1];
	while (main_RunFrameLoop((void*) fcn_0053ed60, 0x10d6) != 0) {
		g_7746a0 = 0;
		image = d3_FindSceneObjectAtScreenPoint((float) g_14ce8c0, (float) g_14ce8c2, 0x60, 1);
		g_7746a4 = image;
		if (g_14ce8cc != 0) {
			g_7746a0 = image;
		} else if (g_14ce8e0 != 0 || g_14cf950 == 1) {
			g_774654 = 1;
		}
		if (g_7746a0 != 0 && fcn_0064f170(g_7746a0, (char*) 0x6a418c, 6) == 0) {
			sel = g_7746a0;
		}
		if (sel != prev) {
			pos[0] = 0.0f;
			pos[1] = 0.0f;
			pos[2] = 0.0f;
			pos[3] = 0.0f;
			dir[0] = 0.0f;
			dir[1] = 0.0f;
			dir[2] = 0.0f;
			d2_SetForm(win2, 1);
			io_AppendText(0x6811b0);
			pos[0] = pos[0] + *(float*) (sel + 0x4c);
			pos[1] = pos[1] + *(float*) (sel + 0x50);
			pos[2] = pos[2] + *(float*) (sel + 0x54);
			d3_AnimateObjectTransform(obj, pos, dir, 0x28, 0x20);
			for (i = 0; i < count; i++) {
				if (sel == data.cities[i]) {
					if (data.cities[i] != 0) {
						strcpy(g_7e1d00, sel + 6);
						sprintf(data.keybuf, (char*) 0x6a4170, g_7e1d00);
						_strupr(data.keybuf);
						idx = txt_FindEntryIndex(data.keybuf);
						if (idx != -1) {
							d2_SetForm(win2, 1);
							io_AppendText(idx);
							io_AppendText(0x68b300);
							io_AppendText(idx + 1);
						}
						d3_SetObjectVisible(sel, 0);
						highlight = data.values[i];
					}
				} else if (data.cities[i] != 0) {
					d3_SetObjectVisible(data.cities[i], 1);
				}
			}
			prev = sel;
		}
		if (g_100f1dc == 2) {
			if (d2_CurrentElementId == info_id) {
				d2_SetFormVisibility(win2, 0);
				d2_SetFormVisibility(win1, 0);
				fcn_0053eb60(highlight);
				d2_SetFormVisibility(win2, 1);
				d2_SetFormVisibility(win1, 1);
				if (g_100f1dc != 2) {
					goto not_checked;
				}
			}
			if (d2_CurrentElementId == ok_id) {
				goto accepted;
			}
		}
not_checked:
		if (g_14cf950 != 0x1c) {
			continue;
		}
accepted:
		d2_SetFormVisibility(win2, 0);
		d2_SetFormVisibility(win1, 0);
		if (network != 0) {
			g_774654 = 1;
			result = 1;
		} else {
			if (d2_RunChooseIntroMenu() != 0 && fcn_0053dc20() != 0) {
				g_774654 = 1;
				result = 1;
				d2_SetFormVisibility(win2, 1);
			}
			d2_SetFormVisibility(win2, 1);
			d2_SetFormVisibility(win1, 1);
		}
	}
	if (win2 != -1) {
		d2_DestroyForm(win2);
	}
	if (win1 != -1) {
		d2_DestroyForm(win1);
	}
	if (obj != 0) {
		fcn_004130b0(obj, (char*) 0x6a415c);
		d3_DestroyObject(obj);
	}
	for (i = 0; i < count; i++) {
		if (data.cities[i] != 0) {
			d3_DestroyObject(data.cities[i]);
		}
	}
	return result;
}
