// FUNCTION: GOLDTL 0x005a3580
// SIZE: 256

typedef struct
{
	char pad0[0x215];
	unsigned char a0 : 1;
	unsigned char a1 : 7;
	unsigned char b0 : 1;
	unsigned char b1 : 1;
	unsigned char b2 : 6;
	char pad217[9];
	int x220;
	int x224;
} Obj;
// SIZE 0x228

extern float g_662d70[4];

char* __cdecl _strlwr(char*);
int __cdecl sprintf(char*, const char*, ...);
char* __cdecl fcn_00445600(int, int, int, char*);
void __cdecl fcn_00455350(char* src, char* pos, float* out);
Obj* __cdecl fcn_00442910(int, float*, float*, char*);
void __cdecl fcn_00412f10(Obj*, char*, int);

Obj* __cdecl fcn_005a3580(char* name)
{
	float pos[4];
	char low[0x100];
	char buf[0x100];
	char* e;
	char* d;
	char* s;
	Obj* o;

	pos[0] = 0.0f;
	pos[1] = 0.0f;
	pos[2] = 0.0f;
	pos[3] = 0.0f;
	s = name;
	d = low;
	while ((*d++ = *s++) != 0) {
	}
	_strlwr(low);
	sprintf(buf, "dummy_%s", low);
	e = fcn_00445600(0, 0x140, 0, buf);
	if (e == 0) {
		return 0;
	}
	fcn_00455350(e, e + 0x4c, pos);
	o = fcn_00442910(0, pos, g_662d70, "sp_STADTPUNKT_K");
	o->a0 = 1;
	o->x220 = 4;
	o->b1 = 0;
	o->x224 = 1;
	o->b0 = 1;
	fcn_00412f10(o, "sonstiges\\STADTPUNKT_ANM_K.baf", 1);
	return o;
}
