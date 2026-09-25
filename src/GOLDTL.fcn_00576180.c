// FUNCTION: GOLD 0x0056dd40
// SIZE: 628
// FUNCTION: GOLDTL 0x576180
// SIZE: 628

#pragma pack(2)
// SIZE 0xe
struct pos14 {
	int a;
	int b;
	int c;
	short d;
};
#pragma pack()

extern struct pos14 g_7f4c00;
extern float g_696550[];
extern float g_696540[];

int __cdecl fcn_00500e20(struct pos14*);
char* __cdecl fcn_00508e40(int);
int __cdecl ahm_CheckFlag(char*);
int __cdecl fcn_00502cd0(int, int, int, int, int);
void __cdecl fcn_005b3120(char*, char*, int, int);
float __cdecl fcn_004ec8a0(char*, int);
void __cdecl fcn_004ee6d0(char*, int, float);
void __cdecl fcn_00529160(char*, int, int, char*);
void __cdecl fcn_00546190(char*);
int __cdecl fcn_005764a0(char*, int);
void __cdecl fcn_00500bb0(struct pos14*, int, int, int);
int __cdecl fcn_00500d20(struct pos14*, struct pos14*);

void __cdecl fcn_00576180(char* u)
{
	int k;
	char* h;
	char* o;
	int q;
	int t;
	float f;

	k = fcn_00500e20(&g_7f4c00);
	f = 0.0f;
	h = fcn_00508e40(*(int*) (u + 0xac));
	if (h == 0 || ahm_CheckFlag(h) == 0 || (f = fcn_004ec8a0(h, *(int*) (u + 0xb0))) <= 0.0f) {
		*(int*) (u + 0x70) = -2;
	}
	if (*(int*) (u + 0x70) != -2 && *(int*) (u + 0x70) != -1) {
		t = (unsigned short) g_7f4c00.b;
		if (!(t >= g_696550[k]) && !(t < g_696540[k])) {
			if (*(int*) (u + 0x70) == 1) {
				q = fcn_00502cd0(*(int*) (*(char**) (h + 0x16c) + 0x5d), 2, 6, 0, 0x24b);
				o = fcn_00508e40(*(int*) (u + 0xc));
				if (o != 0) {
					fcn_005b3120(o, h, q, *(int*) (u + 0xb0));
				}
				fcn_004ee6d0(h, *(int*) (u + 0xb0), f + *(float*) (u + 0xb4));
				fcn_00529160(0, 0, *(unsigned short*) h, 0);
				fcn_00546190(u);
				return;
			}
			if (fcn_005764a0(*(char**) (h + 0x16c), 0x24b) != 0) {
				*(struct pos14*) (u + 0xc0) = g_7f4c00;
				fcn_00500bb0((struct pos14*) (u + 0x52), 0, 0xf, 0);
				return;
			}
			if (*(int*) (u + 0x70) != 0) {
				return;
			}
			*(int*) (u + 0xb8) -= fcn_00500d20((struct pos14*) (u + 0xc0), &g_7f4c00);
			*(struct pos14*) (u + 0x52) = g_7f4c00;
			fcn_00500bb0((struct pos14*) (u + 0x52), 0, 5, 0);
			*(struct pos14*) (u + 0xc0) = g_7f4c00;
			if (*(int*) (u + 0xb8) <= 0) {
				*(int*) (u + 0x70) = 1;
			}
			return;
		}
		*(struct pos14*) (u + 0xc0) = g_7f4c00;
		fcn_00500bb0((struct pos14*) (u + 0x52), 1, 0, 0);
		return;
	}
	fcn_00546190(u);
}
