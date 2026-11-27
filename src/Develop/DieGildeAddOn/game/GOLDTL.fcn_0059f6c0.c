


void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)

typedef struct
{
	int a;
	int size;
	int c;
	int d;
	int kind;
	int pad[14];
	int id;
} Req;
// SIZE 0x50

extern int g_7746a0;
extern int g_14aaf18;
extern int g_14aaf38;
extern int g_14ad2c0;
extern int g_14ab04c;
extern __int64 g_666018;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char s_6aa714[];
extern char s_6aa700[];
extern char s_6aa6e4[];
extern char s_6aa6d0[];

void __cdecl fcn_005338a0(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl fcn_005bdc30(int, Req*, char*, void*, int);
int __cdecl d2_OpenTargetPicker(Req*, char*, int, void*);
void __cdecl d3_EndCameraAndUiMode(void);
void __cdecl d2_RunTalenteDialog(int, int, int);
void __cdecl d2_OpenPaymentTargetPicker(int);
void __cdecl d2_RunSabotageDialog(void);
void __cdecl d2_RunBeatupDialog(void);

/* The first request's zero-fill is the original's hand-written block-fill
 * prelude; recorded C memset probes did not emit it (archived docs/codegen-walls.md
 * section 6b). */
void __cdecl d2_RunSabotageActionsHud(int entity, int mode)
{
	int a;
	int b;
	int c;
	int d;

	fcn_005338a0();
	if (main_RunFrameLoop((void*) d2_RunSabotageActionsHud, 0x67fff) != 0) {
		do {
			a = RegisterStatusText(s_6aa714, g_14aaf18, 0x17);
			b = RegisterStatusText(s_6aa700, g_14aaf38, 0xd);
			c = RegisterStatusText(s_6aa6e4, g_14ad2c0, 0xc);
			d = RegisterStatusText(s_6aa6d0, g_14ab04c, 0x10);
			if (g_7746a0 != 0) {
				if (g_7746a0 == a) {
					Req req;
					char text[0x80];
					int n;
					Req* p;

					n = 0x50;
					p = &req;
					__asm {
						mov edi, p
						mov ebx, n
						xor eax, eax
						lea ecx, [edi+edi*2]
						and ecx, 3
						sub ebx, ecx
						jle short L1
						rep stosb
						mov ecx, ebx
						and ebx, 3
						shr ecx, 2
						rep stosd
					L1:
						add ecx, ebx
						rep stosb
					}
					req.a = 1;
					req.size = -1;
					req.kind = 6;
					req.c = 0xe07c43b4;
					req.d = 3;
					req.id = 0x727;
					io_FormatTextBuffer(text, 0x16ff);
					fcn_005bdc30(1, &req, text, (void*) d2_RunSabotageDialog, 0);
				}
				else if (g_7746a0 == b) {
					Req req;
					char text[0x40];

					memset(&req, 0, sizeof(req));
					req.size = 0x400;
					req.kind = 6;
					req.c = (*(int*)&g_666018);
					req.d = g_66601c;
					req.id = 0x727;
					io_FormatTextBuffer(text, 0x1707);
					d2_OpenTargetPicker(&req, text, 0, (void*) d2_RunBeatupDialog);
					d3_EndCameraAndUiMode();
				}
				else if (g_7746a0 == c) {
					d2_RunTalenteDialog(entity, mode, 2);
				}
				else if (g_7746a0 == d) {
					d2_OpenPaymentTargetPicker(entity);
				}
			}
		} while (main_RunFrameLoop((void*) d2_RunSabotageActionsHud, 0x67fff) != 0);
	}
}
