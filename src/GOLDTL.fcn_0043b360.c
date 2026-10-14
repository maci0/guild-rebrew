typedef struct IRes IRes;
// SIZE 0xc
typedef struct {
	void* slots[2];
	unsigned long (__stdcall* Release)(IRes*);
} IResVtbl;
// SIZE 0x4
struct IRes {
	IResVtbl* v;
};

extern char* g_1042c38;
extern char g_1042d00[];
extern unsigned long g_14ce728;
extern int g_6b8300;
extern int g_6b89c0;
extern int g_6b8010;

void __cdecl fcn_00452340(void);
void __cdecl fcn_0043b8f0(int a);
void __cdecl fcn_00459a90(int a);
void __cdecl fcn_00456c60(void);
void __cdecl fcn_004432d0(int a, int b);
void __cdecl fcn_00456c10(void);
void __cdecl fcn_0041b7c0(void);
void __cdecl fcn_0041b7f0(void);
int __cdecl fcn_0041baa0(void);
int __cdecl fcn_0041ba40(void);
void __cdecl fcn_00436aa0(int a);
void __cdecl fcn_00452360(void);
void __cdecl fcn_0043b990(int a);
void __cdecl fcn_00459a10(int a);
void __cdecl fcn_00456c80(void);
void __cdecl fcn_00450a00(int a);

/* ADDRESS: GOLDTL 0x0043b360 */
char __cdecl fcn_0043b360(void)
{
	char* o;
	int saved;
	int i;
	char r;

	r = 0;
	fcn_00452340();
	for (o = g_1042c38; o != g_1042d00; o = *(char**) (o + 0x1f8)) {
		if (*(IRes**) (o + 0x268) != 0) {
			g_14ce728 = (*(IRes**) (o + 0x268))->v->Release(*(IRes**) (o + 0x268));
			*(IRes**) (o + 0x268) = 0;
		}
	}
	if (g_6b8300 != 0) {
		fcn_0043b8f0(g_6b8300);
	}
	if (g_6b89c0 != 0) {
		fcn_00459a90(g_6b89c0);
	}
	fcn_00456c60();
	saved = g_6b8010;
	for (i = 0; i < 0x40; i++) {
		if (i != saved) {
			fcn_004432d0(i, 1);
			if (g_6b8300 != 0) {
				fcn_0043b8f0(g_6b8300);
			}
			if (g_6b89c0 != 0) {
				fcn_00459a90(g_6b89c0);
			}
			fcn_00456c60();
		}
	}
	fcn_004432d0(saved, 1);
	fcn_00456c10();
	fcn_0041b7c0();
	fcn_0041b7f0();
	if (fcn_0041baa0() == 0) {
		fcn_0041ba40();
		fcn_00436aa0(0);
		fcn_00452360();
		if (g_6b8300 != 0) {
			fcn_0043b990(g_6b8300);
		}
		if (g_6b89c0 != 0) {
			fcn_00459a10(g_6b89c0);
		}
		fcn_00456c80();
		for (i = 0; i < 0x40; i++) {
			if (i != saved) {
				fcn_004432d0(i, 1);
				if (g_6b8300 != 0) {
					fcn_0043b990(g_6b8300);
					fcn_00450a00(1);
				}
				if (g_6b89c0 != 0) {
					fcn_00459a10(g_6b89c0);
				}
			}
		}
		fcn_004432d0(saved, 1);
		fcn_00450a00(1);
		r = 1;
	}
	return r;
}
