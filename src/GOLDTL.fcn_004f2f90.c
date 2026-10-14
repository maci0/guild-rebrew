


#pragma pack(push, 1)

typedef struct
{
	int f0;
	int f4;
	int f8;
	char fc;
	int fd;
	int f11;
	char pad[7];
} F2fMsg;
// SIZE 0x1c

#pragma pack(pop)

void __cdecl fcn_004c6c70(void*);

void __cdecl fcn_004f2f90(int a1, int a2, int a3, int a4, char a5, int a6)
{
	F2fMsg s;

	s.f0 = *(int*) ((char*) a1 + 4);
	s.f4 = *(int*) ((char*) a3 + 1);
	s.f8 = a4;
	s.fc = a5;
	s.fd = a2;
	s.f11 = a6;
	fcn_004c6c70(&s);
}
