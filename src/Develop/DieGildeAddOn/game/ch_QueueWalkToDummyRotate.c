

extern float d3_UnitAxisVectors[3];
char* __cdecl d3sm_GetObjectSuperMap(char* p);
void __cdecl d3_TransformPoint(char* src, char* pos, float* out);
void __cdecl d3_TransformDirection(char* src, float* v, float* out);
float __cdecl d3_SignedPlanarAngle(float* a, float* b);
char __cdecl d3sm_SampleHeight(char* g, float* v, int* a, int* b, int* c);
int __cdecl d3_GetContextIndex(char* p);
char* __cdecl ch_CreateAction(char* e, int kind, ...);

void __cdecl ch_QueueWalkToDummyRotate(char* owner, char* e)
{
	char* g;
	char* r;
	float a[4];
	float b[4];
	int x;
	int y;
	int z;
	float ang;

	g = d3sm_GetObjectSuperMap(owner);
	d3_TransformPoint(e, e + 0x4c, a);
	d3_TransformDirection(e, d3_UnitAxisVectors, b);
	ang = d3_SignedPlanarAngle(d3_UnitAxisVectors, b);
	if (d3sm_SampleHeight(g, a, &x, &y, &z)) {
		r = ch_CreateAction(owner, 0x2d, x, y, d3_GetContextIndex(*(char**) (e + 0x20c)));
		*(int*) (r + 0x160) |= 0x10;
		*(float*) (r + 0x144) = a[0];
		*(float*) (r + 0x148) = a[1];
		*(float*) (r + 0x14c) = a[2];
		ch_CreateAction(owner, 7, (int) (-ang * 57.29577791868204), 1);
	}
}
