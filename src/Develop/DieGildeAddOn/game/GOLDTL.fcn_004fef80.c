


typedef struct
{
	unsigned short id;
	char pad2[6];
	unsigned char x8;
	char pad9;
	unsigned short xa;
	char padc[4];
	float f10;
	char pad14[8];
	float f1c;
	float f20;
	int x24;
} ENTITY_HEALTH_OBJ;
// SIZE 0x28

extern float g_662a94;

/* ADDRESS: GOLDDE 0x004eaa00 */
float __cdecl gm_GetEntityHealth(ENTITY_HEALTH_OBJ* p)
{
	float x;
	float v;

	if (p->id == 0xffff) {
		return -1.0f;
	}
	if (p->x8 == 0) {
		return -1.0f;
	}
	x = p->xa;
	if (x <= p->f20) {
		v = x * ((p->f1c - p->f10) / p->f20) + p->f10;
	} else {
		v = p->f1c;
	}
	v += p->x24;
	return (float)(v > 0.0 ? v : 0.0);
}




typedef struct
{
	unsigned short id;
	char p2[6];
	char active;
	char p9;
	unsigned short cur;
	char pc[4];
	float lo;
	char p14[8];
	float hi;
	float max;
} ENTITY_HEALTH_VIEW;
// SIZE 0x24


/* ADDRESS: GOLDDE 0x004eaa70 */
float __cdecl gm_GetEntityMaxHealth(ENTITY_HEALTH_VIEW* bar)
{
	float v;

	if (bar->id == 0xffff) {
		return -1.0f;
	}
	if (bar->active == 0) {
		return -1.0f;
	}
	v = bar->cur;
	if (v <= bar->max) {
		return (bar->hi - bar->lo) / bar->max * v + bar->lo;
	}
	return bar->hi;
}

extern float flt_0_0;


/* ADDRESS: GOLDTL 0x004ff040 */
/* ADDRESS: GOLDDE 0x004eaac0 */
float __cdecl gm_GetEntityHealthRatio(ENTITY_HEALTH_VIEW* bar)
{
	if (bar->id == 0xffff) {
		return flt_0_0;
	}
	if (bar->active == 0) {
		return flt_0_0;
	}
	return gm_GetEntityHealth((ENTITY_HEALTH_OBJ*) bar) / gm_GetEntityMaxHealth(bar);
}

#include "Develop/DieGildeAddOn/game/entity_record.h"


/* Named float addends: the two rounding stores die late and leave the
 * reference's fxch; fxch before faddp. */
/* ADDRESS: GOLDTL 0x004ff080 */
float __cdecl gm_CalcEntityHealthScore(unsigned short id)
{
	ENTITY_HEALTH_VIEW* p;
	float v;
	float a;
	float b;

	p = (ENTITY_HEALTH_VIEW*) (((char*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[id]));
	if (p->active == 1 || p->active == 0) {
		return flt_0_0;
	}
	v = gm_GetEntityMaxHealth(p);
	a = (float)(gm_GetEntityHealth((ENTITY_HEALTH_OBJ*) p) / v * 0.8);
	b = (float)(v * 0.001f * 0.2);
	return a + b;
}
