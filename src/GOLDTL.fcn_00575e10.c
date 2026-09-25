// FUNCTION: GOLDTL 0x575e10
// SIZE: 601

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
char* __cdecl fcn_004ec950(char*, int);
int __cdecl fcn_00502cd0(int, int, int, int, int);
void __cdecl fcn_005b3190(char*, char*, int, int);
void __cdecl fcn_004eea30(char*, int, float);
void __cdecl fcn_00529160(char*, int, int, char*);
void __cdecl fcn_00546190(char*);
int __cdecl fcn_005764a0(char*, int);
void __cdecl fcn_00500bb0(struct pos14*, int, int, int);
int __cdecl fcn_00500d20(struct pos14*, struct pos14*);

void __cdecl fcn_00575e10(char* u)
{
	int k;
	char* h;
	char* o;
	char* s;
	int q;
	int t;

	k = fcn_00500e20(&g_7f4c00);
	s = 0;
	h = fcn_00508e40(*(int*) (u + 0xac));
	if (h == 0 || ahm_CheckFlag(h) == 0 || (s = fcn_004ec950(h, *(int*) (u + 0xb0))) == 0) {
		*(int*) (u + 0x70) = -2;
	}
	if (*(int*) (u + 0x70) != -2) {
		t = (unsigned short) g_7f4c00.b;
		if (!(t >= g_696550[k]) && !(t < g_696540[k])) {
			if (fcn_005764a0(*(char**) (h + 0x16c), 0x24b) != 0) {
				*(struct pos14*) (u + 0xc0) = g_7f4c00;
				fcn_00500bb0((struct pos14*) (u + 0x52), 0, 0xf, 0);
				return;
			}
			if (*(int*) (u + 0x70) == 1) {
				q = fcn_00502cd0(*(int*) (*(char**) (h + 0x16c) + 0x5d), 2, 6, 0, 0x24b);
				o = fcn_00508e40(*(int*) (u + 0xc));
				if (o != 0) {
					fcn_005b3190(o, h, q, *(int*) (u + 0xb0));
				}
				fcn_004eea30(h, *(int*) (u + 0xb0), *(float*) (u + 0xb4) + *(float*) (s + 4));
				fcn_00529160(0, 0, *(unsigned short*) h, 0);
				fcn_00546190(u);
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
