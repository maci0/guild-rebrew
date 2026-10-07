// FUNCTION: GOLD 0x00422c90
// FUNCTION: GOLDTL 0x0041e530

__declspec(dllimport) long __stdcall DefWindowProcA(void* hwnd, unsigned int msg, unsigned int wp, long lp);
__declspec(dllimport) int __stdcall DestroyWindow(void* hwnd);

typedef struct IUnk41e530 IUnk41e530;

// SIZE 0x28
typedef struct {
	void* fn[10];
} VT41e530;

struct IUnk41e530 {
	VT41e530* vt;
};

long __cdecl fcn_0041f530(int id, long* p1, long* p2);
int __cdecl fcn_0041f5f0(int id);
char* __cdecl fcn_0041f9d0(void* hwnd);

long __stdcall fcn_0041e530(void* hwnd, unsigned int msg, unsigned int wp, long lp)
{
	char* n;
	int id;
	IUnk41e530* o;

	switch (msg) {
	case 2:
		n = fcn_0041f9d0(hwnd);
		if (n != 0) {
			fcn_0041f5f0(*(int*) (n + 8));
		}
		break;
	case 0x100:
		if (wp == 0x20 || wp == 0x1b) {
			n = fcn_0041f9d0(hwnd);
			if (n != 0) {
				o = *(IUnk41e530**) (n + 0x120);
				((void(__stdcall*)(IUnk41e530*)) o->vt->fn[9])(o);
				fcn_0041f5f0(*(int*) (n + 8));
				DestroyWindow(hwnd);
				return 0;
			}
		}
		break;
	case 0x9021:
		id = *(volatile long*) &lp;
		if (fcn_0041f530(id, (long*) &wp, &lp) == 1) {
			fcn_0041f5f0(id);
			DestroyWindow(hwnd);
			return 0;
		}
		break;
	default:
		return DefWindowProcA(hwnd, msg, wp, lp);
	}
	return 0;
}
