// FUNCTION: GOLDTL 0x5742e0
// SIZE: 473

#include <stdio.h>
#include <string.h>

// SIZE 0x50
struct modelent {
	int k[4];
	char name[0x40];
};

// SIZE 0xc
struct vec3 {
	float x;
	float y;
	float z;
};

extern struct modelent g_6a6ee8[];
extern int g_6b8010;

void __cdecl fcn_004432d0(int, int);
char* __cdecl fcn_004488e0(char* name, int a, int b);
void __cdecl fcn_00438b40(char*, struct vec3*);
void __cdecl fcn_00438cb0(char*, float*);
void __cdecl fcn_00514d80(char*);
void __cdecl fcn_004143b0(char*, int, int);
void __cdecl fcn_00442d50(char*, int);
void __cdecl fcn_00573e10(char*);
void __cdecl fcn_00510820(char*, unsigned char*, int);

char* __cdecl fcn_005742e0(float* rot, struct vec3* pos, unsigned char* kind, char* model, char* u)
{
	int saved;
	char name[0x100];
	char* h;
	int i;
	int j;
	int found;

	i = 0;
	found = 0;
	for (; g_6a6ee8[i].k[0] != 0; i++) {
		if (found) {
			break;
		}
		for (j = 0; j < 4; j++) {
			if (*kind == g_6a6ee8[i].k[j]) {
				strcpy(name, g_6a6ee8[i].name);
				found = 1;
				break;
			}
		}
	}
	if (!found) {
		strcpy(name, g_6a6ee8[i].name);
	}
	saved = g_6b8010;
	fcn_004432d0(0, 1);
	h = fcn_004488e0(name, 0, 0);
	if (h == 0) {
		fcn_004432d0(saved, 1);
		return 0;
	}
	fcn_00438b40(h, pos);
	fcn_00438cb0(h, rot);
	h[0x215] &= 0xfe;
	h[0x214] |= 0x80;
	sprintf(h, "he_%i", *(int*) (u + 4));
	h = fcn_004488e0(model, 0, 0);
	if (h == 0) {
		fcn_004432d0(saved, 1);
		return 0;
	}
	fcn_00438b40(h, pos);
	fcn_00438cb0(h, rot);
	fcn_00514d80(h);
	fcn_004143b0(h, 1, 0);
	if (*(float*) (h + 0x50) < pos->y) {
		*(float*) (h + 0x4c) = pos->x;
		*(float*) (h + 0x50) = pos->y;
		*(float*) (h + 0x54) = pos->z;
	}
	fcn_00442d50(h, 0);
	*(int*) (u + 0xbc) = *(int*) (u + 0xc8) = -1;
	fcn_00573e10(u);
	fcn_00510820(h, kind, 2);
	fcn_004432d0(saved, 1);
	return h;
}
