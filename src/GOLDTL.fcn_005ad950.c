// FUNCTION: GOLDTL 0x005ad950
// SIZE: 216

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

extern char* g_868050;

int __cdecl fcn_00525fb0(unsigned char*);
void __cdecl fcn_0052a0c0(unsigned char*, int);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_005ad640(void);
void __cdecl fcn_005bdc30(int, Req*, char*, void*, int);
void __cdecl fcn_0052a2d0(void);
void __cdecl fcn_005305a0(void);

void __cdecl fcn_005ad950(unsigned char* e)
{
	Req req;
	char text[0x400];

	if (fcn_00525fb0(e) == 0) {
		memset(&req, 0, sizeof(req));
		req.size = 0x400;
		if (e != 0) {
			fcn_0052a0c0(e, 0);
			req.id = 0x727;
			req.kind = 7;
			if (g_868050[*e * 589] == 0x13) {
				req.c = 0x90010;
				req.d = 0;
			}
			else {
				req.c = 0xa7fd43b4;
				req.d = 1;
			}
			fcn_0051af00(text, 0x19f6);
			fcn_005bdc30(1, &req, text, fcn_005ad640, 0);
			fcn_0052a2d0();
			fcn_005305a0();
		}
	}
}
