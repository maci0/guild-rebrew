// FUNCTION: GOLDTL 0x005c0670
// SIZE: 105

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

extern int g_66601c;

void __cdecl fcn_0051af00(char*, int, ...);
int __cdecl fcn_005cd440(Req*, char*, int, void*);
void __cdecl fcn_00532ef0(void);
void __cdecl fcn_005c02a0(void);

void __cdecl fcn_005c0670(void)
{
	Req req;
	char text[0x100];

	memset(&req, 0, sizeof(req));
	req.size = 0x40400;
	req.kind = 6;
	req.d = g_66601c;
	req.c = 0;
	fcn_0051af00(text, 0x174f);
	fcn_005cd440(&req, text, 0, (void*) fcn_005c02a0);
	fcn_00532ef0();
}
