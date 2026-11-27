


void __cdecl d3_SetNodePosition(char*, float*);
void __cdecl d3_AlignObjectToTerrain(char*, int, int);
void __cdecl d3_TransformPoint(char*, char*, float*);

void __cdecl d3_SetObjectGroundPosition(char* obj, float* pos)
{
	float v[4];

	d3_SetNodePosition(obj, pos);
	d3_AlignObjectToTerrain(obj, 1, 0);
	d3_TransformPoint(obj, obj + 0x4c, v);
	if (v[1] < pos[1]) {
		d3_SetNodePosition(obj, pos);
	}
}
