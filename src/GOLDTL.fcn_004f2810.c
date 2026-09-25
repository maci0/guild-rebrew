// FUNCTION: GOLD 0x004f0700
// SIZE: 112
// FUNCTION: GOLDTL 0x4f2810
// SIZE: 112

#pragma pack(push, 1)

typedef struct
{
	int f0;
	int f4;
	int f8;
	int fc;
	char f10;
	short f11;
	int f13;
	char pad[9];
} F28Msg;

#pragma pack(pop)
// SIZE 0x20

int __cdecl fcn_004c6c30(void*);

int __cdecl fcn_004f2810(int a1, int a2, int a3, int a4, short a5, int a6)
{
	F28Msg m;

	if (a1 == 0 || a2 == 0 || a4 == -1) {
		return -1;
	}
	m.f0 = 2;
	m.f4 = *(int*) ((char*) a1 + 4);
	m.f8 = *(int*) ((char*) a2 + 1);
	m.fc = a3;
	m.f10 = (char) a4;
	m.f11 = a5;
	m.f13 = a6;
	return fcn_004c6c30(&m);
}
