// FUNCTION: GOLDTL 0x53e7a0
// SIZE: 247

#include <string.h>

// SIZE 0x10
struct vec4 {
	float x;
	float y;
	float z;
	float w;
};

extern float g_662d70[4];

char* __cdecl fcn_0066080a(char*);
int __cdecl sprintf(char*, const char*, ...);
char* __cdecl fcn_00445600(int, int, int, char*);
void __cdecl fcn_00455350(char*, char*, struct vec4*);
char* __cdecl fcn_00442910(int, struct vec4*, struct vec4*, char*);
void __cdecl fcn_00412f10(char*, char*, int);

char* __cdecl fcn_0053e7a0(char* name)
{
	struct vec4 v;
	char upper[0x100];
	char dummy[0x100];
	char* p;
	char* r;

	v.x = 0.0f;
	v.y = 0.0f;
	v.z = 0.0f;
	v.w = 0.0f;
	strcpy(upper, name);
	fcn_0066080a(upper);
	sprintf(dummy, "dummy_%s", upper);
	p = fcn_00445600(0, 0x140, 0, dummy);
	if (p == 0) {
		return 0;
	}
	fcn_00455350(p, p + 0x4c, &v);
	r = fcn_00442910(0, &v, &(*(struct vec4*)g_662d70), "sp_STADTPUNKT_K");
	r[0x215] |= 1;
	*(int*) (r + 0x220) = 4;
	r[0x216] = (r[0x216] & 0xfd) | 1;
	*(int*) (r + 0x224) = 1;
	fcn_00412f10(r, "sonstiges\\STADTPUNKT_ANM_K.baf", 1);
	return r;
}
