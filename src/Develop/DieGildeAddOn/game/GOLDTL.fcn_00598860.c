


void __cdecl d3_SetNodePosition(char*, float*);
void __cdecl fcn_004143b0(char*, int, int);
void __cdecl d3_TransformPoint(char*, char*, float*);

void __cdecl d3_SetObjectGroundPosition(char* obj, float* pos)
{
	float v[4];

	d3_SetNodePosition(obj, pos);
	fcn_004143b0(obj, 1, 0);
	d3_TransformPoint(obj, obj + 0x4c, v);
	if (v[1] < pos[1]) {
		d3_SetNodePosition(obj, pos);
	}
}
