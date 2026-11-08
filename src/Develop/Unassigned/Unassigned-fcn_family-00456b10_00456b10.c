typedef struct IUnk IUnk;
typedef struct IUnkVtbl {
	long (__stdcall* QueryInterface)(IUnk*, void*, void**);
	unsigned long (__stdcall* AddRef)(IUnk*);
	unsigned long (__stdcall* Release)(IUnk*);
} IUnkVtbl;
struct IUnk {
	IUnkVtbl* v;
};

extern unsigned long g_14ce728;

void __cdecl fcn_0045bfb0(int);
typedef int(__stdcall* Fn1)(void* self);

extern unsigned int g_10405fc;
extern unsigned int g_104061c;
extern void** g_1040610[];

/* ADDRESS: GOLDTL 0x00456b10 */
void __cdecl fcn_00456b10(char* s)
{
	int* p;

	if (*(int*) s != 0) {
		p = *(int**) (s + 0xc);
		if (p != 0) {
			p[1] = 0;
			p[0] = 0;
			p[3] = 0;
		}
		fcn_0045bfb0(*(int*) s);
		*(int*) s = 0;
		*(int**) (s + 0xc) = 0;
	}
	if (*(IUnk**) (s + 0x80) != 0) {
		g_14ce728 = (*(IUnk**) (s + 0x80))->v->Release(*(IUnk**) (s + 0x80));
		*(IUnk**) (s + 0x80) = 0;
	}
	if (*(IUnk**) (s + 0x84) != 0) {
		g_14ce728 = (*(IUnk**) (s + 0x84))->v->Release(*(IUnk**) (s + 0x84));
		*(IUnk**) (s + 0x84) = 0;
	}
	*(int*) (s + 0x8c) = 0;
	*(int*) (s + 0x88) = 0;
}

/* ADDRESS: GOLDTL 0x00456c10 */
void __cdecl fcn_00456c10(void)
{
	unsigned int i;
	unsigned int s;

	for (i = 0, s = g_104061c; s <= g_10405fc && i <= 2; i++, s += s) {
		if (g_1040610[i] != 0) {
			(*(int*)&g_14ce728) = ((Fn1) ((void**) *g_1040610[i])[2])(g_1040610[i]);
			g_1040610[i] = 0;
		}
	}
}
