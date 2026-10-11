// FUNCTION: GOLD 0x004582c0
// FUNCTION: GOLDTL 0x454c00

// SIZE 0x8
typedef struct Link {
	char* e;
	struct Link* next;
} Link;

extern char g_6b89a0[];
extern int g_67a370;

void* __cdecl fcn_0041e1d0(void*, int, int);
void __cdecl m_pool_free(void*, void*);
void __cdecl fcn_004379a0(int, int, int, void*, void*);
char __cdecl fcn_004545c0(char*, char*);
void __cdecl fcn_00454850(char*, int, int, int);

char* __cdecl fcn_00454c00(int a1, int mask, int a3, int a4)
{
	char* ctx;
	Link* l;

	ctx = (char*) fcn_0041e1d0(g_6b89a0, 0x48, 0x40);
	*(int*) (ctx + 0x44) = mask;
	*(int*) (ctx + 0x34) = a3;
	*(int*) (ctx + 0x38) = a4;
	fcn_004379a0(g_67a370, a1, mask, fcn_004545c0, ctx);
	fcn_00454850(ctx, a3, 1, a4);
	if (*(int*) (ctx + 0x30) == 0) {
		m_pool_free(g_6b89a0, ctx);
		return 0;
	}
	for (l = *(Link**) (ctx + 0x3c); l != 0; l = l->next) {
		*(int*) (*(char**) (l->e + 0x1ec) + 0xb0) = -1;
	}
	return ctx;
}
