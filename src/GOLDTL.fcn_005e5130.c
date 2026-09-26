// FUNCTION: GOLD 0x005d84b0
// SIZE: 188
// FUNCTION: GOLDTL 0x005e5130
// SIZE: 188

typedef struct
{
	int a;
	int size;
	int c;
	int d;
	int kind;
	int pad[15];
} Req;
// SIZE 0x50

// SIZE 0x21c
typedef struct
{
	char pad0[0x1cc];
	int flags;
	char pad1d0[0x4c];
} House;

extern unsigned short g_774970;
extern char g_7f4ca0[];
extern int g_14b5bc0;
extern char* g_14b5bc8;
extern char g_6b5c60[];

void __cdecl fcn_00526120(int, int);
int __cdecl fcn_00525f60(House*, int);
int __cdecl fcn_005cd440(Req*, char*, char*, void*);
void __cdecl fcn_00532ef0(void);
void __cdecl fcn_005e4e50(void);

/* The request's zero-fill is the original's hand-written block-fill
 * prelude; no msvc6 C memset spelling emits it (docs/codegen-walls.md
 * section 6b). */
void __cdecl fcn_005e5130(void)
{
	Req req;
	Req* p;
	int n;

	if (((House*)g_7f4ca0)[g_774970].flags & 0x20000) {
		fcn_00526120(g_14b5bc0, 4);
		return;
	}
	if (fcn_00525f60(&((House*)g_7f4ca0)[g_774970], 1)) {
		n = 0x50;
		p = &req;
		__asm {
			mov edi, p
			mov ebx, n
			xor eax, eax
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L1
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L1:
			add ecx, ebx
			rep stosb
		}
		req.a = 1;
		req.size = 0x400;
		req.kind = 6;
		fcn_005cd440(&req, g_14b5bc8, g_6b5c60, fcn_005e4e50);
	}
	fcn_00532ef0();
}
