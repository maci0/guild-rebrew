// FUNCTION: GOLDTL 0x00511900
// SIZE: 615

// SIZE 0x85
typedef struct {
	char pad0[4];
	int id;
	char pad8[0x78];
	unsigned char skills[5];
} Figure;

extern int g_7e1fa0[];
extern char g_773d75;
extern int g_7747f8;
extern char* g_aed32c;

unsigned short __cdecl fcn_0042e410(int);
void __cdecl fcn_004c44a0(void);
void __cdecl fcn_004c44b0(void);
int __cdecl fcn_004c44c0(void);
void __cdecl fcn_004c3ff0(void);
void __cdecl fcn_004c4940(void);
void __cdecl ls_ID2Ptr(void);
int __cdecl fcn_004c4fc0(int, int, int, short, int, int, int, int);
int __cdecl fcn_0050b750(int, unsigned char);
void __cdecl fcn_004c5150(int, int, char, int);
Figure* __cdecl fcn_004c4480(int);
void __cdecl fcn_004c4510(Figure*, int);
int __cdecl fcn_004c4700(unsigned char, unsigned char, short, void*);
void __cdecl fcn_004c53a0(void);

void __cdecl fcn_00511900(int count, int size, int* faces)
{
	int face;
	int price[5];
	int bonus[5];
	int ids[8];
	int start;
	int step;
	int i;
	int j;
	int k;
	Figure* p;
	float v;
	int n;

	face = 0;
	start = fcn_0042e410(size);
	step = fcn_0042e410(2) != 0 ? 1 : 3;
	price[0] = 500;
	price[1] = 750;
	price[2] = 1000;
	price[3] = 20000;
	price[4] = 40000;
	bonus[0] = -31;
	bonus[1] = -21;
	bonus[2] = 0;
	bonus[3] = 42;
	bonus[4] = 84;
	fcn_004c44a0();
	for (i = 0; i < count; i++) {
		k = size;
		while (k != 0) {
			if (faces[start] != 0) {
				face = faces[start];
				faces[start] = 0;
				break;
			}
			k--;
			start = (step + start) % size;
		}
		ids[i] = fcn_004c4fc0(5, -1, -1, 0x10, -1, face, 0, 2);
		fcn_004c5150(-2, -1, g_773d75, fcn_0050b750(price[g_7e1fa0[i]], g_773d75));
		if (g_7747f8 != 0) {
			fcn_004c5150(-2, -1, g_773d75, fcn_0050b750(fcn_0042e410(5000) + 5000, g_773d75));
		}
	}
	fcn_004c44b0();
	while (fcn_004c44c0() == 0) {
		fcn_004c3ff0();
		fcn_004c4940();
		ls_ID2Ptr();
	}
	fcn_004c44a0();
	for (i = 0; i < count; i++) {
		p = fcn_004c4480(ids[i]);
		if (g_7e1fa0[i] != 2) {
			fcn_004c4510(p, p->id);
			for (j = 0; j < 5; j++) {
				unsigned char b;

				v = (float) (p->skills[j] + bonus[g_7e1fa0[i]]);
				n = (int) (252.0f < v ? 252.0f : v);
				b = n < 0 ? 0 : n;
				fcn_004c4700(1, 1, (short) (&p->skills[j] - g_aed32c), &b);
			}
			fcn_004c53a0();
		}
	}
	fcn_004c44b0();
	while (fcn_004c44c0() == 0) {
		fcn_004c3ff0();
		fcn_004c4940();
		ls_ID2Ptr();
	}
}
