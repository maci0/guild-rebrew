// FUNCTION: GOLD 0x00402140
// FUNCTION: GOLDTL 0x00402610

extern int g_6b8010;
extern int g_67a370;
extern int g_6b8058;
extern int g_6b8300;
extern char g_10432c0[];
int __cdecl fcn_00413190(char* p);
void __cdecl fcn_004432d0(int a, int b);
void __cdecl fcn_0043aa30(int flags);
int __cdecl fcn_0045b700(int a, int b, int c);
void __cdecl fcn_004058f0(int r);
void __cdecl fcn_0043a9c0(int flags);

int __cdecl fcn_00402610(char* obj)
{
	int saved;
	int flags;
	int x;
	int r;
	char* p;

	saved = g_6b8010;
	p = *(char**) (obj + 0x88);
	flags = 0;
	r = *(int*) (p + 0xb0);
	if (r == 0) {
		x = g_6b8058;
		if (p != (*(char**)&g_67a370)) {
			x = *(int*) (p + 0x3d8);
		}
		if (*(p + 0x3d5) == 0 && x != 0) {
			fcn_004432d0(fcn_00413190(p), 1);
			flags = x & ~2;
			fcn_0043aa30(flags);
		}
		*(int*) (*(char**) (obj + 0x88) + 0xb0) =
			fcn_0045b700(g_6b8300, *(int*) (*(char**) (obj + 0x88) + 0xb4), 2);
		p = *(char**) (obj + 0x88);
		r = *(int*) (p + 0xb0);
		if (p != g_10432c0 && (*(char**)&g_67a370) == p && r != 0) {
			fcn_004058f0(r);
		}
		if (flags != 0) {
			fcn_0043a9c0(flags);
			fcn_004432d0(saved, 1);
		}
	}
	return r;
}
