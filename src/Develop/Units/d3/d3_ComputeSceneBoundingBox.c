

extern int d3_ActiveScene;

void __cdecl d3_VisitSceneObjects(int, int, int, void*, void*);
char __cdecl d3_AccumulateObjectBounds(char*, float*);

void __cdecl d3_ComputeSceneBoundingBox(float* mn, float* mx)
{
	float bb[8];

	bb[0] = 1.0e10f;
	bb[1] = 1.0e10f;
	bb[2] = 1.0e10f;
	bb[4] = -1.0e10f;
	bb[5] = -1.0e10f;
	bb[6] = -1.0e10f;
	d3_VisitSceneObjects(d3_ActiveScene, 0, 0x40, d3_AccumulateObjectBounds, bb);
	mn[0] = bb[0];
	mn[1] = bb[1];
	mn[2] = bb[2];
	mx[0] = bb[4];
	mx[1] = bb[5];
	mx[2] = bb[6];
}
