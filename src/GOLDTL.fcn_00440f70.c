// FUNCTION: GOLDTL 0x440f70
// SIZE: 223

typedef struct IDev IDev;
// SIZE 0xcc
typedef struct IDevVtbl {
	void* slots[37];
	long (__stdcall* SetTransform)(IDev*, int, float*);
	void* slots2[12];
	long (__stdcall* SetRenderState)(IDev*, int, int);
} IDevVtbl;
// SIZE 0x4
struct IDev {
	IDevVtbl* v;
};

// SIZE 0x1f4
typedef struct Cell {
	char pad[0x1ee];
	char on;
	char pad2[5];
} Cell;

extern char* g_6b8014;
extern IDev* g_6b5de0;
extern int g_6b7fac;

float* __stdcall fcn_005ec410(float*, float, float, float);
float* __stdcall fcn_005eb970(float*, float*, float*);
void __cdecl fcn_00440670(int, int, int);
void __cdecl fcn_00440870(char*, Cell*);

void __cdecl fcn_00440f70(char* o, char flag)
{
	float m[16];
	Cell (*cells)[8];
	int a;
	int b;

	fcn_005ec410(m, *(float*) (o + 0x50) - *(float*) (g_6b8014 + 0x4c), *(float*) (o + 0x54) - *(float*) (g_6b8014 + 0x50),
	             *(float*) (o + 0x58) - *(float*) (g_6b8014 + 0x54));
	fcn_005eb970(m, m, (float*) (g_6b8014 + 0x18c));
	g_6b5de0->v->SetTransform(g_6b5de0, 0x100, m);
	if (flag != 0) {
		fcn_00440670(g_6b7fac, *(unsigned char*) (o + 0x8035), *(int*) (o + 0x7da0));
	}
	cells = (Cell (*)[8]) (o + 0xa0);
	for (a = 0; a < 8; a++) {
		for (b = 0; b < 8; b++) {
			if (cells[a][b].on != 0) {
				fcn_00440870(o, &cells[a][b]);
			}
		}
	}
	g_6b5de0->v->SetRenderState(g_6b5de0, 0x2f, 0x10);
}
