#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_675310; extern int g_67530c; extern int g_774658; extern int g_774650; extern int g_6a2520; extern int g_7725c8; extern int g_774688; extern int g_77468c;
void __cdecl fcn_00530510(void); void __cdecl sv_ClearObjectSelection(void);
void __cdecl init_LoadObjektScene(int);
void __cdecl fcn_004432d0(int, int);
void __cdecl fcn_0043aa30(int);
void __cdecl fcn_005167c0(void*, int);
void __cdecl fcn_00516c50(void*, void*);
void __cdecl fcn_00438b40(void*, void*);
void __cdecl fcn_00438cb0(void*, void*);
void __cdecl fcn_005338a0(void);
void* __cdecl fcn_00426cc0(int);
void __cdecl fcn_00428720(void*);
void __cdecl fcn_005312d0(int);
void __cdecl fcn_0043a9c0(int);
void* __cdecl fcn_00502cd0(int, int, int, int, int);
void __cdecl fcn_0058f700(void*);
void __cdecl fcn_0058fdc0(void*);
void __cdecl fcn_0059b050(void*);
void __cdecl fcn_0059b0b0(void*);
void __cdecl fcn_0059b140(void*);
void __cdecl fcn_0059c760(void*);
void __cdecl fcn_0059cd20(void*);
void __cdecl fcn_00590330(void*);
void __cdecl fcn_0058ff00(void*);
void __cdecl fcn_005e6840(void*);
void __cdecl fcn_005e68e0(void*);
void __cdecl fcn_005e6950(void*);

/* Saves the current render/scene state, notifies the game of the incoming
 * message id, dispatches it to its handler and then restores the state. */
/* ADDRESS: GOLDTL 0x005a86a0 */
void __cdecl fcn_005a86a0(void* a0)
{
	int save10;
	int save40;
	int save44;
	int save48;
	int save50;
	int save54;
	int save58;
	unsigned short id;
	char v1;
	char* saved688;
	void* t;
	int sub;
	void* message;

	message = a0;
	sub = -1;
	save10 = *(int*) &g_6b8010;
	*(void**) &g_7746cc = a0;
	*(int*) &g_6791c8 = *(int*) ((char*) a0 + 2);
	g_675310 = *(int*) ((char*) a0 + 2);
	g_774658 = g_774650 + 1;
	save40 = *(int*) &g_7e3a40;
	save44 = *(int*) &g_7e3a44;
	save48 = *(int*) &g_7e3a48;
	save50 = *(int*) &g_7e3a50;
	save54 = *(int*) &g_7e3a54;
	save58 = *(int*) &g_7e3a58;
	g_6a2520 = 0;
	fcn_00530510();
	sv_ClearObjectSelection();
	id = *(unsigned short*) a0;
	v1 = *(char*) (id + (unsigned long)&g_7f3b40);
	if (v1 != (char) 0xfe) {
		if (v1 == (char) 0xff || *(char*) ((int) v1 * 0x3dc + 0x1043695) != 0) {
			g_7725c8 = 1;
			init_LoadObjektScene(id);
			g_7725c8 = 0;
		}
		*(unsigned short*) (*(int*) &g_7746c8 + 0x29) = *(unsigned short*)message;
		fcn_004432d0(*(char*) (*(unsigned short*)message + (unsigned long)&g_7f3b40), 0);
		fcn_0043aa30(3);
		fcn_005167c0(*(void**) &g_7746c8, *(unsigned short*)message);
		fcn_00516c50(*(void**) &g_7746c8, a0);
		if (*(void**) &g_67a370 != 0) {
			t = *(void**) ((char*) *(void**) &g_67a370 + 0x3c8);
			if (t != 0 && *(void**) ((char*) t + 0x210) != 0) {
				((void (__cdecl*) (void*, int, void*, void*)) *(void**) ((char*) t + 0x210))
					(*(void**) &g_67a370, 4, (char*) t + 0x214, 0);
			}
		}
		sub = *(int*) &g_6791d0;
		fcn_00438b40(*(void**) &g_6b8014, (char*) *(void**) &g_6b8014 + 0x5c);
		fcn_00438cb0(*(void**) &g_6b8014, (char*) *(void**) &g_6b8014 + 0x90);
		saved688 = (char*)g_774688;
		*(int*) &g_7e3a40 = *(int*) ((char*) *(void**) &g_6b8014 + 0x4c);
		*(int*) &g_7e3a44 = *(int*) ((char*) *(void**) &g_6b8014 + 0x50);
		*(int*) &g_7e3a48 = *(int*) ((char*) *(void**) &g_6b8014 + 0x54);
		*(int*) &g_7e3a50 = *(int*) ((char*) *(void**) &g_6b8014 + 0x84);
		*(int*) &g_7e3a54 = *(int*) ((char*) *(void**) &g_6b8014 + 0x88);
		*(int*) &g_7e3a58 = *(int*) ((char*) *(void**) &g_6b8014 + 0x8c);
		a0 = *(void**)&g_77468c;
		*(void**)&g_774688 = 0;
		*(void**)&g_77468c = 0;
	} else {
		saved688 = a0;
	}
	*(char*) &g_772d10 = 0;
	switch (*(unsigned short*)message) {
	case 0x205:
		fcn_0058fdc0(*(void**) &g_7746c8);
		break;
	case 0x2c:
	case 0x109:
		fcn_0059b050(*(void**) &g_7746c8);
		break;
	case 0x2d:
		fcn_0059b0b0(*(void**) &g_7746c8);
		break;
	case 0x33:
		fcn_0059b140(*(void**) &g_7746c8);
		break;
	case 0x37:
		fcn_0059c760(*(void**) &g_7746c8);
		break;
	case 0x107:
		fcn_0059cd20(*(void**) &g_7746c8);
		break;
	case 0x211:
		fcn_00590330(*(void**) &g_7746c8);
		break;
	case 0x21b:
		fcn_0058ff00(*(void**) &g_7746c8);
		break;
	case 0x276:
		fcn_005e6840(*(void**) &g_7746c8);
		break;
	case 0x27f:
		fcn_005e6950(*(void**) &g_7746c8);
		break;
	case 0x28a:
		fcn_005e68e0(*(void**) &g_7746c8);
		break;
	default:
		fcn_0058f700(message);
		break;
	}
	*(char*) &g_772d10 = 1;
	fcn_00530510();
	sv_ClearObjectSelection();
	fcn_005338a0();
	*(void**) &g_7ea360 = 0;
	if (sub != -1) {
		t = fcn_00426cc0(sub);
		if (t != 0) {
			fcn_00428720(t);
			fcn_005312d0(*(int*) ((char*) t + 0x100));
		}
	}
	if (*(void**) &g_67a370 != 0) {
		t = *(void**) ((char*) *(void**) &g_67a370 + 0x3c8);
		if (t != 0 && *(void**) ((char*) t + 0x294) != 0) {
			((void (__cdecl*) (void*, int, void*, void*)) *(void**) ((char*) t + 0x294))
				(*(void**) &g_67a370, 5, (char*) t + 0x298, 0);
		}
	}
	if (*(int*) &g_6791d0 != -1) {
		fcn_005312d0(*(int*) &g_6791d0);
	}
	fcn_0043a9c0(3);
	fcn_004432d0(save10, 0);
	*(void**) &g_7746cc = 0;
	*(unsigned short*) (*(int*) &g_7746c8 + 0x29) = 0xfd;
	*(int*) &g_6791c8 = 0;
	g_67530c = *(int*) (*(int*) &g_7746c8 + 1);
	save10 = *(int*) (*(int*) &g_7746c8 + 0x5d);
	g_675310 = *(int*) ((char*) fcn_00502cd0(save10, 2, 6, 0, 0xfd) + 2);
	g_774658 = g_774650;
	*(void**)&g_77468c = a0;
	*(int*) &g_7e3a40 = save40;
	*(int*) &g_7e3a44 = save44;
	*(int*) &g_7e3a48 = save48;
	*(void**)&g_774688 = saved688;
	*(int*) &g_7e3a50 = save50;
	*(int*) &g_7e3a54 = save54;
	*(int*) &g_7e3a58 = save58;
}
