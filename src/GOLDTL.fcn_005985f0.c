// FUNCTION: GOLD 0x58fd20
// FUNCTION: GOLDTL 0x005985f0

typedef struct
{
	int x0;
	char pad4[0x3c];
	float v[3];
	int x4c;
	int x50;
} Out;
// SIZE 0x54

extern int g_6b8010;
extern int g_67a370;
extern char s_6aa1b4[];

int __cdecl sprintf(char*, const char*, ...);
void __cdecl fcn_004432d0(int, int);
int __cdecl fcn_00597ff0(int, Out*);
void __cdecl fcn_00455350(char*, char*, float*);
void __cdecl fcn_004379a0(int, int, int, void*, Out*);
void __cdecl fcn_00598550(void);

int __cdecl fcn_005985f0(Out* out, unsigned char* obj)
{
	char buf[0x100];
	int old;

	if (*(char**) (obj + 0x61) == 0) {
		return 0;
	}
	old = g_6b8010;
	fcn_004432d0(0, 1);
	out->x0 = 0;
	if (fcn_00597ff0(obj[0], out) == 0) {
		fcn_004432d0(old, 1);
		return 0;
	}
	fcn_00455350(*(char**) (obj + 0x61), *(char**) (obj + 0x61) + 0x4c, out->v);
	sprintf(buf, s_6aa1b4, out->v[0], out->v[1], out->v[2]);
	out->x50 = 0;
	fcn_004379a0(g_67a370, 0, 0x180, (void*) fcn_00598550, out);
	if (out->x50 == 0) {
		fcn_004432d0(old, 1);
		return 0;
	}
	fcn_004432d0(old, 1);
	return 1;
}
