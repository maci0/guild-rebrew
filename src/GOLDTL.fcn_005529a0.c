// FUNCTION: GOLD 0x0054a940
// SIZE: 188
// FUNCTION: GOLDTL 0x005529a0
// SIZE: 188

#pragma pack(push, 2)
// SIZE 0xe
typedef struct {
	int a;
	int b;
	int c;
	short d;
} Stamp;
#pragma pack(pop)

extern Stamp g_7f4c00;

void __cdecl fcn_00546190(char* p);
void __cdecl fcn_00500bb0(Stamp* s, int a, int b, int c);

void __cdecl fcn_005529a0(char* p)
{
	int i;
	int* q;

	p[0xd8] = 0;
	q = (int*) (p + 0x8c);
	for (i = 0; i < 6; i++) {
		if (*q++ != -1) {
			p[0xd8]++;
		}
	}
	if (p[0xd8] == 0) {
		fcn_00546190(p);
		return;
	}
	for (i = 0; i < 6; i++) {
		((int*) (p + 0xac))[i] = -1;
	}
	p[0xd2] = 0;
	*(Stamp*) (p + 0xc4) = g_7f4c00;
	*(Stamp*) (p + 0x52) = g_7f4c00;
	fcn_00500bb0((Stamp*) (p + 0x52), 0, 2, 0);
}
