#include <string.h>
/*
 * Network game browser: poll the advertised sessions, build one list row per
 * compatible host (name, map, players, ping) and drive the modal dialog.
 */

extern int g_100f1dc;           /* 0x0100f1dc */
extern char* g_1015ea0;         /* 0x01015ea0 */
extern int g_14ac5e4;           /* 0x014ac5e4 */
extern int g_14ac614;           /* 0x014ac614 */
extern int g_14ac618;           /* 0x014ac618 */
extern int g_14ac61c;           /* 0x014ac61c */
extern int g_14ce8e0;           /* 0x014ce8e0 */
extern char g_14cf950;          /* 0x014cf950 */
extern int d2_CurrentElementId;            /* 0x0067d370 */
extern volatile unsigned int g_6b7fac;            /* 0x006b7fac */
extern int g_6b7fdc;            /* 0x006b7fdc */
extern int d2_CurrentWindowId;            /* 0x00772514 */
extern int d2_SuppressOverlay;            /* 0x007725c8 */
#include "client_dialog_state.h"            /* 0x00774654 */
extern unsigned char g_7747b0;  /* 0x007747b0 */
extern int g_9badc0;            /* 0x009badc0 */
extern int g_9badc4;            /* 0x009badc4 */
extern int g_9badc8;            /* 0x009badc8 */
extern int g_9badcc;            /* 0x009badcc */

extern char g_7e22c0[], g_7e21a0[], g_7e1d00[];
extern char s_6a1e4c[]; /* "Network" */
extern char s_6a2e24[]; /* "_STADTWAPPEN_BERLIN" */
extern char s_6a2e38[]; /* "_STADTWAPPEN_%s" */
extern char s_6a3a4c[]; /* "Host" */
extern char s_6a3a54[]; /* "Gamedata\\network\\%s.SAV" */
extern char s_6a3a6c[]; /* "Menu\\SEARCH_NETWORK" */

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_PositionFormWindows(int, int);
void __cdecl d2_CenterForm(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl d2_InitWindowBounds(int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_CreateButtonRow(int, int, int*, int, int, int, int);
int __cdecl d2_SetElementEnabled(int, int);
int __cdecl main_RunFrameLoop(int, int);
int __cdecl d2_OpenMessageBox(int, int);
int __cdecl nt_ListenForServerAnnouncements(int, int, char*, int);
int __cdecl d2_DestroyForm(int);
int __cdecl d2_ClearWindowChildren(int, int);
int __cdecl d2_ClearRadioGroup(int);
int* __cdecl d2_CreateRadioGroup(int);
int __cdecl vfs_Tfopen(char*, int, int);
int __cdecl fcn_00521eb0(int, char*);
int __cdecl CloseVfsStream(int);
int __cdecl __strupr(char*);
int __cdecl sprintf(char*, const char*, ...);
int __cdecl d2_FindResourceByName(char*);
int __cdecl d2_AddElementToWindow(int, int, int, int);
int __cdecl d2_AddToRadioGroup(int, int);
int __cdecl d2_CreateChildWindow(int, int, int, int, int, int);
int __cdecl d2_SetElementFont(int, int);
int __cdecl d2_SetFormVisibility(int, int);
int __cdecl d2_PromptNetworkHost(void);
int __cdecl d2_SelectRadioGroup(int, int);
__declspec(dllimport) int __stdcall WritePrivateProfileStringA(char*, char*, char*, char*);

/* ADDRESS: GOLDTL 0x00539930 */
unsigned int __cdecl d2_ShowServerBrowser(int a0)
{
	int v17[24];
	char hosts[8][0x80];
	char header1[0xfc], header2[0xfc];
	
	
	
	
	
	
	char path[260];
	
	char mapName[128];
	char crestName[128];
	
	char savePath[260];
	
	
	int v36;
	int v38;
	int v4;
	int dialog;
	int v12;
	int group;
	int buttons[3];
	int v32;
	char v2;
	unsigned char v3;
	int v34;
	int v35;
	int v37;
	int v39;
	int v40;
	
	
	
	
	int* v31;
	int* v13;
	int* v33;
	char* v7;
	char* v8;
	unsigned char* v9;

	v38 = 0;
	v4 = 1;
	v36 = g_6b7fac;
	group = -1;
	dialog = d2_LoadForm(0, 0, s_6a3a6c);
	d2_PositionFormWindows(dialog, 1);
	d2_CenterForm(dialog, 2);
	d2_SetForm(dialog, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	d2_SetForm(dialog, 1);
	io_AppendText(0x1ca5);
	d2_SetForm(dialog, 3);
	d2_CreateButtonRow(d2_CurrentWindowId, 0, buttons, 3, g_14ac614, g_14ac618, g_14ac61c);
	d2_SetElementEnabled(buttons[0], 0);
	if (main_RunFrameLoop(0x539930, 0x24087) != 0) {
		do {
			if (g_6b7fac > v36 + 0x5dc || v4 != 0) {
				int v6;
				v4 = 1;
				d2_SuppressOverlay = 1;
				v6 = d2_OpenMessageBox(g_14ac5e4, 0);
				v36 = nt_ListenForServerAnnouncements(0x3039, 3000, ((char*) hosts), 8);
				d2_DestroyForm(v6);
				v32 = 0;
				d2_SuppressOverlay = 0;
				d2_SetForm(dialog, 2);
				d2_ClearWindowChildren(d2_CurrentWindowId, 1);
				if (group != -1) {
					d2_ClearRadioGroup(group);
				}
				group = (int) d2_CreateRadioGroup(0);
				if (v36 >= 1) {
					v12 = -0x116;
					v34 = 0;
					v35 = 0xc;
					v31 = v17;
					v37 = -0x116;
					do {
						int v11;
						v11 = *(int*) ((int) ((int*) ((char*) hosts + 0x7c)) + v32);
						*v31 = -1;
						if (v11 == 0x3f) {
							if (a0 != 0) {
								goto label_539d27;
							}
						} else if (v11 == 0x7f && a0 == 0) {
							goto label_539d27;
						}
						if (v11 == 0x3f) {
							v8 = &((char*) hosts + 0x16)[v32];
							strcpy(mapName, v8);
						} else {
							v13 = (int*) ((int) ((int*) ((char*) hosts + 0x5a)) + v32);
							sprintf(path, s_6a3a54, &((unsigned char*) hosts + 0x36)[v32 + 4]);
							v32 = vfs_Tfopen(path, 0x6750e8, g_6b7fdc);
							if (v32 != 0) {
								v4 = 1;
								fcn_00521eb0(v32, header1);
								v12 = 0;
								if ((int) ((*(unsigned int*) (header1 + 0x31)) & 0xff) > 0) {
									do {
										if (*v13 != ((int*) (header1 + 0x78))[v12]) {
											v4 = 0;
											goto label_539ba4;
										}
										v12 += 1;
										v13 = &v13[1];
									} while (v12 < (int) ((*(unsigned int*) (header1 + 0x31)) & 0xff));
									CloseVfsStream(v32);
								} else {
label_539ba4:
									CloseVfsStream(v32);
								}
							} else {
								v4 = 0;
							}
							v8 = &((char*) hosts + 0x16)[v34];
							strcpy(mapName, v8);
							v12 = v37;
							v32 = v34;
						}
						if (v4 != 0) {
							__strupr(mapName);
							sprintf(crestName, s_6a2e38, mapName);
							v32 = d2_FindResourceByName(crestName);
							if (v32 == -1) {
								v32 = d2_FindResourceByName(s_6a2e24);
							}
							d2_SetForm(dialog, 2);
							v32 = d2_AddElementToWindow(8, v34, v32, d2_CurrentWindowId);
							*v31 = v32;
							*(int*) (v32 * 0x2f4 + 0x5c + (int) g_1015ea0) = 1;
							if (*(int*) ((int) ((int*) ((char*) hosts + 0x7c)) + v34) == 0x3f
									&& ((unsigned char*) hosts + 0x36)[v34] <= ((unsigned char*) hosts + 0x36)[v34 + 1]) {
								d2_SetElementEnabled(v32, 0);
							}
							*(int*) (v32 * 0x2f4 + 0x1d0 + (int) g_1015ea0) = 3;
							d2_AddToRadioGroup(group, v32);
							v32 = d2_CreateChildWindow(0x88, v35, 400, 0x78, 0x10, d2_CurrentWindowId);
							v31[1] = v32;
							d2_SetElementFont(*(int*) (d2_CurrentWindowId * 0x3cc + 0x10161bc), 0x53);
							io_AppendText(0x1cbc, &((char*) hosts)[v34], v8, ((unsigned char*) hosts + 0x36)[v34]);
							v12 = v37;
							v32 = v34;
						} else {
							*v31 = -1;
						}
label_539d27:
						v31 = &v31[3];
						v32 += 0x80;
						v12 -= 0x80;
						v35 += 0x80;
						v36 -= 1;
						v34 = v32;
						v37 = v12;
					} while (v36 != 0);
				}
				v4 = 0;
				v36 = g_6b7fac;
			}
			if (g_14ce8e0 != 0 || g_14cf950 == 1) {
				g_774654 = 1;
			}
			if (g_100f1dc != -1) {
				if (d2_CurrentElementId == buttons[0]) {
					v32 = *(int*) (group * 0x8c + 0x102cbc8);
					if (v32 != -1) {
						v12 = v32 * 0x80;
						v8 = &((char*) hosts)[v12];
						v7 = v8;
						do {
							v2 = *v7;
							v7[0x7e2000 - (int) v8] = v2;
							v7 = &v7[1];
						} while (v2 != 0);
						WritePrivateProfileStringA(s_6a1e4c, s_6a3a4c, (char*) 0x7e2000, g_7e22c0);
						g_774654 = 1;
						v38 = 1;
						memcpy((void*) 0x9baa60, v8, 0x80);














						if (a0 != 0 && ((int*) ((char*) hosts + 0x7c))[v32 * 0x20] == 0x7f) {
							unsigned char* v10;
							v8 = &((char*) hosts + 0x16)[v12];
							v32 = (int) g_7e1d00 - (int) v8;
							do {
								v2 = *v8;
								v8[v32] = v2;
								v8 = &v8[1];
							} while (v2 != 0);
							v10 = &((unsigned char*) hosts + 0x36)[v12 + 4];
							v32 = -(int) v10;
							v9 = v10;
							do {
								v3 = *v9;
								v9[v32 + (int) g_7e21a0] = v3;
								v9 = &v9[1];
							} while (v3 != 0);
							do {
								v3 = *v10;
								v10[v32 + 0x7e254a] = v3;
								v10 = &v10[1];
							} while (v3 != 0);
							*(int*) &g_7747b0 |= 0x40;
							sprintf(savePath, s_6a3a54, g_7e21a0);
							memset(header2, 0, sizeof(header2));







							v32 = vfs_Tfopen(savePath, 0x6750e8, g_6b7fdc);
							if (v32 != 0) {
								fcn_00521eb0(v32, (char*) ((int*) header2));
								CloseVfsStream(v32);
							}
							memset((void*) 0x9bada0, 0, 0x30);








							g_9badc0 = (*(unsigned int*) (header2 + 0x60)) & 0xff;
							g_9badc4 = (*(unsigned int*) (header2 + 0x6c)) & 0xff;
							v32 = 0;
							do {
								v2 = header2[0x40 + v32];
								((char*) 0x9bada0)[v32] = v2;
								v32 += 1;
							} while (v2 != 0);
							if (((int*) header2)[0] >= 0x10054) {
								v32 = 0;
								do {
									v2 = header2[0x50 + v32];
									((char*) 0x9badb0)[v32] = v2;
									v32 += 1;
								} while (v2 != 0);
								g_9badc8 = (int) ((*(unsigned int*) (header2 + 0x63)) & 0xff);
								g_9badcc = (*(unsigned int*) (header2 + 0x64));
							}
						}
					}
				} else if (d2_CurrentElementId == buttons[1]) {
					v4 = 1;
				} else if (d2_CurrentElementId == buttons[2]) {
					d2_SetFormVisibility(dialog, 0);
					if (d2_PromptNetworkHost() != 0) {
						g_774654 = 1;
						v38 = 1;
					}
					d2_SetFormVisibility(dialog, 1);
				}
			}
			if (*(int*) (group * 0x8c + 0x102cbc8) != -1) {
				d2_SetElementEnabled(buttons[0], 1);
			} else {
				d2_SetElementEnabled(buttons[0], 0);
			}
		} while (main_RunFrameLoop(0x539930, 0x24087) != 0);
		if (group != -1) {
			d2_ClearRadioGroup(group);
		}
	}
	d2_DestroyForm(dialog);
	return v38;
}
