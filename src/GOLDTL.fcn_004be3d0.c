extern char g_1043370[];

typedef struct MapPos {
	int f0;
	int f4;
	int col;
	int row;
	float x;
	float y;
} MapPos;

char* __cdecl gm_SearchTable67(unsigned int);
int __cdecl fcn_004be300(char*, char*);
void __cdecl fcn_00455350(char*, float*, float*);
char __cdecl fcn_0045b990(char*, float*, int*, int*, float*);
void __cdecl fcn_005b00f0(char*, int, int);
int __cdecl fcn_0046f740(int, int, int, int);
int __cdecl fcn_004693b0(int);
void __cdecl fcn_00469470(int, int);

/* ADDRESS: GOLDTL 0x004be3d0 */
int __cdecl fcn_004be3d0(int* a0, char* a1, char* a2, float a3)
{
	float out[4];
	MapPos p;
	char* rec;
	char* obj;
	int idx;
	int a;
	int b;
	int v;
	int n;
	char* map;

	idx = *(unsigned char*) 0x773d75;
	map = *(char**) 0x1043370;
	a = *(int*) (0x86834c + idx * 0x2f4);
	b = *(int*) (0x868350 + idx * 0x2f4);
	rec = gm_SearchTable67(*(unsigned int*) (a2 + 4));
	if (rec == 0) {
		return -1;
	}
	obj = *(char**) (rec + 0x61);
	fcn_00455350(obj, (float*) (obj + 0x4c), out);
	if (!fcn_0045b990(map, out, &p.col, &p.row, &a3)) {
		return -1;
	}
	fcn_005b00f0((char*) &p, a, b);
	v = fcn_0046f740((int) p.x - 0x20, (int) p.y - 0x20,
		fcn_004be300(a2, a2) + 0x7bb, a0[2]);
	n = *(int*) 0x772900;
	*(int*) (0x10058a0 + n * 8) = v;
	*(int*) (*(int*) 0x1015ea0 + v * 0x2f4 + 0x58) = 1;
	if (*(int*) 0x6816d8 == -1) {
		*(int*) 0x6816d8 = fcn_004693b0(1);
	} else {
		fcn_00469470(*(int*) 0x6816d8, *(int*) (0x10058a0 + n * 8));
	}
	*(int*) (0x10058a4 + n * 8) = (int) a2;
	*(int*) 0x772900 = n + 1;
	return v;
}
