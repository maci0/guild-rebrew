extern void __cdecl fcn_00455350(char*, char*, float*);
extern void __cdecl fcn_004518a0(float*);
extern double __cdecl fcn_0064f6f0(double);
extern void __cdecl fcn_00412cf0(int, float*, float*, int, int);

/* ADDRESS: GOLDTL 0x0052d1f0 */

/* Emit one oriented effect for a node.  The anchor offset of the node is
 * resolved by fcn_00455350, shifted by 600 units of the anchor span plus the
 * 900 unit height offset, and the heading/pitch pair is derived from the
 * horizontal delta by two arccosines; arguments outside [-1,1] clamp to the
 * domain edge and the sign of the delta selects the branch. */
void __cdecl fcn_0052d1f0(char* a0)
{
	float base[4];
	float pos[4];
	float dir[4];
	float level[4];
	float angles[4];
	float dot;
	float d;

	fcn_00455350(a0, a0 + 0x4c, base);
	angles[1] = 0.0f;
	angles[0] = 0.0f;
	level[0] = 0.0f;
	level[1] = 0.0f;
	level[2] = 0.0f;
	level[3] = 0.0f;
	dir[1] = 0.0f;
	pos[0] = base[0] + ((*(float*) (a0 + 0x19c) + *(float*) (a0 + 0x18c)) * *(float*) 0x6628a8 -
	                    *(float*) (a0 + 0x1ac) * *(float*) 0x6628a0) *
	                       *(float*) 0x665e1c;
	pos[1] = base[1] + ((*(float*) (a0 + 0x1a0) + *(float*) (a0 + 0x190)) * *(float*) 0x6628a8 -
	                    *(float*) (a0 + 0x1b0) * *(float*) 0x6628a0) *
	                       *(float*) 0x665e1c;
	pos[2] = base[2] + ((*(float*) (a0 + 0x1a4) + *(float*) (a0 + 0x194)) * *(float*) 0x6628a8 -
	                    *(float*) (a0 + 0x1b4) * *(float*) 0x6628a0) *
	                       *(float*) 0x665e1c;
	pos[1] = pos[1] + *(float*) 0x665e18;
	dir[0] = base[0] - pos[0];
	dir[2] = base[2] - pos[2];
	fcn_004518a0(dir);
	dot = *(float*) 0x662d40 * dir[0] + *(float*) 0x662d44 * dir[1] + *(float*) 0x662d48 * dir[2];
	if (dot < -1.0 || 1.0 < dot) {
		if (dot < -1.0)
			d = -1.0f;
		else
			d = 1.0f;
	} else {
		d = dot;
	}
	angles[1] = (float) fcn_0064f6f0(d);
	if (0.0 < dir[0])
		angles[1] = -angles[1];
	dir[0] = base[0] - pos[0];
	dir[1] = base[1] - pos[1];
	dir[2] = base[2] - pos[2];
	level[0] = dir[0];
	level[2] = dir[2];
	fcn_004518a0(dir);
	fcn_004518a0(level);
	dot = dir[0] * level[0] + dir[1] * level[1] + dir[2] * level[2];
	if (dot < -1.0 || 1.0 < dot) {
		if (dot < -1.0)
			d = -1.0f;
		else
			d = 1.0f;
	} else {
		d = dot;
	}
	angles[0] = (float) fcn_0064f6f0(d);
	if (dir[1] < 0.0)
		angles[0] = -angles[0];
	pos[1] = pos[1] + *(float*) 0x6652cc;
	fcn_00412cf0(*(int*) 0x6b8014, pos, angles, *(int*) 0x6a256c, 0x28);
}
