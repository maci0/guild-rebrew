#include <string.h>

typedef struct
{
	void (__cdecl* fn)(int a, int n, int total);
	int id;
	int total;
	int count;
	char skip;
} fcn_0043aad0_Cb;
// SIZE 0x14

extern char s_67a464[];

int __cdecl fcn_0065f220(const char* a, const char* b);
void __cdecl fcn_00439860(char* o);
int __cdecl fcn_0044c200(char* a, char* b);
void __cdecl fcn_00449f90(char* o, int a, char* name);
void __cdecl fcn_00438ac0(char* o, int a);

// FUNCTION: GOLDTL 0x43aad0
char __cdecl fcn_0043aad0(char* o, fcn_0043aad0_Cb* cb)
{
	char* ext;
	int len;
	int n;
	char buf[0x100];

	if (*(char**) (o + 0x1ec) == 0 || *(char**) (*(char**) (o + 0x1ec) + 0x40c) == 0 || *(int*) (o + 0x220) != cb->id) {
		return 1;
	}
	if (cb->skip) {
		cb->total++;
		return 1;
	}
	if (cb->fn != 0) {
		n = cb->count;
		cb->count = n + 1;
		cb->fn(0, n, cb->total);
	}
	strcpy(buf, *(char**) (*(char**) (o + 0x1ec) + 0x40c));
	len = strlen(buf);
	if (len > 2) {
		ext = buf + len - 2;
		if (!strcmp(ext, "_0") || !strcmp(ext, "_1") || fcn_0065f220(ext, s_67a464) == 0) {
			*ext = 0;
		}
	}
	fcn_00439860(o);
	if (fcn_0044c200(buf, buf)) {
		fcn_00449f90(o, 0, buf);
	}
	fcn_00438ac0(o, 1);
	return 1;
}
