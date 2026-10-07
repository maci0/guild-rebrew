void __cdecl fcn_00455350(char*, char*, float*);
float __cdecl fcn_00444700(void*, float*);
void __cdecl fcn_00451720(float*, float*, float*, float*);
char* __cdecl fcn_004051d0(char*, char*, int, ...);
void __cdecl fcn_004050c0(char*);

// FUNCTION: GOLD 0x00406210
// FUNCTION: GOLDTL 0x406db0

/* Starts a turn-towards event: queues a turn by the angle between the
 * character and the event's target object. */
void __cdecl fcn_00406db0(char* ev)
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
	fcn_00455350(target, target + 0x4c, pos);
	angle = fcn_00444700(*(void**) (obj + 0x34), pos);
	rot[1] = angle;
	rot[0] = 0.0f;
	rot[2] = 0.0f;
	fcn_00451720(rot, (float*) (*(char**) (obj + 0x34) + 0x84), b, a);
	rot[0] += *(float*) (*(char**) (obj + 0x34) + 0x84);
	rot[1] += *(float*) (*(char**) (obj + 0x34) + 0x88);
	rot[2] += *(float*) (*(char**) (obj + 0x34) + 0x8c);
	fcn_004051d0(obj, ev, 7, (int) (angle * 57.2957795f), 0);
	fcn_004050c0(ev);
}
