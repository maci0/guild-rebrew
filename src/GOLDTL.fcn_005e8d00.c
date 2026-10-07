// FUNCTION: GOLD 0x005dc210
// FUNCTION: GOLDTL 0x005e8d00

extern int g_7763a0;
extern int g_7763a4;
extern int g_7763a8;
extern float g_7763ac[];
extern float g_77640c[];
extern float g_77646c[];
extern float g_7764cc[];
extern float g_77652c[];
extern float g_77658c;

int __cdecl ls_ReadVfsDataChecked(void*, int, int, int);

int __cdecl fcn_005e8d00(int fh)
{
	if (ls_ReadVfsDataChecked(&g_7763a0, 4, 1, fh) == 0) {
		return 0;
	}
	if (ls_ReadVfsDataChecked(&g_7763a4, 4, 1, fh) == 0) {
		return 0;
	}
	if (ls_ReadVfsDataChecked(&g_7763a8, 4, 1, fh) == 0) {
		return 0;
	}
	if (ls_ReadVfsDataChecked(g_7763ac, 0x60, 1, fh) == 0) {
		return 0;
	}
	if (ls_ReadVfsDataChecked(g_77640c, 0x60, 1, fh) == 0) {
		return 0;
	}
	if (ls_ReadVfsDataChecked(g_77646c, 0x60, 1, fh) == 0) {
		return 0;
	}
	if (ls_ReadVfsDataChecked(g_7764cc, 0x60, 1, fh) == 0) {
		return 0;
	}
	if (ls_ReadVfsDataChecked(g_77652c, 0x60, 1, fh) == 0) {
		return 0;
	}
	return ls_ReadVfsDataChecked(&g_77658c, 4, 1, fh) != 0;
}
