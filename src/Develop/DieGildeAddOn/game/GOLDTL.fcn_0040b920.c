

extern float g_662d40[3];
char* __cdecl fcn_00402610(char* p);
void __cdecl d3_TransformPoint(char* src, char* pos, float* out);
void __cdecl fcn_00455140(char* src, float* v, float* out);
float __cdecl fcn_00451380(float* a, float* b);
char __cdecl fcn_0045b990(char* g, float* v, int* a, int* b, int* c);
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

	g = fcn_00402610(owner);
	d3_TransformPoint(e, e + 0x4c, a);
	fcn_00455140(e, g_662d40, b);
	ang = fcn_00451380(g_662d40, b);
	if (fcn_0045b990(g, a, &x, &y, &z)) {
		r = ch_CreateAction(owner, 0x2d, x, y, d3_GetContextIndex(*(char**) (e + 0x20c)));
		*(int*) (r + 0x160) |= 0x10;
		*(float*) (r + 0x144) = a[0];
		*(float*) (r + 0x148) = a[1];
		*(float*) (r + 0x14c) = a[2];
		ch_CreateAction(owner, 7, (int) (-ang * 57.29577791868204), 1);
	}
}
