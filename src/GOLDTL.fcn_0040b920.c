// FUNCTION: GOLDTL 0x0040b920

extern float g_662d40[3];
char* __cdecl fcn_00402610(char* p);
void __cdecl fcn_00455350(char* src, char* pos, float* out);
void __cdecl fcn_00455140(char* src, float* v, float* out);
float __cdecl fcn_00451380(float* a, float* b);
char __cdecl fcn_0045b990(char* g, float* v, int* a, int* b, int* c);
int __cdecl fcn_00413190(char* p);
char* __cdecl fcn_0040c120(char* e, int kind, ...);

void __cdecl fcn_0040b920(char* owner, char* e)
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
	fcn_00455350(e, e + 0x4c, a);
	fcn_00455140(e, g_662d40, b);
	ang = fcn_00451380(g_662d40, b);
	if (fcn_0045b990(g, a, &x, &y, &z)) {
		r = fcn_0040c120(owner, 0x2d, x, y, fcn_00413190(*(char**) (e + 0x20c)));
		*(int*) (r + 0x160) |= 0x10;
		*(float*) (r + 0x144) = a[0];
		*(float*) (r + 0x148) = a[1];
		*(float*) (r + 0x14c) = a[2];
		fcn_0040c120(owner, 7, (int) (-ang * 57.29577791868204), 1);
	}
}
