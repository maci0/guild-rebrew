#include "Develop/client_types.h"
#pragma pack(push, 2)







typedef struct Msg5a2db0 {
	int pad0;
	unsigned char type;
	char pad5[3];
	int seed;
	int id;
	char pad10[0x28 - 0x10];
	pos14_7f4c00 pos;
	unsigned char flag;
	char pad37[0x58 - 0x37];
	unsigned char mode;
	char pad59[3];
	int target;
	int from;
	char pad64[0xf8 - 0x64];
} Msg5a2db0;
#pragma pack(pop)

#include <string.h>


extern char* g_14ab4ec;
extern char* g_14ab54c;
extern char* g_14ab5cc;
extern char* g_7746a0;
extern int g_774808;
extern char g_14cf950;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern char g_7f4ca4[];
extern pos14_7f4c00 gm_GameTime;

void __cdecl d2_ClearStatusTextSlots(void);
int __cdecl main_RunFrameLoop(void*, int);
char* __cdecl RegisterStatusText(char* name, char* path, int arg);
void __cdecl d2_OpenContactEinkaufPanel(char* e);
void __cdecl d2_ShowWirtshausDialog(char* e);
void __cdecl d2_OpenStammtischDialog(char* a, char* b);
void __cdecl d2_OpenDunkleEcke(char* a, char* b);
void __cdecl cm_SendCopyEntityData(Msg5a2db0* m);

#pragma optimize("y", off)


/* Runs one contact/office tick per pumped message, resolving the three
 * office markers and dispatching on the active contact. */
/* ADDRESS: GOLDTL 0x005a2db0 */
void __cdecl d2_RunWirtshausContactMenu(char* target, char* actor)
{
	Msg5a2db0 m;
	char* p1;
	char* p2;
	char* p3;

	d2_ClearStatusTextSlots();
	while (main_RunFrameLoop(d2_RunWirtshausContactMenu, 0x67fff)) {
		d2_OpenContactEinkaufPanel(target);
		p1 = RegisterStatusText("contact_WUERFELSPIEL", g_14ab4ec, 0x16);
		p2 = RegisterStatusText("contact_STAMMTISCH", g_14ab54c, 0x16);
		p3 = RegisterStatusText("ob_DUNKLE_ECKE", g_14ab5cc, 0x16);
		if (g_7746a0) {
			if (g_7746a0 == p1) {
				d2_ShowWirtshausDialog(target);
			} else if (g_7746a0 == p2) {
				d2_OpenStammtischDialog(target, actor);
			} else if (g_7746a0 == p3) {
				d2_OpenDunkleEcke(target, actor);
			}
		}
		if (g_774808) {
			if (g_14cf950 == 0x12) {
				{
					void* fill_dst;
					int fill_len;
					fill_dst = &m;
					fill_len = sizeof(m);
					__asm {
						mov edi, fill_dst
						mov ebx, fill_len
						xor eax, eax
						lea ecx, [edi+edi*2]
						and ecx, 3
						sub ebx, ecx
						jle short fill_done
						rep stosb
						mov ecx, ebx
						and ebx, 3
						shr ecx, 2
						rep stosd
					fill_done:
						add ecx, ebx
						rep stosb
					}
				}
				m.type = 0x74;
				m.seed = *(int*) (g_7f4ca4 + g_774970 * 0x21c);
				m.id = -1;
				m.pos = *(pos14_7f4c00*) &gm_GameTime;
				m.flag = 2;
				m.target = *(int*) (target + 1);
				m.from = *(int*) (actor + 2);
				cm_SendCopyEntityData(&m);
			} else if (g_14cf950 == 0x17) {
				d2_OpenDunkleEcke(target, actor);
			}
		}
	}
}
