


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

extern int g_14abcc0;

int __cdecl fcn_00525fb0(char*);
void __cdecl fcn_0052a0c0(char*, int);
void __cdecl fcn_005bdc30(int, Req*, int, void*, int);
void __cdecl fcn_0052a2d0(void);
void __cdecl fcn_005305a0(void);
int __cdecl fcn_005af2f0(int, char*);

void __cdecl fcn_005af4e0(char* a)
{
	Req req;

	if (fcn_00525fb0(a) != 0) {
		return;
	}
	memset(&req, 0, sizeof(req));
	req.size = 0x400;
	req.kind = 2;
	req.c = 0;
	if (a == 0) {
		return;
	}
	fcn_0052a0c0(a, 0);
	fcn_005bdc30(1, &req, g_14abcc0, (void*) fcn_005af2f0, 0);
	fcn_0052a2d0();
	fcn_005305a0();
}
