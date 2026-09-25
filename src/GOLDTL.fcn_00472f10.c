typedef struct
{
	int i[0x3cc / 4];
} fcn_00472f10_Win;
// SIZE 0x3cc

extern fcn_00472f10_Win g_1015f40[];
extern int g_772514;
extern int g_772568;
extern char s_67d890[];
extern char s_67d868[];

void __cdecl fcn_0041d9e0(const char* msg);
int __cdecl fcn_00466190(int id);
void __cdecl fcn_00475fd0(int surf);
void __cdecl fcn_0047cba0(int x, int y, int surf, int src, int mode);
void __cdecl fcn_00476060(int surf);

// FUNCTION: GOLDTL 0x472f10
// SIZE: 142
void __cdecl fcn_00472f10(int x, int y, int id)
{
	fcn_00472f10_Win* w;
	int src;

	w = &g_1015f40[g_772514];
	if (w->i[0x290 / 4] == 0) {
		fcn_0041d9e0(s_67d890);
		return;
	}
	if (w->i[0x38 / 4] == 0) {
		fcn_0041d9e0(s_67d868);
		return;
	}
	src = fcn_00466190(id);
	if (src != 0) {
		fcn_00475fd0(w->i[0x38 / 4]);
		fcn_0047cba0(x, y, w->i[0x38 / 4], src, g_772568);
		fcn_00476060(w->i[0x38 / 4]);
	}
}
