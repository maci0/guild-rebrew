#include "Develop/DieGildeAddOn/game/entity_record.h"
/* Settlement/party interaction step: resolves the current interaction entity,
 * scores the houses around the actor on the 0x90e0a0/0x869480 influence
 * matrices, then raises the script events (0x210..0x218) and the ambient
 * dialogue for the chosen house. */
#include <stdlib.h>
#include "Develop/DieGildeAddOn/game/game_matrices.h"
extern int g_7747b4;
extern char g_7f4ca0[];

int __cdecl gm_IsNpcEntityState(void*);
int __cdecl fcn_00508eb0(int, int);
float __cdecl gm_CalcEntityFavor(unsigned int a0, unsigned int a1, unsigned int a2);
unsigned short __cdecl gm_RandomMod(int);
void __cdecl cm_BeginPacketFieldDelta(int, int);
void __cdecl cm_AppendPacketFieldDelta(int, int, int, void*);
void __cdecl cm_AppendPacketFieldValue(int, int, int, void*);
void __cdecl cm_RequestChangeAttribute(void);
void __cdecl cm_RequestCopyEntityData(int, int, int, int);
void* __cdecl gm_LookupEntityRecordById(int);
int __cdecl he_NotifyFeudDeclared(void*, void*);
void* __cdecl he_NotifyFeudEscalated(void*, void*);
void __cdecl he_NotifyFeudEnded(void*, void*);

/* ADDRESS: GOLDTL 0x0047d2a0 */
int __cdecl ai_UpdateEntityFeud(char* entity)
{
	register char* h;
	register char* other;
	int best;
	float bestscore;
	register int i;
	int d;
	float f;
	unsigned char b;
	unsigned char b2;
	unsigned char zeroVal;

	if (*(int*) (entity + 0x210) == -1) {
		if (entity[0x166] == 0 && entity[0x169] == 0 && entity[2] != 5) {
			return 0;
		}
		best = -1;
		bestscore = 128.0f;
		i = 0;
		for (h = g_7f4ca0 + 2; (int) h < 0x85a0a2; h += (int)sizeof(ENTITY_RECORD), i++) {
			if (!((i != (int) *(unsigned short*) entity && h[0] == 6) || h[0] == 7)) {
				if (gm_IsNpcEntityState(h - 2) == 0 || (h[0x164] == 0 && h[0x167] == 0)) {
					continue;
				}
			}
			d = abs(fcn_00508eb0(i, 0) - fcn_00508eb0(*(unsigned short*) entity, 0));
			f = (10.0f - (float) d * 0.5f) * 0.1f;
			if ((float) (signed char) g_90e0a0[i][*(unsigned short*) entity] * f < bestscore) {
				if (gm_CalcEntityFavor(i, (int) *(unsigned short*) entity, 1) < 34.0f) {
					bestscore = (float) (signed char) g_90e0a0[i][*(unsigned short*) entity] * f;
					best = i;
				}
			}
		}
		if (best == -1) {
			return 0;
		}
		if (((signed char) g_869480[best][*(unsigned short*) entity] / 2
		     + (signed char) g_90e0a0[best][*(unsigned short*) entity])
		    >= -50 - ((int) gm_RandomMod(0x20) & 0xffff)) {
			return 0;
		}
		b = 0;
		cm_BeginPacketFieldDelta((int) entity, *(int*) (entity + 4));
		cm_AppendPacketFieldDelta(1, 1, 0x215, &b);
		d = abs((int) bestscore);
		b = (unsigned char) (d / 3 + 1);
		if ((((int) b < g_7747b4 + g_7747b4 + 0x23) ? (int) b : (g_7747b4 + g_7747b4 + 0x23))
		    <= g_7747b4 + g_7747b4 + 0xf) {
			b = (unsigned char) (g_7747b4 + g_7747b4 + 0xf);
		} else if ((int) b >= g_7747b4 + g_7747b4 + 0x23) {
			b = (unsigned char) (g_7747b4 + g_7747b4 + 0x23);
		}
		cm_AppendPacketFieldDelta(1, 1, 0x216, &b);
		h = (char *)&((ENTITY_RECORD*)g_7f4ca0)[best];
		cm_AppendPacketFieldDelta(4, 1, 0x210, h + 4);
		cm_AppendPacketFieldDelta(1, 1, 0x214, &g_90e0a0[best][*(unsigned short*) entity]);
		cm_RequestChangeAttribute();
		cm_RequestCopyEntityData(*(int*) (h + 4), *(int*) (entity + 4), 0, 2);
		he_NotifyFeudDeclared(entity, h);
		return 0;
	}
	other = (char*) gm_LookupEntityRecordById(*(int*) (entity + 0x210));
	if ((entity[0x166] == 0 && entity[0x169] == 0 && entity[2] != 5) || other == 0) {
		goto reset;
	}
	if (other[0x169] == 0 && other[0x166] == 0 && other[2] != 6
	    && other[2] != 7 && other[2] != 5) {
		goto reset;
	}
	if ((int) (unsigned char) entity[0x215] > (int) (unsigned char) entity[0x216] + 5) {
		goto reset;
	}
	if ((unsigned char) entity[0x215] >= (unsigned char) entity[0x216]) {
		goto pulse;
	}
	if ((signed char) g_90e0a0[*(unsigned short*) other][*(unsigned short*) entity]
	    + (signed char) entity[0x214] > 0) {
		goto pulse2;
	}
	if ((unsigned char) entity[0x215] > 3) {
		return (int) other;
	}
	b = (unsigned char) ((int) gm_RandomMod(2) + 1);
	cm_BeginPacketFieldDelta((int) entity, *(int*) (entity + 4));
	cm_AppendPacketFieldValue(1, 1, 0x215, &b);
	if ((int) (unsigned char) entity[0x215] + b > 3) {
		cm_AppendPacketFieldDelta(1, 1, 0x218, entity + 0x217);
	}
	cm_RequestChangeAttribute();
	if ((int) (unsigned char) entity[0x215] + b <= 3) {
		return 0;
	}
	he_NotifyFeudEscalated(entity, other);
	return (int) other;

reset:
	b = 0;
	b2 = 0;
	best = -1;
	zeroVal = 0;
	cm_BeginPacketFieldDelta((int) entity, *(int*) (entity + 4));
	cm_AppendPacketFieldDelta(1, 1, 0x215, &b);
	cm_AppendPacketFieldDelta(1, 1, 0x216, &b2);
	cm_AppendPacketFieldDelta(4, 1, 0x210, &best);
	cm_AppendPacketFieldDelta(1, 1, 0x214, &zeroVal);
	cm_RequestChangeAttribute();
	b = 1;
	cm_AppendPacketFieldDelta(1, 1, 0x218, &b);
	cm_RequestChangeAttribute();
	if (other != 0) {
		cm_RequestCopyEntityData(*(int*) (entity + 0x210), *(int*) (entity + 4), 0x3c, 2);
		he_NotifyFeudEnded(entity, other);
	}
	return 0;

pulse:
	b = 1;
	b2 = 1;
	cm_BeginPacketFieldDelta((int) entity, *(int*) (entity + 4));
	cm_AppendPacketFieldValue(1, 1, 0x215, &b);
	cm_AppendPacketFieldDelta(1, 1, 0x218, &b2);
	cm_RequestChangeAttribute();
	return 0;

pulse2:
	b = (unsigned char) (entity[0x216] + 1);
	b2 = 1;
	cm_BeginPacketFieldDelta((int) entity, *(int*) (entity + 4));
	cm_AppendPacketFieldDelta(1, 1, 0x215, &b);
	cm_AppendPacketFieldDelta(1, 1, 0x218, &b2);
	cm_RequestChangeAttribute();
	return 0;
}
unsigned char _dpad_7747b4[76];
