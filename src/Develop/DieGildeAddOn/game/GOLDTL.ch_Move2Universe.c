#include <string.h>

extern char g_10432c0[];
extern int d3_CurrentContextIndex;
extern int g_67530c;
extern int g_675310;

void __cdecl ReportClientMessage(const char* msg);
#include "Develop/DieGildeAddOn/game/ch_queue.h"
char* __cdecl fcn_00445600(char* a, int b, char* c, char* d);
void __cdecl d3_TransformPoint(char* src, char* pos, float* out);
int __cdecl ch_MoveCharacter2Universe(char* obj, void* universe);
char __cdecl SelectTextureSet(void* obj, void* ctx, unsigned char a, char b);
#include "Develop/DieGildeAddOn/game/ch_action.h"
void __cdecl ch_SetPosition(char* obj, float* position, int flag);
void __cdecl fcn_004432d0(int a, int b);
void __cdecl ch_SetVisible(char* obj, int shown);

/* ADDRESS: GOLDTL 0x00407390 */
void __cdecl ch_Move2Universe(char* a0)
{
	char* action;
	char* character;
	char* p;
	int contextIndex;
	int v5;
	char v8[16];
	char name[0x80];

	action = a0;
	contextIndex = *(int*) (a0 + 0x30);
	character = *(char**) (a0 + 0x14);
	if (contextIndex < 0) {
		ReportClientMessage((char*) 0x675a40);
		ch_RemoveQueueEntry(action);
		return;
	}
	if ((contextIndex == 0) == (*(int*) (action + 0x34) != -1)) {
		if (contextIndex == 0) {
			ReportClientMessage((char*) 0x6759c8);
		} else {
			ReportClientMessage((char*) 0x675950);
		}
		ch_RemoveQueueEntry(action);
		return;
	}
	v5 = (int) ch_MoveCharacter2Universe(character, g_10432c0 + contextIndex * 0x3dc);
	if (v5 == 0) {
		ReportClientMessage((char*) 0x675918);
		ch_RemoveQueueEntry(action);
		return;
	}
	{
		int saved = d3_CurrentContextIndex;

		fcn_004432d0(*(int*) (action + 0x30), 1);
		if (*(int*) (action + 0x30) == 0) {
			if (g_67530c == *(int*) (character + 0x2c))
				SelectTextureSet(*(void**) (character + 0x34),
					(char*) *(int*) (*(int*) (character + 0x34) + 0x1ec) + 0xf4,
					0, 0);
		} else {
			if (g_67530c == *(int*) (character + 0x2c))
				SelectTextureSet(*(void**) (character + 0x34),
					(char*) *(int*) (*(int*) (character + 0x34) + 0x1ec) + 0xf4,
					*(unsigned char*) (character + 0x23a), 1);
		}
		ch_ClearSitting((unsigned char*) character);
		if (*(char*) (action + 0x17c)) {
			ch_SetPosition(character, (float*) (action + 0x180), 0);
		} else {
			if (*(char*) (action + 0xf0)) {
				strcpy(name, action + 0xf0);
			} else {
				memcpy(name, (void*) 0x675908, 14);
			}
			p = fcn_00445600(0, 0x100, 0, name);
			if (p != 0 || (p = fcn_00445600(0, 0x100, 0, (char*) 0x675908)) != 0
				|| (p = fcn_00445600(0, 0x100, 0, (char*) 0x675908)) != 0) {
				d3_TransformPoint(p, p + 0x4c, (float*) v8);
				ch_SetPosition(character, (float*) v8, 0);
			}
		}
		*(int*) (character + 0x2c) = *(int*) (action + 0x34);
		*(int*) (character + 0x30) = *(int*) (action + 0x38);
		*(int*) (character + 0x38) = 0;
		*(int*) (character + 0x3c) = 0;
		*(int*) (character + 0x40) = 0;
		ch_SetVisible(character, 1);
		if (saved == *(int*) (action + 0x30)) {
			if ((*(int*) (character + 0x2c) != -1 && g_67530c != *(int*) (character + 0x2c))
				|| (g_675310 != -1 && g_675310 != *(int*) (character + 0x30)))
				ch_SetVisible(character, 0);
		}
		if (*(int*) (action + 0x28) != 0
			&& *(char*) (*(int*) (action + 0x28) + 9) == 0x38)
			ch_SetVisible(character, 0);
		fcn_004432d0(saved, 1);
		ch_RemoveQueueEntry(action);
	}
}
