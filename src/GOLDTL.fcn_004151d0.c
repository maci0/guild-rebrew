void __cdecl fcn_00432120(char*, int*, int, float*, float*);
void __cdecl fcn_00451340(float*, float*, float, float*);
void __cdecl fcn_00451900(float*, float*);
float* __stdcall fcn_005eb970(float*, const float*, const float*);
void __cdecl fcn_004519d0(float*, float*);

// FUNCTION: GOLDTL 0x4151d0

/* Samples a model's current animation blend: interpolated position and the
 * combined rotation angles. */
int __cdecl fcn_004151d0(char* obj, float* pos, float* rot)
{
	int* blend;
	float rot0[3];
	float rot1[3];
	float pos0[4];
	float pos1[4];
	float m1[16];
	float m0[16];
	float m[16];

	if (*(char**) (obj + 0x1ec) == 0 || *(int*) (*(char**) (obj + 0x1ec) + 0x484) == 0) {
		pos[0] = 0.0f;
		pos[1] = 0.0f;
		pos[2] = 0.0f;
		rot[0] = 0.0f;
		rot[1] = 0.0f;
		rot[2] = 0.0f;
		return 1;
	}
	blend = (int*) (*(char**) (obj + 0x1ec) + 0x41c);
	fcn_00432120(obj, blend, blend[0], pos0, rot0);
	fcn_00432120(obj, blend, blend[1], pos1, rot1);
	fcn_00451340(pos0, pos1,
	    (float) blend[2] / *(int*) (*(char**) (blend[0x1a] + 0x15c) + blend[0] * 0xc0 + 4), pos);
	fcn_00451900(rot0, m0);
	fcn_00451900(rot1, m1);
	fcn_005eb970(m, m0, m1);
	fcn_004519d0(m, rot);
	return 1;
}
