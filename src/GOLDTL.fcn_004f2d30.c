// FUNCTION: GOLD 0x004f0c20
// SIZE: 96
// FUNCTION: GOLDTL 0x4f2d30
// SIZE: 96

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
} F2dMsg;

#pragma pack(pop)
// SIZE 0x20

int __cdecl fcn_004c6c30(void*);

int __cdecl fcn_004f2d30(int a1, int a2, int a3, int a4)
{
	F2dMsg m;

	if (a1 == 0 || a3 == -1) {
		return -1;
	}
	m.f0 = 5;
	m.f4 = -1;
	m.f8 = *(int*) ((char*) a1 + 1);
	m.fc = a2;
	m.f10 = (char) a3;
	m.f11 = 0;
	m.f13 = a4;
	return fcn_004c6c30(&m);
}
