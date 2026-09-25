// FUNCTION: GOLDTL 0x0059d9b0
// SIZE: 150

void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)

// SIZE 0x50
typedef struct {
	int a;
	int size;
	int c;
	int d;
	int kind;
	int pad[14];
	int id;
} Req;

int __cdecl fcn_00525fb0(int);
void __cdecl fcn_0052a0c0(int, int);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_0059d6b0(void);
void __cdecl fcn_005bdc30(int, Req*, char*, void*, int);
void __cdecl fcn_0052a2d0(void);
void __cdecl fcn_005305a0(void);

void __cdecl fcn_0059d9b0(int e)
{
	Req req;
	char text[0x400];

	if (fcn_00525fb0(e) == 0) {
		memset(&req, 0, sizeof(req));
		req.size = 0x400;
		if (e != 0) {
			fcn_0052a0c0(e, 0);
			req.id = 0x727;
			req.kind = 6;
			req.c = 0;
			fcn_0051af00(text, 0x19f6);
			fcn_005bdc30(1, &req, text, fcn_0059d6b0, 0);
			fcn_0052a2d0();
			fcn_005305a0();
		}
	}
}
