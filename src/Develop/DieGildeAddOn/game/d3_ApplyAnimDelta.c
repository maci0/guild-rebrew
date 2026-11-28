struct D3_ANIM_FRAME {
	char pad0[0x20];
	float pos[3];
	float rot[3];
	char pad38[0x88];
};
// SIZE 0xc0

void __cdecl d3_SetNodePosition(char* node, float* v);
void __cdecl d3_SetObjectRotation(char* node, float* v);

#define D3_ANIM_FRAMES(anim) (*(struct D3_ANIM_FRAME**) (*(char**) ((anim) + 0x68) + 0x15c))

/* ADDRESS: GOLD 0x004315c0 */
/* ADDRESS: GOLDTL 0x004311a0 */
/* ADDRESS: GOLDDE 0x0042a8b0 */
void __cdecl d3_ApplyAnimDelta(char* node, char* anim, int from, int to, int flags)
{
	float d[4];
	float v[4];

	if ((flags & 1) == 1) {
		d[0] = D3_ANIM_FRAMES(anim)[to].pos[0] - D3_ANIM_FRAMES(anim)[from].pos[0];
		d[1] = D3_ANIM_FRAMES(anim)[to].pos[1] - D3_ANIM_FRAMES(anim)[from].pos[1];
		d[2] = D3_ANIM_FRAMES(anim)[to].pos[2] - D3_ANIM_FRAMES(anim)[from].pos[2];
		v[0] = d[2] * *(float*) (node + 0x1ac) + d[1] * *(float*) (node + 0x19c) + d[0] * *(float*) (node + 0x18c);
		v[1] = d[2] * *(float*) (node + 0x1b0) + d[1] * *(float*) (node + 0x1a0) + d[0] * *(float*) (node + 0x190);
		v[2] = d[2] * *(float*) (node + 0x1b4) + d[1] * *(float*) (node + 0x1a4) + d[0] * *(float*) (node + 0x194);
		v[0] += *(float*) (node + 0x4c);
		v[1] += *(float*) (node + 0x50);
		v[2] += *(float*) (node + 0x54);
		d3_SetNodePosition(node, v);
	}
	if ((flags & 2) == 2) {
		d[0] = D3_ANIM_FRAMES(anim)[to].rot[0] - D3_ANIM_FRAMES(anim)[from].rot[0];
		d[1] = D3_ANIM_FRAMES(anim)[to].rot[1] - D3_ANIM_FRAMES(anim)[from].rot[1];
		d[2] = D3_ANIM_FRAMES(anim)[to].rot[2] - D3_ANIM_FRAMES(anim)[from].rot[2];
		d[0] += *(float*) (node + 0x84);
		d[1] += *(float*) (node + 0x88);
		d[2] += *(float*) (node + 0x8c);
		d3_SetObjectRotation(node, d);
	}
}
