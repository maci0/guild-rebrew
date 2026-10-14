


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

extern int g_7746a0;
extern int g_14aaf18;
extern int g_14aaf38;
extern int g_14ad2c0;
extern int g_14ab04c;
extern __int64 g_666018;
extern int g_66601c;
extern char s_6aa714[];
extern char s_6aa700[];
extern char s_6aa6e4[];
extern char s_6aa6d0[];

void __cdecl fcn_005338a0(void);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_005338d0(char*, int, int);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_005bdc30(int, Req*, char*, void*, int);
int __cdecl fcn_005cd440(Req*, char*, int, void*);
void __cdecl fcn_00532ef0(void);
void __cdecl fcn_005bebe0(int, int, int);
void __cdecl fcn_005c0670(int);
void __cdecl fcn_005bf0d0(void);
void __cdecl fcn_005bf9e0(void);

/* The first request's zero-fill is the original's hand-written block-fill
 * prelude; no msvc6 C memset spelling emits it (docs/codegen-walls.md
 * section 6b). */
void __cdecl fcn_0059f6c0(int a0, int a1)
{
	int a;
	int b;
	int c;
	int d;

	fcn_005338a0();
	if (fcn_005373e0((void*) fcn_0059f6c0, 0x67fff) != 0) {
		do {
			a = fcn_005338d0(s_6aa714, g_14aaf18, 0x17);
			b = fcn_005338d0(s_6aa700, g_14aaf38, 0xd);
			c = fcn_005338d0(s_6aa6e4, g_14ad2c0, 0xc);
			d = fcn_005338d0(s_6aa6d0, g_14ab04c, 0x10);
			if (g_7746a0 != 0) {
				if (g_7746a0 == a) {
					Req req;
					char text[0x80];
					int n;
					Req* p;

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
					req.size = -1;
					req.kind = 6;
					req.c = 0xe07c43b4;
					req.d = 3;
					req.id = 0x727;
					fcn_0051af00(text, 0x16ff);
					fcn_005bdc30(1, &req, text, (void*) fcn_005bf0d0, 0);
				}
				else if (g_7746a0 == b) {
					Req req;
					char text[0x40];

					memset(&req, 0, sizeof(req));
					req.size = 0x400;
					req.kind = 6;
					req.c = (*(int*)&g_666018);
					req.d = g_66601c;
					req.id = 0x727;
					fcn_0051af00(text, 0x1707);
					fcn_005cd440(&req, text, 0, (void*) fcn_005bf9e0);
					fcn_00532ef0();
				}
				else if (g_7746a0 == c) {
					fcn_005bebe0(a0, a1, 2);
				}
				else if (g_7746a0 == d) {
					fcn_005c0670(a0);
				}
			}
		} while (fcn_005373e0((void*) fcn_0059f6c0, 0x67fff) != 0);
	}
}
