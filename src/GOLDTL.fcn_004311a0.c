struct frame_4311a0 {
	char pad0[0x20];
	float pos[3];
	float rot[3];
	char pad38[0x88];
};
// SIZE 0xc0

void __cdecl fcn_00438b40(char* node, float* v);
void __cdecl fcn_00438cb0(char* node, float* v);

#define FRAMES_4311A0(an) (*(struct frame_4311a0**) (*(char**) ((an) + 0x68) + 0x15c))

// FUNCTION: GOLDTL 0x4311a0
// SIZE: 390
void __cdecl fcn_004311a0(char* node, char* an, int from, int to, int flags)
{
	float d[4];
	float v[4];

	if ((flags & 1) == 1) {
		d[0] = FRAMES_4311A0(an)[to].pos[0] - FRAMES_4311A0(an)[from].pos[0];
		d[1] = FRAMES_4311A0(an)[to].pos[1] - FRAMES_4311A0(an)[from].pos[1];
		d[2] = FRAMES_4311A0(an)[to].pos[2] - FRAMES_4311A0(an)[from].pos[2];
		v[0] = d[2] * *(float*) (node + 0x1ac) + d[1] * *(float*) (node + 0x19c) + d[0] * *(float*) (node + 0x18c);
		v[1] = d[2] * *(float*) (node + 0x1b0) + d[1] * *(float*) (node + 0x1a0) + d[0] * *(float*) (node + 0x190);
		v[2] = d[2] * *(float*) (node + 0x1b4) + d[1] * *(float*) (node + 0x1a4) + d[0] * *(float*) (node + 0x194);
		v[0] += *(float*) (node + 0x4c);
		v[1] += *(float*) (node + 0x50);
		v[2] += *(float*) (node + 0x54);
		fcn_00438b40(node, v);
	}
	if ((flags & 2) == 2) {
		d[0] = FRAMES_4311A0(an)[to].rot[0] - FRAMES_4311A0(an)[from].rot[0];
		d[1] = FRAMES_4311A0(an)[to].rot[1] - FRAMES_4311A0(an)[from].rot[1];
		d[2] = FRAMES_4311A0(an)[to].rot[2] - FRAMES_4311A0(an)[from].rot[2];
		d[0] += *(float*) (node + 0x84);
		d[1] += *(float*) (node + 0x88);
		d[2] += *(float*) (node + 0x8c);
		fcn_00438cb0(node, d);
	}
}
