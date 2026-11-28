

void __cdecl d3_TransformPoint(char* src, char* pos, float* out);
char* __cdecl d3sm_GetSceneSuperMap(char* p);
char __cdecl d3sm_3D2SuperMap(char* g, float* v, int* a, int* b, int* c);
int __cdecl d3_GetContextIndex(char* p);
char* __cdecl ch_CreateAction(char* e, int kind, int a, int b, int c);

char* __cdecl ch_QueueWalkToDummy(char* owner, char* e)
{
	char* result;
	char* g;
	float v[4];
	int a;
	int b;
	int c;

	result = 0;
	d3_TransformPoint(e, e + 0x4c, v);
	g = *(char**) (*(char**) (e + 0x20c) + 0xb0);
	if (g == 0) {
		g = d3sm_GetSceneSuperMap(*(char**) (e + 0x20c));
	}
	if (d3sm_3D2SuperMap(g, v, &a, &b, &c)) {
		result = ch_CreateAction(owner, 0x2d, a, b, d3_GetContextIndex(*(char**) (e + 0x20c)));
		if (result != 0) {
			*(int*) (result + 0x160) |= 0x10;
			*(float*) (result + 0x144) = v[0];
			*(float*) (result + 0x148) = v[1];
			*(float*) (result + 0x14c) = v[2];
		}
	}
	return result;
}
