


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
} F4fMsg;

#pragma pack(pop)
// SIZE 0x20

int __cdecl fcn_004c6c30(void*);

int __cdecl fcn_004f0430(int a1, void* a2, int a3, short a4, int a5)
{
	F4fMsg m;

	if (a1 == 0 || a2 == 0) {
		return -1;
	}
	m.f0 = 1;
	m.f4 = *(int*) ((char*) a1 + 4);
	m.f8 = *(int*) ((char*) a2 + 1);
	m.fc = a3;
	m.f10 = (char) 0xff;
	m.f11 = a4;
	m.f13 = a5;
	return fcn_004c6c30(&m);
}
