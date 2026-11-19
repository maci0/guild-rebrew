extern void __cdecl d3_TransformPoint(char*, char*, float*);
extern void __cdecl fcn_004518a0(float*);
#include <math.h>
extern void __cdecl d3_AnimateObjectTransform(int, float*, float*, int, int);


/* Emit one oriented effect for a node.  The anchor offset of the node is
 * resolved by d3_TransformPoint, shifted by 600 units of the anchor span plus the
 * 900 unit height offset, and the heading/pitch pair is derived from the
 * horizontal delta by two arccosines; arguments outside [-1,1] clamp to the
 * domain edge and the sign of the delta selects the branch. */
/* ADDRESS: GOLDTL 0x0052d1f0 */
void __cdecl fcn_0052d1f0(char* effectNode)
{
	float base[4];
	float pos[4];
	float dir[4];
	float level[4];
	float angles[4];
	float dot;
	float s[3];

	d3_TransformPoint(effectNode, effectNode + 0x4c, base);
	level[0] = 0.0f;
	level[1] = 0.0f;
	level[2] = -1.0f;
	angles[0] = 0.0f;
	angles[1] = 0.0f;
	angles[2] = 0.0f;
	dir[1] = 0.0f;
	s[0] = (*(float*) (effectNode + 0x19c) + *(float*) (effectNode + 0x18c)) * *(float*) 0x6628a8 - *(float*) (effectNode + 0x1ac) * *(float*) 0x6628a0;
	s[1] = (*(float*) (effectNode + 0x1a0) + *(float*) (effectNode + 0x190)) * *(float*) 0x6628a8 - *(float*) (effectNode + 0x1b0) * *(float*) 0x6628a0;
	s[2] = (*(float*) (effectNode + 0x1a4) + *(float*) (effectNode + 0x194)) * *(float*) 0x6628a8 - *(float*) (effectNode + 0x1b4) * *(float*) 0x6628a0;
	pos[0] = s[0] * 600.0f;
	pos[1] = s[1] * 600.0f;
	pos[2] = s[2] * 600.0f;
	pos[0] += base[0];
	pos[1] += base[1];
	pos[2] += base[2];
	pos[1] = pos[1] + 900.0f;
	dir[0] = base[0] - pos[0];
	dir[1] = 0.0f;
	dir[2] = base[2] - pos[2];
	fcn_004518a0(dir);
	dot = *(float*) 0x662d48 * dir[2] + *(float*) 0x662d44 * dir[1] + *(float*) 0x662d40 * dir[0];
	angles[1] = (float) acos(dot < -1.0 || !(dot < 1.0) ? (dot < -1.0 ? -1.0 : 1.0) : dot);
	if (dir[0] > 0.0f)
		angles[1] = -angles[1];
	level[0] = base[0] - pos[0];
	level[1] = 0.0f;
	level[2] = base[2] - pos[2];
	dir[0] = base[0] - pos[0];
	dir[1] = base[1] - pos[1];
	dir[2] = base[2] - pos[2];
	fcn_004518a0(dir);
	fcn_004518a0(level);
	dot = dir[2] * level[2] + dir[1] * level[1] + dir[0] * level[0];
	angles[0] = (float) acos(dot < -1.0 || !(dot < 1.0) ? (dot < -1.0 ? -1.0 : 1.0) : dot);
	if (0.0f > dir[1])
		angles[0] = -angles[0];
	pos[1] = pos[1] + 700.0f;
	d3_AnimateObjectTransform(*(int*) 0x6b8014, pos, angles, *(int*) 0x6a256c, 0x28);
}
