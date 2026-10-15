#include <stdio.h>

// SIZE 0x75
struct anim_409ae0 {
	char pad0[0x5c];
	float speed;
	char pad60[0xd];
	unsigned char pad6d0 : 4;
	unsigned char looping : 1;
	unsigned char paused : 1;
	char pad6e[2];
	unsigned int flags;
	unsigned char pad740 : 1;
	unsigned char walk : 1;
	unsigned char turn : 1;
	unsigned char stop : 1;
};

extern char g_6b5c28;

void __cdecl fcn_00435500(char*, char*);
#include "Develop/Units/d3/d3_animation.h"
void __cdecl fcn_00413120(void*);
void __cdecl fcn_00402aa0(char*);
struct anim_409ae0* __cdecl fcn_00404dc0(char*, const char*, int);
void __cdecl m_FreeTracked(void*);
void __cdecl fcn_004050c0(char*);

/* ADDRESS: GOLD 0x00408cb0 */
/* ADDRESS: GOLDTL 0x00409ae0 */

/* Starts a walk event: removes a pending morph, attaches the walk (or cart
 * pulling) motion and scales its speed to the event's step time. */
int __cdecl fcn_00409ae0(char* ev, char* step)
{
	char* obj;
	float scale;
	char* morph;
	char name[0x60];

	obj = *(char**) (ev + 0x14);
	*(int*) (obj + 0x80) = 0;
	if (*(int*) (obj + 0x7c) != 0) {
		sprintf(name, "morph_%i", (int) obj);
		fcn_00435500(*(char**) (*(char**) (obj + 0x34) + 0x1ec) + 0xf4, name);
		morph = fcn_00433ba0(name);
		fcn_00434760(morph, 1);
		*(int*) (obj + 0x7c) = 0;
	}
	fcn_00413120(*(void**) (obj + 0x34));
	if (*(int*) (*(char**) (obj + 0x34) + 0x1cc) == 0) {
		fcn_00402aa0(obj);
	}
	if (*(int*) (obj + 0x124) != 0) {
		*(struct anim_409ae0**) (obj + 0x70) = fcn_00404dc0(obj, "bewegung/karren_ziehen", 1);
	} else {
		*(struct anim_409ae0**) (obj + 0x70) = fcn_00404dc0(obj, "bewegung/gehen", 1);
	}
	if (*(struct anim_409ae0**) (obj + 0x70) == 0) {
		if (g_6b5c28 != 0) {
			(*(char**) (ev + 0x14))[0x8c] |= 8;
		}
		if (*(void**) (ev + 0xf4) != 0) {
			m_FreeTracked(*(void**) (ev + 0xf4));
			*(void**) (ev + 0xf4) = 0;
		}
		fcn_004050c0(ev);
		return 0;
	}
	(*(struct anim_409ae0**) (obj + 0x70))->looping = 0;
	(*(struct anim_409ae0**) (obj + 0x70))->flags = (*(struct anim_409ae0**) (obj + 0x70))->flags & ~2 | 1;
	if (*(int*) (obj + 4) & 8) {
		(*(struct anim_409ae0**) (obj + 0x70))->speed = 30.0f;
	} else if (*(int*) (obj + 4) & 0x10) {
		(*(struct anim_409ae0**) (obj + 0x70))->speed = 60.0f;
	} else {
		(*(struct anim_409ae0**) (obj + 0x70))->speed = 15.0f;
	}
	scale = 50.0f / *(float*) (step + 0x10);
	if (2.0f < scale) {
		scale = 2.0f;
	}
	(*(struct anim_409ae0**) (obj + 0x70))->speed *= scale;
	(*(struct anim_409ae0**) (obj + 0x70))->walk = 1;
	(*(struct anim_409ae0**) (obj + 0x70))->stop = 0;
	(*(struct anim_409ae0**) (obj + 0x70))->turn = 1;
	(*(struct anim_409ae0**) (obj + 0x70))->paused = 0;
	*(int*) (ev + 0x104) = 1;
	return 1;
}
