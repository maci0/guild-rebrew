#include <math.h>

#include "Develop/DieGildeAddOn/game/ch_motion.h"

extern int __cdecl sprintf(char* buf, const char* fmt, ...);

extern int ch_UpdateTime;
extern unsigned int g_67529c;

float __cdecl fcn_00444700(char* obj, float* pos);
void __cdecl fcn_00438d70(int a1, int a2, int a3, int a4);

/* ADDRESS: GOLDTL 0x0040a200 */
void __cdecl ch_WalkOnPathRotation(char* obj)
{
	char buf[256];
	float position[4];
	float relative[4];
	char* inst;
	char* o;
	float turnDelta;
	float turnStep;
	float angle;
	double base;
	int ticks;

	inst = *(char**) (obj + 0x14);
	if (*(float*) (obj + 0x108) < 0.0f) {
		o = *(char**) (inst + 0x34);
		turnDelta = fcn_00444700(o, (float*) (obj + 0x124));
		base = *(float*) (o + 0x88);
		*(float*) (obj + 0x108) = turnDelta;
		if (turnDelta <= 0.04 && turnDelta >= -0.04) {
			angle = turnDelta + *(float*) (o + 0x88);
			*(int*) (obj + 0x108) = 0;
		} else {
			ticks = ch_UpdateTime - g_67529c;
			turnStep = ticks * 0.9090909f;
			if (*(int*) (inst + 4) & 8) {
				turnStep *= 0.4f;
			} else if (*(int*) (inst + 4) & 0x10) {
				turnStep *= 1.4f;
			}
			if (fabs(turnDelta) > 2.0943951f && !(*(int*) (inst + 4) & 8)) {
				*(float*) (inst + 0x1a4) = 0.4f;
			}
			if (fabs(turnDelta) > 1.5707964f) {
				turnStep *= 0.19999998807907104f;
			} else if (fabs(turnDelta) > 1.0471976f) {
				turnStep *= 0.14f;
			} else if (fabs(turnDelta) > 0.52359879f) {
				turnStep *= 0.06f;
			} else {
				turnStep *= 0.04f;
			}
			angle = (float) (base - turnStep);
			angle = (float) fmod(angle, 6.2831855f);
			if (angle < 0.0) {
				angle += 6.2831855f;
			}
			if (angle < turnDelta + *(float*) (o + 0x88)) {
				angle = turnDelta + *(float*) (o + 0x88);
				*(int*) (obj + 0x108) = 0;
			}
		}
		fcn_00438d70((int) o, *(int*) (o + 0x84), *(int*) &angle,
		             *(int*) (o + 0x8c));
		return;
	}
	if (*(float*) (obj + 0x108) > 0.0f) {
		o = *(char**) (inst + 0x34);
		turnDelta = fcn_00444700(o, (float*) (obj + 0x124));
		base = *(float*) (o + 0x88);
		*(float*) (obj + 0x108) = turnDelta;
		if (turnDelta <= 0.04 && turnDelta >= -0.04) {
			angle = turnDelta + *(float*) (o + 0x88);
			*(int*) (obj + 0x108) = 0;
		} else {
			ticks = ch_UpdateTime - g_67529c;
			turnStep = ticks * 0.9090909f;
			if (*(int*) (inst + 4) & 8) {
				turnStep *= 0.4f;
			} else if (*(int*) (inst + 4) & 0x10) {
				turnStep *= 0.8f;
			}
			if (fabs(turnDelta) > 2.0943951f && !(*(int*) (inst + 4) & 8)) {
				*(float*) (inst + 0x1a4) = 0.4f;
			}
			if (fabs(turnDelta) > 1.5707964f) {
				turnStep *= 0.19999998807907104f;
			} else if (fabs(turnDelta) > 1.0471976f) {
				turnStep *= 0.14f;
			} else if (fabs(turnDelta) > 0.52359879f) {
				turnStep *= 0.06f;
			} else {
				turnStep *= 0.04f;
			}
			angle = (float) (base + turnStep);
			angle = (float) fmod(angle, 6.2831855f);
			if (angle < 0.0) {
				angle += 6.2831855f;
			}
			if (angle > turnDelta + *(float*) (o + 0x88)) {
				angle = turnDelta + *(float*) (o + 0x88);
				*(int*) (obj + 0x108) = 0;
			}
		}
		fcn_00438d70((int) o, *(int*) (o + 0x84), *(int*) &angle,
		             *(int*) (o + 0x8c));
		return;
	}
	o = *(char**) (inst + 0x34);
	position[0] = *(float*) (o + 0x4c);
	position[1] = *(float*) (o + 0x50);
	position[2] = *(float*) (o + 0x54);
	relative[0] = position[0] - *(float*) (obj + 0x124);
	relative[1] = position[1] - *(float*) (obj + 0x128);
	relative[2] = position[2] - *(float*) (obj + 0x12c);
	if (sqrt(relative[2] * relative[2] + relative[1] * relative[1] + relative[0] * relative[0]) >
	    *(float*) (obj + 0x10c) * 1.4) {
		if (*(int*) (obj + 0xf8) >= *(int*) (obj + 0xf0) - 1) {
			ch_SetPosition(inst, (float*) (obj + 0x124), 0);
		}
		inst = *(char**) (inst + 0x70);
		if (inst) {
			*((unsigned char*) inst + 0x74) |= 8;
		}
		sprintf(buf,
		        "ch_WalkOnPathRotation(): Have missed my treshhold... %s "
		        "[%f %f]",
		        *(char**) (*(char**) (obj + 0x14) + 0x34),
		        *(float*) (obj + 0x124), *(float*) (obj + 0x12c));
	}
}
