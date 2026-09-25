// FUNCTION: GOLDTL 0x005ad5a0
// SIZE: 158

void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)

typedef struct
{
	int a;
	int size;
	int c;
	int d;
	int kind;
	int pad[14];
	int id;
} Req;
// SIZE 0x50

int __cdecl fcn_00525fb0(char*);
void __cdecl fcn_0052a0c0(char*, int);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_005bdc30(int, Req*, char*, void*, int);
void __cdecl fcn_0052a2d0(void);
void __cdecl fcn_005305a0(void);
void __cdecl fcn_005ad380(void);

void __cdecl fcn_005ad5a0(char* a)
{
	Req req;
	char text[0x80];

	if (fcn_00525fb0(a) != 0) {
		return;
	}
	memset(&req, 0, sizeof(req));
	req.size = 0x400;
	if (a == 0) {
		return;
	}
	fcn_0052a0c0(a, 0);
	fcn_0051af00(text, 0x19e2);
	req.id = 0x727;
	req.kind = 7;
	req.c = 0xa07443b4;
	req.d = 1;
	fcn_005bdc30(1, &req, text, (void*) fcn_005ad380, 0);
	fcn_0052a2d0();
	fcn_005305a0();
}
