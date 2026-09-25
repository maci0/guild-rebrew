// FUNCTION: GOLDTL 0x57d830
// SIZE: 279

extern float g_6652c4;
extern float g_6628a0;
extern double g_665f00;
extern double g_664f08;
extern double g_662b20;

char* __cdecl fcn_00508e40(int);
void __cdecl fcn_005015e0(int*, int*, int*, int);
int __cdecl fcn_0050c710(int, int, int);
float __cdecl fcn_00507f10(char*, int);
float __cdecl gm_RandomFloat01(void);
unsigned short __cdecl fcn_005b5660(int, unsigned short*);

void __cdecl fcn_0057d830(char* u, int count)
{
	int found;
	float sq;
	char* h;
	int n;
	float mult;
	float g;
	int i;

	h = fcn_00508e40(*(int*) (u + 0xc));
	if (h == 0) {
		return;
	}
	fcn_005015e0(&found, 0, 0, *(int*) (u + 0x10));
	if (found == 0) {
		return;
	}
	n = fcn_0050c710(found, 0x1d, 1);
	mult = n * g_6652c4 + g_6628a0;
	g = fcn_00507f10(h, 2);
	sq = g * g;
	for (i = count; i > 0; i--) {
		*(int*) (u + 0xac) += (int) (((gm_RandomFloat01() + sq) * g_665f00 + g_664f08) * mult) << 5;
	}
	if (gm_RandomFloat01() + g_6628a0 < mult) {
		for (i = 0; i < 4; i++) {
			if (*(unsigned short*) (u + 0xc8 + i * 2) == 0) {
				if (gm_RandomFloat01() > g_662b20) {
					*(unsigned short*) (u + 0xc8 + i * 2) = fcn_005b5660(i, (unsigned short*) (u + 0xc8));
				}
				break;
			}
		}
	}
}
