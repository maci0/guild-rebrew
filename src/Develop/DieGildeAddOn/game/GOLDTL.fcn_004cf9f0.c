#include <string.h>


/* ADDRESS: GOLDTL 0x004cf9f0 */
int __cdecl d3_GetObjectEntity(char* p)
{
	return *(int*) (p + 0x204);
}

/* 0x4d4790 lives in this file because it calls fcn_004cf9f0 and keeps a value
 * in edx across that call: msvc6 does that only for a callee compiled earlier in
 * the same translation unit, whose register use it has already seen. */

extern unsigned short* g_772e98;

void* __cdecl gm_GetEquippedCombatGear(char*);
float __cdecl gm_GetEntityHealthRatio(char*);
void __cdecl d3_SpawnBlutEffect(int, int, float, float, float, float);
#include "Develop/DieGildeAddOn/game/ch_queue.h"
int __cdecl ch_RunDeathFallAction(void);
char* __cdecl ch_CreateQueuedAction(char*, int (__cdecl*)(void), int, int, int);
void __cdecl sb_PlayVoice(int, char*, int, int, int, int, int);
unsigned int __cdecl cut_RandMod(int);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl d3_ApplyWorldTransformToObject(char*, char*, char*);
void __cdecl d3_SetObjectVisible(char*, int);
void __cdecl d2_ShowStatusBanner(char*);


/* ADDRESS: GOLDTL 0x004d4790 */
int __cdecl cut_HandleUnitDefeat(char* e)
{
	char buf[0x100];
	char* p;
	char* q;

	gm_GetEquippedCombatGear(e);
	if (gm_GetEntityHealthRatio(e) < 0.05) {
		d3_SpawnBlutEffect(*(int*) (*(char**) (e + 0x184) + 0x34), 0x40, 0.25f, 0.1f, 0.14f, 55.0f);
		ch_CancelActionQueue(*(char**) (e + 0x184));
		p = ch_CreateQueuedAction(*(char**) (e + 0x184), ch_RunDeathFallAction, 0x14, 0x36, 1);
		strcpy(p + 0xf0, "kampf/todumfallen");
		e[8] = 0;
		*(int*) (*(char**) (*(char**) (e + 0x184) + 0x34) + 0x220) = 0;
		sb_PlayVoice(0, "Schmerzschrei", 1, 0x3f, 0x7f, 0, 0);
		if (cut_RandMod(100) > 50) {
			*(int*) (e + 0x24) = (int) (-(int) *(float*) (e + 0x1c) - 20.0);
			io_FormatTextBuffer(buf, 0x1181, *(unsigned short*) e);
		} else {
			*(int*) (e + 0x24) = (int) (10.0 - (int) *(float*) (e + 0x1c));
			io_FormatTextBuffer(buf, 0x1182, *(unsigned short*) e);
		}
		q = *(char**) (e + 0x1ac);
		if (q != 0) {
			d3_ApplyWorldTransformToObject(q, *(char**) (*(char**) (e + 0x184) + 0x34) + 0x4c, *(char**) (*(char**) (e + 0x184) + 0x34) + 0x18c);
			d3_SetObjectVisible(q, 1);
			*(char**) (e + 0x1ac) = 0;
			*(int*) (d3_GetObjectEntity(q) + 0xa) = *g_772e98;
		}
		d2_ShowStatusBanner(buf);
		return 1;
	}
	return 0;
}

extern unsigned short* g_772e9c;

char __cdecl d3_SetSubtreeVisible(int, unsigned char);


/* ADDRESS: GOLDTL 0x004d4ee0 */
void __cdecl cut_CollectGroundItem(char* e)
{
	char* q;
	char* o;
	char* r;

	q = *(char**) (e + 0x180);
	o = *(char**) (e + 0x17c);
	r = (char*) d3_GetObjectEntity(q);
	if (r != 0) {
		*(int*) (r + 0xa) = *g_772e9c;
		*(char**) (o + 0x1ac) = q;
	}
	d3_SetSubtreeVisible((int) q, 0);
}
