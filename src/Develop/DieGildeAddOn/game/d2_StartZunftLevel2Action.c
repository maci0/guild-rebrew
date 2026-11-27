


typedef struct {
	char b[0x21c];
} ZUNFT_UPGRADE_ENTITY_VIEW;
// SIZE 0x21c

extern char g_7f4ca0[];
#include "Develop/DieGildeAddOn/game/game_player.h"
extern int g_14aad38;
extern int g_14aac9c;
extern char g_7d4190[];

int __cdecl amt_CanUpgradeBuildingTier2(ZUNFT_UPGRADE_ENTITY_VIEW* e);
void __cdecl d2_ShowModalMessageBox(int, int);
void __cdecl d2_CheckActionBlocker(ZUNFT_UPGRADE_ENTITY_VIEW* e, int);
void __cdecl d2_RunZunftLevel2Dialog(void);
void __cdecl d2_RunCityScrollMapDialog(int, char*, int, void (__cdecl*)(void), int);

#pragma optimize("y", off)
void __cdecl d2_StartZunftLevel2Action(void)
{
	char buf[0x50];
	char* fdest;
	int flen;
	int r;

	r = amt_CanUpgradeBuildingTier2(&((ZUNFT_UPGRADE_ENTITY_VIEW*)g_7f4ca0)[g_774970]);
	if (r != 1) {
		if (r == -1) {
			d2_ShowModalMessageBox(g_14aad38, 0);
			return;
		}
		d2_CheckActionBlocker(&((ZUNFT_UPGRADE_ENTITY_VIEW*)g_7f4ca0)[g_774970], 5);
		return;
	}
	flen = 0x50;
	fdest = buf;
	__asm {
		mov edi, fdest
		mov ebx, flen
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
	*(int*) (buf + 0) = 1;
	*(int*) (buf + 4) = -1;
	*(int*) (buf + 0x10) = 6;
	*(char**) (buf + 8) = g_7d4190;
	*(int*) (buf + 0xc) = 1;
	*(int*) (buf + 0x4c) = 0x727;
	d2_RunCityScrollMapDialog(1, buf, g_14aac9c, d2_RunZunftLevel2Dialog, 0);
}
#pragma optimize("", on)
