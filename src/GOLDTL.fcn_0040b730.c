// FUNCTION: GOLDTL 0x0040b730
// SIZE: 192

void __cdecl fcn_00455350(char* src, char* pos, float* out);
char* __cdecl fcn_004026f0(char* p);
char __cdecl fcn_0045b990(char* g, float* v, int* a, int* b, int* c);
int __cdecl fcn_00413190(char* p);
char* __cdecl fcn_0040c120(char* e, int kind, int a, int b, int c);

char* __cdecl fcn_0040b730(char* owner, char* e)
{
	char* result;
	char* g;
	float v[4];
	int a;
	int b;
	int c;

	result = 0;
	fcn_00455350(e, e + 0x4c, v);
	g = *(char**) (*(char**) (e + 0x20c) + 0xb0);
	if (g == 0) {
		g = fcn_004026f0(*(char**) (e + 0x20c));
	}
	if (fcn_0045b990(g, v, &a, &b, &c)) {
		result = fcn_0040c120(owner, 0x2d, a, b, fcn_00413190(*(char**) (e + 0x20c)));
		if (result != 0) {
			*(int*) (result + 0x160) |= 0x10;
			*(float*) (result + 0x144) = v[0];
			*(float*) (result + 0x148) = v[1];
			*(float*) (result + 0x14c) = v[2];
		}
	}
	return result;
}
