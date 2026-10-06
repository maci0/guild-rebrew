// FUNCTION: GOLDTL 0x005d04c0

typedef struct {
	char pad[0x40];
	int a;
	int b;
	char pad2[0x2ac];
} Row5d04;
// SIZE 0x2f4

extern char g_868060[];
extern char g_6a40d0[];
extern char g_6a40b0[];
extern char g_6a40a0[];
extern char g_6a4080[];
extern float g_66418c;
extern float g_665e64;
extern int g_14ce8e0;
extern int g_774654;

char* __cdecl fcn_00445600(int, int, int, char*);
char* __cdecl fcn_00442910(int, float*, char*, char*);
void __cdecl fcn_00412f10(char*, char*, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00442be0(char*);

void __cdecl fcn_005d04c0(void)
{
	float dx;
	float dz;
	float pos[4];
	char* objs[4];
	char* a;
	char* b;
	char* o;
	int i;
	float z;

	pos[0] = 0.0f;
	pos[1] = 0.0f;
	pos[2] = 0.0f;
	pos[3] = 0.0f;
	a = fcn_00445600(0, 0x140, 0, g_6a40d0);
	b = fcn_00445600(0, 0x140, 0, g_6a40b0);
	if (a == 0 || b == 0) {
		return;
	}
	dx = *(float*) (b + 0x4c) - *(float*) (a + 0x4c);
	dz = *(float*) (b + 0x54) - *(float*) (a + 0x54);
	for (i = 0; i < 4; i++) {
		pos[0] = 0.0f;
		pos[1] = 0.0f;
		pos[2] = 0.0f;
		pos[3] = 0.0f;
		pos[0] = *(float*) (a + 0x4c);
		pos[1] = *(float*) (a + 0x50);
		z = *(float*) (a + 0x54);
		pos[0] += ((Row5d04*)g_868060)[i].a * g_66418c * dx;
		pos[2] = ((Row5d04*)g_868060)[i].b * g_665e64 * dz + z;
		o = fcn_00442910(0, pos, a + 0x84, g_6a40a0);
		o[0x215] |= 1;
		o[0x216] = (o[0x216] & ~2) | 1;
		objs[i] = o;
		fcn_00412f10(o, g_6a4080, 1);
	}
	while (fcn_005373e0(fcn_005d04c0, 0x67fff) != 0) {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	}
	for (i = 0; i < 4; i++) {
		fcn_00442be0(objs[i]);
	}
}
