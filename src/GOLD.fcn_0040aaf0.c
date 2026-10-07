// GLOBAL: GOLD 0x5ebb74
extern float g_662d40[3];
// FUNCTION: GOLD 0x40aaf0

char* __cdecl fcn_00402140(char* p);
void __cdecl fcn_00458a10(char* src, char* pos, float* out);
void __cdecl fcn_00458800(char* src, float* v, float* out);
float __cdecl fcn_004539e0(float* a, float* b);
char __cdecl fcn_0045f160(char* g, float* v, int* a, int* b, int* c);
int __cdecl fcn_00411be0(char* p);
char* __cdecl fcn_0040b2f0(char* e, int kind, ...);

void __cdecl fcn_0040aaf0(char* owner, char* e)
{
	char* g;
	char* r;
	float a[4];
	float b[4];
	int x;
	int y;
	int z;
	float ang;

	g = fcn_00402140(owner);
	fcn_00458a10(e, e + 0x4c, a);
	fcn_00458800(e, g_662d40, b);
	ang = fcn_004539e0(g_662d40, b);
	if (fcn_0045f160(g, a, &x, &y, &z)) {
		r = fcn_0040b2f0(owner, 0x2d, x, y, fcn_00411be0(*(char**) (e + 0x208)));
		*(int*) (r + 0x160) |= 0x10;
		*(float*) (r + 0x144) = a[0];
		*(float*) (r + 0x148) = a[1];
		*(float*) (r + 0x14c) = a[2];
		fcn_0040b2f0(owner, 7, (int) (-ang * 57.29577791868204), 1);
	}
}
