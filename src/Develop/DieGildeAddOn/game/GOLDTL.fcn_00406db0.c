void __cdecl d3_TransformPoint(char*, char*, float*);
float __cdecl d3_ComputeYawToTarget(void*, float*);
void __cdecl d3_WrapEulerAnglesPi(float*, float*, float*, float*);

#include "Develop/DieGildeAddOn/game/ch_queue.h"


/* Starts a turn-towards event: queues a turn by the angle between the
 * character and the event's target object. */
/* ADDRESS: GOLD 0x00406210 */
/* ADDRESS: GOLDTL 0x00406db0 */
void __cdecl ch_ExecTurnTowards(char* ev)
{
	char* obj;
	char* target;
	float angle;
	float rot[3];
	float a[3];
	float b[3];
	float pos[4];

	target = *(char**) (ev + 0x30);
	obj = *(char**) (ev + 0x14);
	d3_TransformPoint(target, target + 0x4c, pos);
	angle = d3_ComputeYawToTarget(*(void**) (obj + 0x34), pos);
	rot[1] = angle;
	rot[0] = 0.0f;
	rot[2] = 0.0f;
	d3_WrapEulerAnglesPi(rot, (float*) (*(char**) (obj + 0x34) + 0x84), b, a);
	rot[0] += *(float*) (*(char**) (obj + 0x34) + 0x84);
	rot[1] += *(float*) (*(char**) (obj + 0x34) + 0x88);
	rot[2] += *(float*) (*(char**) (obj + 0x34) + 0x8c);
	ch_InsertAction(obj, ev, 7, (int) (angle * 57.2957795f), 0);
	ch_RemoveQueueEntry(ev);
}
