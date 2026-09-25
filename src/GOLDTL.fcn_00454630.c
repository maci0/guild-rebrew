// FUNCTION: GOLDTL 0x454630
// SIZE: 167

// SIZE 0x8
typedef struct Link {
	char* e;
	struct Link* next;
} Link;

extern char g_6b89a0[];

void* __cdecl fcn_0041e1d0(void*, int, int);
void __cdecl fcn_0041e2e0(void*, void*);
char __cdecl fcn_004545c0(char*, char*);

char* __cdecl fcn_00454630(char* src, float* lo, float* hi)
{
	char* ctx;
	Link* l;
	char* d;

	ctx = (char*) fcn_0041e1d0(g_6b89a0, 0x48, 0x40);
	for (l = *(Link**) (src + 0x3c); l != 0; l = l->next) {
		d = *(char**) (l->e + 0x1ec);
		if (*(float*) (d + 0x90) <= hi[0] && *(float*) (d + 0xa0) >= lo[0] && *(float*) (d + 0x98) <= hi[2] && *(float*) (d + 0xa8) >= lo[2]) {
			fcn_004545c0(l->e, ctx);
		}
	}
	if (*(int*) (ctx + 0x30) == 0) {
		fcn_0041e2e0(g_6b89a0, ctx);
		return 0;
	}
	return ctx;
}
