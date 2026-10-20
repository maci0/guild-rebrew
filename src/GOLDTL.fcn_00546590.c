typedef struct {
	unsigned char r;
	unsigned char g;
	unsigned char f0 : 1;
	unsigned char f1 : 7;
	unsigned char x;
} COLOR546590;

typedef struct {
	unsigned char b0;
	unsigned char f0 : 1;
	unsigned char r0 : 1;
	unsigned char f2 : 1;
	unsigned char f3 : 1;
	unsigned char f4 : 1;
	unsigned char r1 : 3;
	unsigned char pad2[6];
	unsigned char r2 : 1;
	unsigned char e : 1;
	unsigned char r3 : 6;
	unsigned char pad9[3];
} FLAGS546590;

typedef struct {
	int id;
	float pos[3];
	float f10;
	float rot[3];
	char pad20[0x38];
} FRAME546590;

extern float g_662d70[4];

void __cdecl fcn_00455350(char* object, float* in, float* out);
int __cdecl fcn_004133e0(char* e, float* lo, float* hi);
char* __cdecl fcn_00442910(int parent, float* pos, float* dir, char* name);
void __cdecl fcn_0043a3f0(char* a, char* b, COLOR546590 c);
void __cdecl fcn_00414be0(char* p, unsigned char r, unsigned char g, unsigned char b);
int __cdecl fcn_004339e0(char* obj, FLAGS546590 fl, int n, FRAME546590* frames);
int __cdecl fcn_00546480(char* entity);

/* ADDRESS: GOLDTL 0x00546590 */
char* __cdecl fcn_00546590(char* a0, char* name, char* entity)
{
	FRAME546590 frames[2];
	FLAGS546590 flags;
	COLOR546590 color;
	float pos[3];
	float lo;
	float hi;
	char* obj;

	fcn_00455350(entity, (float*) (entity + 0x4c), pos);
	fcn_004133e0(entity, &lo, &hi);
	pos[1] = hi;
	obj = fcn_00442910(0, pos, g_662d70, name);
	*(char**) (a0 + 0xc) = obj;
	*(char**) (a0 + 8) = entity;
	if (obj != 0) {
		obj[0x216] |= 3;
		obj[0x214] &= 0x7f;
		obj[0x217] &= 0xfe;
		*(int*) (obj + 0x220) = 5;
		color.r = 0x80;
		color.g = 0;
		color.f0 = 1;
		color.f1 = 0;
		color.x = 0;
		fcn_0043a3f0(obj, *(char**) (obj + 0x1cc), color);
		fcn_00414be0(obj, 0xc0, 0xa0, 0x80);
		flags.b0 = 0;
		flags.f0 = 0;
		flags.f2 = 0;
		flags.f3 = 0;
		flags.f4 = 0;
		flags.e = 1;
		frames[0].id = 0x8c0;
		frames[0].pos[0] = 0.0f;
		frames[0].pos[1] = 0.0f;
		frames[0].pos[2] = 0.0f;
		frames[0].rot[0] = 0.0f;
		frames[0].rot[1] = 0.0f;
		frames[0].rot[2] = 0.0f;
		frames[1].pos[0] = 0.0f;
		frames[1].pos[1] = 0.0f;
		frames[1].pos[2] = 0.0f;
		frames[1].rot[0] = 0.0f;
		frames[1].rot[1] = 60.0f;
		frames[1].rot[2] = 0.0f;
		fcn_004339e0(obj, flags, 2, frames);
		fcn_00546480(entity);
	}
	return obj;
}
