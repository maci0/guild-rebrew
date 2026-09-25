// FUNCTION: GOLDTL 0x575ab0
// SIZE: 567

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
void __cdecl fcn_005b3200(char*, char*, int, int);
void __cdecl fcn_004ee830(char*, int);
void __cdecl fcn_00529160(char*, int, int, char*);
void __cdecl fcn_00546190(char*);
int __cdecl fcn_005764a0(char*, int);
void __cdecl fcn_00500bb0(struct pos14*, int, int, int);
int __cdecl fcn_00500d20(struct pos14*, struct pos14*);

void __cdecl fcn_00575ab0(char* u)
{
	int k;
	char* h;
	char* o;
	int q;
	int t;

	k = fcn_00500e20(&g_7f4c00);
	h = fcn_00508e40(*(int*) (u + 0xac));
	if (h == 0 || ahm_CheckFlag(h) == 0) {
		*(int*) (u + 0x70) = -2;
	}
	if (*(int*) (u + 0x70) != -2 && *(int*) (u + 0x70) != -1) {
		t = (unsigned short) g_7f4c00.b;
		if (!(t >= g_696550[k]) && !(t < g_696540[k])) {
			if (*(int*) (u + 0x70) == 1) {
				q = fcn_00502cd0(*(int*) (*(char**) (h + 0x16c) + 0x5d), 2, 6, 0, 0x24b);
				o = fcn_00508e40(*(int*) (u + 0xc));
				if (o != 0) {
					fcn_005b3200(o, h, q, *(int*) (u + 0xb0));
				}
				fcn_004ee830(h, *(int*) (u + 0xb0));
				fcn_00529160(0, 0, *(unsigned short*) h, 0);
				fcn_00546190(u);
				return;
			}
			if (fcn_005764a0(*(char**) (h + 0x16c), 0x24b) != 0) {
				*(struct pos14*) (u + 0xbc) = g_7f4c00;
				fcn_00500bb0((struct pos14*) (u + 0x52), 0, 0xf, 0);
				return;
			}
			if (*(int*) (u + 0x70) != 0) {
				return;
			}
			*(int*) (u + 0xb4) -= fcn_00500d20((struct pos14*) (u + 0xbc), &g_7f4c00);
			*(struct pos14*) (u + 0x52) = g_7f4c00;
			fcn_00500bb0((struct pos14*) (u + 0x52), 0, 5, 0);
			*(struct pos14*) (u + 0xbc) = g_7f4c00;
			if (*(int*) (u + 0xb4) <= 0) {
				*(int*) (u + 0x70) = 1;
			}
			return;
		}
		*(struct pos14*) (u + 0xbc) = g_7f4c00;
		fcn_00500bb0((struct pos14*) (u + 0x52), 1, 0, 0);
		return;
	}
	fcn_00546190(u);
}
