// FUNCTION: GOLDTL 0x4f2e80
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
} F2eMsg;

#pragma pack(pop)
// SIZE 0x20

int __cdecl fcn_004c6c30(void*);

int __cdecl fcn_004f2e80(int a1, int a2)
{
	F2eMsg m;

	if (a1 == 0) {
		return -1;
	}
	m.f0 = 6;
	m.f4 = -1;
	m.f8 = *(int*) ((char*) a1 + 1);
	m.fc = 0;
	m.f10 = 0;
	m.f11 = 0;
	m.f13 = a2;
	return fcn_004c6c30(&m);
}
