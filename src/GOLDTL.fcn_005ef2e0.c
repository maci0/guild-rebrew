#include <malloc.h>
#include <windows.h>

void __fastcall fcn_006165dd(void* o, int dummy);
void __fastcall fcn_00616815(void* o, int dummy);
void __fastcall fcn_006168be(void* o, int dummy);
void __fastcall fcn_0061680a(void* o, int dummy);
int __fastcall fcn_006165ef(void* o, int dummy, wchar_t* name, int flag);
int __fastcall fcn_00618c83(void* o, int dummy, int a, int b, void* p,
	int one, int c, int d, int e, int f);

typedef struct Obj5ef2e0 {
	int f0;
	int f4;
	int f8;
	int fc;
} Obj5ef2e0;

/* ADDRESS: GOLDTL 0x005ef2e0 */
int __stdcall fcn_005ef2e0(wchar_t* name, int a2, int* a3, int* a4, int* a5)
{
	Obj5ef2e0 obj;
	char buf[0x3e8];
	char* p;
	int n;
	int r;

	fcn_006165dd(&obj, 0);
	fcn_00616815(buf, 0);
	r = 0;
	if (a3 != 0) {
		*a3 = 0;
	}
	if (a4 != 0) {
		*a4 = 0;
	}
	if (a5 != 0) {
		*a5 = 0;
	}
	n = fcn_006165ef(&obj, 0, name, 1);
	if (n < 0) {
		return n;
	}
	n = WideCharToMultiByte(0, 0, name, -1, 0, 0, 0, 0);
	p = (char*) _alloca((n + 3) & ~3);
	WideCharToMultiByte(0, 0, name, -1, p, n, 0, 0);
	n = fcn_00618c83(buf, 0, obj.f8, obj.fc, p, 1, a2, (int) a3, (int) a4,
	    (int) a5);
	if (n < 0) {
		r = n;
	}
	fcn_006168be(buf, 0);
	fcn_0061680a(&obj, 0);
	return r;
}
